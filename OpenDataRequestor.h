#ifndef OPENDATAREQUESTOR_H
#define OPENDATAREQUESTOR_H

#include <QObject>
#include <QFile>

class QNetworkReply;
class QNetworkAccessManager;

class OpenDataRequestor : public QObject
{
      Q_OBJECT

   signals:
      void signalTaskDone();

   public:
      explicit OpenDataRequestor(QObject *parent = nullptr);
      ~OpenDataRequestor();

   public slots:
      void makeRequest();

   private:
      QNetworkAccessManager *manager = nullptr;

   private slots:
      void replyFinished(QNetworkReply *reply);
};

#endif // OPENDATAREQUESTOR_H
