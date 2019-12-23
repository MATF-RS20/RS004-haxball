#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // TODO Connect to server
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_exitButton_clicked()
{
    QApplication::exit();
}

void MainWindow::on_createButton_clicked()
{
    hide();
    game = new Game(this);
    game->show();
}

void MainWindow::on_settingsButton_clicked()
{
    settings = new Settings(this);
    settings->show();
}
