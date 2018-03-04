#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "board.hpp"
#include "collider.hpp"

typedef struct{
    unsigned cost;
    unsigned max_hp;
    unsigned attackDamage;
    float attackRange;
    float moveSpeed;
} Attributes;


class Board;

class Unit
{
public:

    //AnimationHandler animHandler;
    //sf::Sprite sprite;
  
    Board* parentBoard;

    sf::RectangleShape body; 

    Attributes attributes;
    unsigned hp;

    void attack(Unit& target);
    Collider getCollider() { return Collider(body); };

    Unit(Board* board, sf::Vector2f pos, Attributes attributes);
    ~Unit() {};
};

#endif
