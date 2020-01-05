#ifndef PLAYER
#define PLAYER

#include <QGraphicsRectItem>
#include <QPen>

#include <QTcpSocket>

enum Actions{
   key_left = 1,
   key_right = 2,
   key_up = 3,
   key_down = 4,
   shot = 5
};

class Player: public QGraphicsEllipseItem{

public:
    Player();
    void keyPressEvent(QKeyEvent * event);
    Player* drawPlayer(int x, int y);
    void set_playerX(int x);
    void set_playerY(int y);
    const char* actionToString(Actions a);

private:
    int player_x;
    int player_y;
    Player* player;
};

#endif // PLAYER

