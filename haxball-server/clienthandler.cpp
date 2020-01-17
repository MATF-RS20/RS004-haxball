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

    qDebug() << "[run] Client handler thread is running...";

    m_socket = new QTcpSocket();

    if(!m_socket->setSocketDescriptor(this->m_socket_descriptor))
    {
        qDebug() << "[run] Socket descriptor: " << m_socket_descriptor <<  " is NOT connected to server...";

        emit error(m_socket->error());
        return;
    }

    setUpListeners();

    qDebug() <<  "[run] Socket descriptor: " << m_socket_descriptor << " is connected to server...";

    auto player_game_data = m_server_ptr->player_game_data();

    if(!isRegistred)
    {
      //the first time client is getting server data...
      qDebug() << "Player is NOT registered!";

      //return just client ID
      std::string data_str;
      data_str.append("playerId").append(" ");
      data_str.append(std::to_string(m_socket_descriptor));

      m_socket->write(data_str.c_str());
      emit m_socket->bytesWritten(static_cast<int>(data_str.length()));

    }
    else
    {
        qDebug() << "[run & registerPlayer]";

        //emit registerPlayer();

        //send data to client again
        emit sendNewPlayerData();

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

    //qDebug() << str_r_data;

    if(ql[0] == "coords")
      {
        // PROTOCOL:   "coord player_id x y"

        auto clientId = ql[1].toDouble();
        auto X_coord = ql[2].toDouble();
        auto Y_coord = ql[3].toDouble();

        qDebug() << "[coords]: clientId: " << clientId << " X: " << X_coord << " Y: " << Y_coord;

        //save new data to server
        emit handlePlayerCoords(clientId, X_coord, Y_coord);

        //send data to client again
        emit sendNewPlayerData();

      }

     else if(ql[0] == "joinGame")
      {
        // PROTOCOL:   "joinGame client_id game_id player_name "


        auto clientId = ql[1].toLong();
        auto gameId = ql[2].toStdString();
        auto playerName = ql[3].toStdString();

        qDebug() << "[joinGame] " << " clienId: " << ql[1] << " gameId: " << ql[2] <<  " playerName: " <<  ql[3] ;

        if(joinGame(clientId, playerName, gameId))
          {
            qDebug() << "[joinGame & registerPlayer]";
            emit registerPlayer();

            //send new data to client
            qDebug() << "[joinGame & onSendNewPlayerData]";
            emit sendNewPlayerData();
          }

      }

    else if(ql[0] == "createGame")
      {
        // PROTOCOL:   "createGame client_id player_name game_name player_number"

        auto clientId = ql[1].toLong();
        auto playerName = ql[2].toStdString();
        auto gameName = ql[3].toStdString();
        auto playerNumber = ql[4].toUInt();

        qDebug() << "[createGame]" << " clientId " << ql[1] <<  " playerName: " << ql[2] <<  " gameName: " << ql[3] <<  " playerNumber: " << ql[4];

        if(createGame(clientId, playerName, gameName, playerNumber))
          {
            qDebug() << "[createGame] -> registerPlayer";
            emit registerPlayer();

            //send new data to client
            qDebug() << "[createGame] -> onSendNewPlayerData";
            emit sendNewPlayerData();
          }

      }

     else if(ql[0] == "refresh")
      {
        // PROTOCOL:   "refresh"

        qDebug() << "[refresh]";

        std::string games_str("gameNames ");

        auto games = m_server_ptr->createdGames();

        for(auto iter = std::begin(games); iter != games.end(); iter++)
        {
          games_str.append((*iter)->toString());
        }

        //write game data to socket

        m_socket->write(games_str.c_str());
        emit m_socket->bytesWritten(static_cast<int>(games_str.length()));

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

void PlayerHandler::onHandlePlayerCoords(long clientId, double X_coord, double Y_coord)
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
              qDebug() << "[onHandlePlayerCoords] " << " clientId: " << clientId << " X_w: " << X_coord<< " Y_w: " << Y_coord;
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

      auto cliendId = res->first;
      auto game_ptr = res->second;

      std::vector<Player> & teammates = game_ptr->players();


      std::string data_str("coords ");

      for(auto iter = std::begin(teammates) ; iter != std::end(teammates) ; iter++)
        {
          if(iter->id() == m_socket_descriptor)
            {
//              qDebug() << iter->toString().c_str();
              data_str.append(iter->toString());
            }
        }

      qDebug() << "[onSendNewPlayerData] Data to Client: " << data_str.c_str();

      m_socket->write(data_str.c_str());
      emit m_socket->bytesWritten(static_cast<int>(data_str.length()));

}

void PlayerHandler::onPlayerRegistered()
{
  qDebug() << "[onPlayerRegistered]";
  isRegistred = true;

//  emit sendNewPlayerData();
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
  connect(this, SIGNAL(handlePlayerCoords(long, long, long)), this, SLOT(onHandlePlayerCoords(long, long, long)));
  connect(this, SIGNAL(registerPlayer()), this, SLOT(onPlayerRegistered()));

  connect(this, SIGNAL(sendNewPlayerData()), this, SLOT(onSendNewPlayerData()));

}


bool PlayerHandler::joinGame(qintptr clientId, std::string playerName, std::string gameId)
{
//  qDebug() << "[joinGame] : " << " client";

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
  qDebug() << "[createGame]";

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

