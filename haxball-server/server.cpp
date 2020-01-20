#include "server.hpp"
#include "clienthandler.hpp"
#include "worker.hpp"

#include <string>
#include <vector>

#define LOG_DATA(str) (auto s QString::fromStdString(str);   emit logServerData(s))


Server::Server(QHostAddress address, quint16 port, QObject* parent)
  :QTcpServer(parent), m_host_address(address), m_port(port)
{
  initData();
}

void Server::start()
{
  qDebug() << "[start] Server is starting...";

  //all listeners will be connect
  setUpListeners();

  if(!this->listen(m_host_address, m_port))
    {
      qDebug() << "[start] Server could not be started...";
    }
  else
    {
      qDebug()  << "[start] Server is listening at " << m_host_address << " : " << m_port << "...";
    }

}

void Server::stop()
{
  qDebug() << "[stop] Server is stopping...";

  this->close();

  qDebug() << "[stop] Server is stoped...";
}

void Server::restart()
{
  qDebug() << "[restart] Server is restarting...";

  this->stop();
  this->start();
}

void Server::port(quint16 port)
{
  m_port = port;
}

void Server::hostAddress(QHostAddress address)
{
  m_host_address = address;
}

quint16 Server::port() const
{
  return m_port;
}

QHostAddress Server::hostAddress() const
{
  return m_host_address;
}


void Server::addGames(std::shared_ptr<Game> game_ptr)
{
  m_created_games.push_back(game_ptr);
}


std::map<qintptr, std::shared_ptr<Game>> & Server::player_game_data()
{
  return m_player_game_data;
}


std::vector<std::shared_ptr<Game>> & Server::createdGames()
{
  return m_created_games;
}



void Server::incomingConnection(qintptr handle)
{

  qDebug() << "[incomingConnection] Client  is connecting...";

  PlayerHandler *thread = new PlayerHandler(handle, this);
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  thread->start();

  return;
}


void Server::setUpListeners()
{
  //setup listener for data logging
  connect(this, SIGNAL(logServerData(std::string &)), parent(), SLOT(previewLoggedServerData(std::string &)));

}


void Server::initData()
{
  //init players-games hash map
  for(auto iter = std::begin(m_player_game_data); iter != m_player_game_data.end(); iter++)
    {
      iter->second = nullptr;
    }

}

bool Server::joinGame(qintptr clientId, std::string playerName, std::string gameId)
{

  //create new player
  std::shared_ptr<Player> player_ptr = std::make_shared<Player>(clientId, playerName);

  //find player game

  std::shared_ptr<Game> tmp_ptr;
  for(auto game_ptr : m_created_games)
    {
      if(gameId == game_ptr->gameId())
        {
          game_ptr->addPlayer(player_ptr);
          m_player_game_data.insert(std::pair<qintptr, std::shared_ptr<Game>>(clientId, game_ptr));
          break;
        }
    }

  return true;
}



bool Server::createGame(qintptr clientId, std::string playerName, std::string gameName, unsigned playerNumber)
{

  qDebug() << "[createGame]";

  //create new game
  auto game_ptr = std::make_shared<Game>(gameName, playerNumber);

  //create new player
  auto player_ptr = std::make_shared<Player>(clientId, playerName);

  //add player to game
  game_ptr->addPlayer(player_ptr);

  //add game to created games
  m_created_games.push_back(game_ptr);

  //add game to player-game data
  m_player_game_data.insert(std::pair<qintptr, std::shared_ptr<Game>>(clientId, game_ptr));

  return true;
}



std::pair<bool, std::shared_ptr<Game>> Server::findGameById(std::string gameId)
{

  for(auto g : m_created_games)
    {
      if(g->gameId() == gameId)
        {
          return { true, g };
        }
    }
  return { false, nullptr };

}

void Server::printServerContent() const
{
  qDebug() << "[printServerContent] START ***************************************";
  qDebug() << "[printServerContent] ************* GAME - PLAYER data ************* ";
  for(auto iter = std::cbegin(m_player_game_data) ; iter != std::cend(m_player_game_data) ;iter++)
    {
      qDebug() << "[printServerContent] playerId: " << iter->first << " game: " << iter->second->toString();
    }

  qDebug() << "************* CRATED GAMES data ************* ";
  for(auto iter = std::cbegin(m_created_games) ; iter != std::cend(m_created_games) ;iter++)
    {
      qDebug() << "[printServerContent] game: "<< (*iter)->toString();
    }
  qDebug() << "[printServerContent] END ***************************************";
}




