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

    isRegistred = false;
}

void PlayerHandler::run()
{

    auto log =  "[run] Client handler thread is running...";
    m_server_ptr->log_data(log);

    m_socket = new QTcpSocket();

    if(!m_socket->setSocketDescriptor(this->m_socket_descriptor))
    {
        auto l = "[run] Socket descriptor: " +  std::to_string(m_socket_descriptor) + " is NOT connected to server...";
        m_server_ptr->log_data(l.c_str());

        emit error(m_socket->error());
        return;
    }

    setUpListeners();

    auto l = "[run] Socket descriptor: " +  std::to_string(m_socket_descriptor) + " is connected to server...";
    m_server_ptr->log_data(l.c_str());

    auto player_game_data = m_server_ptr->player_game_data();

    if(!isRegistred)
    {
      //the first time client is getting server data...
      qDebug() << "[checkIsPlayerRegistred]: false";

      //return just client ID
      std::string data_str;
      data_str.append("playerId").append(" ");
      data_str.append(std::to_string(m_socket_descriptor));

      m_socket->write(data_str.c_str());

      emit registerPegister();

    }
    else
    {

    }


    exec();

}

void PlayerHandler::onReadyRead()
{

  QByteArray data;

  while(!(data = m_socket->readLine()).isEmpty())
  {

    QString str_r_data(data);
    QStringList ql = str_r_data.split(QRegExp("\\s+"));

    qDebug() << str_r_data;

    if(ql[0] == "coord")
      {
        // PROTOCOL:   "coord player_id x y"
        qDebug() << "coord";

        auto clientId = ql[1].toLong();
        auto X_coord = ql[2].toLong();
        auto Y_coord = ql[3].toLong();

        emit handlePlayerCoords(clientId, X_coord, Y_coord);

      }

     else if(ql[0] == "joinGame")
      {
        // PROTOCOL:   "joinGame client_id game_id player_name "

        auto l = "joinGame: clienId: " + ql[1] + " gameId: " + ql[2] + " playerName: " + ql[3] ;
        m_server_ptr->log_data(l.toStdString());

        auto clientId = ql[1].toLong();
        auto gameId = ql[2].toStdString();
        auto playerName = ql[3].toStdString();

        joinGame(clientId, playerName, gameId);

        qDebug() << "[joinGame]";

//        isRegistred = true;
        emit registerPegister();

      }

    else if(ql[0] == "createGame")
      {
        // PROTOCOL:   "createGame client_id player_name game_name player_number"

        auto l = "createGame: clientId: " + ql[1] + " playerName: " + ql[2] + " gameName: " + ql[3] + " playerNumber: " + ql[4];
        m_server_ptr->log_data(l.toStdString());

        auto clientId = ql[1].toLong();
        auto playerName = ql[2].toStdString();
        auto gameName = ql[3].toStdString();
        auto playerNumber = ql[4].toUInt();
        createGame(clientId, playerName, gameName, playerNumber);

        qDebug() << "[createGame]";
//        isRegistred = true;

        //user is registered
        emit registerPegister();

      }

     else if(ql[0] == "refresh")
      {
        // PROTOCOL:   "refresh"

        std::string games_str("gameNames ");

        auto games = m_server_ptr->createdGames();

        for(auto iter = std::begin(games); iter != games.end(); iter++)
        {
          games_str.append((*iter)->toString());
        }

        //write game data to socket
        m_socket->write(games_str.c_str());

        emit m_socket->bytesWritten(static_cast<int>(games_str.length()));

//        isRegistred = false;
        emit registerPegister();
      }

    //write data to socket
    m_socket->readLine();

    }

}

void PlayerHandler::onConnected()
{
    qDebug() << "[onConnected] Socket descriptor: "  << m_socket_descriptor << " is connected to server...";
}

void PlayerHandler::onDisconnected()
{
    qDebug() << "[onDisconnected] Socket descriptor: "  << m_socket_descriptor << " is disconnected from server...";
    m_socket->deleteLater();

    //remove player
    m_server_ptr->player_game_data().erase(m_socket_descriptor);

    exit(0);
}

void PlayerHandler::onHandlePlayerCoords(qintptr clientId, long X_coord, long Y_coord)
{

  auto data = m_server_ptr->player_game_data();
  auto res =  data.find(clientId);
  if(res != data.end())
  {
    auto players = res->second->players();
    for(auto iter = std::begin(players) ; iter != std::end(players); iter++)
      {
          if(iter->id() == clientId)
            {
              iter->x_y(X_coord, Y_coord);
            }
      }
  }

  emit sendNewPlayerData();

}

void PlayerHandler::onSendNewPlayerData()
{
    //write data to sock

      auto client_game = m_server_ptr->player_game_data();

      auto res = client_game.find(m_socket_descriptor);

      auto res_game = m_server_ptr->findGameById(res->second->gameId());

      if(!res_game.first)
        {
          qDebug() << "Error getting created game!";
          exit(1);
        }

      auto teammates = res_game.second->players();

      qDebug() << "coords";
      m_socket->write("coords");

      for(auto iter = std::begin(teammates) ; iter != std::end(teammates) ; iter++)
        {
          qDebug() << iter->toString().c_str();
          m_socket->write(iter->toString().c_str());
        }

}

void PlayerHandler::onPlayerRegistered()
{
  isRegistred = true;
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

  //update/send player data
  connect(this, SIGNAL(handlePlayerCoords(qintptr, long, long)), this, SLOT(onHandlePlayerCoords(qintptr, long, long)));
  connect(this, SIGNAL(registerPegister()), this, SLOT(onPlayerRegistered()));
}


bool PlayerHandler::joinGame(qintptr clientId, std::string playerName, std::string gameId)
{
  if(m_server_ptr->joinGame(clientId, playerName, gameId))
    {
      qDebug() <<"Game is joined!";
      return true;
    }
  else
    {
      qDebug() <<"Game could not start!";
      return false;
    }
}

bool PlayerHandler::createGame(qintptr clientId, std::string playerName, std::string gameName, unsigned playerNumber)
{
  if(m_server_ptr->createGame(clientId, playerName, gameName, playerNumber))
    {
      qDebug() <<"Game is created!";
      return true;
    }
  else
    {
      qDebug() <<"Game could not start!";
      return false;
    }
}

