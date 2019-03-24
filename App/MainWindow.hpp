#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "BigDataContainer.hpp"
#include <iostream>
#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QCategoryAxis>

QT_CHARTS_USE_NAMESPACE

using namespace std;

class QComboBox;
class QCheckBox;

namespace QT_CHARTS_NAMESPACE
{
class QDateTimeAxis;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(const QString &path, const QString &station, QWidget *parent = nullptr);
   ~MainWindow() override = default;

   void slotUpdateChartByDay();
   void slotUpdateChartByDate();

private:
   BigDataContainer *bigData = nullptr;
   QComboBox *stationsCombo = nullptr;
   QComboBox *daysCombo = nullptr;
   QComboBox *intervalCombo = nullptr;
   QCheckBox *softLineCheck = nullptr;
   QCheckBox *bikesCheck = nullptr;
   QCheckBox *slotsCheck = nullptr;
   QChartView *stationAvailabilityChart = nullptr;
   QChart *chart = nullptr;
   QChartView *chartView = nullptr;
   QLineSeries *bikeSeries = nullptr;
   QLineSeries *slotsSeries = nullptr;
   QCategoryAxis *axisX = nullptr;
   QDateTimeAxis *axis2 = nullptr;

   void createChart();
   void createAndCustomizeSeries();
   void addValuesToSeries();
};

#endif // MAINWINDOW_HPP
