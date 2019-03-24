#include "MainWindow.hpp"
#include <QStackedWidget>
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QDateEdit>
#include <QGroupBox>
#include <QDebug>

MainWindow::MainWindow(const QString &path, const QString &station, QWidget *parent)
   : QMainWindow(parent)
{
   bigData = new BigDataContainer(path);
   bigData->init();

   auto mainFrame = new QFrame();
   auto mainLayout = new QVBoxLayout(mainFrame);

   /* Adding stations layout */
   stationsCombo = new QComboBox();
   stationsCombo->addItems(bigData->getStations());
   stationsCombo->setCurrentIndex(stationsCombo->findText(QString("%1 - ").arg(station), Qt::MatchStartsWith));

   auto stationLayout = new QHBoxLayout();
   stationLayout->addWidget(new QLabel(tr("Select a station")));
   stationLayout->addWidget(stationsCombo);

   mainLayout->addLayout(stationLayout);

   /* Adding date and day layout */
   const auto dateGroupBox = new QGroupBox();
   const auto dateLayout = new QGridLayout(dateGroupBox);

   const auto rbDay = new QRadioButton(tr("Select a day"));
   rbDay->setChecked(true);
   dateLayout->addWidget(rbDay, 0, 0);

   const auto dateWidget = new QDateEdit(QDate::currentDate());
   dateWidget->setCalendarPopup(true);
   dateLayout->addWidget(dateWidget, 0, 1);

   const auto rbDate = new QRadioButton(tr("Show average per day:"));
   dateLayout->addWidget(rbDate, 1, 0);

   daysCombo = new QComboBox();
   daysCombo->addItems({ tr("All"), tr("Monday"), tr("Tuesday"), tr("Wednesday"), tr("Thursday"), tr("Friday"), tr("Saturday"), tr("Sunday"), tr("Today") });
   daysCombo->setDisabled(true);
   dateLayout->addWidget(daysCombo, 1, 1);

   mainLayout->addWidget(dateGroupBox);

   /* Adding inverval layout */
   const auto intervalLayout = new QHBoxLayout();
   intervalLayout->addWidget(new QLabel(tr("Select an interval:")));

   intervalCombo = new QComboBox();
   intervalCombo->addItem(tr("Hour"), 60);
   intervalCombo->addItem(tr("30 min."), 30);
   intervalCombo->addItem(tr("15 min."), 15);
   intervalCombo->addItem(tr("10 min."), 10);
   intervalCombo->addItem(tr("5 min."), 5);
   intervalLayout->addWidget(intervalCombo);

   mainLayout->addLayout(intervalLayout);

   /* Adding chart options */
   auto checksLayout = new QHBoxLayout();

   softLineCheck = new QCheckBox(tr("Make graph line soft"));
   checksLayout->addWidget(softLineCheck);

   bikesCheck = new QCheckBox(tr("Show bikes"));
   bikesCheck->setChecked(true);
   checksLayout->addWidget(bikesCheck);

   slotsCheck = new QCheckBox(tr("Show slots"));
   slotsCheck->setChecked(false);
   checksLayout->addWidget(slotsCheck);

   mainLayout->addLayout(checksLayout);

   /* Update chart data */
   createChart();
   //slotUpdateChartByDay();

   /* Add stacked widget with the chart */

   auto stackedWidget = new QStackedWidget();
   stackedWidget->addWidget(chartView);

   mainLayout->addWidget(stackedWidget);

   setCentralWidget(mainFrame);

   /* Connects */
   connect(stationsCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::slotUpdateChartByDay);
   connect(rbDay, &QRadioButton::toggled, dateWidget, &QDateEdit::setEnabled);
   connect(rbDay, &QRadioButton::toggled, this, &MainWindow::slotUpdateChartByDay);
   connect(rbDate, &QRadioButton::toggled, daysCombo, &QDateEdit::setEnabled);
   connect(rbDate, &QRadioButton::toggled, this, &MainWindow::slotUpdateChartByDay);
   connect(daysCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::slotUpdateChartByDay);
   connect(intervalCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::slotUpdateChartByDay);
   connect(softLineCheck, &QCheckBox::stateChanged, this, &MainWindow::slotUpdateChartByDay);
   connect(bikesCheck, &QCheckBox::stateChanged, this, &MainWindow::slotUpdateChartByDay);
   connect(slotsCheck, &QCheckBox::stateChanged, this, &MainWindow::slotUpdateChartByDay);
}

void MainWindow::createChart()
{
   /* Create chart */

   chart = new QChart();
   chart->legend()->hide();

   QFont font;
   font.setPixelSize(18);
   chart->setTitleFont(font);
   chart->setTitleBrush(QBrush(Qt::black));

   /* Create chart view */

   chartView = new QChartView(chart);
   chartView->setRenderHint(QPainter::Antialiasing);

   QFont labelsFont;
   labelsFont.setPixelSize(12);

   QPen axisPen(QRgb(0xd18952));
   axisPen.setWidth(1);

   QCategoryAxis *axisY = new QCategoryAxis();
   axisY->setLabelsFont(labelsFont);
   axisY->setLinePen(axisPen);
   axisY->setLabelsBrush(QBrush(Qt::black));
   axisY->setGridLineVisible(false);
   axisY->setShadesPen(Qt::NoPen);
   axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
   axisY->setShadesVisible(true);
   axisY->append("Low", 5);
   axisY->append("Optimal", 15);
   axisY->append("Perfect", 30);
   axisY->setRange(0, 30);
   chart->addAxis(axisY, Qt::AlignLeft);
}

void MainWindow::createAndCustomizeSeries()
{
   delete bikeSeries;
   delete slotsSeries;

   if (softLineCheck->isChecked())
   {
      bikeSeries = new QSplineSeries();
      slotsSeries = new QSplineSeries();
   }
   else
   {
      bikeSeries = new QLineSeries();
      slotsSeries = new QLineSeries();
   }

   auto penWidth = intervalCombo->currentData().toInt() >= 30 ? 3 : intervalCombo->currentData().toInt() >= 10 ? 2 : 1;
   QPen pen(QRgb(0xfdb157));
   pen.setWidth(penWidth);
   bikeSeries->setPen(pen);

   pen.setColor("blue");
   slotsSeries->setPen(pen);
}

void MainWindow::slotUpdateChartByDay()
{
   createAndCustomizeSeries();

   const auto stationId = stationsCombo->currentText().split(" - ").first();

   chart->setTitle(QString("Availability for station %2 (%1)").arg(stationId).arg(stationsCombo->currentText().split(" - ").last()));

   const auto weekday = daysCombo->currentIndex() - 1;

   auto count = 0;

   const auto bikesData = bikesCheck->isChecked()
       ? daysCombo->currentText() == tr("Today")
           ? bigData->getDataByStationCurrentDay(stationId.toInt(), true)
           : bigData->getDataByStation(stationId.toInt(), true, weekday, intervalCombo->currentData().toInt())
       : QMap<QDateTime, int>();

   for (auto iter = bikesData.constBegin(); iter != bikesData.constEnd(); ++iter)
   {
      *bikeSeries << QPointF(static_cast<qreal>(iter.key().toMSecsSinceEpoch()), static_cast<qreal>(iter.value()));
   }

   const auto slotsData = slotsCheck->isChecked()
       ? daysCombo->currentText() == tr("Today")
           ? bigData->getDataByStationCurrentDay(stationId.toInt(), false)
           : bigData->getDataByStation(stationId.toInt(), false, weekday, intervalCombo->currentData().toInt())
       : QMap<QDateTime, int>();

   count = 0;

   for (auto iter = slotsData.constBegin(); iter != slotsData.constEnd(); ++iter)
      *slotsSeries << QPointF(count++, iter.value());

   // Customize axis label font
   QFont labelsFont;
   labelsFont.setPixelSize(12);

   // Customize axis colors
   QPen axisPen(QRgb(0xd18952));
   axisPen.setWidth(1);

   auto tickCount = 0;

   if (weekday == -1)
      tickCount = 7 * 24 / 4;
   else
   {
      switch (intervalCombo->currentData().toInt())
      {
         case 60:
         case 30:
            tickCount = 24;
            break;
         case 15:
            tickCount = 48;
            break;
         case 10:
            tickCount = 96;
            break;
         case 5:
            tickCount = 144;
            break;
         default:
            break;
      }
   }

   delete axis2;

   labelsFont.setPixelSize(12);

   axisPen = QPen(QRgb(0xd18952));
   axisPen.setWidth(1);

   axis2 = new QDateTimeAxis();
   axis2->setLabelsFont(labelsFont);
   axis2->setLinePen(axisPen);
   axis2->setLabelsBrush(QBrush(Qt::black));
   axis2->setGridLineVisible(false);
   axis2->setShadesPen(Qt::NoPen);
   axis2->setFormat("hh");
   axis2->setTickCount(tickCount);
   chart->addAxis(axis2, Qt::AlignBottom);

   delete axisX;
   axisX = new QCategoryAxis();
   axisX->setLabelsFont(labelsFont);
   axisX->setLinePen(axisPen);
   axisX->setLabelsBrush(QBrush(Qt::black));
   axisX->setGridLineVisible(false);
   axisX->setShadesPen(Qt::NoPen);
   axisX->append("Night (0-6)", 6 * 60 / intervalCombo->currentData().toInt());
   axisX->append("Morning (6-12)", 12 * 60 / intervalCombo->currentData().toInt());
   axisX->append("Afternoon (12-19)", 19 * 60 / intervalCombo->currentData().toInt());
   axisX->append("Evening (19-24)", 24 * 60 / intervalCombo->currentData().toInt());
   axisX->setRange(0, 24 * 60 / intervalCombo->currentData().toInt());
   chart->addAxis(axisX, Qt::AlignTop);

   if (bikesCheck->isChecked())
      chart->addSeries(bikeSeries);

   if (slotsCheck->isCheckable())
      chart->addSeries(slotsSeries);

   bikeSeries->attachAxis(axis2);
   //chart->createDefaultAxes();
}
