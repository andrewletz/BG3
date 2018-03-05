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
    float attackRadius;
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
    sf::CircleShape range;

    Attributes attributes;
    unsigned hp;
    bool dying = false;

    UnitCollider getUnitCollider() { return UnitCollider(body, range); };
    void attack(Unit& target);
    bool shouldDie();
    void draw(sf::RenderWindow& window);

    Unit(Board* board, sf::Vector2f pos, Attributes attributes);
    ~Unit() {};
};

#endif
