#include "ChartWidget.h"
#include "BigDataContainer.hpp"

#include <QDateTimeAxis>

ChartWidget::ChartWidget(BigDataContainer *bigData, QWidget *parent)
   : QChartView(parent)
   , bigData(bigData)
{
   labelsFont.setPixelSize(12);

   chart = new QChart();
   chart->legend()->hide();

   QFont font;
   font.setPixelSize(18);
   chart->setTitleFont(font);
   chart->setTitleBrush(QBrush(Qt::black));

   setChart(chart);
   setRenderHint(QPainter::Antialiasing);
}

void ChartWidget::initialize(const int interval)
{
   createAxisY();
   createAxisTimeInDay(interval);
}

void ChartWidget::createAxisY()
{
   delete axisY;
   axisY = new QCategoryAxis();
   axisY->setLabelsFont(labelsFont);
   axisY->setLinePen(xAxisPen);
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

void ChartWidget::createAxisTimeInDay(const int interval)
{
   delete axisX;
   axisX = new QCategoryAxis();
   axisX->setLabelsFont(labelsFont);
   axisX->setLinePen(xAxisPen);
   axisX->setLabelsBrush(QBrush(Qt::black));
   axisX->setGridLineVisible(false);
   axisX->setShadesPen(Qt::NoPen);
   axisX->append("Night (0-6)", 6 * 60 / interval);
   axisX->append("Morning (6-12)", 12 * 60 / interval);
   axisX->append("Afternoon (12-19)", 19 * 60 / interval);
   axisX->append("Evening (19-24)", 24 * 60 / interval);
   axisX->setRange(0, 24 * 60 / interval);
   chart->addAxis(axisX, Qt::AlignTop);
}

void ChartWidget::updateChartByDate(const int stationId, const QString &stationName, const int interval, const QDate &date)
{
   updateChartGeneralInfo(stationId, stationName);

   createAndCustomizeSeries(interval);

   const auto bikesData = showBikes
       ? bigData->getDataByStationByDate(stationId, Data::MECHANICAL, date, interval)
       : QMap<QDateTime, int>();

   for (auto iter = bikesData.constBegin(); iter != bikesData.constEnd(); ++iter)
      *bikeSeries << QPointF(static_cast<qreal>(iter.key().toMSecsSinceEpoch()), static_cast<qreal>(iter.value()));

   const auto ebikesData = showBikes
       ? bigData->getDataByStationByDate(stationId, Data::EBIKE, date, interval)
       : QMap<QDateTime, int>();

   for (auto iter = ebikesData.constBegin(); iter != ebikesData.constEnd(); ++iter)
      *ebikeSeries << QPointF(static_cast<qreal>(iter.key().toMSecsSinceEpoch()), static_cast<qreal>(iter.value()));

   const auto slotsData = showSlots
       ? bigData->getDataByStationByDate(stationId, Data::SLOT, date, interval)
       : QMap<QDateTime, int>();

   for (auto iter = slotsData.constBegin(); iter != slotsData.constEnd(); ++iter)
      *slotsSeries << QPointF(static_cast<qreal>(iter.key().toMSecsSinceEpoch()), iter.value());

   createAxisTiming(interval);
   updateChartAxis();
}

void ChartWidget::updateChartByWeekday(const int stationId, const QString &stationName, const int interval, const int weekday)
{
   updateChartGeneralInfo(stationId, stationName);

   createAndCustomizeSeries(interval);

   const auto bikesData = showBikes
       ? bigData->getDataByStation(stationId, Data::MECHANICAL, weekday, interval)
       : QMap<QDateTime, int>();

   for (auto iter = bikesData.constBegin(); iter != bikesData.constEnd(); ++iter)
      *bikeSeries << QPointF(static_cast<qreal>(iter.key().toMSecsSinceEpoch()), static_cast<qreal>(iter.value()));

   const auto ebikesData = showBikes
       ? bigData->getDataByStation(stationId, Data::EBIKE, weekday, interval)
       : QMap<QDateTime, int>();

   for (auto iter = ebikesData.constBegin(); iter != ebikesData.constEnd(); ++iter)
      *ebikeSeries << QPointF(static_cast<qreal>(iter.key().toMSecsSinceEpoch()), static_cast<qreal>(iter.value()));

   const auto slotsData = showSlots
       ? bigData->getDataByStation(stationId, Data::SLOT, weekday, interval)
       : QMap<QDateTime, int>();

   for (auto iter = slotsData.constBegin(); iter != slotsData.constEnd(); ++iter)
      *slotsSeries << QPointF(static_cast<qreal>(iter.key().toMSecsSinceEpoch()), iter.value());

   createAxisTiming(interval, weekday);

   updateChartAxis();
}

void ChartWidget::updateChartGeneralInfo(const int stationId, const QString &stationName)
{
   chart->setTitle(QString("Availability for station %2 (%1)").arg(stationId).arg(stationName));
}

void ChartWidget::createAndCustomizeSeries(const int interval)
{
   delete bikeSeries;
   delete ebikeSeries;
   delete slotsSeries;

   if (softLine)
   {
      bikeSeries = new QSplineSeries();
      ebikeSeries = new QSplineSeries();
      slotsSeries = new QSplineSeries();
   }
   else
   {
      bikeSeries = new QLineSeries();
      ebikeSeries = new QLineSeries();
      slotsSeries = new QLineSeries();
   }

   auto penWidth = interval >= 30 ? 3 : interval >= 10 ? 2 : 1;

   QPen pen(QBrush(0xfdb157), penWidth);
   bikeSeries->setPen(pen);

   pen.setColor("geen");
   ebikeSeries->setPen(pen);

   pen.setColor("blue");
   slotsSeries->setPen(pen);
}

void ChartWidget::updateChartAxis()
{
   if (showBikes)
   {
      chart->addSeries(bikeSeries);
      chart->addSeries(ebikeSeries);
      bikeSeries->attachAxis(axis2);
      bikeSeries->attachAxis(axisY);
      ebikeSeries->attachAxis(axis2);
      ebikeSeries->attachAxis(axisY);
   }

   if (showSlots)
   {
      chart->addSeries(slotsSeries);
      slotsSeries->attachAxis(axis2);
      slotsSeries->attachAxis(axisY);
   }
}

void ChartWidget::createAxisTiming(const int interval, const int weekday)
{
   auto tickCount = 0;

   if (weekday == -1)
      tickCount = 7 * 24 / 4;
   else
   {
      switch (interval)
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
   axis2 = new QDateTimeAxis();
   axis2->setLabelsFont(labelsFont);
   axis2->setLinePen(xAxisPen);
   axis2->setLabelsBrush(QBrush(Qt::black));
   axis2->setGridLineVisible(false);
   axis2->setShadesPen(Qt::NoPen);
   axis2->setFormat("hh");
   axis2->setTickCount(tickCount);
   chart->addAxis(axis2, Qt::AlignBottom);
}
