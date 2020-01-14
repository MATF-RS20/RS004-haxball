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
    if(checkCreateGame()){
        QByteArray serverRequest;
        const QString protocol = "createGame";

        serverRequest.append(protocol + " ")
                     .append(m_playerId + " ")
                     .append(m_playerName + " ")
                     .append(m_gameName + " ")
                     .append(QString::number(m_playerNumber) + "\n");

        m_clientsocket->getSocket()->write(serverRequest);
    }

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
    QByteArray serverRequest;
    const QString protocol = "refresh";

    serverRequest.append(protocol);

    m_clientsocket->getSocket()->write(serverRequest);
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
    if(checkCreateGame()){
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

bool MainWindow::checkCreateGame()
{
    m_playerName = ui->playerNameTextEdit->toPlainText().trimmed();
    m_gameName = ui->gameNameTextEdit->toPlainText().trimmed();
    m_playerNumber = ui->PlayerNumberSpinBox->value();

    bool flag = true;

    if(m_playerName.size() == 0){
        ui->messageLabel->setText("Enter player name!");
        flag = false;
    }
    else if(m_gameName.size() == 0){
        ui->messageLabel->setText("Enter game name!");
        flag = false;
    }
    else if(m_playerNumber == 0){
        ui->messageLabel->setText("Set player number!");
        flag = false;
    }
    else if(m_playerName.split(" ").size() > 1){
        ui->messageLabel->setText("Player name must be one word!");
        flag = false;
    }
    else if(m_gameName.split(" ").size() > 1){
        ui->messageLabel->setText("Game name must be one word!");
        flag = false;
    }
    else{
        ui->messageLabel->setText("");
    }
    return flag;
}

void MainWindow::playerIdReady(QString id)
{
    m_playerId = id;
    qDebug() << "playerId: " << id;
}

void MainWindow::gameNamesReady(QStringList games)
{

    for(QStringList::iterator iter = games.begin(); iter != games.end(); iter += 4){
        QStringList oneGame{*iter, *(iter+1), *(iter+2), *(iter+3)};
        m_games.append(oneGame.join(" "));
    }

    ui->gamesListWidget->addItems(m_games);

    qDebug() << "gameNamesReady(QStringList games)";
}


