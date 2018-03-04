#include <iostream>
#include "board.hpp"

#include "collider.hpp"

void Board::step(sf::RenderWindow& window)
{
    for (auto unit : units)
    {
        window.draw(unit.body);
        window.draw(unit.range);
    }
    checkCollisions();
}

void Board::addUnit(Unit unit)
{
    this->units.push_back(unit);
}

void Board::checkCollisions()
{
    for (int i = 0; i < this->units.size(); i++)
    {
        for (int j = 0; j < this->units.size(); j++)
        {
            if (j != i)
            {
                UnitCollider firstCollider = units[i].getUnitCollider();
                UnitCollider secondCollider = units[j].getUnitCollider();
                if (firstCollider.checkUnitCollision(secondCollider, 0.0f))
                {
                    std::cout << "unit body collision detected " << i << " " << j << std::endl;
                }

                if (firstCollider.checkRangeCollision(secondCollider))
                {
                    std::cout << "unit range collision detected " << i << " " << j << std::endl;
                    units[i].attack(units[j]);
                }
            }
        }
    }
}
