#ifndef HEALTH_BAR_HPP
#define HEALTH_BAR_HPP

#include <SFML/Graphics.hpp>

class HealthBar {
    public:
        HealthBar(int max);
        sf::RectangleShape backBar;
        sf::RectangleShape healthBar;

        void draw(int curHP, sf::Vector2f newPos, sf::RenderWindow& window);
    private:
        int maxHP;
        sf::Vector2f maxSize;
};

#endif
