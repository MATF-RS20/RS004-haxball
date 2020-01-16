#include "game.hpp"
#include "ui_game.h"
#include "player.hpp"
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
#include <QStringList>

const qreal MOVE_STEP = 5.0;

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::FocusPolicy::StrongFocus);

    scene = new QGraphicsScene();


    // iscrtavanje terena
    scene = drawField();

    ui->view->setScene(scene);
    setWindowState(Qt::WindowFullScreen);
    this->installEventFilter(this);

/*
    // iscrtavanje igraca
    scene = drawPlayers();
    // iscrtavanje lopte
    scene = drawBall();



*/

    setUpListener();

    // HARDCODE!
    m_me = std::make_shared<Player>(0, 0);
    scene->addItem(m_me.get());
}

Game::~Game()
{
    delete ui;
}

QGraphicsScene *Game::getScene() const
{
    return scene;
}


void Game::on_exit_button_clicked()
{
    QApplication::exit();
}

// Slot coordsReady se izvrsava kada se sa servera posalju koordinate.
// Koordinate se dobijaju u formatu: x_ball y_ball id_player1 x1 y1 id_player2 x2 y2 ...
void Game::coordsReadReady(QStringList coords)
{
    qDebug() << "[coordsReadReady]";
    //Citaju se koordinate lopte.
    //m_ball.setX(coords.takeLast().toDouble());
    //m_ball.setY(coords.takeLast().toDouble());

    // Citaju se koordinate svih igraca i azuriraju se ili dodaju novi u hes mapu.
    for(QStringList::iterator iter = coords.begin(); iter != coords.end(); iter += 3){
        int playerId = iter->toInt();

        qreal x = (iter + 1)->toDouble();
        qreal y = (iter + 2)->toDouble();

        qDebug() << "x: " << x << "  y: " << y;

        auto player_it = m_players.find(playerId);
        if(player_it != m_players.end()){
            (*player_it)->setX(x);
            (*player_it)->setY(y);
        }
        else{
            std::shared_ptr<Player> player = std::make_shared<Player>(0, 0);
            player->setX(x);
            player->setY(y);
            scene->addItem(player.get());
            m_players.insert(playerId, player);
        }
    }
}

void Game::coordsWriteReady()
{
    qDebug() << "coordsWriteReady";

    QByteArray serverRequest;
    const QString protocol = "coords";

    serverRequest.append(protocol + " ")
                 .append(QString::number(m_me->getId()) + " ")
                 .append(QString::number(m_me->x()) + " ")
                 .append(QString::number(m_me->y()) + " ");

    m_clientsocket->getSocket()->write(serverRequest);

}

// Metoda setUpListener registruje signale i njima odgovarajuce slotove.
void Game::setUpListener()
{
    connect(this, SIGNAL(onPlayerAction()), this, SLOT(coordsWriteReady()));
}


std::shared_ptr<Player> Game::getMe() const
{
    return m_me;
}

void Game::setSocket(std::shared_ptr<ClientSocket> sock)
{
    m_clientsocket = sock;
}

// TODO: Resiti ukoso kretanje
void Game::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    switch(key){
        case Qt::Key_Up: m_me->setY(m_me->y() - MOVE_STEP); break;
        case Qt::Key_Down: m_me->setY(m_me->y() + MOVE_STEP); break;
        case Qt::Key_Left: m_me->setX(m_me->x() - MOVE_STEP); break;
        case Qt::Key_Right: m_me->setX(m_me->x() + MOVE_STEP); break;
    }

    emit onPlayerAction();
}

void Game::keyReleaseEvent(QKeyEvent *event)
{

}




QGraphicsScene* Game::drawField()
{
    QGraphicsScene* scene = getScene();
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(5);

    // teren i golovi
    scene->addRect(-50, 175, 50, 150, pen);
    scene->addRect(1000, 175, 50, 15
                   , pen);
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

/* ============================= KOMSA =============================

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
        //player->setFlag(QGraphicsItem::ItemIsFocusable);
        //player->setFocus();
    }
    Player* player = new Player();
    player->drawPlayer(300, 200);
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    return scene;
}


QGraphicsScene* Game::drawBall()
{
    scene = getScene();
    Player* player = new Player();
    player->drawPlayer(480, 230);
    player->setBrush(Qt::white);
    scene->addItem(player);
    //player->setFlag(QGraphicsItem::ItemIsFocusable);
    // player->setFocus();
    return scene;
}

*/
