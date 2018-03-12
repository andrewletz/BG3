#include <SFML/Window.hpp>
#include "engine/unit.hpp"
#include "engine/board.hpp"

#include <vector>
#include <iostream>

int main()
{
    Attributes testAttribute1;
    testAttribute1.cost = 0;
    testAttribute1.attackRadius = 100.f;
    testAttribute1.visionRadius = 200.f;
    testAttribute1.attackDamage = 5;
    testAttribute1.moveSpeed = 0.08f;
    testAttribute1.max_hp = 500;

    Attributes testAttribute2;
    testAttribute2.cost = 0;
    testAttribute2.attackRadius = 50.f;
    testAttribute2.visionRadius = 200.f;
    testAttribute2.attackDamage = 1;
    testAttribute2.moveSpeed = 0.05f;
    testAttribute2.max_hp = 500;

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
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    Unit newUnit = Unit(&gameBoard, newPosition, RIGHT, testAttribute1);
                    gameBoard.addUnit(newUnit);
                } else if (event.mouseButton.button == sf::Mouse::Left) 
                { 
                    Unit newUnit = Unit(&gameBoard, newPosition, LEFT, testAttribute2);
                    gameBoard.addUnit(newUnit);
                }
            }
        }

        window.clear();
        gameBoard.step(window);
        window.display();
    }
}
