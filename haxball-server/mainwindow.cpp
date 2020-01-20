#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QHostAddress>


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  //set up logging text style
  setUpLoggingPreview();

  //get singleton server instance shared between components
  m_server_ptr = Server::instance(QHostAddress::LocalHost, 3333, this);
  m_server_ptr->start();

  //set up settings dialog
  ui_dialog = new DialogSettings(m_server_ptr, this);
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

void MainWindow::previewLoggedServerData(std::string new_data)
{
  //ui->logTextEdit->append(QString::fromStdString(new_data));
  return;
}

void MainWindow::on_startButton_clicked()
{
    m_server_ptr->start();
}

void MainWindow::on_stopButton_clicked()
{
    m_server_ptr->stop();
}

void MainWindow::on_restartButton_clicked()
{
    m_server_ptr->restart();
}

void MainWindow::on_exitButton_clicked()
{
  this->close();
}


void MainWindow::setUpLoggingPreview()
{
 // ui->logTextEdit->setReadOnly(true);
  //QPalette p = ui->logTextEdit->palette();
 // p.setColor(QPalette::Base, Qt::black);
  //p.setColor(QPalette::Text, Qt::white);
 // ui->logTextEdit->setPalette(p);
}
