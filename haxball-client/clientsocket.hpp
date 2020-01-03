#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QAbstractSocket>
#include <QHostAddress>

#include <memory>

class ClientSocket : public QObject
{

  Q_OBJECT

public:
    explicit ClientSocket(QHostAddress host, quint16 port, QObject* parent = nullptr);
    bool connectToServer();
    void setHost(QHostAddress host);
    void setPort(quint16 port);
    QTcpSocket* getSocket();

    //sigleton class method
    static std::shared_ptr<ClientSocket> instance(QHostAddress address, quint16 port, QObject* parent = nullptr)
    {
      static std::shared_ptr<ClientSocket> s (new ClientSocket(address, port, parent));
      return s;
    }

signals:

public slots:

  void onConnected();
  void onDisconnected();
  void onBytesWritten(qint64 bytes);
  void onReadyRead();

private:
  QTcpSocket* m_socket;
  QHostAddress m_host;
  quint16 m_port;

};

#endif // CLIENTSOCKET_HPP
