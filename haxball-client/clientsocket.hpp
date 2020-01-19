#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QAbstractSocket>
#include <QHostAddress>
#include <vector>
#include <algorithm>
#include <iterator>

#include <QByteArray>

#include <memory>

class ClientSocket : public QObject
{

  Q_OBJECT

public:
    explicit ClientSocket(QHostAddress host, quint16 port, QObject* parent = nullptr);
    bool connectToServer();
    void setHost(QHostAddress host);
    void setPort(quint16 port);
    QString getResult() const;
    QTcpSocket* getSocket();
    QStringList getGames();

    //sigleton class method
    static std::shared_ptr<ClientSocket> instance(QHostAddress address, quint16 port, QObject* parent = nullptr)
    {
      static std::shared_ptr<ClientSocket> s (new ClientSocket(address, port, parent));
      return s;
    }

signals:
    void onPlayerId(QString id);
    void onGameNames(QStringList games);
    void onCoords(QStringList coords);

public slots:

  void onConnected();
  void onDisconnected();
  void onBytesWritten(qint64 bytes);
  void onReadyRead();

private:
  QTcpSocket* m_socket;
  QHostAddress m_host;
  quint16 m_port;

  QByteArray m_data;
  QList<QString> m_optData;

  QString m_playerID;
  QStringList m_games;
  QString m_result;
};

#endif // CLIENTSOCKET_HPP
