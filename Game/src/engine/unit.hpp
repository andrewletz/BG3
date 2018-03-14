#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include <stack>

#include "collider.hpp"
#include "animation_handler.hpp"
#include "global_enum.hpp"

enum Action { DYING, MARCH, MOVE, ATTACK, PAUSE };

typedef struct{
    unsigned cost;
    unsigned attackDamage;
    int max_hp;
    float attackRadius;
    float visionRadius;
    float moveSpeed;
} Attributes;

class Unit
{
public:
    Unit(sf::Texture* texture, sf::Vector2f pos, Enums::Teams team, Attributes attributes);
    ~Unit() {};

    AnimationHandler animHandler;
 
    std::stack<Action> actionStack;

    sf::RectangleShape body; 
    sf::CircleShape vision;
    sf::CircleShape range;

    Attributes attributes;
    Enums::Teams team;

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
    bool advanceTarget();
    bool step();
    void draw(sf::RenderWindow& window);

private:
    int hp;
    sf::Vector2f originalPos;
    float moveSpeed;
    bool dying = false;
    Unit* target = nullptr;
    
    void attack(Unit* target) { target->hp = target->hp - this->attributes.attackDamage; };
};

#endif
