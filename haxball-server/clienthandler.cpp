#include "clienthandler.hpp"

#include <memory>

#include "server.hpp"
#include "mainwindow.hpp"


PlayerHandler::PlayerHandler(qintptr id, QObject *parent)
  : QThread(parent)
{
    m_socket_descriptor = id;
    qDebug() << "[PlayerHandler] Created socket descriptor: " << m_socket_descriptor;

    //get singleton server instance
    m_server_ptr = Server::instance(QHostAddress::LocalHost, 3333, this);
}

void PlayerHandler::run()
{
    qDebug() << m_socket_descriptor << "[run] Client handler thread is running...";

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
        //TODO: ...





    }
    else
    {
        //the first time client is getting server data...

//        //retrun all game to client
//        std::string games_str(std::to_string(m_socket_descriptor));

//        auto games = m_server_ptr->createdGames();
//        for(auto iter = std::begin(games); iter != games.end(); iter++)
//        {
//          games_str.append((*iter)->toString());
//        }
//        m_socket->write(QString::fromStdString(games_str).toUtf8());
//        emit m_socket->bytesWritten(games_str.length());


        //return just client ID
        std::string data_str;
        data_str.append("playerId").append(" ");
        data_str.append(std::to_string(m_socket_descriptor));
        m_socket->write(data_str.c_str());

      }


    exec();
}

void PlayerHandler::onReadyRead()
{
    QByteArray data = m_socket->readAll();

    QString str_r_data(data);
    QStringList ql = str_r_data.split(" ");

    if(ql[0] == "joinGame")
      {
        //    "joinGame client_id game_id player_name "
        qDebug() << "joinGame: clienId: " << ql[0] << " gameId: " << ql[1] ;

        auto clientId = ql[0].toLong();
        auto gameId = ql[1].toStdString();
        joinGame(clientId, gameId);

      }
    else if(ql[0] == "createGame")
      {
        //    "createGame client_id player_name game_name player_number"
        qDebug() << "createRoom: clienId: " << ql[0] << " gameId: " << ql[1] << " player_number: " << ql[2];

        auto clientId = ql[0].toLong();
        auto gameId = ql[1].toStdString();
        auto playerNumber = ql[2].toUInt();
        createGame(clientId, gameId, playerNumber);

      }


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


void PlayerHandler::joinGame(long clientId, std::string gameId)
{
  m_server_ptr->addPlayerToGame(clientId, gameId);
}

void PlayerHandler::createGame(long clientId, std::string gameId, unsigned playerNumber)
{
  m_server_ptr->addPlayerToGame(clientId, gameId);
}


