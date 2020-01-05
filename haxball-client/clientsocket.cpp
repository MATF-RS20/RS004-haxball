#include "clientsocket.hpp"
#include "settings.h"
#include <QString>
#include <iostream>
#include "mainwindow.hpp"

ClientSocket::ClientSocket(QHostAddress host, quint16 port, QObject* parent)
  : m_host(host), m_port(port), QObject(parent)
{
    m_socket = new QTcpSocket();

}

bool ClientSocket::connectToServer()
{
  qDebug() << "Connecting to server...";

  //Connect signal and slots
  connect(m_socket, SIGNAL(connected()), this, SLOT(onConnected()));
  connect(m_socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
  connect(m_socket, SIGNAL(bytesWritten(qint64 bytes)), this, SLOT(onBytesWritten(qint64 bytes)));
  connect(m_socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

  bool success = true;

  m_socket->connectToHost(m_host, m_port);

  //wait for connectin 10 secs
  if(!m_socket->waitForConnected(10000))
  {
      success = false;

      qDebug() << "Client not successful connected to serever! Server timeout!";
  }

  return success;

}

void ClientSocket::setHost(QHostAddress host)
{
    m_host = host;
}

void ClientSocket::setPort(quint16 port)
{
    m_port = port;
}

void ClientSocket::onConnected()
{
  qDebug() << "Connected to server! Getting all created games...";

  //m_data = m_socket->readAll();
  //qDebug() << m_data;

}

void ClientSocket::onDisconnected()
{
  qDebug() << "Disconnected to server...";
}


void ClientSocket::onBytesWritten(qint64 bytes)
{
  qDebug() << "BytesWritten...";
  qDebug() << "Written data: " << bytes;

}

std::vector<std::string> ClientSocket::split(const std::string& str)
{
       std::vector<std::string> reci;

       auto first = str.begin();
       while (first != str.end()) {
           first = std::find_if_not(first, str.end(), isspace);
           auto last = std::find_if(first, str.end(), isspace);
           if(first != str.end()) {
               reci.emplace_back(first, last);
           }
           first = last;
       }
       return reci;
}


void ClientSocket::onReadyRead()
{
  qDebug() << "ReadyRead...";

  QByteArray data = m_socket->readAll();
  QString string_data = QString(data);
  games = split(string_data.toStdString());

  qDebug() << "Read data: " << string_data;

}

QTcpSocket* ClientSocket::getSocket()
{
    return m_socket;
}

std::vector<std::string> ClientSocket::getGames()
{
    return games;
}
