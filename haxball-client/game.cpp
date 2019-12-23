#include "game.h"
#include "ui_game.h"
#include <QGraphicsScene>


Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->view->setScene(scene);

    setWindowFlag(Qt::FramelessWindowHint);
    setWindowState(Qt::WindowFullScreen);
}

Game::~Game()
{
    delete ui;
}

QGraphicsScene *Game::getScene() const
{
    return scene;
}
