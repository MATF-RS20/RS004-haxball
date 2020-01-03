#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "game.h"

#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  clientsocket = new ClientSocket(QHostAddress::LocalHost, 3333);
  clientsocket->connectToServer(QHostAddress::LocalHost, 3333);
}

MainWindow::~MainWindow()
{
    delete ui;
}

ClientSocket *MainWindow::getClientSocket() const
{
    return clientsocket;
}


void MainWindow::on_exitButton_clicked()
{
    QApplication::exit();
}

void MainWindow::on_createButton_clicked()
{
    hide();
    game = new Game(this);
    game->show();
}

void MainWindow::on_settingsButton_clicked()
{
    settings = new Settings(this);
    settings->show();
}
