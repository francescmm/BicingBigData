#ifndef BIGDATACONTAINER_H
#define BIGDATACONTAINER_H

#include "Station.hpp"
#include <QDateTime>
#include <QMap>
#include <QSqlDatabase>

enum class Data
{
   EBIKE,
   MECHANICAL,
   SLOT
};

class BigDataContainer
{
public:
   BigDataContainer(const QString &path);
   ~BigDataContainer() = default;
   void init();
   QStringList getStations() const;
   Station getStation(int stationId) const;
   QMap<QDateTime, int> getDataByStationByDate(int id, Data bikes = Data::EBIKE, const QDate &date = QDate::currentDate(), int interval = 60);
   QMap<QDateTime, int> getDataByStation(int id, Data bikes = Data::EBIKE, int weekday = -1, int interval = 60);

private:
   QSqlDatabase dbCon;
   QVector<Station> stations;
   QString mPath;

   BigDataContainer(const BigDataContainer &bdc) = default;
   BigDataContainer &operator=(const BigDataContainer &bdc);

   void fillGapsAtBeginnig(const QDateTime lastRegisterTime, int interval, QMap<QDateTime, int> &map);
};

#endif // BIGDATACONTAINER_H
