#ifndef BOARD_HPP
#define BOARD_HPP

#include "unit.hpp"

#include <vector>

class Unit;

class Board
{
public:
    std::vector<Unit> units;
    // background of some type

    void step(sf::RenderWindow& window);
    void addUnit(Unit unit);
    void checkCollisions();

    Board() {};
    ~Board() {};
};

#endif
