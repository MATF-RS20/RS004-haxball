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

  //getters
  std::shared_ptr<Server> server();

  void setUpListeners();
  void setUpLoggingPreview();

public slots:
  void previewLogData(QString & new_data);

private slots:
  void on_actionSettings_triggered();
  void on_startButton_clicked();
  void on_stopButton_clicked();
  void on_restartButton_clicked();
  void on_exitButton_clicked();

private:
  //fields
  Ui::MainWindow *ui;
  DialogSettings *ui_dialog;

  std::shared_ptr<Server> m_server_ptr;
  std::string m_logger;

  //methods

};
#endif // MAINWINDOW_HPP
