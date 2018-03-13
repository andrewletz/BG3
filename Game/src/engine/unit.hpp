#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include <stack>

#include "board.hpp"
#include "collider.hpp"
#include "animation_handler.hpp"


enum Teams { LEFT, RIGHT, NONE };
enum Action { DYING, MARCH, MOVE, ATTACK, PAUSE };

typedef struct{
    unsigned cost;
    unsigned attackDamage;
    int max_hp;
    float attackRadius;
    float visionRadius;
    float moveSpeed;
} Attributes;


class Board;

class Unit
{
public:
    Unit(Board* board, sf::Texture* texture, sf::Vector2f pos, Teams team, Attributes attributes);
    ~Unit() {};

    AnimationHandler animHandler;
    sf::RectangleShape body;
 
    std::stack<Action> actionStack;

    //sf::RectangleShape body; 
    sf::CircleShape vision;
    sf::CircleShape range;

    Attributes attributes;
    Teams team;

    Collider getCollider() { return Collider(body, range, vision); };
    sf::Vector2f getPosition() { return body.getPosition(); };

    void start();
    void pause();
    void reset();
    void resume();
    
    void setTarget(Unit* target) { this->target = target; };
    bool hasTarget();
    bool shouldDie();
    bool isLiving();
    bool targetInRange();
    void step();
    void draw(sf::RenderWindow& window);
private:
    Board* parentBoard;
    
    int hp;
    sf::Vector2f originalPos;
    float moveSpeed;
    bool dying = false;
    Unit* target = nullptr;
    
    void attack(Unit* target) { target->hp = target->hp - this->attributes.attackDamage; };
};

#endif