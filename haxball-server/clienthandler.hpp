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

  PlayerHandler() = delete;

  PlayerHandler(qintptr id, QObject* parent = nullptr);

  void run();

  QByteArray data();

  bool joinGame(qintptr clientId, std::string playerName, std::string gameId);
  bool createGame(qintptr clientId, std::string playerName, std::string gameName, unsigned playerNumber);


signals:

    void error(QTcpSocket::SocketError socketerror);

    void saveToServerPlayerData(long clientId, double X_coord, double Y_coord);
    void sendToClientPlayerData();
    void sendGameId();

public slots:

    void onReadyRead();
    void onConnected();
    void onDisconnected();

    void onSaveToServerPlayerData(long clientId, double X_coord, double Y_coord);
    void onSendToClientPlayerData();
    void onSendGameId();

private:

    QTcpSocket *m_socket;
    qintptr m_playerId;
    std::shared_ptr<Server> m_server_ptr;
    bool isRegistred;

    void setUpListeners();

};

#endif // CLIENTHANDLER_HPP
