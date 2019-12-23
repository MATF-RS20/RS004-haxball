#include "game.h"
#include "ui_game.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->view->setScene(scene);

    setWindowFlag(Qt::FramelessWindowHint);
    setWindowState(Qt::WindowFullScreen);

    this->installEventFilter(this);
}

Game::~Game()
{
    delete ui;
}

QGraphicsScene *Game::getScene() const
{
    return scene;
}

bool Game::eventFilter(QObject * , QEvent * event){
    if(event->type() == QEvent::KeyPress){
        pressedKeys += static_cast<QKeyEvent *>(event)->key();
        //qDebug() << "Key press!";
    }
    else if(event->type() == QEvent::KeyRelease){
         pressedKeys -= static_cast<QKeyEvent *>(event)->key();
         //qDebug() << "Key relase!";
    }

    qDebug() << pressedKeys.size();

    return false;
}
