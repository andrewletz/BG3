#include "healthbar.hpp"

HealthBar::HealthBar(int maxHP) : maxSize(30.f, 5.f) {
    this->maxHP = maxHP;

    this->backBar.setOrigin(this->maxSize / 2.0f);
    this->backBar.setSize(this->maxSize);
    this->backBar.setFillColor(sf::Color::Red);
    
    this->healthBar.setOrigin(0, 0);
    this->healthBar.setSize(this->maxSize);
    this->healthBar.setFillColor(sf::Color::Green);
}

void HealthBar::draw(int curHP, sf::Vector2f newPos, sf::RenderWindow& window) {
    this->backBar.setPosition(newPos);
    this->healthBar.setPosition(newPos.x - (this->maxSize.x / 2), newPos.y - (this->maxSize.y / 2));
    
    float xScale = (curHP / this->maxHP) * this->maxSize.x;

    sf::Vector2f newSize(xScale, this->maxSize.y);
    this->healthBar.setSize(newSize);

    window.draw(this->backBar);
    window.draw(this->healthBar);
}
