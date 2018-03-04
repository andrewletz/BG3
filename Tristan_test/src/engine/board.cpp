#include <iostream>
#include "board.hpp"

#include "collider.hpp"

void Board::step(sf::RenderWindow& window)
{
    for (auto unit : units)
    {
        window.draw(unit.body);
    }
    checkUnitRange();
}

void Board::addUnit(Unit unit)
{
    this->units.push_back(unit);
}

void Board::checkUnitRange()
{
    for (int i = 0; i < this->units.size(); i++)
    {
        for (int j = 0; j < this->units.size(); j++)
        {
            if (j != i)
            {
                Collider secondCollider = units[j].getCollider();
                if (units[i].getCollider().checkCollision(secondCollider, 1.0f))
                {
                    std::cout << "collision detected " << i << " " << j << std::endl;
                    units[i].attack(units[j]);
                }
            }
        }
    }
}
