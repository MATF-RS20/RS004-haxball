#ifndef CLIENTHANDLER_HPP
#define CLIENTHANDLER_HPP

#include <QThread>
#include <QTcpSocket>
#include <QDebug>


class PlayerHandler : public QThread
{

  Q_OBJECT

public:

  explicit PlayerHandler(qintptr id, QObject* parent = nullptr);

  void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void connected();
    void disconnected();

public slots:

private:
    //fields
    QTcpSocket *m_socket;
    qintptr m_socket_descriptor;

    //methods


};

#endif // CLIENTHANDLER_HPP
