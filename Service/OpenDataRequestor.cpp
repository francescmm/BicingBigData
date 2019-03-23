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

QMutex OpenDataRequestor::mutex(QMutex::Recursive);

OpenDataRequestor::OpenDataRequestor(const QString &absolutePath, QObject *parent)
   : QObject(parent)
   , mAbsolutePath(absolutePath)
{
}

void OpenDataRequestor::makeRequest()
{
   manager = new QNetworkAccessManager(this);

   connect(manager, &QNetworkAccessManager::finished, this, &OpenDataRequestor::replyFinished, Qt::QueuedConnection);

   manager->get(QNetworkRequest(QUrl("http://wservice.viabicing.cat/v2/stations")));
}

void OpenDataRequestor::setupDatabase()
{
   dbCon = QSqlDatabase::addDatabase("QSQLITE");

   if (dbCon.databaseName().isEmpty())
      dbCon.setDatabaseName(QString("%1testing.db").arg(mAbsolutePath));
}

void OpenDataRequestor::createSchema()
{
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

void OpenDataRequestor::replyFinished(QNetworkReply *reply)
{
   const auto dataReceived = reply->readAll();
   const auto jsonObject = QJsonDocument::fromJson(dataReceived).object();
   const auto stations = jsonObject["stations"].toArray();
   const auto fileName = QString("%1data/%2.json").arg(mAbsolutePath).arg(QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss"));

   QFile file(fileName);

   if (file.open(QIODevice::WriteOnly))
   {
      file.write(dataReceived);
      file.close();
   }

   QStringList values;

   for (const auto &station : stations)
   {
      const auto stationObj = station.toObject();
      const auto value = QString("(%1, %2, %3, '%4', '%5')")
                             .arg(stationObj["id"].toVariant().toInt())
                             .arg(stationObj["bikes"].toVariant().toInt())
                             .arg(stationObj["slots"].toVariant().toInt())
                             .arg(stationObj["status"].toString())
                             .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

      values.append(value);
   }

   if (dbCon.open() && !values.isEmpty())
   {
      QMutexLocker lock(&mutex);
      const auto sql = QString("INSERT INTO station_status (id_station, bikes, slots, state, updateDT) VALUES %1").arg(values.join(","));

      QSqlQuery query;
      query.exec(sql);

      dbCon.close();
   }

   emit signalTaskDone();
}
