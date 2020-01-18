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

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);

    setUp();

    // HARDCODE!
    m_me = std::make_shared<Player>(0, 0);
    scene->addItem(m_me.get());
    scene->addItem(new Ball(485,235));
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
    qDebug() << "[coordsReadReady]: Sa servera je stigla poruka: " << coords;
    //Citaju se koordinate lopte.
    //m_ball.setX(coords.takeLast().toDouble());
    //m_ball.setY(coords.takeLast().toDouble());

    // Citaju se koordinate svih igraca i azuriraju se ili dodaju novi u hes mapu.
    for(QStringList::iterator iter = coords.begin(); iter != coords.end(); iter += 3){
        int playerId = iter->toInt();

        qreal x = (iter + 1)->toDouble();
        qreal y = (iter + 2)->toDouble();

        auto player_it = m_players.find(playerId);
        if(player_it != m_players.end()){
            (*player_it)->setX(x);
            (*player_it)->setY(y);
            qDebug() << "[coordsReadReady]: Azuriran je postojeci igrac " << playerId << " na poziciju (" << x <<", " << y <<")";
        }
        else{
            std::shared_ptr<Player> player = std::make_shared<Player>(0, 0);
            player->setX(x);
            player->setY(y);
            scene->addItem(player.get());
            m_players.insert(playerId, player);

            qDebug() << "[coordsReadReady]: Dodat je novi igrac " << playerId << " na poziciju (" << x <<", " << y <<")";
        }
    }
}

void Game::coordsWriteReady()
{
    QByteArray serverRequest;
    const QString protocol = "coords";

    serverRequest.append(protocol + " ")
                 .append(QString::number(m_me->getId()) + " ")
                 .append(QString::number(m_me->x()) + " ")
                 .append(QString::number(m_me->y()) + " ");

    m_clientsocket->getSocket()->write(serverRequest);

    qDebug() << "[coordsWriteReady]: Serveru je poslat zahtev: " << QString(serverRequest);

}


void Game::checkGoal() {
    if(m_me->x() < -20 || m_me->x() > 980) {
       emit onGoal();
       m_me->setX(480);
       m_me->setY(230);
    }
    // m_ball.x() < 20 za loptu(desni gol)
}

void Game::goalWrite() {
    QByteArray serverRequest;
    const QString protocol = "goal";

    // m_ball.x() < 20 za loptu(levi gol)
    if(m_me->x() < -20) {
        serverRequest.append(protocol + " Crveni tim " + " ");
    }
    // m_ball.x() < 20 za loptu(desni gol)
    else if(m_me->x() > 980) {
        serverRequest.append(protocol + " Plavi tim " + " ");
    }
     m_clientsocket->getSocket()->write(serverRequest);

    qDebug() << "[goalWrite]: Serveru je poslat zahtev: " << QString(serverRequest);

}

// Metoda setUpListener registruje signale i njima odgovarajuce slotove i inicijalizuje potrebne komponente.
void Game::setUp()
{
    connect(this, SIGNAL(onPlayerAction()), this, SLOT(coordsWriteReady()));
    connect(this, SIGNAL(onGoal()), this, SLOT(goalWrite()));

    setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    scene = new QGraphicsScene();
    startTimer(1000/60);
    scene = drawField();
    ui->view->setScene(scene);
    setWindowState(Qt::WindowFullScreen);
    installEventFilter(this);
}


std::shared_ptr<Player> Game::getMe() const
{
    return m_me;
}

void Game::setSocket(std::shared_ptr<ClientSocket> sock)
{
    m_clientsocket = sock;
}

bool Game::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type()==QEvent::KeyPress) {
        pressedKeys += (static_cast<QKeyEvent*>(event))->key();
        emit onPlayerAction();
    }
    else if(event->type()==QEvent::KeyRelease){
        pressedKeys -= (static_cast<QKeyEvent*>(event))->key();
        emit onPlayerAction();
    }

    return false;
}


void Game::timerEvent(QTimerEvent *event)
{
    if(pressedKeys.contains(Qt::Key_Left)){
        m_me->accelerateX(-Player::ACCELERATION);
    }
    if(pressedKeys.contains(Qt::Key_Right)){
        m_me->accelerateX(Player::ACCELERATION);
    }
    if(pressedKeys.contains(Qt::Key_Up)){
        m_me->accelerateY(-Player::ACCELERATION);
    }
    if(pressedKeys.contains(Qt::Key_Down)){
        m_me->accelerateY(Player::ACCELERATION);
    }
    if(pressedKeys.contains(Qt::Key_Space)){
        m_me->setPen(QPen(Qt::yellow, 5, Qt::SolidLine));
    }
    else{
        m_me->setPen(QPen(Qt::white, 5, Qt::SolidLine));
    }

    m_me->moveBy(m_me->getSpeedX(), m_me->getSpeedY());

    m_me->slow(Player::SLOWING);
    checkGoal();
}


QGraphicsScene* Game::drawField()
{
    QGraphicsScene* scene = getScene();
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(5);

    // the stadium and goals
    scene->addRect(-50, 175, 50, 150, pen);
    scene->addRect(1000, 175, 50, 150, pen);
    pen.setColor(Qt::white);
    scene->addRect(0, 0, 1000, 500, pen);
    scene->addLine(500, 0, 500, 500,pen);

    // center
    scene->addEllipse(400, 150, 200, 200,pen);
    // goalpost
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
