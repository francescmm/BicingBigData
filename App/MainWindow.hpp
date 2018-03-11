#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "BigDataContainer.hpp"
#include <QMainWindow>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QCategoryAxis>

QT_CHARTS_USE_NAMESPACE

class QComboBox;
class QCheckBox;

class MainWindow : public QMainWindow
{
      Q_OBJECT

   public:
      explicit MainWindow(const QString &path, const QString &station, QWidget *parent = nullptr);
      ~MainWindow();

    private slots:
        void slotUpdateChart();

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
};

#endif // MAINWINDOW_HPP
