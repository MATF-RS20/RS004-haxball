#include "clienthandler.hpp"


ClientHandler::ClientHandler(qintptr id, QObject *parent)
  : QThread(parent)
{
    this->m_socket_descriptor = id;
    qDebug() << "Created socket descriptor: " << m_socket_descriptor;
}

void ClientHandler::run()
{
    qDebug() << m_socket_descriptor << "Client handler thread is running...";
    m_socket = new QTcpSocket();
    if(!m_socket->setSocketDescriptor(this->m_socket_descriptor))
    {
        emit error(m_socket->error());
        return;
    }

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);
    connect(m_socket, SIGNAL(connected()), this, SLOT(connected()), Qt::DirectConnection);

    //qDebug() << "Socket descriptor: " << m_socket_descriptor << " is connected to server...";

    exec();
}

void ClientHandler::readyRead()
{
    QByteArray data = m_socket->readAll();

    qDebug() << "Socket descriptor: " << m_socket_descriptor << " Data read: " << data;

    m_socket->write(data);
}

void ClientHandler::connected()
{
    qDebug() << "Socket descriptor: "  << m_socket_descriptor << " is connected to server...";
}

void ClientHandler::disconnected()
{
    qDebug() << "Socket descriptor: "  << m_socket_descriptor << " is disconnected from server...";
    m_socket->deleteLater();
    exit(0);
}

