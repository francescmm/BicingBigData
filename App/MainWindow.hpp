#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "BigDataContainer.hpp"
#include <QMainWindow>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <iostream>

QT_CHARTS_USE_NAMESPACE

using namespace std;

class QComboBox;
class QCheckBox;
class QDateEdit;
class QRadioButton;

namespace QT_CHARTS_NAMESPACE {
class QDateTimeAxis;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const QString& path, const QString& station, QWidget* parent = nullptr);
    ~MainWindow() override = default;

private:
    BigDataContainer* bigData = nullptr;
    QRadioButton* rbDate = nullptr;
    QRadioButton* rbWeekday = nullptr;
    QComboBox* stationsCombo = nullptr;
    QComboBox* daysCombo = nullptr;
    QComboBox* intervalCombo = nullptr;
    QDateEdit* dateWidget = nullptr;
    QCheckBox* softLineCheck = nullptr;
    QCheckBox* bikesCheck = nullptr;
    QCheckBox* slotsCheck = nullptr;
    QChartView* stationAvailabilityChart = nullptr;
    QChart* chart = nullptr;
    QChartView* chartView = nullptr;
    QLineSeries* bikeSeries = nullptr;
    QLineSeries* ebikeSeries = nullptr;
    QLineSeries* slotsSeries = nullptr;
    QCategoryAxis* axisX = nullptr;
    QDateTimeAxis* axis2 = nullptr;
    QCategoryAxis* axisY = nullptr;
    QFont labelsFont;
    QPen xAxisPen = QPen(QBrush(0xd18952), 1);

    void createChart();
    void createAndCustomizeSeries();
    void addValuesToSeries();
    void createAxisY();
    void createAxisTimeInDay();
    void createAxisTiming();
    void updateChartGeneralInfo();
    void updateChartAxis();

    void slotUpdateChart();
    void slotUpdateChartByWeekday();
    void slotUpdateChartByDate();
};

#endif // MAINWINDOW_HPP
