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

MainWindow::MainWindow(const QString &path, const QString &station, QWidget *parent)
   : QMainWindow(parent)
{
    bigData = new BigDataContainer(path);
    bigData->init();

    stationsCombo = new QComboBox();
    stationsCombo->addItems(bigData->getStations());
    stationsCombo->setCurrentIndex (stationsCombo->findText (QString("%1 - ").arg(station), Qt::MatchStartsWith));
    connect(stationsCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(slotUpdateChart()));

    auto stationLayout = new QHBoxLayout();
    stationLayout->addWidget(new QLabel(tr("Select a station")));
    stationLayout->addWidget(stationsCombo);

    daysCombo = new QComboBox();
    daysCombo->addItems({tr("All"),tr("Monday"), tr("Tuesday"), tr("Wednesday"), tr("Thursday"), tr("Friday"), tr("Saturday"), tr("Sunday")});
    connect(daysCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(slotUpdateChart()));

    auto daysLayout = new QHBoxLayout();
    daysLayout->addWidget(new QLabel(tr("Select a day:")));
    daysLayout->addWidget(daysCombo);

    intervalCombo = new QComboBox();
    intervalCombo->addItem(tr("Hour"), 60);
    intervalCombo->addItem(tr("30 min."), 30);
    intervalCombo->addItem(tr("15 min."), 15);
    intervalCombo->addItem(tr("10 min."), 10);
    intervalCombo->addItem(tr("5 min."), 5);
    connect(intervalCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(slotUpdateChart()));

    auto intervalLayout = new QHBoxLayout();
    intervalLayout->addWidget(new QLabel(tr("Select an interval:")));
    intervalLayout->addWidget(intervalCombo);

    softLineCheck = new QCheckBox(tr("Make graph line soft"));
    connect(softLineCheck, SIGNAL(stateChanged(int)), this, SLOT(slotUpdateChart()));

    bikesCheck = new QCheckBox(tr("Show bikes"));
    bikesCheck->setChecked(true);
    connect(bikesCheck, SIGNAL(stateChanged(int)), this, SLOT(slotUpdateChart()));

    slotsCheck = new QCheckBox(tr("Show slots"));
    slotsCheck->setChecked(false);
    connect(slotsCheck, SIGNAL(stateChanged(int)), this, SLOT(slotUpdateChart()));

    auto checksLayout = new QHBoxLayout();
    checksLayout->addWidget(softLineCheck);
    checksLayout->addWidget(bikesCheck);
    checksLayout->addWidget(slotsCheck);

    slotUpdateChart();

    auto stackedWidget = new QStackedWidget();
    //stackedWidget->addWidget(stationAvailabilityChart);
    stackedWidget->addWidget(chartView);

    auto mainLayout = new QVBoxLayout();
    mainLayout->addLayout(stationLayout);
    mainLayout->addLayout(daysLayout);
    mainLayout->addLayout(intervalLayout);
    mainLayout->addLayout(checksLayout);
    mainLayout->addWidget(stackedWidget);

    auto mainFrame = new QFrame();
    mainFrame->setLayout(mainLayout);

    setCentralWidget(mainFrame);
}

MainWindow::~MainWindow()
{
}

#include <QDebug>
void MainWindow::slotUpdateChart()
{
    auto stationId = stationsCombo->currentText().split(" - ").first();
    auto weekday = daysCombo->currentIndex() - 1;
    const auto bikesData = bikesCheck->isChecked() ? bigData->getDataByStation(stationId.toInt(), true, weekday, intervalCombo->currentData().toInt()) : QMap<QDateTime, int>();
    auto slotsData = slotsCheck->isChecked() ? bigData->getDataByStation(stationId.toInt(), false, weekday, intervalCombo->currentData().toInt()) : QMap<QDateTime, int>();
    auto count = 0;
    QLineSeries *bikeSeries = nullptr;
    QLineSeries *slotsSeries = nullptr;

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

    for (auto iter = bikesData.constBegin (); iter != bikesData.constEnd (); ++iter)
        bikeSeries->append (static_cast<qreal>(iter.key ().toMSecsSinceEpoch()), static_cast<qreal>(iter.value ()));

    count = 0;

    for (auto iter = slotsData.constBegin(); iter != slotsData.constEnd(); ++iter)
        *slotsSeries << QPointF(count++, iter.value());

    QChart *chart = new QChart();
    chart->legend()->hide();

    if (bikesCheck->isChecked())
        chart->addSeries(bikeSeries);

    if (slotsCheck->isCheckable())
        chart->addSeries(slotsSeries);

    // Customize series
    auto penWidth = intervalCombo->currentData().toInt() >= 30 ? 3 : intervalCombo->currentData().toInt() >= 10 ? 2 : 1;
    QPen pen(QRgb(0xfdb157));
    pen.setWidth(penWidth);
    bikeSeries->setPen(pen);

    pen.setColor("blue");
    slotsSeries->setPen(pen);

    // Customize chart title
    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle(QString("Availability for station %2 (%1)").arg(stationId).arg(stationsCombo->currentText().split(" - ").last()));

    QCategoryAxis *axisX = new QCategoryAxis();
    QCategoryAxis *axisY = new QCategoryAxis();

    // Customize axis label font
    QFont labelsFont;
    labelsFont.setPixelSize(12);
    axisX->setLabelsFont(labelsFont);
    axisY->setLabelsFont(labelsFont);

    // Customize axis colors
    QPen axisPen(QRgb(0xd18952));
    axisPen.setWidth(1);
    axisX->setLinePen(axisPen);
    axisY->setLinePen(axisPen);

    // Customize axis label colors
    QBrush axisBrush(Qt::black);
    axisX->setLabelsBrush(axisBrush);
    axisY->setLabelsBrush(axisBrush);

    // Customize grid lines and shades
    axisX->setGridLineVisible(false);
    axisY->setGridLineVisible(false);
    axisY->setShadesPen(Qt::NoPen);
    axisY->setShadesBrush(QBrush(QColor(0x99, 0xcc, 0xcc, 0x55)));
    axisY->setShadesVisible(true);

    if (weekday != -1)
    {
        axisX->append("Night (0-6)", 6 * 60 / intervalCombo->currentData().toInt());
        axisX->append("Morning (6-12)", 12 * 60 / intervalCombo->currentData().toInt());
        axisX->append("Afternoon (12-19)", 19 * 60 / intervalCombo->currentData().toInt());
        axisX->append("Evening (19-24)", 24 * 60 / intervalCombo->currentData().toInt());
    }
    else
    {
        QString oldVal;
        auto count = 0;
        auto xAxisCounter = 0;

        for (auto iter = bikesData.constBegin (); iter != bikesData.constEnd (); ++iter, ++count)
        {
           if (oldVal != iter.key().date().toString("dddd"))
           {
              oldVal = iter.key().date().toString("dddd");
              axisX->append(oldVal, count);
              count = -1;
              ++xAxisCounter;
           }
        }
    }

    axisX->setRange(0, bikeSeries->count());

    bikeSeries->attachAxis(axisX);

    auto tickCount = 0;

    if (weekday == -1)
        tickCount = 7*24 / 4;
    else
    {
        switch (intervalCombo->currentData().toInt()) {
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

    QDateTimeAxis *axis2 = new QDateTimeAxis ();
    //axis2->setLabelFormat("");
    axis2->setTickCount(tickCount);
    axis2->setFormat("hh");
    //axis2->setRange(0, bikeSeries->count());
    chart->addAxis(axis2, Qt::AlignBottom);
    bikeSeries->attachAxis(axis2);

    axisY->append("Low", 5);
    axisY->append("Optimal", 15);
    axisY->append("Perfect", 30);
    axisY->setRange(0, 30);

    bikeSeries->attachAxis(axisY);

    QValueAxis *axis = new QValueAxis;
    axis->setTickCount(7);
    axis->setRange(0, 30);
    chart->addAxis(axis, Qt::AlignRight);
    bikeSeries->attachAxis(axis);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->setAxisX(axisX, slotsSeries);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->setAxisY(axisY, slotsSeries);

    if (chartView == nullptr)
        chartView = new QChartView(chart);
    else
        chartView->setChart(chart);

    chartView->setRenderHint(QPainter::Antialiasing);
}
