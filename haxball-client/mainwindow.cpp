#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
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
