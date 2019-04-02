#include "Station.hpp"

Station::Station(const Station& s)
{
    id = s.id;
    latitude = s.latitude;
    longitude = s.longitude;
    streetName = s.streetName;
    streetNumber = s.streetNumber;
    altitude = s.altitude;
    nearbyStations = s.nearbyStations;
}

Station& Station::operator=(const Station& s)
{
    if (this != &s) {
        id = s.id;
        latitude = s.latitude;
        longitude = s.longitude;
        streetName = s.streetName;
        streetNumber = s.streetNumber;
        altitude = s.altitude;
        nearbyStations = s.nearbyStations;
    }

    return *this;
}

int Station::getId() const
{
    return id;
}

void Station::setId(int value)
{
    id = value;
}

float Station::getLatitude() const
{
    return latitude;
}

void Station::setLatitude(float value)
{
    latitude = value;
}

float Station::getLongitude() const
{
    return longitude;
}

void Station::setLongitude(float value)
{
    longitude = value;
}

QString Station::getStreetName() const
{
    return streetName;
}

void Station::setStreetName(const QString& value)
{
    streetName = value;
}

int Station::getStreetNumber() const
{
    return streetNumber;
}

void Station::setStreetNumber(int value)
{
    streetNumber = value;
}

int Station::getAltitude() const
{
    return altitude;
}

void Station::setAltitude(int value)
{
    altitude = value;
}

QList<int> Station::getNearbyStations() const
{
    return nearbyStations;
}

void Station::setNearbyStations(const QList<int>& value)
{
    nearbyStations = value;
}
