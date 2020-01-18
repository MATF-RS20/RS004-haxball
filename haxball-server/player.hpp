#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QObject>
#include <memory>


class Player
{

public:

Player() = default;

~Player() = default;

explicit Player(qintptr id, std::string name, double x0 = 0, double y0 = 0);

Player(const Player & other);

Player(const std::shared_ptr<Player>& other);

Player & operator= (const Player & other);

Player(Player && other) noexcept;

Player & operator= (Player && other) noexcept;

QString toString() const;

std::string name() const;

qintptr id() const;

void setXY(double x, double y);


private:

qintptr m_id;
double m_x0, m_y0;
std::string  m_name;

};

#endif // PLAYER_HPP
