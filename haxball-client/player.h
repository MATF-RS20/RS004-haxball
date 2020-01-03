#ifndef PLAYER
#define PLAYER

#include <QGraphicsRectItem>
#include <QPen>


class Player: public QGraphicsEllipseItem{

public:
    Player();
    void keyPressEvent(QKeyEvent * event);
    Player* drawPlayer(int x, int y);
    void set_playerX(int x);
    void set_playerY(int y);
private:
    int player_x;
    int player_y;
    Player* player;
};

#endif // PLAYER

