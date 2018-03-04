#include "collider.hpp"
#include <cmath>
#include <iostream>

UnitCollider::UnitCollider(sf::RectangleShape& body, sf::CircleShape& range) :
    body(body), range(range)
{
}

UnitCollider::~UnitCollider()
{
}

bool UnitCollider::checkUnitCollision(UnitCollider & other, float push)
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

bool UnitCollider::checkRangeCollision(UnitCollider & other)
{

    /* CAN BE MADE MORE SIMPLE
    // loop through points in this units range circle
    for (int i = 0; i < this->range.getPointCount(); i++)
    {
        sf::Vector2f cPoint = other.range.getPoint(i);
        sf::Vector2f rPos = getPosition();
        sf::Vector2f half = getHalfSize();

        if (cPoint.x < (rPos.x + half.x) || cPoint.x > (rPos.x - half.x)) {
            if (cPoint.y < (rPos.y + half.y) || cPoint.y > (rPos.y - half.y)) {
                return true;
            }
        }
    }
    */
    sf::Vector2f thisPos = range.getPosition();
    sf::Vector2f otherPos = other.body.getPosition();
    if (pow((otherPos.x - thisPos.x), 2.0f) + pow((otherPos.y - thisPos.y), 2.0f) < pow(this->range.getRadius(), 2.0f))
        return true;
    
    return false;
}
