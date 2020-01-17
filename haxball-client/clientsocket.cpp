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



void ClientSocket::onReadyRead()
{
    m_data = m_socket->readLine();

    m_optData = QString(m_data).split(MainWindow::regex);

    qDebug() << "PRIMLJENO: " << m_optData;

    QString opt = m_optData.takeFirst();


    if(!opt.compare("playerId")){
        emit onPlayerId(m_optData.first());
    }
    else if(!opt.compare("gameNames")){
        qDebug() << "emit onGameNames: " << m_optData;
        emit onGameNames(QStringList(m_optData));
    }
    else if(!opt.compare("coords")){
        emit onCoords(QStringList(m_optData));
    }
    else{
        qDebug() << "Primljena poruka ne podrzava poznate protokole";
    }





}

QTcpSocket* ClientSocket::getSocket()
{
    return m_socket;
}

QStringList ClientSocket::getGames()
{
    return m_games;
}
