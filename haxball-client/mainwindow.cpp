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

  m_clientsocket = ClientSocket::instance(QHostAddress::LocalHost, 3333);
  m_clientsocket->connectToServer();

  setUpListener();

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
    QByteArray serverRequest;
    /*
    serverRequest.append("createGame ")
                 .append(ui->playerNameTextEdit->toPlainText().trimmed() + " ")
                 .append(ui->gameNameTextEdit->toPlainText().trimmed() + " ")
                 .append()
                          + ui->PlayerNumberSpinBox->value();

    m_clientsocket->getSocket()->wr

    /*

    /*
    hide();
    game = new Game(this);
    game->show();
    */
}

void MainWindow::on_settingsButton_clicked()
{
    settings = new Settings(this);
    settings->show();
}

void MainWindow::on_refreshButton_clicked()
{

    QStringList games = m_clientsocket.get()->getGames();

    qDebug() << "[on_refreshButton_clicked]: " << games;

    ui->roomsListWidget->clear();
    ui->roomsListWidget->addItems(games);
}

void MainWindow::on_joinButton_clicked()
{
    /*
    std::string msg = clientsocket.get()->getGames()[0];
    QString currentRoom = ui->comboBox->currentText();
    sendMsg.append(msg + " " + currentRoom.toStdString()); // saljem serveru idPlayer , idGame

    clientsocket->getSocket()->write(QString::fromStdString(sendMsg).toUtf8());
    emit clientsocket->getSocket()->bytesWritten(sendMsg.length());
    sendMsg = "";
    clientsocket->getSocket()->flush();
    */

}

void MainWindow::enableCreateGameButton()
{
    if(ui->playerNameTextEdit->toPlainText().trimmed().size() != 0 &&
       ui->gameNameTextEdit->toPlainText().trimmed().size() != 0 &&
       ui->PlayerNumberSpinBox->value() != 0){

        ui->createButton->setEnabled(true);
    }
    else{
        ui->createButton->setEnabled(false);
    }
}

void MainWindow::setUpListener()
{

    connect(m_clientsocket.get(), SIGNAL(onPlayerId(QString)), this, SLOT(playerIdReady(QString)));
    connect(m_clientsocket.get(), SIGNAL(onGameNames(QStringList)), this, SLOT(gameNamesReady(QStringList)));

    connect(ui->playerNameTextEdit, SIGNAL(textChanged()), this, SLOT(enableCreateGameButton()));
    connect(ui->gameNameTextEdit, SIGNAL(textChanged()), this, SLOT(enableCreateGameButton()));
    connect(ui->PlayerNumberSpinBox, SIGNAL(valueChanged(int)), this, SLOT(enableCreateGameButton()));
}

void MainWindow::playerIdReady(QString id)
{
    m_playerId = id;
    qDebug() << "playerIdReady(QString id)";
}


