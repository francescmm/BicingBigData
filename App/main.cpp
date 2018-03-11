#include "MainWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   QMap<QString,QString> arguments;

   for (auto i = 1; i < argc; i += 2)
      arguments.insert (argv[i], argv[i+1]);

   auto path = arguments.value("-path");

   if (!path.endsWith ("/"))
      arguments["-path"] = path.append("/");

   MainWindow w { arguments.value("-path"), arguments.value ("-station") };
   w.show();

   return a.exec();
}
