#include "clienthandler.hpp"

#include <memory>

#include "server.hpp"
#include "mainwindow.hpp"


PlayerHandler::PlayerHandler(qintptr id, QObject *parent)
  : QThread(parent)
{
    m_socket_descriptor = id;
    qDebug() << "[PlayerHandler()] Created socket descriptor: " << m_socket_descriptor;

    //get singleton server instance
    m_server_ptr = Server::instance(QHostAddress::LocalHost, 3333, this);
}

void PlayerHandler::run()
{
    //qDebug() << m_socket_descriptor << "Client handler thread is running...";

    m_socket = new QTcpSocket();
    if(!m_socket->setSocketDescriptor(this->m_socket_descriptor))
    {
        qDebug() << "[run] Socket descriptor: " << m_socket_descriptor << " is NOT connected to server...";
        emit error(m_socket->error());
        return;
    }

    setUpListeners();


    qDebug() << "[run] Socket descriptor: " << m_socket_descriptor << " is connected to server...";

    auto player_game_data = m_server_ptr->player_game_data();

    if(checkIsPlayerRegistred(m_socket_descriptor))
    {
        //return player connection ID

    }
    else
    {
//      //register current player
//      auto game_ptr = std::make_shared<Game>();
//      player_game_data[m_socket_descriptor] = game_ptr;
//      m_server_ptr->addGames(game_ptr);

//      //add current player to game
//      Player player(m_socket_descriptor);
//      game_ptr->addPlayer(player);

//      auto s = QString::fromStdString(game_ptr->toString());
//      //QByteArray data(s.c_str(), s.length());

//      m_socket->write(s.toUtf8());
//      emit m_socket->bytesWritten(s.length());




        //retrun all game to client

        std::string games_str("playerId: " + std::to_string(m_socket_descriptor));

        auto games = m_server_ptr->createdGames();
        for(auto iter = std::begin(games); iter != games.end(); iter++)
        {
          games_str.append((*iter)->toString());
        }
        m_socket->write(QString::fromStdString(games_str).toUtf8());
        emit m_socket->bytesWritten(games_str.length());


    }


    exec();
}

void PlayerHandler::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    //QByteArray data;
    //data.append("test123 bla bla blaaaa");

    qDebug() << "Data for writting: " << data;

    //m_socket->write(data);
}

void PlayerHandler::onConnected()
{
    qDebug() << "[onConnected] Socket descriptor: "  << m_socket_descriptor << " is connected to server...";


}

void PlayerHandler::onDisconnected()
{
    qDebug() << "[onDisconnected] Socket descriptor: "  << m_socket_descriptor << " is disconnected from server...";
    m_socket->deleteLater();
    exit(0);
}


bool PlayerHandler::checkIsPlayerRegistred(qintptr id)
{
  auto player_game_data = m_server_ptr->player_game_data();
  return nullptr != player_game_data[id];
}

QByteArray PlayerHandler::data()
{
  return  m_data;
}


void PlayerHandler::setUpListeners()
{
  connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()), Qt::DirectConnection);
  connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);
  connect(m_socket, SIGNAL(connected()), this, SLOT(onReadyRead()), Qt::DirectConnection);
}
