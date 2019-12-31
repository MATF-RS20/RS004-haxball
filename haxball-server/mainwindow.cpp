#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  //create and start server object that can be shared between components
  m_server = std::make_shared<Server>(QHostAddress::LocalHost, 3333);
  m_server->start();

  //set up settings dialog
  ui_dialog = new DialogSettings(m_server);
}

MainWindow::~MainWindow()
{
  delete ui;
  delete ui_dialog;
}


void MainWindow::on_actionSettings_triggered()
{
  ui_dialog->show();
}

//data logger
void MainWindow::logger(const std::string & s)
{
  m_logger.append(s);
}

std::string MainWindow::logger() const
{
  return m_logger;
}

