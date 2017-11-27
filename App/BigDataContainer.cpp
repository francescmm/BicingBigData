#include "BigDataContainer.hpp"
#include <QSqlQuery>
#include <QSqlError>

static const char * Path = "E:";

BigDataContainer::BigDataContainer()
{
    dbCon = QSqlDatabase::addDatabase("QSQLITE");
    dbCon.setDatabaseName(QString("%1/testing.db").arg(Path));

    if (dbCon.open())
    {
        QFile dbFile(":/db_structure");

        if (dbFile.open(QIODevice::ReadOnly))
        {
            auto dbFileContent = dbFile.readAll();
            auto statements = dbFileContent.split(';');

            for (const auto s : statements)
            {
                QSqlQuery query;
                query.exec(s);
            }

            dbCon.close();
            dbFile.close();
        }
    }
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

QMap<QDateTime, int> BigDataContainer::getDataByStation(int id, bool bikes, int weekday, int interval) const
{
    QMap<QDateTime, int> map;

    if (dbCon.isOpen())
    {
        auto sql = QString("SELECT updateDT, ROUND(AVG(%1)) FROM station_status WHERE id_station = %2").arg(bikes ? "bikes" : "slots").arg(id);

        if (weekday > -1)
            sql += QString(" AND WEEKDAY(updateDT) = %1").arg(weekday);

        sql += QString(" GROUP BY strftime('%d', updateDT), strftime('%H', updateDT), 4 * strftime('%H', updateDT) + cast(strftime('%M', updateDT) / %1 as int) ORDER BY strftime('%s', updateDT), updateDT").arg(interval);

        QSqlQuery query;

        if (query.exec(sql))
        {
            while (query.next())
                map.insert(query.value(0).toDateTime(), query.value(1).toInt());
        }
    }

    return map;
}
