#ifndef CLIENTHANDLER_HPP
#define CLIENTHANDLER_HPP

#include <QThread>
#include <QTcpSocket>
#include <QDebug>


class ClientHandler : public QThread
{

  Q_OBJECT

public:

  explicit ClientHandler(int id, QObject* parent = nullptr);

  void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

public slots:

private:
    QTcpSocket *socket;
    int socket_descriptor;

};

#endif // CLIENTHANDLER_HPP
