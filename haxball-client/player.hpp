#ifndef PLAYER
#define PLAYER

#include <QGraphicsRectItem>

#include <QPen>
#include <QGraphicsScene>

#include <QTcpSocket>

/* ============================= KOMSA =============================
enum Actions{
   key_left = 1,
   key_right = 2,
   key_up = 3,
   key_down = 4,
   shot = 5
};
*/


class Player : public QGraphicsEllipseItem{

public:
    Player() = default;
    Player(const qreal x, const qreal y,
           const qreal diameter = 40,
           const QColor& circleColor = QColor(Qt::red),
           const QColor& circularColor = QColor(Qt::white),
           const int circularWidth = 5);


    void draw(QGraphicsScene* scene);

/* ============================= KOMSA =============================
    void keyPressEvent(QKeyEvent * event);
    Player* drawPlayer(int x, int y);
    const char* actionToString(Actions a);
*/

private:

};

#endif // PLAYER

