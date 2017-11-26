#ifndef BICINGSERVICE_HPP
#define BICINGSERVICE_HPP

#include "OpenDataRequestor.h"
#include <QtService>
#include <QTimer>
#include <QDate>
#include <QProcess>

class QThread;

class BicingService : public QObject, public QtService<QCoreApplication>
{
   Q_OBJECT

   signals:
      void signalLunchRequestor();

   public:
      explicit BicingService(int argc, char **argv);
      ~BicingService ();

   protected:
      void start() override;
      void pause() override;
      void resume () override;

   private:
      OpenDataRequestor *requestor = nullptr;
      QTimer *mTimer = nullptr;

   private slots:
      void slotCreateRequestor();
};

#endif // BICINGSERVICE_HPP
