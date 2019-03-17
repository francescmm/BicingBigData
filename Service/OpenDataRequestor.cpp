#include "OpenDataRequestor.hpp"
#include <QDir>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

QSqlDatabase OpenDataRequestor::dbCon = QSqlDatabase::addDatabase("QSQLITE");

OpenDataRequestor::OpenDataRequestor(const QString &absolutePath, QObject *parent)
    : QObject(parent), mAbsolutePath(absolutePath)
{
    if (dbCon.databaseName().isEmpty())
        dbCon.setDatabaseName(QString("%1testing.db").arg(mAbsolutePath));

    QDir dir(mAbsolutePath);

    if (!dir.exists("data"))
    {
        qDebug() << "Creating directory...";
        dir.mkdir(QString("%1data").arg(mAbsolutePath));

        if (dbCon.open())
        {
            QFile dbFile(":/db_structure");

            if (dbFile.open(QIODevice::ReadOnly))
            {
                auto dbFileContent = dbFile.readAll();
                auto statements = dbFileContent.split(';');

                for (const auto &s : statements)
                {
                    QSqlQuery query;
                    query.exec(s);
                }

                dbCon.close();
                dbFile.close();
            }
        }
    }
}

OpenDataRequestor::~OpenDataRequestor()
{
    delete manager;
}

void OpenDataRequestor::makeRequest()
{
    manager = new QNetworkAccessManager();

    connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)), Qt::QueuedConnection);

    manager->get(QNetworkRequest(QUrl("http://wservice.viabicing.cat/v2/stations")));
}

void OpenDataRequestor::replyFinished(QNetworkReply *reply)
{
    auto dataReceived = reply->readAll();
    auto jsonObject = QJsonDocument::fromJson(dataReceived).object();
    auto stations = jsonObject["stations"].toArray();
    auto fileName = QString("%1data/%2.json").arg(mAbsolutePath).arg(QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss"));

    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly))
    {
        file.write(dataReceived);
        file.close();
    }

    QStringList values;
    auto sql = QString("INSERT INTO station_status (id_station, bikes, slots, state, updateDT) VALUES %1");

    foreach (auto station, stations)
    {
        auto stationObj = station.toObject();

        auto value = QString("(%1, %2, %3, '%4', '%5')")
                             .arg(stationObj["id"].toVariant().toInt())
                             .arg(stationObj["bikes"].toVariant().toInt())
                             .arg(stationObj["slots"].toVariant().toInt())
                             .arg(stationObj["status"].toString())
                             .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        values.append(value);
    }

    QSqlQuery query;

    if (dbCon.open())
    {
        sql = sql.arg(values.join(","));
        auto done = query.exec(sql);

        dbCon.close();
    }

    emit signalTaskDone();
}
