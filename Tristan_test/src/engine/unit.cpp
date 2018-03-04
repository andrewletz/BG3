#include <iostream>
#include <vector>
#include "unit.hpp"
#include "board.hpp"
#include "collider.hpp"

Unit::Unit(Board* board, sf::Vector2f pos, Attributes attributes)
{
    this->parentBoard = board;
    this->attributes = attributes;
    this->hp = attributes.max_hp;

    sf::Vector2f sizeVec;
    sizeVec.x = 10.0f;
    sizeVec.y = 10.0f;

    this->body.setSize(sizeVec);
    this->body.setOrigin(sizeVec / 2.0f);
    this->body.setPosition(pos);
    
    this->body.setFillColor(sf::Color::Green);
}

void Unit::attack(Unit& target)
{
    target.hp = target.hp - this->attributes.attackDamage;
}
