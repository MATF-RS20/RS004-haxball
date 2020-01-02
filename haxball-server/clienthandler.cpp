#include "clienthandler.hpp"

#include <memory>

#include "server.hpp"

PlayerHandler::PlayerHandler(qintptr id, QObject *parent)
  : QThread(parent)
{
    m_socket_descriptor = id;
    qDebug() << "Created socket descriptor: " << m_socket_descriptor;

    //get singleton server instance
    m_server_ptr = Server::instance(QHostAddress::LocalHost, 3333, this);
}

void PlayerHandler::run()
{
    //qDebug() << m_socket_descriptor << "Client handler thread is running...";

    m_socket = new QTcpSocket();
    if(!m_socket->setSocketDescriptor(this->m_socket_descriptor))
    {
        emit error(m_socket->error());
        return;
    }

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(connected()), this, SLOT(connected()), Qt::DirectConnection);

    qDebug() << "Socket descriptor: " << m_socket_descriptor << " is connected to server...";

    exec();
}

void PlayerHandler::readyRead()
{
    QByteArray data = m_socket->readAll();

    qDebug() << "Socket descriptor: " << m_socket_descriptor << " Data read: " << data;

    m_socket->write(data);
}

void PlayerHandler::connected()
{
    qDebug() << "Socket descriptor: "  << m_socket_descriptor << " is connected to server...";
}

void PlayerHandler::disconnected()
{
    qDebug() << "Socket descriptor: "  << m_socket_descriptor << " is disconnected from server...";
    m_socket->deleteLater();
    exit(0);
}

