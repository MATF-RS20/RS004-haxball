#ifndef SERVER_HPP
#define SERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>


class Server : public QTcpServer
{

  Q_OBJECT

public:

  explicit Server(QHostAddress host, quint16 port, QObject* parent = nullptr);

  void start();

signals:

public slots:

protected:
  void handle_connection(int handle);

private:

  QHostAddress m_host;
  quint16 m_port;

};

#endif // SERVER_HPP
