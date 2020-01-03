#include "clientsocket.hpp"
#include "settings.h"

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
  qDebug() << "Connected to server...";


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

void ClientSocket::onReadyRead()
{
  qDebug() << "ReadyRead...";

  qDebug() << "Read data: " << m_socket->readAll();

}

QTcpSocket* ClientSocket::getSocket()
{
    return m_socket;
}
