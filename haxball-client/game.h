#ifndef GAME_H
#define GAME_H

#include <QDialog>
#include <QGraphicsScene>

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

private:
    Ui::Game *ui;
    QGraphicsScene* scene;

};

#endif // GAME_H
