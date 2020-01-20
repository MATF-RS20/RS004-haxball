#include "clienthandler.hpp"

#include <memory>

#include "server.hpp"
#include "mainwindow.hpp"


PlayerHandler::PlayerHandler(qintptr id, QObject *parent)
  :QThread(parent), m_playerId(id)
{
  qDebug() << "[PlayerHandler] Assigned player ID: " << id;

  //get singleton server instance
  m_server_ptr = Server::instance(QHostAddress::LocalHost, 3333, this);

  isRegistred = false;
}


void PlayerHandler::run()
{

  qDebug() << "[run] Player connection is initializing...";

  m_socket = new QTcpSocket();


  if(!m_socket->setSocketDescriptor(this->m_playerId))
    {
      qDebug() << "[run] Palyer is NOT connected to server! (Tried to be assigned playerId: " << m_playerId << " )";

      emit error(m_socket->error());

      return;
    }


  qDebug() << "[run] Palyer is connected to server! (Assigned playerId: " << m_playerId << " )";

  //setup all listeners (signals/slots)
  setUpListeners();

  auto player_game_data = m_server_ptr->player_game_data();


  if(!isRegistred)
    {
      //the first time client is getting server data...
      qDebug() << "[run] Player is NOT registered yet...";

      // just return client ID
      QByteArray buffer;
      QString data_str;
      data_str.append("playerId").append(" ").append(QString::number(m_playerId));
      buffer.append(data_str);

      m_socket->write(buffer);
      m_socket->flush();

    }
  else
    {
      qDebug() << "[run] Player with playerId: " << m_playerId << " allready registred...";

      //send data to client again
      emit sendToClientPlayerData();

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

      if(ql[0] == "coords")
        {
          // PROTOCOL:   "coord player_id x y"

          long clientId = ql[1].toLong();
          double X_coord = ql[2].toDouble();
          double Y_coord = ql[3].toDouble();

          qDebug() << "[coords]: Reading data: clientId: " << clientId << " X: " << X_coord << " Y: " << Y_coord;

          // handle new data to server
          emit saveToServerPlayerData(clientId, X_coord, Y_coord);

        }

      else if(ql[0] == "joinGame")
        {
          // PROTOCOL:   "joinGame client_id game_id player_name "

          auto clientId = ql[1].toLong();
          auto gameId = ql[2].toStdString();
          auto playerName = ql[3].toStdString();

          qDebug() << "[joinGame]: Primljeno od klijenta: " << " clienId:" << ql[1] << " gameId:" << ql[2] <<  " playerName:" <<  ql[3] ;

          if(joinGame(clientId, playerName, gameId))
            {
              qDebug() << "[joinGame & registerPlayer]";
              isRegistred  = true;

              //send new data to client
              qDebug() << "[joinGame & onSendNewPlayerData]";
              emit sendToClientPlayerData();
            }
          else
            {
              qDebug() << "[joinGame]: Player with ID :" << clientId << " is not joined to game...";
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
              qDebug() << "[createGame]: Game: " << QString::fromStdString(gameName) << " is created by playerId :" << clientId;

              //              qDebug() << "[createGame] -> registerPlayer";
              isRegistred  = true;

              //send new data to client
              //              qDebug() << "[createGame] -> onSendNewPlayerData";

              //send game ID
              emit sendGameId();

              //send data back
              //emit sendToClientPlayerData();
            }
          else
            {
              qDebug() << "[createGame]: Game: " << QString::fromStdString(gameName) << " could NOT be created by playerId :" << clientId;
            }

        }

      else if(ql[0] == "refresh")
        {
          // PROTOCOL:   "refresh"

          qDebug() << "[refresh]";

          auto created_games = m_server_ptr->createdGames();

          QString games_str("gameNames ");

          for(auto iter = std::begin(created_games); iter != created_games.end(); iter++)
            {
              games_str.append((*iter)->toSocketString());
            }

          //write game data to socket
          QByteArray buffer;
          buffer.append(games_str);
          m_socket->write(buffer);

          m_socket->flush();

        }

      else
        {
          qDebug() << "[UNKNOWN PROTOCOL]";
        }

      //write data to socket
      m_socket->readLine();

    }

}

void PlayerHandler::onConnected()
{
  qDebug() << "[onConnected] Player with ID: "  << m_playerId << " is connected to server...";
}

void PlayerHandler::onDisconnected()
{
  qDebug() << "[onDisconnected] Player with ID: "  << m_playerId << " is disconnecting from server...";
  m_socket->deleteLater();

  //remove player
  m_server_ptr->player_game_data().erase(m_playerId);

  //  exit(0);
}

void PlayerHandler::onSaveToServerPlayerData(long clientId, double X_coord, double Y_coord)
{

  auto data = m_server_ptr->player_game_data();
  auto res =  data.find(clientId);

  if(res != data.end())
    {
      auto game_ptr = res->second;
      std::vector<std::shared_ptr<Player>> players = game_ptr->players();

      for(auto iter = std::begin(players) ; iter != std::end(players); iter++)
        {
          if(iter->get()->id() == clientId)
            {
              iter->get()->setXY(X_coord, Y_coord);
              qDebug() << "[onHandlePlayerCoords] " << " Writting data: clientId: " << clientId << " X_w: " << X_coord<< " Y_w: " << Y_coord;
            }
        }

    }
  else
    {
      qDebug() << "[onHandlePlayerCoords] Error";
    }

  //send updated data back to server
  emit sendToClientPlayerData();

}

void PlayerHandler::onSendToClientPlayerData()
{

  //write data to sock

  auto player_game_data = m_server_ptr->player_game_data();

  auto res_iter = player_game_data.find(m_playerId);

  if(res_iter != player_game_data.end())
    {

      auto playerId = res_iter->first;
      auto game_ptr = res_iter->second;

      auto teammates = game_ptr->players();

      QString data_str("coords ");

      //get ball coordinates
      auto ballX = game_ptr->ball().x();
      auto ballY = game_ptr->ball().y();

      data_str.append(QString::number(ballX)).append(" ");
      data_str.append(QString::number(ballY)).append(" ");

      for(auto iter = std::begin(teammates) ; iter != std::end(teammates) ; iter++)
        {
          if(iter->get()->id() != playerId)
            {
              data_str.append(iter->get()->toString());
            }
        }
      data_str.append("\n");

      QByteArray buffer;
      buffer.append(data_str);
      m_socket->write(buffer);

      m_socket->flush();
    }
  else {
      qDebug() << "[onSendNewPlayerData]: Igrac nije pronadjen u hes mapi" << m_playerId;
    }


}

void PlayerHandler::onSendGameId()
{


  auto player_game_data = m_server_ptr->player_game_data();

  auto res_iter = player_game_data.find(m_playerId);

  if(res_iter != player_game_data.end())
    {

      auto game_id = res_iter->second->gameId();

      QString data_str("gameId ");
      data_str.append(QString::fromStdString(game_id + "\n"));

      QByteArray buffer;
      buffer.append(data_str);
      m_socket->write(buffer);

      m_socket->flush();

    }


}


void PlayerHandler::setUpListeners()
{
  connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()), Qt::DirectConnection);
  connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);
  connect(m_socket, SIGNAL(connected()), this, SLOT(onReadyRead()), Qt::DirectConnection);

  // update/send player data
  connect(this, SIGNAL(saveToServerPlayerData(long, double, double)), this, SLOT(onSaveToServerPlayerData(long, double, double)));
  connect(this, SIGNAL(sendToClientPlayerData()), this, SLOT(onSendToClientPlayerData()));
  connect(this, SIGNAL(sendGameId()), this, SLOT(onSendGameId()));

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

