#ifndef SERVER_HPP
#define SERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

#include <memory>


class Server : public QTcpServer
{

  Q_OBJECT

public:

  explicit Server(QObject* parent = nullptr);
  explicit Server(const QHostAddress address, const quint16 port, QObject* parent = nullptr);

  //server api
  void start();
  void stop();
  void restart();

  //setters
  void port(quint16 port);
  void hostAddress(QHostAddress address);
  void writeToLog(QString & s);

  //getters
  quint16 port() const;
  QHostAddress hostAddress() const;
  QString & readFromLog();

signals:
  void newLogData(QString & new_data);

protected:
  void incomingConnection(qintptr handle);

private:
  //methodes
  void setUpListeners();

  //fields
  QHostAddress m_host_address;
  quint16 m_port;
  QString m_log;

};

#endif // SERVER_HPP
