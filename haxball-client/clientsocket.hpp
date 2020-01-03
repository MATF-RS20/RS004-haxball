#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QAbstractSocket>
#include <QHostAddress>

#include <QByteArray>


class ClientSocket : public QObject
{

  Q_OBJECT

public:
    explicit ClientSocket(QHostAddress host, quint16 port, QObject* parent = nullptr);
    bool connectToServer(QHostAddress host, quint16 port);
    void setHost(QHostAddress host);
    void setPort(quint16 port);

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

  QByteArray m_data;

};

#endif // CLIENTSOCKET_HPP
