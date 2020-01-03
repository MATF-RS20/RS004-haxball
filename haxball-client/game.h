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
    QGraphicsScene* drawField();
    QGraphicsScene* drawPlayers();
    QGraphicsScene* drawBall();

private slots:
    void on_exit_button_clicked();

private:
    Ui::Game *ui;
    QGraphicsScene* scene;
    QSet<int> pressedKeys;

};

#endif // GAME_H
