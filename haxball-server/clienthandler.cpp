#include "clienthandler.hpp"


ClientHandler::ClientHandler(int id, QObject *parent)
  : QThread(parent)
{
    this->socket_descriptor = id;
}

void ClientHandler::run()
{
    qDebug() << socket_descriptor << "Client handler thread is running...";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socket_descriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(ready_read()), this, SLOT(ready_read()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    qDebug() << socket_descriptor << " is connected to server...";

    exec();
}

void ClientHandler::ready_read()
{
    QByteArray data = socket->readAll();

    qDebug() << socket_descriptor << " Data in: " << data;

    socket->write(data);
}

void ClientHandler::disconnected()
{
    qDebug() << socket_descriptor << " is disconnected from server...";
    socket->deleteLater();
    exit(0);
}

