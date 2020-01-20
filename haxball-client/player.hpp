#ifndef PLAYER
#define PLAYER

#include <QGraphicsRectItem>

#include <QPen>
#include <QGraphicsScene>
#include <clientsocket.hpp>
#include <QTcpSocket>



class Player : public QGraphicsEllipseItem{

public:
    Player() = default;
    Player(const qreal x, const qreal y,
           const int team,
           const qreal diameter = 40,
           const QColor& circleColor = QColor(Qt::red),
           const QColor& circularColor = QColor(Qt::white),
           const int circularWidth = 5);


    int getId() const;
    void setId(int value);

    qreal getSpeedX() const;
    qreal getSpeedY() const;

    void accelerateX(qreal acc);
    void accelerateY(qreal acc);
    void slow(qreal s);

    static const qreal MAX_SPEED;
    static const qreal ACCELERATION;
    static const qreal SLOWING;


private:
    int m_id;
    qreal m_speedX = 0;
    qreal m_speedY = 0;
    int team;
};

#endif // PLAYER

