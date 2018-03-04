#include <SFML/Graphics.hpp>
#include <algorithm>

#include "game_state_start.hpp"
#include "game_state_main.hpp"
#include "game_state.hpp"

GameStateStart::GameStateStart(Game* game)
{
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
}

void GameStateStart::loadgame()
{
    this->game->pushState(new GameStateMain(this->game));

    return;
}

void GameStateStart::draw(const float dt)
{
    this->game->window.setView(this->view);

    this->game->window.clear(sf::Color::Black);
    this->game->window.draw(this->game->background);

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
            /* Resize the window */
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
                this->view.setCenter(newWidth, newHeight);
                if (event.size.height != originalHeight && event.size.width != originalWidth) {
                    this->game->window.create(sf::VideoMode(newWidth, newHeight), "BG3");
                }
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
                if(event.key.code == sf::Keyboard::Escape) this->game->window.close();
                else if(event.key.code == sf::Keyboard::Space) this->loadgame();
                break;
            }
            default: break;
        }
    }

    return;
}