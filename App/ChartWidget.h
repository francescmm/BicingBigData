#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QtCharts/QCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

namespace QT_CHARTS_NAMESPACE
{
class QDateTimeAxis;
}

class BigDataContainer;

class ChartWidget : public QChartView
{
public:
   ChartWidget(BigDataContainer *bigData, QWidget *parent = nullptr);
   void initialize(int interval);

   void updateChartByDate(int stationId, const QString &stationName, int interval, const QDate &date);
   void updateChartByWeekday(int stationId, const QString &stationName, int interval, const int weekday);
   void setBikesVisible(bool visible = true) { showBikes = visible; }
   void setSlotsVisible(bool visible = true) { showSlots = visible; }
   void enbleSoftLine(bool enable = true) { softLine = enable; }

private:
   void createAxisY();
   void createAxisTimeInDay(int interval);
   void updateChartGeneralInfo(int stationId, const QString &stationName);
   void createAndCustomizeSeries(int interval);
   void updateChartAxis();
   void createAxisTiming(int interval, int weekday = -1);

   BigDataContainer *bigData = nullptr;
   QChart *chart = nullptr;
   QLineSeries *bikeSeries = nullptr;
   QLineSeries *ebikeSeries = nullptr;
   QLineSeries *slotsSeries = nullptr;
   QCategoryAxis *axisX = nullptr;
   QDateTimeAxis *axis2 = nullptr;
   QCategoryAxis *axisY = nullptr;
   QFont labelsFont;
   QPen xAxisPen = QPen(QBrush(0xd18952), 1);
   bool showBikes = true;
   bool showSlots = false;
   bool softLine = false;
};

#endif // CHARTWIDGET_H
