#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowFlag(Qt::FramelessWindowHint);
  w.setWindowState(Qt::WindowFullScreen);
  w.show();
  return a.exec();
}
