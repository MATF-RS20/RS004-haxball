#include "mainwindow.hpp"

#include <QApplication>
#include <QHostAddress>

#include "server.hpp"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  Server server(QHostAddress::LocalHost, 3334);

  server.start();


  return a.exec();
}
