#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

#include "game_state_start.hpp"
#include "game_state_main.hpp"
#include "game_state.hpp"
#include "button.hpp"

GameStateStart::GameStateStart(Game* game)
{
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
    //make a vector to contain the two buttons
    std::string Label = "Start";
    std::string Message = "load_game";
    sf::Vector2i currRes = this->game->getResolution();
    sf::Vector2f currPos(currRes.x, currRes.y);
    std::cout << currPos.x << " " << currPos.y << std::endl;
    sf::Vector2f currSize(100.0f, 45.0f);
    Button *startButton = new Button(currPos, currSize, Label, Message); //needs to appear dynamically
    this->buttons.push_back(startButton);
}

void GameStateStart::loadgame()
{
    this->game->background.setTexture(this->game->texmgr.getRef("background_main"), true);
    this->game->background.setScale(
                    float(this->view.getSize().x) / float(this->game->background.getTexture()->getSize().x),
                    float(this->view.getSize().y) / float(this->game->background.getTexture()->getSize().y));
    this->game->pushState(new GameStateMain(this->game));
    return;
}

void GameStateStart::draw(const float dt)
{
    this->game->window.setView(this->view);

    this->game->window.clear(sf::Color::Black);
    this->game->window.draw(this->game->background);


    //Before this happens need to reposition the button if the resolution has changed.
    int butlen = buttons.size();
    for(int i = 0; i < butlen; i++)
    {
        buttons[i]->Draw(this->game->window);
    }

    return;
}

void GameStateStart::update(const float dt)
{
}

void GameStateStart::handleInput()
{
    sf::Event event;


    while(this->game->window.pollEvent(event))
    {
        switch(event.type)
        {
            /* Close the window */
            case sf::Event::Closed:
            {
                game->window.close();
                break;
            }
            /* Logic that happens when the window is resized */
            case sf::Event::Resized:
            {
                float originalHeight = this->view.getSize().y;
                float originalWidth = this->view.getSize().x;

                float scaleHeight = float(event.size.height) / originalHeight;
                float scaleWidth = float(event.size.width) / originalWidth;
                float scale = std::min(scaleHeight, scaleWidth);

                int newWidth = int(originalWidth * scale);
                int newHeight = int(originalHeight * scale);
                this->view.setSize(newWidth, newHeight);
                this->view.setCenter(newWidth / 2, newHeight / 2);

                this->game->window.setSize(sf::Vector2u(uint(newWidth), uint(newHeight)));
                this->game->window.setView(this->view);

                this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0)));
                this->game->background.setScale(
                    float(newWidth) / float(this->game->background.getTexture()->getSize().x),
                    float(newHeight) / float(this->game->background.getTexture()->getSize().y));
                break;
            }
            case sf::Event::KeyPressed:
            {
                if(event.key.code == sf::Keyboard::Escape) {
                    this->game->window.close();
                } else if(event.key.code == sf::Keyboard::Space) {
                    this->loadgame();
                } else if(event.key.code == sf::Keyboard::Equal) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                        this->game->cycleResolution(true);  
                    }
                } else if(event.key.code == sf::Keyboard::Dash) {  
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                        this->game->cycleResolution(false);
                    }
                }
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    //The following vector stores store where the click happened
                    sf::Vector2i clickPos;

                    clickPos.x = event.mouseButton.x;
                    clickPos.y = event.mouseButton.y;

                    int butlen = buttons.size();
                    for(int i = 0; i < butlen; i++)
                    {
                        buttons[i]->isClicked(clickPos);
                    }
                    break;
                }
            }
            default: break;
        }
    }

    return;
}