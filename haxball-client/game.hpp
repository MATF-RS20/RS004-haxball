#ifndef GAME_H
#define GAME_H

#include "clientsocket.hpp"
#include "player.hpp"
#include "ball.hpp"

#include <QDialog>
#include <QGraphicsScene>
#include <QSet>
#include <QMap>
#include <QPair>


namespace Ui {
class Game;
}

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    QGraphicsScene* getScene() const;
    QGraphicsScene* drawField();
    QGraphicsScene* drawPlayers();
    QGraphicsScene* drawBall();
    void setSocket(std::shared_ptr<ClientSocket> sock);

    QGraphicsScene* drawPlayer(int x, int y);

    bool eventFilter(QObject * obj, QEvent * event);
    void timerEvent(QTimerEvent* event);
    void checkGoal();
    std::shared_ptr<Player> getMe() const;

signals:
    void onPlayerAction();
    void onGoal();

private slots:
    void on_exit_button_clicked();
    // Slot coordsReady se izvrsava kada se sa servera posalju koordinate svih igraca.
    void coordsReadReady(QStringList coords);
    void coordsWriteReady();
    void goalWrite();

private:

    void setUp();

    Ui::Game *ui;
    QGraphicsScene* scene;

    QHash<int, std::shared_ptr<Player>> m_players;
    Ball m_ball;
    std::shared_ptr<Player> m_me;
    QSet<int> pressedKeys;

    std::shared_ptr<ClientSocket> m_clientsocket;

};

#endif // GAME_H
