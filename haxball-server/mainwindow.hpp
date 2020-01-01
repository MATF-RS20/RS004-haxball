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

  void setUpListeners();

public slots:
  void previewLogData(QString & new_data);

private slots:
  void on_actionSettings_triggered();
  void on_startButton_clicked();
  void on_stopButton_clicked();
  void on_restartButton_clicked();
  void on_exitButton_clicked();

private:
  Ui::MainWindow *ui;
  DialogSettings *ui_dialog;

  std::shared_ptr<Server> m_server;
  std::string m_logger;

};
#endif // MAINWINDOW_HPP
