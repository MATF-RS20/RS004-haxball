#ifndef PLAYERHANDLER_HPP
#define PLAYERHANDLER_HPP

#include <QTcpSocket>
#include <QThread>

class PlayerHandler : public QThread
{

  Q_OBJECT

public:

  explicit PlayerHandler(int id, QObject* parent = nullptr);

  void run() override;


signals:
    void error(QTcpSocket::SocketError socket_error);

public slots:
    void ready_read();
    void disconnected();


private:
    QTcpSocket *socket;
    int socket_descriptor;

};

#endif // PLAYERHANDLER_HPP
