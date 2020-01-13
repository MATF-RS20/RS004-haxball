#include "server.hpp"
#include "clienthandler.hpp"

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
  log_data("[start] Server is starting...");

  //all listeners will be connect
  setUpListeners();

  if(!this->listen(m_host_address, m_port))
    {
      log_data("[start] Server could not be started...");
    }
  else
    {
      log_data("[start] Server is listening at...");
//      qDebug()  << "[start] Server is listening at " << m_host_address << " : " << m_port << "...";
    }

}

void Server::stop()
{
  log_data("[stop] Server is stopping...");

  this->close();

  log_data("[stop] Server is stoped...");
}

void Server::restart()
{
  log_data("[restart] Server is restarting...");

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


std::vector<std::shared_ptr<Game>> Server::createdGames() const
{
  return m_created_games;
}



void Server::incomingConnection(qintptr handle)
{

  log_data("[incomingConnection] Client  is connecting...");

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

bool Server::registerPlayer(qintptr player_id)
{
  m_player_game_data[player_id] = nullptr;
  return true;
}


void Server::initData()
{
  //init players-games hash map
  for(auto iter = std::begin(m_player_game_data); iter != m_player_game_data.end(); iter++)
  {
     iter->second = nullptr;
  }


  //add games for test
  auto game_ptr = std::make_shared<Game>();
  m_created_games.push_back(game_ptr);
  QThread::sleep(2);
  auto game_ptr2 = std::make_shared<Game>();
  m_created_games.push_back(game_ptr2);

}

void Server::log_data(const char* str)
{
    std::string s(str);
    qDebug() << str;

    emit logServerData(s);
}


