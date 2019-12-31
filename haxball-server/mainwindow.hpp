#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <server.hpp>

#include "dialogsettings.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  std::shared_ptr<Server> server();

private slots:

  /******************************************************************************
   *
   * TCP Server
   *
   ******************************************************************************/
  void logger(const std::string & s);
  std::string logger() const;


  void on_actionSettings_triggered();

private:
  Ui::MainWindow *ui;
  DialogSettings *ui_dialog;

  std::shared_ptr<Server> m_server;
  std::string m_logger;
};
#endif // MAINWINDOW_HPP
