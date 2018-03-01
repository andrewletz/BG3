#include <iostream>
#include "board.hpp"

void Board::stepDraw(sf::RenderWindow& window)
{
    for (auto unit : units)
    {
        unit.update();
        window.draw(unit.shape);
    }
}

void Board::addUnit(Unit unit)
{
    this->units.push_back(unit);
}
