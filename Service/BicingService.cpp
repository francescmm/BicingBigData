#include "BicingService.hpp"
#include <QThread>

BicingService::BicingService(int argc, char **argv)
   : QObject()
   , QtService<QCoreApplication>(argc, argv, "BicingBigData Daemon")
{
   setServiceDescription("Deamon for retrieving data from Bicing");
   setServiceFlags(CanBeSuspended);

   const auto pathIndex = argc == 3 ? 1 : 2;

   if ((argc == 3 or argc == 4) and strcmp(argv[pathIndex], "-path") == 0)
   {
      mAbsolutePath = argv[pathIndex + 1];

      if (!mAbsolutePath.endsWith("/"))
         mAbsolutePath.append("/");
   }
}

void BicingService::start()
{
   if (!mAbsolutePath.isEmpty())
   {
      mTimer = new QTimer(this);
      mTimer->setInterval(60000);
      mTimer->setTimerType(Qt::PreciseTimer);

      connect(mTimer, &QTimer::timeout, this, &BicingService::slotCreateRequestor);

      slotCreateRequestor();

      mTimer->start();
   }
}

void BicingService::pause()
{
   mTimer->stop();
}

void BicingService::resume()
{
   mTimer->start();
}

void BicingService::slotCreateRequestor()
{
   auto requestor = new OpenDataRequestor(mAbsolutePath);
   auto thread = new QThread();

   requestor->moveToThread(thread);

   connect(thread, &QThread::started, requestor, &OpenDataRequestor::makeRequest);
   connect(requestor, &OpenDataRequestor::signalTaskDone, thread, &QThread::quit);
   connect(thread, &QThread::finished, requestor, &OpenDataRequestor::deleteLater);
   connect(thread, &QThread::finished, thread, &QThread::deleteLater);
   connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, thread, &QThread::quit);

   thread->start();
}
