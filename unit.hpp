#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>

#include <vector>
#include "board.hpp"

class Board;

class Unit
{
public:

    //AnimationHandler animHandler;
    //sf::Sprite sprite;
  
    Board* parentBoard;

    sf::CircleShape shape;
    sf::FloatRect boundingBox;

    bool isMoving;

    unsigned int cost;
    unsigned int attackDamage;
    unsigned int attackRange;
    unsigned int moveSpeed;
    
    unsigned int pos_x = 0;
    unsigned int pos_y = 0;

    std::vector<Unit> findInRange();
    void attack();
    void update();
    void updatePos();
    bool checkUnitCollision();

    Unit(Board* board, int, int, float, int);
    ~Unit() {};
};

#endif
