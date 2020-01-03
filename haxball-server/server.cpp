#include "server.hpp"
#include "clienthandler.hpp"

#include <string>
#include <vector>


Server::Server(QHostAddress address, quint16 port, QObject* parent)
  :QTcpServer(parent), m_host_address(address), m_port(port)
{
  m_log = QString();
  initData();
}

void Server::start()
{
  //all listeners will be connect
  setUpListeners();


  //write to log
  QString s;
  s.append("Server is starting at ").append(m_host_address.toString()).append(" : ").append(QString::number(m_port));
  writeToLog(s);

  if(!this->listen(m_host_address, m_port))
    {
      s.clear();
      s.append("Server could not be started...");
      writeToLog(s);
    }
  else
    {
      s.append("Server is listening at ").append(m_host_address.toString()).append(":").append(QString::number(m_port)).append("...");
      writeToLog(s);
    }

}

void Server::stop()
{
//  //write to log
//  QString s;
//  s.append("Server is stoped...");
//  writeToLog(s);

  this->close();
}

void Server::restart()
{

  //write to log
  QString s;
  s.append("Server is restarted...");
  writeToLog(s);

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

void Server::writeToLog(QString & s)
{
  QString & curr_log = readFromLog();
  curr_log.append(s);

  //notify about logging
  emit newLogData(s);
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


QString & Server::readFromLog()
{
  return m_log;
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

  //write to log
  QString s;
  s.append("Client with connection ID: ").append(QString::number(handle)).append(" is connecting...");
  writeToLog(s);

  PlayerHandler *thread = new PlayerHandler(handle, this);
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  thread->start();

  return;
}


void Server::setUpListeners()
{
  //setup listener for data logging
  connect(this, SIGNAL(newLogData(QString &)), parent(), SLOT(previewLogData(QString &)));

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


