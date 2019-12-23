#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "game.h"
#include "settings.h"
#include "clientsocket.hpp"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // TODO SIGNAL - Connect to server

private slots:
    void on_exitButton_clicked();
    void on_createButton_clicked();

    void on_settingsButton_clicked();

private:
    Ui::MainWindow *ui;
    Game* game;
    Settings* settings;
    ClientSocket* clientsocket;
};
#endif // MAINWINDOW_HPP
