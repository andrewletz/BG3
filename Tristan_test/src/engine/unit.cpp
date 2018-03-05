#include <iostream>
#include <vector>
#include "unit.hpp"
#include "board.hpp"
#include "collider.hpp"

Unit::Unit(Board* board, sf::Vector2f pos, Attributes attributes)
{
    // setup member vars
    this->parentBoard = board;
    this->attributes = attributes;
    this->hp = attributes.max_hp;

    // TODO remove this temporary sizing
    sf::Vector2f sizeVec;
    sizeVec.x = 10.0f;
    sizeVec.y = 10.0f;

    // setup body rectangle
    this->body.setSize(sizeVec);
    this->body.setOrigin(sizeVec / 2.0f);
    this->body.setPosition(pos);
  
    // setup range circle
    this->range.setRadius(attributes.attackRadius);
    this->range.setOrigin(attributes.attackRadius, attributes.attackRadius);
    this->range.setPosition(pos);

    // color
    sf::Color rColor(0, 255, 0);
    rColor.a = 100;
    this->body.setFillColor(sf::Color::Red);
    this->range.setFillColor(rColor);
}

void Unit::attack(Unit& target)
{
    target.hp = target.hp - this->attributes.attackDamage;
}

bool Unit::shouldDie()
{
    if (hp <= 0) return true;
    return false;
}

void Unit::draw(sf::RenderWindow& window)
{
    window.draw(body);
    window.draw(range);
}
