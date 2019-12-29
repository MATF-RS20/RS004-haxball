#ifndef SERVER_HPP
#define SERVER_HPP

#include <memory>

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>


class Server : public QTcpServer
{

  //server class should be implemented as singleton class

  Q_OBJECT

public:

  explicit Server(const QHostAddress address, const quint16 port, QObject* parent = nullptr);

  void start();

  void port(quint16 port);
  void hostAddress(QHostAddress address);

  quint16 port() const;

  QHostAddress hostAddress() const;

signals:

public slots:

protected:
  void incomingConnection(int handle);


private:

  QHostAddress m_host_address;
  quint16 m_port;

};

#endif // SERVER_HPP
