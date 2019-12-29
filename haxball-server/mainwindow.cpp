#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_startButton_clicked()
{
  //start server

}


void MainWindow::on_stopButton_clicked()
{
  //stop server

}

void MainWindow::on_restartButton_clicked()
{
  //restart server

}

void MainWindow::on_exitButton_clicked()
{
  //close app
  this->close();

}
