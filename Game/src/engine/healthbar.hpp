#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#include <SFML/Graphics.hpp>

class HealthBar {
    public:
        HealthBar(int max);
        sf::RectangleShape backBar;
        sf::RectangleShape healthBar;

        int maxHP = 100;
        void draw(int curHP, sf::Vector2f newPos, sf::RenderWindow& window);
        void setMax(int max);
    private:
        sf::Vector2f maxSize;
};

#endif
