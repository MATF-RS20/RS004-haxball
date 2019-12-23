#ifndef CLIENTSOCKET_HPP
#define CLIENTSOCKET_HPP

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QAbstractSocket>
#include <QHostAddress>


class ClientSocket : public QObject
{

  Q_OBJECT

public:
  explicit ClientSocket(QHostAddress host, quint16 port, QObject* parent = nullptr);
  bool connectToServer(QHostAddress host, quint16 port);

signals:

public slots:

  void connected();
  void disconnected();
  void bytesWritten(qint64 bytes);
  void readyRead();

private:

  QTcpSocket* m_socket;
  QHostAddress m_host;
  quint16 m_port;

};

#endif // CLIENTSOCKET_HPP
