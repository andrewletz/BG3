#include <SFML/Graphics.hpp>
#include <iostream>

#include "game_state.hpp"
#include "game_state_start.hpp"
#include "game_state_main.hpp"

GameStateMain::GameStateMain(Game* game) : roundManager(game)
{
    this->game = game;
    this->background.setTexture(game->texmgr.getRef("background_main"));
    
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->gameView.setSize(pos);
    pos *= 0.5f;
    this->gameView.setCenter(pos);

    this->background.setScale(
            float(this->gameView.getSize().x) / float(this->background.getTexture()->getSize().x),
            float(this->gameView.getSize().y) / float(this->background.getTexture()->getSize().y));

    // Variables used to set up buttons
    sf::Vector2i resolution = this->game->getResolution();
    sf::Vector2f position(resolution.x * 0.11f, resolution.y - (resolution.y * 0.08f));

    std::vector<std::string> buttonStrings = {"unit_one", "unit_two", "unit_three", "unit_four", "unit_five", "unit_six", "unit_seven", "unit_eight"};
    for (int i = 0; i < 8; i++) {
        this->buttons.push_back(new UnitButton(this->game, position, "unit_background", buttonStrings[i], buttonStrings[i]));
        position.x += resolution.x * 0.11f;
    }

    // Left board
    position.y = (resolution.y / 2.0);
    position.x = resolution.x / 4.0;
    Button *leftField = new Button(this->game, position, "left_board", "left_board");
    this->board.push_back(leftField);

    // Right board
    position.x = resolution.x - (resolution.x / 4.0);
    Button *rightField = new Button(this->game, position, "right_board", "right_board");
    this->board.push_back(rightField);

    // Outline is a container object
    position.x = resolution.x / 2.0;
    this->uiElements.push_back(new Container(this->game, position, "outline"));

    this->currUnit = UNIT_ONE;
}

void GameStateMain::draw(const float dt)
{
    this->game->window.clear(sf::Color::Black);
    this->game->window.draw(this->background);

    //draw the buttons
    int butlen = buttons.size();
    for(int i = 0; i < butlen; i++)
    {
        buttons[i]->draw(this->game->window);
    }
    //draw the board
    board[0]->draw(this->game->window);
    board[1]->draw(this->game->window);

    // Phase dependent draws (mainly for outline)
    switch(roundManager.phase) {
        case roundManager.Phase::PLACE:
            this->uiElements[0]->draw(this->game->window);
            break;
    }

    // Unit drawing handled by roundmanager, do this last as they should be on top
    this->roundManager.draw(this->game->window);
    
    return;
}

void GameStateMain::update(const float dt)
{
    this->roundManager.update(dt);
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
                // bool shiftPressed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift));
                if(event.key.code == sf::Keyboard::Escape) {
                    game->popState();
                }
                // else if(event.key.code == sf::Keyboard::Escape) {
                //     this->game->window.close();
                // } 
                // else if(event.key.code == sf::Keyboard::Equal && shiftPressed) {
                //     this->game->cycleResolution(true);  
                // } 
                // else if(event.key.code == sf::Keyboard::Dash && shiftPressed) {
                //     this->game->cycleResolution(false);
                // }
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
                        if(validClick == "unit_one")
                        {
                            this->currUnit = UNIT_ONE;
                        }
                        else if(validClick == "unit_two")
                        {
                            this->currUnit = UNIT_TWO;
                        }
                        else if(validClick == "unit_three")
                        {
                            this->currUnit = UNIT_THREE;
                        }
                        else if(validClick == "unit_four")
                        {
                            this->currUnit = UNIT_FOUR;
                        }
                        else if(validClick == "unit_five")
                        {
                            this->currUnit = UNIT_FIVE;
                        }
                        else if(validClick == "unit_six")
                        {
                            this->currUnit = UNIT_SIX;
                        }
                        else if(validClick == "unit_seven")
                        {
                            this->currUnit = UNIT_SEVEN;
                        }
                        else if(validClick == "unit_eight")
                        {
                            this->currUnit = UNIT_EIGHT;
                        }
                    }
                    break;
                }
            }
            case sf::Event::Resized:
            {
                float originalHeight = this->gameView.getSize().y;
                float originalWidth = this->gameView.getSize().x;

                float scaleHeight = float(event.size.height) / originalHeight;
                float scaleWidth = float(event.size.width) / originalWidth;
                float scale = std::min(scaleHeight, scaleWidth);

                int newWidth = int(originalWidth * scale);
                int newHeight = int(originalHeight * scale);
                this->gameView.setSize(newWidth, newHeight);
                this->gameView.setCenter(newWidth / 2, newHeight / 2);

                this->game->window.setSize(sf::Vector2u(uint(newWidth), uint(newHeight)));
                this->game->window.setView(this->gameView);

                this->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0)));
                this->background.setScale(
                    float(newWidth) / float(this->background.getTexture()->getSize().x),
                    float(newHeight) / float(this->background.getTexture()->getSize().y));

                int butlen = buttons.size();
                for(int i = 0; i < butlen; i++)
                {
                    buttons[i]->updatePos(scale);
                }
                //draw the board
                board[0]->updatePos(scale);
                board[1]->updatePos(scale);

                break;
            }
            default: break;
        }
    }

    return;
}
