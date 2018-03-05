#include <iostream>
#include <vector>

#include "board.hpp"
#include "collider.hpp"

void Board::step(sf::RenderWindow& window)
{   
    // contains units that will be purged from game
    std::vector<int> dyingUnits;

    // loop through and step each unit
    for (int i = 0; i < units.size(); i++)
    {
        if (units[i].shouldDie())
        {
            units[i].dying = true;
            dyingUnits.push_back(i);
        }
        units[i].step(window);
    }

    // check for unit and range collision, after movement
    checkCollisions();
   
    // purge marked units
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
                    units[i].attack(units[j]);
                }
            }
        }
    }
}
