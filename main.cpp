#include <SFML/Window.hpp>
#include "unit.hpp"
#include "board.hpp"

#include <vector>
#include <iostream>

int main()
{
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
                Unit newUnit = Unit(&gameBoard, 0, 10, float(10), 10);
                newUnit.updatePos(event.mouseButton.x - newUnit.attackRange, event.mouseButton.y - newUnit.attackRange);
                gameBoard.addUnit(newUnit);
            }
        }

        window.clear();
        gameBoard.stepDraw(window);
        window.display();
    }
}
