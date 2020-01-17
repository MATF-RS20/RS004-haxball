#include "dialogsettings.hpp"
#include "ui_dialogsettings.h"

#include <string>

DialogSettings::DialogSettings(std::shared_ptr<Server> server_ptr, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DialogSettings)
{
  ui->setupUi(this);

  //get singleton server instance
  m_server_ptr =  Server::instance(QHostAddress::LocalHost, 3333, this);

  //setup current host addres and port
  auto address = server_ptr->hostAddress().toString();
  auto port = server_ptr->port();

  ui->HostAddressTextEdit->setPlainText(address);
  ui->hostPortTextEdit->appendPlainText(QString::number(port));

}

DialogSettings::~DialogSettings()
{
  delete ui;
}

void DialogSettings::on_buttonBox_accepted()
{
  auto curr_address = m_server_ptr->hostAddress();
  auto curr_port = m_server_ptr->port();

  auto curr_address_str = curr_address.toString();
  auto curr_port_str = QString::number(curr_port);

  auto host_addr = ui->HostAddressTextEdit->toPlainText();
  auto host_port = ui->hostPortTextEdit->toPlainText();

  if(curr_address_str != host_addr || curr_port_str != host_port)
    {
      //FIXME: Restart serve not work

      if(m_server_ptr->isListening())
      {
         m_server_ptr->close();
      }

      QHostAddress qa(host_addr);
      quint16 port = host_port.toShort();

      m_server_ptr->hostAddress(qa);
      m_server_ptr->port(port);
      m_server_ptr->start();
    }

}
