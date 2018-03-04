#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <SFML/Graphics.hpp>

class UnitCollider
{
public:
    UnitCollider(sf::RectangleShape& body, sf::CircleShape& range);
    ~UnitCollider();

    void move(float dx, float dy) { body.move(dx, dy); }

    bool checkRangeCollision(UnitCollider& other);
    bool checkUnitCollision(UnitCollider& other, float push);
    sf::Vector2f getPosition() { return body.getPosition(); }
    sf::Vector2f getHalfSize() { return body.getSize() / 2.0f; }

private:
    sf::RectangleShape& body;
    sf::CircleShape& range;
};

#endif
