#include "game.h"
#include "ui_game.h"
#include "player.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>
#include <QPen>
#include <QTimer>
#include <QObject>
#include <vector>
#include <utility>
#include "clientsocket.hpp"

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();

    // iscrtavanje terena
    scene = drawField();
    // iscrtavanje igraca
    scene = drawPlayers();
    // iscrtavanje lopte
    scene = drawBall();

    ui->view->setScene(scene);
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

void Game::on_exit_button_clicked()
{
    QApplication::exit();
}

QGraphicsScene* Game::drawField()
{
    QGraphicsScene* scene = getScene();
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(5);

    // teren i golovi
    scene->addRect(-50, 175, 50, 150, pen);
    scene->addRect(1000, 175, 50, 150, pen);
    pen.setColor(Qt::white);
    scene->addRect(0, 0, 1000, 500, pen);
    scene->addLine(500, 0, 500, 500,pen);

    // centar
    scene->addEllipse(400, 150, 200, 200,pen);
    // stative
    pen.setColor(Qt::black);
    pen.setWidth(2);
    scene->addEllipse(-10, 165 , 20, 20,pen, QBrush(Qt::white));
    scene->addEllipse(-10, 315, 20, 20,pen, QBrush(Qt::white));
    scene->addEllipse(990, 165, 20, 20,pen, QBrush(Qt::white));
    scene->addEllipse(990, 315, 20, 20,pen, QBrush(Qt::white));
    return scene;
}

QGraphicsScene* Game::drawPlayers()
{
    scene = getScene();
    std::vector<std::pair<int, int>> kordinate;
    kordinate.push_back(std::make_pair(410,250));
    kordinate.push_back(std::make_pair(320,125));
    kordinate.push_back(std::make_pair(400,92));
    for (auto &e : kordinate) {
        Player* player = new Player();
        player->drawPlayer(e.first, e.second);
        scene->addItem(player);
        player->setFlag(QGraphicsItem::ItemIsFocusable);
        player->setFocus();
    }
    return scene;
}


QGraphicsScene* Game::drawBall()
{
    scene = getScene();
    Player* player = new Player();
    player->drawPlayer(480, 230);
    player->setBrush(Qt::white);
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    return scene;
}
