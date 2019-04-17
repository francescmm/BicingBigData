#include "BigDataContainer.hpp"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include <cmath>

BigDataContainer::BigDataContainer(const QString &path)
   : mPath(path)
{
   dbCon = QSqlDatabase::addDatabase("QSQLITE");
   dbCon.setDatabaseName(QString("%1testing.db").arg(mPath));
}

void BigDataContainer::init()
{
   if (dbCon.open())
   {
      auto sql = "SELECT id, latitude, longitude, streetName, streetNumber, altitude FROM stations ORDER BY id";
      QSqlQuery query;

      if (query.exec(sql))
      {
         while (query.next())
         {
            Station s;
            s.id = query.value(0).toInt();
            s.latitude = query.value(1).toFloat();
            s.longitude = query.value(2).toFloat();
            s.streetName = query.value(3).toString();
            s.streetNumber = query.value(4).toInt();
            s.altitude = query.value(5).toInt();

            stations.append(s);
         }
      }
      else
         qDebug() << query.lastError().text();
   }
}

QStringList BigDataContainer::getStations() const
{
   QStringList list;

   foreach (auto s, stations)
   {
      auto name = s.streetName
                      .remove("Carrer de l'")
                      .remove("Carrer l'")
                      .remove("Carrer d'")
                      .remove("Carrer de les ")
                      .remove("Carrer dels ")
                      .remove("Carrer de la ")
                      .remove("Carrer del ")
                      .remove("Carrer de ")
                      .remove("C/")
                      .remove("C/ ")
                      .remove("C\\")
                      .remove("C\\ ");

      auto num = s.streetNumber;

      if (num != 0)
         name += QString(" %1").arg(num);

      list.append(QString("%1 - %2").arg(s.id).arg(name));
   }

   return list;
}

Station BigDataContainer::getStation(const int stationId) const
{
   auto station = std::find_if(stations.begin(), stations.end(), [stationId](const Station &s) { return s.id == stationId; });

   if (station != stations.end())
      return *station;

   return Station();
}

QMap<QDateTime, int> BigDataContainer::getDataByStationByDate(int id, Data bikes, const QDate &date, int interval)
{
   QMap<QDateTime, int> map;

   if (dbCon.isOpen())
   {
      auto sql = QString("SELECT updateDT, ROUND(AVG(%1)) "
                         "FROM station_status "
                         "WHERE id_station = %2 "
                         "AND date(updateDT) = date('%3')"
                         " GROUP BY strftime('%d', updateDT)"
                         ", strftime('%H', updateDT)"
                         ", 4 * strftime('%H', updateDT) + cast(strftime('%M', updateDT) / %4 as int) "
                         "ORDER BY strftime('%s', updateDT), updateDT")
                     .arg(bikes == Data::EBIKE ? "ebike" : bikes == Data::MECHANICAL ? "mechanical" : "slots")
                     .arg(id)
                     .arg(date.toString("yyyy-MM-dd"))
                     .arg(interval);

      QDateTime lastRegisterTime;
      QSqlQuery query;

      if (query.exec(sql))
      {
         while (query.next())
         {
            lastRegisterTime = query.value(0).toDateTime();

            if (map.empty())
               fillGapsAtBeginnig(lastRegisterTime, interval, map);

            map.insert(lastRegisterTime, query.value(1).toInt());
         }
      }
   }

   return map;
}

QMap<QDateTime, int> BigDataContainer::getDataByStation(int id, Data bikes, int weekday, int interval)
{
   QMap<QDateTime, int> map;

   if (dbCon.isOpen())
   {
      auto sql = QString("SELECT updateDT, ROUND(AVG(%1)) "
                         "FROM station_status "
                         "WHERE id_station = %2"
                         " AND strftime('%w', updateDT) = '%3'"
                         " GROUP BY strftime('%d', updateDT), strftime('%H', updateDT)"
                         ", 4 * strftime('%H', updateDT) + cast(strftime('%M', updateDT) / %4 as int) "
                         "ORDER BY strftime('%s', updateDT), updateDT")
                     .arg(bikes == Data::EBIKE ? "ebike" : bikes == Data::MECHANICAL ? "mechanical" : "slots")
                     .arg(id)
                     .arg(weekday)
                     .arg(interval);

      QDateTime lastRegisterTime;
      QSqlQuery query;

      if (query.exec(sql))
      {
         while (query.next())
         {
            lastRegisterTime = query.value(0).toDateTime();

            if (map.empty())
               fillGapsAtBeginnig(lastRegisterTime, interval, map);

            map.insert(lastRegisterTime, query.value(1).toInt());
         }
      }
   }

   return map;
}

void BigDataContainer::fillGapsAtBeginnig(const QDateTime lastRegisterTime, int interval, QMap<QDateTime, int> &map)
{
   const auto hourFirstRegister = QTime(lastRegisterTime.time().hour(), 0, 0);

   for (auto hour = QTime(0, 0, 0); hour < hourFirstRegister; hour = hour.addSecs(60 * interval))
   {
      const auto emptyRegister = QDateTime(lastRegisterTime.date(), hour);
      map.insert(emptyRegister, 0);
   }
}
