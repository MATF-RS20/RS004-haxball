#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QGraphicsScene>
#include "clientsocket.hpp"
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
    bool eventFilter(QObject * obj, QEvent * event);
    QGraphicsScene* drawField();
    QGraphicsScene* drawPlayers();
    QGraphicsScene* drawBall();
    void setSocket(std::shared_ptr<ClientSocket> sock);

private slots:
    void on_exit_button_clicked();
    // Slot coordsReady se izvrsava kada se sa servera posalju koordinate svih igraca.
    void coordsReady(QStringList coords);

private:

    void setUpListener();
    void drawAllPlayers();

    Ui::Game *ui;
    QGraphicsScene* scene;
    QSet<int> pressedKeys;

    QHash<int, QPair<int, int>> m_playerCoords;
    QPair<int, int> m_ballCord;

    std::shared_ptr<ClientSocket> m_clientsocket;

};

#endif // GAME_H
