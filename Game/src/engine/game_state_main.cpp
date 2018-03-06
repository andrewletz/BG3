#include <SFML/Graphics.hpp>

#include "game_state.hpp"
#include "game_state_start.hpp"
#include "game_state_main.hpp"

void GameStateMain::draw(const float dt)
{
    this->background.setTexture(game->texmgr.getRef("background_main"));
    this->background.setScale(
                    float(this->gameView.getSize().x) / float(this->background.getTexture()->getSize().x),
                    float(this->gameView.getSize().y) / float(this->background.getTexture()->getSize().y));

    this->game->window.clear(sf::Color::Black);
    this->game->window.draw(this->background);
    return;
}

void GameStateMain::update(const float dt)
{
    return;
}

void GameStateMain::handleInput()
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
            case sf::Event::KeyPressed:
            {
                if(event.key.code == sf::Keyboard::Escape) {
                    game->popState();
                }
                break;
            }
            default: break;
        }
    }

    return;
}

GameStateMain::GameStateMain(Game* game)
{
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->guiView.setSize(pos);
    this->gameView.setSize(pos);
    pos *= 0.5f;
    this->guiView.setCenter(pos);
    this->gameView.setCenter(pos);
}