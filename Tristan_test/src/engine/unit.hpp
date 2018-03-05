#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "board.hpp"
#include "collider.hpp"


enum Team { LEFT, RIGHT, NONE };

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
    Team team;

    bool hasTarget = false;
    Unit* target;

    UnitCollider getUnitCollider() { return UnitCollider(body, range); };
    void attack(Unit& target) { target.hp = target.hp - this->attributes.attackDamage; };
    void setTarget(Unit* target) { this->target = target; };
    bool shouldDie();
    void step(sf::RenderWindow& window);

    Unit(Board* board, sf::Vector2f pos, Team team, Attributes attributes);
    ~Unit() {};
};

#endif
