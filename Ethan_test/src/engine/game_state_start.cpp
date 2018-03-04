#include <SFML/Graphics.hpp>
#include <vector>

#include "game_state_start.hpp"
#include "game_state_editor.hpp"
#include "game_state.hpp"
#include "Button.hpp"

GameStateStart::GameStateStart(Game* game)
{
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
    //make a vector to contain the two buttons
    Button startButton = Button(400, 300, "Start", &this->loadgame());
    this->buttons.push_back()
}

void GameStateStart::loadgame()
{
    this->game->pushState(new GameStateEditor(this->game));

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
    
    //The following two ints store where the click happened
    int clickX;
    int clickY;
    //The following two ints store where the mouse release happened
    int relX;
    int relY;

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
                this->view.setSize(event.size.width, event.size.height);
                this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0)));
                this->game->background.setScale(
                    float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
                    float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
                break;
            }
            case sf::Event::KeyPressed:
            {
                if(event.key.code == sf::Keyboard::Escape) this->game->window.close();
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    clickX = event.mouseButton.x;
                    clickY = event.mouseButton.y;
                }
            }
            case sf::Event::MouseButtonReleases:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    relX = event.mouseButton.x;
                    relY = event.mouseButton.y;
                    //check if clickX/Y and relX/Y are inside of the boxes of any of the button squares

                }
            }
            default: break;
        }
    }

    return;
}