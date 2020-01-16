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

//  bool checkIsPlayerRegistred(qintptr id);
  QByteArray data();

  bool joinGame(qintptr clientId, std::string playerName, std::string gameId);
  bool createGame(qintptr clientId, std::string playerName, std::string gameName, unsigned playerNumber);


signals:
    void error(QTcpSocket::SocketError socketerror);
    void handlePlayerCoords(qintptr clientId, long X_coord, long Y_coord);
    void sendNewPlayerData();
    void registerPegister();

public slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onHandlePlayerCoords(qintptr clientId, long X_coord, long Y_coord);
    void onSendNewPlayerData();
    void onPlayerRegistered();


private:
    QTcpSocket *m_socket;
    qintptr m_socket_descriptor;
    std::shared_ptr<Server> m_server_ptr;
    QByteArray m_data;
    bool isRegistred;

    void setUpListeners();



};

#endif // CLIENTHANDLER_HPP
