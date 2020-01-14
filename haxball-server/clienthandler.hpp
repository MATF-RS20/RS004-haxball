#ifndef CLIENTHANDLER_HPP
#define CLIENTHANDLER_HPP

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

#include <memory>

#include <server.hpp>

class PlayerHandler : public QThread
{

  Q_OBJECT

public:

  explicit PlayerHandler(qintptr id, QObject* parent = nullptr);

  void run();

  bool checkIsPlayerRegistred(qintptr id);
  QByteArray data();

  void joinGame(qintptr clientId, std::string playerName, std::string gameId);
  void createGame(qintptr clientId, std::string playerName, std::string gameName, unsigned playerNumber);


signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();

public slots:

private:
    QTcpSocket *m_socket;
    qintptr m_socket_descriptor;
    std::shared_ptr<Server> m_server_ptr;
    QByteArray m_data;

    void setUpListeners();

};

#endif // CLIENTHANDLER_HPP
