#include "playerhandler.hpp"


PlayerHandler::PlayerHandler(int id, QObject *parent) :
    QThread(parent)
{
    this->socket_descriptor = id;
}

void PlayerHandler::run()
{
    qDebug() << socket_descriptor << "Server thread is starting...";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socket_descriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket, SIGNAL(ready_read()), this, SLOT(ready_read()),Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()),Qt::DirectConnection);

    qDebug() << socket_descriptor << "Player is connected...";

    exec();
}

void PlayerHandler::ready_read()
{
    QByteArray data = socket->readAll();

    qDebug() << socket_descriptor << " Data in: " << data;

    socket->write(data);
}

void PlayerHandler::disconnected()
{
    qDebug() << socket_descriptor << "Player is disconnected...";
    socket->deleteLater();
    exit(0);
}

