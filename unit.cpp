#include <iostream>
#include "unit.hpp"
#include "board.hpp"

Unit::Unit(Board* board, int cost, int attackDamage, float attackRange, int moveSpeed)
{
    this->parentBoard = board;
    this->cost = cost;
    this->attackDamage = attackDamage;
    this->attackRange = attackRange;
    this->moveSpeed = moveSpeed;
    this->shape.setRadius(attackRange);
    this->boundingBox = this->shape.getGlobalBounds();

    this->shape.setFillColor(sf::Color::Green);
}

/*
std::vector<Unit> Unit::findInRange()
{
    break;
}

void Unit::attack()
{
    break;
}
*/

void Unit::updatePos()
{
    this->shape.setPosition(this->pos_x, this->pos_y);
}

void Unit::update()
{
    pos_x = pos_x + 10;
    pos_y = pos_y + 10;
    this->shape.setPosition(pos_x, pos_y);
    this->boundingBox = this->shape.getGlobalBounds();
    //checkUnitCollision();
}
/*
bool Unit::checkUnitCollision()
{
    for (auto unit : this->parentBoard->units)
    {
        sf::FloatRect thisBound = this->shape.getGlobalBounds();

        if (this->boundingBox != &unit->boundingBox)
        {
            if (this->boundingBox.intersects(unit.boundingBox))
            {
                std::cout << "collision" << std::endl;
            }
        }
    }
    return false;
}
*/
