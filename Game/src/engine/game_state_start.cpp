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
    this->background.setTexture(game->texmgr.getRef("background"));

    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);

    //make the start button and add it to the buttos vector
    std::string Message = "load_game";
    std::string textFile = "assets/images/start-button.png";
    sf::Vector2i currRes = this->game->getResolution();
    sf::Vector2f currPos(currRes.x / 2, currRes.y / 2);
    Button *startButton = new Button(currPos, textFile, Message); //needs to appear dynamically
    this->buttons.push_back(startButton);

    //make the quit button and add it to the vector
    std::string Message2 = "quit_game";
    std::string textFile2 = "assets/images/quit-button.png";
    sf::Vector2i currRes2 = this->game->getResolution();
    sf::Vector2f currPos2(currRes.x / 2, currRes.y / 2 + 100);
    Button *quitButton = new Button(currPos2, textFile2, Message2);
    this->buttons.push_back(quitButton);

    //make the logo (which is a button) and add it to the vector
    std::string Message3 = "logo";
    std::string textFile3 = "assets/images/logo.png";
    sf::Vector2i currRes3 = this->game->getResolution();
    sf::Vector2f currPos3(currRes.x / 2, currRes.y / 2 - 200);
    Button *logoButton = new Button(currPos3, textFile3, Message3);
    this->buttons.push_back(logoButton);
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
    this->game->window.draw(this->background);

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

                this->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0)));
                this->background.setScale(
                    float(newWidth) / float(this->background.getTexture()->getSize().x),
                    float(newHeight) / float(this->background.getTexture()->getSize().y));

                //TODO: reposition the button
                int butlen = buttons.size();
                for(int i = 0; i < butlen; i++)
                {
                    buttons[i]->updatePos(scale);
                }
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
                        std::string validClick = buttons[i]->isClicked(clickPos);
                        if(validClick == "load_game")
                        {
                            this->loadgame();
                        }
                        else if(validClick == "quit_game")
                        {
                            game->window.close();
                        }
                    }
                    break;
                }
            }
            default: break;
        }
    }

    return;
}