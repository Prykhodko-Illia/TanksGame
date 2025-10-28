#pragma once
#include <utility>

class ITank {
public:
    using intPair = std::pair<int, int>;

    ITank(int health, int damage);
    virtual ~ITank() = default;
    virtual bool takeDamage(int amount) = 0;
    // virtual void shoot() = 0;

    void move(intPair const &moveVector);

    int getHealth() const;
    void setHealth(int value);

    int getDamage() const;
    void setDamage(int value);
    intPair getPosition() const;

private:
    int m_health = 0;
    int m_damage = 0;

    intPair m_position{};
};
