#include "healthbar.hpp"

HealthBar::HealthBar(int max) : maxSize(50.f, 5.f) {
    this->maxHP = max;
    
    this->backBar.setOrigin(this->maxSize / 2.0f);
    this->backBar.setSize(this->maxSize);
    this->backBar.setFillColor(sf::Color::Red);
    
    this->healthBar.setOrigin(0, 0);
    this->healthBar.setSize(this->maxSize);
    this->healthBar.setFillColor(sf::Color::Green);
}

void HealthBar::setMax(int max) {
    this->maxHP = max;
}

void HealthBar::draw(int curHP, sf::Vector2f newPos, sf::RenderWindow& window) {
    this->backBar.setPosition(newPos);
    this->healthBar.setPosition(newPos.x - (maxSize.x / 2), newPos.y - (maxSize.y / 2));
   
    float xScale = ((float) curHP / (float) maxHP) * maxSize.x;

    sf::Vector2f newSize(xScale, this->maxSize.y);
    this->healthBar.setSize(newSize);

    window.draw(this->backBar);
    window.draw(this->healthBar);
}
