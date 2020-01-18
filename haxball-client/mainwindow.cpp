#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "game.hpp"
#include "clientsocket.hpp"
#include <QHostAddress>
#include <vector>
#include <QString>
#include <iostream>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_game(new Game(this))
{
  ui->setupUi(this);

  m_clientsocket = ClientSocket::instance(QHostAddress::LocalHost, 3333);
  m_clientsocket->connectToServer();

  setUpListener();

  m_game->setSocket(m_clientsocket);
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

        qDebug() << "[on_createButton_clicked]: Serveru je poslato " << serverRequest;

        m_clientsocket->getSocket()->write(serverRequest);
    }




    this->hide();
    m_game->show();


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
    if(checkJoinGame()){
        QByteArray serverRequest;
        const QString protocol = "joinGame";
        QString gameId = m_currentItem->text().split(MainWindow::regex)[1];


        serverRequest.append(protocol + " ")
                     .append(m_playerId + " ")
                     .append(gameId + " ")
                     .append(m_playerName + " ");

        m_clientsocket->getSocket()->write(serverRequest);

        hide();
        m_game->show();
    }
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

void MainWindow::enableJoinGameButton()
{
    if(checkJoinGame()){
        ui->joinButton->setEnabled(true);
    }
    else{
        ui->joinButton->setEnabled(false);
    }
}

void MainWindow::setUpListener()
{

    connect(m_clientsocket.get(), SIGNAL(onPlayerId(QString)), this, SLOT(playerIdReady(QString)));
    connect(m_clientsocket.get(), SIGNAL(onGameNames(QStringList)), this, SLOT(gameNamesReady(QStringList)));

    connect(ui->playerNameTextEdit, SIGNAL(textChanged()), this, SLOT(enableCreateGameButton()));
    connect(ui->gameNameTextEdit, SIGNAL(textChanged()), this, SLOT(enableCreateGameButton()));
    connect(ui->PlayerNumberSpinBox, SIGNAL(valueChanged(int)), this, SLOT(enableCreateGameButton()));

    connect(ui->gamesListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(enableJoinGameButton()));

     connect(m_clientsocket.get(), SIGNAL(onCoords(QStringList)), m_game, SLOT(coordsReadReady(QStringList)));
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
    else if(m_playerName.split(MainWindow::regex).size() > 1){
        ui->messageLabel->setText("Player name must be one word!");
        flag = false;
    }
    else if(m_gameName.split(MainWindow::regex).size() > 1){
        ui->messageLabel->setText("Game name must be one word!");
        flag = false;
    }
    else{
        ui->messageLabel->setText("");
        ui->messageLabel->setText("");
    }
    return flag;
}

bool MainWindow::checkJoinGame()
{
    m_playerName = ui->playerNameTextEdit->toPlainText().trimmed();
    m_currentItem = ui->gamesListWidget->currentItem();

    bool flag = true;

    if(m_playerName.size() == 0){
        ui->messageLabel->setText("Enter player name!");
        flag = false;
    }
    if(m_currentItem == nullptr){
        ui->messageLabel->setText("Select game room!");
        flag = false;
    }
    return flag;
}

void MainWindow::playerIdReady(QString id)
{
    m_playerId = id;
    m_game->getMe()->setId(id.toInt());
    qDebug() << "playerId: " << id;
}

void MainWindow::gameNamesReady(QStringList games)
{
    QStringList new_games;
    for(QStringList::iterator iter = games.begin(); iter != games.end(); iter += 4){
        QStringList oneGame{*iter, *(iter+1), *(iter+2), *(iter+3)};
        qDebug() << "oneGame: " << oneGame;
        new_games.append(oneGame.join(" "));
    }

    m_games = std::move(new_games);

    ui->gamesListWidget->clear();
    ui->gamesListWidget->addItems(m_games);

    qDebug() << "gameNamesReady(QStringList games)";
}



void MainWindow::on_gamesListWidget_itemSelectionChanged()
{

    m_currentItem = ui->gamesListWidget->currentItem();

    ui->gameNameTextEdit->setText(m_currentItem->text().split(MainWindow::regex)[0]);
    ui->PlayerNumberSpinBox->setValue(m_currentItem->text().split(MainWindow::regex)[2].toInt());
}

const QRegExp MainWindow::regex("\\s+");

