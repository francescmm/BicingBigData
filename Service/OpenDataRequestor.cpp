#include "OpenDataRequestor.h"
#include <QDir>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

static const char * Path = "Path/To/Storage";

OpenDataRequestor::OpenDataRequestor (QObject *parent) : QObject(parent)
{
   QDir dir (Path);

   if (!dir.exists ("data"))
      dir.mkdir (QString ("%1data").arg(Path));
}

OpenDataRequestor::~OpenDataRequestor()
{
   delete manager;
}

void OpenDataRequestor::makeRequest ()
{
   manager = new QNetworkAccessManager ();

   connect (manager, SIGNAL (finished (QNetworkReply*)), this, SLOT (replyFinished (QNetworkReply*)), Qt::QueuedConnection);

   manager->get (QNetworkRequest (QUrl ("http://wservice.viabicing.cat/v2/stations")));
}

void OpenDataRequestor::replyFinished (QNetworkReply *reply)
{
   auto dataReceived = reply->readAll ();
   auto fileName = QString ("%1/data/%2.json").arg (Path).arg (QDateTime::currentDateTime ().toString ("yyyyMMdd-hhmmss"));

   QFile file (fileName);

   if (file.open (QIODevice::WriteOnly))
   {
      file.write (dataReceived);
      file.close ();
   }

   emit signalTaskDone();
}
