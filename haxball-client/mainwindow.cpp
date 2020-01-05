#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "game.h"
#include "clientsocket.hpp"
#include <QHostAddress>
#include <vector>
#include <QString>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  clientsocket = ClientSocket::instance(QHostAddress::LocalHost, 3333);
  clientsocket->connectToServer();

}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_refreshButton_clicked()
{

    std::vector<std::string> games = clientsocket.get()->getGames();

    if(games.size() != 0)
    {
        ui->joinButton->setEnabled(true);
        for(unsigned iter = 1;  iter < games.size(); iter+=3)
        {
            ui->comboBox->addItem(QString::fromStdString(games[iter]));
        }
    }
    else{
        ui->joinButton->setEnabled(false);
    }
}

void MainWindow::on_joinButton_clicked()
{
    std::string msg = clientsocket.get()->getGames()[0];
    QString currentRoom = ui->comboBox->currentText();
    sendMsg.append(msg + " " + currentRoom.toStdString()); // saljem serveru idPlayer , idGame
    clientsocket->getSocket()->write(QString::fromStdString(sendMsg).toUtf8());
    emit clientsocket->getSocket()->bytesWritten(sendMsg.length());
}
