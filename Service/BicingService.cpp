#include "BicingService.hpp"
#include <QThread>
#include <QDebug>

BicingService::BicingService(int argc, char **argv)
   : QObject(), QtService<QCoreApplication>(argc, argv, "BicingBigData Daemon")
{
   setServiceDescription("Deamon for retrieving data from Bicing");
   setServiceFlags(CanBeSuspended);

   const auto pathIndex = argc == 3 ? 1 : 2;

   if ((argc == 3 or argc == 4) and strcmp(argv[pathIndex], "-path") == 0)
   {
      mAbsolutePath = argv[pathIndex + 1];

      if (!mAbsolutePath.endsWith ("/"))
         mAbsolutePath.append ("/");
   }
}

BicingService::~BicingService ()
{
   delete mTimer;
}

void BicingService::start()
{
   if (!mAbsolutePath.isEmpty ())
   {
      mTimer = new QTimer ();
      mTimer->setInterval (60000);
      mTimer->setTimerType (Qt::PreciseTimer);

      connect (mTimer, SIGNAL (timeout ()), this, SLOT (slotCreateRequestor ()));

      slotCreateRequestor();

      mTimer->start ();
   }
   else
      qDebug() << "No path specified!";
}

void BicingService::pause()
{
}

void BicingService::resume ()
{
}

void BicingService::slotCreateRequestor()
{
   auto requestor = new OpenDataRequestor(mAbsolutePath);
   auto thread = new QThread();

   requestor->moveToThread (thread);

   connect(thread, SIGNAL(started()), requestor, SLOT(makeRequest()));
   connect(requestor, SIGNAL(signalTaskDone()), thread, SLOT(quit()));
   connect(thread, SIGNAL(finished()), requestor, SLOT(deleteLater()));
   connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
   connect(QCoreApplication::instance(), SIGNAL(aboutToQuit()), thread, SLOT(quit()));

   thread->start ();
}
