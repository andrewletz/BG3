#include <iostream>
#include <vector>

#include "board.hpp"
#include "collider.hpp"

void Board::step(sf::RenderWindow& window)
{       
    std::vector<int> dyingUnits;

    checkCollisions();
    for (int i = 0; i < units.size(); i++)
    {
        if (units[i].shouldDie())
        {
            units[i].dying = true;
            dyingUnits.push_back(i);
        }
        units[i].draw(window);
    }

    for (auto unit : dyingUnits)
    {
        units.erase(units.begin() + unit);
    }
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
                    //std::cout << "unit body collision detected " << i << " " << j << std::endl;
                }

                if (firstCollider.checkRangeCollision(secondCollider))
                {
                    //std::cout << "unit range collision detected " << i << " " << j << std::endl;
                    std::cout << "current unit hp = " << units[j].hp << ", new hp = ";
                    units[i].attack(units[j]);
                    std::cout << units[j].hp << std::endl;
                }
            }
        }
    }
}
