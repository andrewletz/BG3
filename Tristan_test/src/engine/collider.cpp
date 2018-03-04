#include "collider.hpp"

Collider::Collider(sf::RectangleShape& body) :
    body(body)
{
}

Collider::~Collider()
{
}

bool Collider::checkCollision(Collider & other, float push)
{
    sf::Vector2f otherPosition = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f thisPosition = getPosition();
    sf::Vector2f thisHalfSize = getHalfSize();

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;

    float intersectionX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectionY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectionX < 0.0f && intersectionY < 0.0f)
    {
        push = std::min(std::max(push, 0.0f), 1.0f);
        if (intersectionX > intersectionY)
        {
            if (deltaX > 0.0f)
            {
                move(intersectionX * (1.0f - push), 0.0f);
                other.move(-intersectionX * push, 0.0f);
            }
            else
            {
                move(-intersectionX * (1.0f - push), 0.0f);
                other.move(intersectionX * push, 0.0f);
            }
        }
        else
        {
            if (deltaY > 0.0f)
            {
                move(0.0f, intersectionY * (1.0f - push));
                other.move(0.0f, -intersectionY * push);
            }
            else
            {
                move(0.0f, -intersectionY * (1.0f - push));
                other.move(0.0f, intersectionY * push);
            }
        }
            
        return true;
    }

    return false;
}
