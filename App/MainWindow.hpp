#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <iostream>

using namespace std;

class QComboBox;
class QCheckBox;
class QDateEdit;
class QRadioButton;
class ChartWidget;
class BigDataContainer;

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(const QString &path, const QString &station, QWidget *parent = nullptr);
   ~MainWindow() override = default;

private:
   BigDataContainer *bigData = nullptr;
   QRadioButton *rbDate = nullptr;
   QRadioButton *rbWeekday = nullptr;
   QComboBox *stationsCombo = nullptr;
   QComboBox *daysCombo = nullptr;
   QComboBox *intervalCombo = nullptr;
   QDateEdit *dateWidget = nullptr;
   QCheckBox *softLineCheck = nullptr;
   QCheckBox *bikesCheck = nullptr;
   QCheckBox *slotsCheck = nullptr;
   ChartWidget *chartView = nullptr;

   void createAndCustomizeSeries();
   void addValuesToSeries();
   void createAxisTiming();

   void slotUpdateChart();
};

#endif // MAINWINDOW_HPP
