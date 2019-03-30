#include "BigDataContainer.hpp"
#include <QSqlQuery>
#include <QSqlError>

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
      auto sql = "SELECT id, latitude, longitude, streetName, streetNumber, altitude, type FROM stations ORDER BY id";
      QSqlQuery query;

      if (query.exec(sql))
      {
         while (query.next())
         {
            Station s;
            s.setId(query.value(0).toInt());
            s.setLatitude(query.value(1).toFloat());
            s.setLongitude(query.value(2).toFloat());
            s.setStreetName(query.value(3).toString());
            s.setStreetNumber(query.value(4).toInt());
            s.setAltitude(query.value(5).toInt());
            s.setType(static_cast<StationType>(query.value(6).toInt()));

            stations.append(s);
         }
      }
   }
}

QStringList BigDataContainer::getStations() const
{
   QStringList list;

   foreach (auto s, stations)
   {
      auto name = s.getStreetName()
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

      auto num = s.getStreetNumber();

      if (num != 0)
         name += QString(" %1").arg(num);

      list.append(QString("%1 - %2").arg(s.getId()).arg(name));
   }

   return list;
}

QMap<QDateTime, int> BigDataContainer::getDataByStationCurrentDay(int id, bool bikes, const QDate &date, int interval)
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
                     .arg(bikes ? "bikes" : "slots")
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

QMap<QDateTime, int> BigDataContainer::getDataByStation(int id, bool bikes, int weekday, int interval)
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
                     .arg(bikes ? "bikes" : "slots")
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
