#ifndef STATION_HPP
#define STATION_HPP

#include <QList>
#include <QString>

struct Station
{
   int id = -1;
   float latitude = 0.0;
   float longitude = 0.0;
   QString streetName;
   int streetNumber = 0;
   int altitude = 0;
   QList<int> nearbyStations;
};

#endif // STATION_HPP
