#ifndef BIGDATACONTAINER_H
#define BIGDATACONTAINER_H

#include "Station.hpp"
#include <QMap>
#include <QDateTime>
#include <QSqlDatabase>

class BigDataContainer
{
public:
   BigDataContainer(const QString &path);
   ~BigDataContainer() = default;
   void init();
   QStringList getStations() const;
   QMap<QDateTime, int> getDataByStationByDate(int id, bool bikes = true, const QDate &date = QDate::currentDate(), int interval = 60);
   QMap<QDateTime, int> getDataByStation(int id, bool bikes = true, int weekday = -1, int interval = 60);

private:
   QSqlDatabase dbCon;
   QVector<Station> stations;
   QString mPath;

   BigDataContainer(const BigDataContainer &bdc) = default;
   BigDataContainer &operator=(const BigDataContainer &bdc);

   void fillGapsAtBeginnig(const QDateTime lastRegisterTime, int interval, QMap<QDateTime, int> &map);
};

#endif // BIGDATACONTAINER_H
