#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QGraphicsScene>
#include <QSet>

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

private:
    Ui::Game *ui;
    QGraphicsScene* scene;
    QGraphicsRectItem* rect1;
    QGraphicsRectItem* rect2;
    QGraphicsRectItem* rect3;
    QGraphicsRectItem* rect4;
    QGraphicsEllipseItem* circle1;
    QGraphicsEllipseItem* circle2;
    QGraphicsEllipseItem* circle3;
    QGraphicsEllipseItem* circle4;
    QGraphicsEllipseItem* circle5;
    QSet<int> pressedKeys;

};

#endif // GAME_H
