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
        ~BigDataContainer() { }
        void init();
        QStringList getStations() const;
        QMap<QDateTime, int> getDataByStation(int id, bool bikes = true, int weekday = -1, int interval = 60) const;

    private:
        QSqlDatabase dbCon;
        QVector<Station> stations;
        QString mPath;

        BigDataContainer(const BigDataContainer &bdc) { }
        BigDataContainer & operator = (const BigDataContainer &bdc);
};

#endif // BIGDATACONTAINER_H
