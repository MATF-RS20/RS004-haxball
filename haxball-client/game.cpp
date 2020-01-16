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
    m_players.insert(123, std::make_shared<Player>(100, 100));
    m_players.insert(124, std::make_shared<Player>(150, 150));
    m_players.insert(125, std::make_shared<Player>(200, 200));
    drawAllPlayers();
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
    //Citaju se koordinate lopte.
    m_ball.setX(coords.takeLast().toDouble());
    m_ball.setY(coords.takeLast().toDouble());

    // Citaju se koordinate svih igraca i azuriraju se ili dodaju novi u hes mapu.
    for(QStringList::iterator iter = coords.begin(); iter != coords.end(); iter += 3){
        int playerId = iter->toInt();

        qreal x = (iter + 1)->toDouble();
        qreal y = (iter + 2)->toDouble();

        auto player_it = m_players.find(playerId);
        if(player_it != m_players.end()){
            (*player_it)->setX(x);
            (*player_it)->setY(y);
        }
        else{
            m_players.insert(playerId, std::make_shared<Player>(x, y));
        }
    }

    drawAllPlayers();
}

void Game::coordsWriteReady()
{
 return;
}

// Metoda setUpListener registruje signale i njima odgovarajuce slotove.
void Game::setUpListener()
{
    // Objekat klase clientsocket emituje signal onCoords(QStringList) kada od servera dobije koordinate igraca.
    connect(m_clientsocket.get(), SIGNAL(onCoords(QStringList)), this, SLOT(coordsReadReady(QStringList)));
}

// Metoda drawAllPlayers prolazi kroz celu hes mapu i za svaki par koordinata poziva funkciju za iscrtavanje igraca.
void Game::drawAllPlayers()
{
    QHash<int, std::shared_ptr<Player>>::iterator i = m_players.begin();
    while(i != m_players.end()){
        (*i)->draw(scene);
        ++i;
    }
}

void Game::setSocket(std::shared_ptr<ClientSocket> sock)
{
    m_clientsocket = sock;
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
