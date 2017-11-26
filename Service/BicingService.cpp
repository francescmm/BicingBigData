#include "BicingService.hpp"
#include <QThread>

BicingService::BicingService(int argc, char **argv)
   : QObject(), QtService<QCoreApplication>(argc, argv, "Bicing Daemon")
{
   setServiceDescription("Deamon for retrieving data from Bicing");
   setServiceFlags(CanBeSuspended);
}

BicingService::~BicingService ()
{
   delete mTimer;
}

void BicingService::start()
{
   mTimer = new QTimer ();
   mTimer->setInterval (60000);
   mTimer->setTimerType (Qt::PreciseTimer);

   connect (mTimer, SIGNAL (timeout ()), this, SLOT (slotCreateRequestor ()));

   slotCreateRequestor();

   mTimer->start ();
}

void BicingService::pause()
{
}

void BicingService::resume ()
{
}

void BicingService::slotCreateRequestor()
{
   auto requestor = new OpenDataRequestor();
   auto thread = new QThread();

   requestor->moveToThread (thread);

   connect(thread, SIGNAL(started()), requestor, SLOT(makeRequest()));
   connect(requestor, SIGNAL(signalTaskDone()), thread, SLOT(quit()));
   connect(thread, SIGNAL(finished()), requestor, SLOT(deleteLater()));
   connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
   connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()), thread, SLOT(quit()));

   thread->start ();
}
