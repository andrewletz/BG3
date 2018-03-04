#include <SFML/Window.hpp>
#include "engine/unit.hpp"
#include "engine/board.hpp"

#include <vector>
#include <iostream>

int main()
{
    Attributes testAttribute;
    testAttribute.cost = 0;
    testAttribute.attackRange = 10.f;
    testAttribute.attackDamage = 0;
    testAttribute.moveSpeed = 0.f;


    sf::RenderWindow window(sf::VideoMode(800, 600), "GameScreen");
    Board gameBoard = Board();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f newPosition;
                newPosition.x = event.mouseButton.x; newPosition.y = event.mouseButton.y;
                Unit newUnit = Unit(&gameBoard, newPosition, testAttribute);
                gameBoard.addUnit(newUnit);
            }
        }

        window.clear();
        gameBoard.step(window);
        window.display();
    }
}
