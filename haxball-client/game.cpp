#include "game.h"
#include "ui_game.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QPixmap>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QFont>
#include <QKeyEvent>
#include <QDebug>

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();

    // teren i golovi
    rect1 = new QGraphicsRectItem(0, 0, 1000, 500);
    rect2 = new QGraphicsRectItem(-50, 175, 50, 150);
    rect3 = new QGraphicsRectItem(1000, 175, 50, 150);
    rect4 = new QGraphicsRectItem(500, 0, 0, 500);

    // centar terena
    circle1 = new QGraphicsEllipseItem(400, 150, 200, 200);
    // stative na golovi
    circle2 = new QGraphicsEllipseItem(-12.5, 162.5, 25, 25);
    circle3 = new QGraphicsEllipseItem(-12.5, 312.5, 25, 25);
    circle4 = new QGraphicsEllipseItem(987.5, 162.5, 25, 25);
    circle5 = new QGraphicsEllipseItem(987.5, 312.5, 25, 25);

    circle1->setStartAngle(0);
    circle1->setSpanAngle(360*16);

    circle2->setStartAngle(0);
    circle2->setSpanAngle(360*16);
    circle2->setBrush(QBrush(Qt::white));

    circle3->setStartAngle(0);
    circle3->setSpanAngle(360*16);
    circle3->setBrush(QBrush(Qt::white));

    circle4->setStartAngle(0);
    circle4->setSpanAngle(360*16);
    circle4->setBrush(QBrush(Qt::white));

    circle5->setStartAngle(0);
    circle5->setSpanAngle(360*16);
    circle5->setBrush(QBrush(Qt::white));

    QPixmap pixmapItem("./img/trava_za_teren.png");
    QPixmap pixmapItems = pixmapItem.scaled(QSize(1000,500),  Qt::IgnoreAspectRatio);

    scene->addPixmap(pixmapItems);
    scene->addItem(rect1);
    scene->addItem(rect2);
    scene->addItem(rect3);
    scene->addItem(rect4);
    scene->addItem(circle1);
    scene->addItem(circle2);
    scene->addItem(circle3);
    scene->addItem(circle4);
    scene->addItem(circle5);

    QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget(rect1);
    QLabel* label1 = new QLabel();
    QFont f("Arial", 35);
    label1->setFont(f);
    label1->setText("Player 1");
    proxy->setWidget(label1);
    proxy->setPos(0, -120);

    QGraphicsProxyWidget* proxy2 = new QGraphicsProxyWidget(rect1);
    QLabel* label2 = new QLabel();
    label2->setFont(f);
    label2->setText("Player 2");
    proxy2->setWidget(label2);
    proxy2->setPos(830, -120);

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
