#ifndef DIALOGSETTINGS_HPP
#define DIALOGSETTINGS_HPP

#include <QDialog>
#include <QHostAddress>

#include "server.hpp"

namespace Ui {
  class DialogSettings;
}

class DialogSettings : public QDialog
{
  Q_OBJECT

public:
  explicit DialogSettings(std::shared_ptr<Server> server_ptr, QWidget *parent = nullptr);
  ~DialogSettings();

private slots:
  void on_buttonBox_accepted();

private:
  Ui::DialogSettings *ui;

  std::shared_ptr<Server> m_server_ptr;
  QHostAddress m_host_address;
  quint16 m_port;

};

#endif // DIALOGSETTINGS_HPP
