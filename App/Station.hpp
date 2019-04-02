#ifndef STATION_HPP
#define STATION_HPP

#include <QList>
#include <QString>

class Station {
public:
    Station() {}
    Station(const Station& s);
    Station& operator=(const Station& s);
    ~Station() {}

    int getId() const;
    void setId(int value);

    float getLatitude() const;
    void setLatitude(float value);

    float getLongitude() const;
    void setLongitude(float value);

    QString getStreetName() const;
    void setStreetName(const QString& value);

    int getStreetNumber() const;
    void setStreetNumber(int value);

    int getAltitude() const;
    void setAltitude(int value);

    QList<int> getNearbyStations() const;
    void setNearbyStations(const QList<int>& value);

private:
    int id = 0;
    float latitude = 0.0;
    float longitude = 0.0;
    QString streetName;
    int streetNumber = 0;
    int altitude = 0;
    QList<int> nearbyStations;
};

#endif // STATION_HPP
