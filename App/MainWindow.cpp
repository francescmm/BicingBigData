#include "MainWindow.hpp"
#include "ChartWidget.h"
#include "BigDataContainer.hpp"

#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QDateTime>
#include <QDebug>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QStackedWidget>

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

   rbDate = new QRadioButton(tr("Select a day"));
   rbDate->setChecked(true);
   dateLayout->addWidget(rbDate, 0, 0);

   dateWidget = new QDateEdit(QDate::currentDate());
   dateWidget->setCalendarPopup(true);
   dateLayout->addWidget(dateWidget, 0, 1);

   rbWeekday = new QRadioButton(tr("Show average per day:"));
   dateLayout->addWidget(rbWeekday, 1, 0);

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
   chartView = new ChartWidget(bigData);
   chartView->initialize(intervalCombo->currentData().toInt());

   /* Add stacked widget with the chart */

   auto stackedWidget = new QStackedWidget();
   stackedWidget->addWidget(chartView);

   mainLayout->addWidget(stackedWidget);

   setCentralWidget(mainFrame);

   /* Connects */
   connect(stationsCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::slotUpdateChart);
   connect(dateWidget, &QDateEdit::dateChanged, this, &MainWindow::slotUpdateChart);
   connect(rbDate, &QRadioButton::toggled, dateWidget, &QDateEdit::setEnabled);
   connect(rbDate, &QRadioButton::toggled, this, &MainWindow::slotUpdateChart);
   connect(rbWeekday, &QRadioButton::toggled, daysCombo, &QDateEdit::setEnabled);
   connect(rbWeekday, &QRadioButton::toggled, this, &MainWindow::slotUpdateChart);
   connect(daysCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::slotUpdateChart);
   connect(intervalCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::slotUpdateChart);
   connect(softLineCheck, &QCheckBox::stateChanged, this, &MainWindow::slotUpdateChart);
   connect(bikesCheck, &QCheckBox::stateChanged, this, &MainWindow::slotUpdateChart);
   connect(slotsCheck, &QCheckBox::stateChanged, this, &MainWindow::slotUpdateChart);

   setMinimumSize(800, 600);
}

void MainWindow::slotUpdateChart()
{
   const auto stationId = stationsCombo->currentText().split(" - ").first().toInt();
   const auto stationName = stationsCombo->currentText().split(" - ").last();

   chartView->enbleSoftLine(softLineCheck->isChecked());
   chartView->setBikesVisible(bikesCheck->isChecked());
   chartView->setSlotsVisible(slotsCheck->isChecked());

   if (rbWeekday->isChecked())
      chartView->updateChartByWeekday(stationId, stationName, intervalCombo->currentData().toInt(), daysCombo->currentIndex() - 1);
   else
      chartView->updateChartByDate(stationId, stationName, intervalCombo->currentData().toInt(), dateWidget->date());
}
