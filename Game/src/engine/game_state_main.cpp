#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "game_state.hpp"
#include "game_state_start.hpp"
#include "game_state_main.hpp"
#include "game_state_pause.hpp"

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
    sf::Vector2f position(resolution.x * 0.44f, resolution.y - (resolution.y * 0.08f));

    std::vector<std::string> buttonStrings = {"man_at_arms", "bow_archer", /*"unit_three", "unit_four", "unit_five", "unit_six", "unit_seven", "unit_eight"*/};
    for (int i = 0; i < 2; i++) {
        this->buttons.push_back(new UnitButton(this->game, position, "unit_background", buttonStrings[i], buttonStrings[i]));
        position.x += resolution.x * 0.11f;
    }

    // Left board
    position.y = (resolution.y / 2.0);
    position.x = resolution.x / 4.0;

    Button *leftField = new Button(this->game, position, "left_board", "left_board");
    this->board.push_back(leftField);

    this->uiElements.push_back(new Container(this->game, position, "blue_left"));

    // Right board
    position.x = resolution.x - (resolution.x / 4.0);
    Button *rightField = new Button(this->game, position, "right_board", "right_board");
    this->board.push_back(rightField);

    this->uiElements.push_back(new Container(this->game, position, "blue_right"));

    // Outline is a container object
    position.x = resolution.x / 2.0;
    this->uiElements.push_back(new Container(this->game, position, "outline"));

    // Under build grass
    position.y += position.y * (0.035f);
    Container *underBuilds = new Container(this->game, position, "under_build_grass");
    this->uiElements.push_back(underBuilds);

    //make the clock to show how much time is left  [0]
    position.x = (resolution.x / 2.0);
    position.y = resolution.y - (resolution.y * 0.8885);
    std::unique_ptr<uiText> temp(new uiText(this->game, position, 1));
    this->uiNumbers.push_back(std::move(temp));
    
    position.y = resolution.y - (resolution.y * 0.877f);
    this->uiElements.push_back(new Container(this->game, position, "mini_button"));

    //make the cost text  [1] and [2]
    position.x = resolution.x * 0.44f;
    position.y = resolution.y - (resolution.y * 0.03f);
    std::unique_ptr<uiText> temp2(new uiText(this->game, position, 2));
    this->uiNumbers.push_back(std::move(temp2));

    position.x = resolution.x * 0.55f;
    std::unique_ptr<uiText> temp3(new uiText(this->game, position, 3));
    this->uiNumbers.push_back(std::move(temp3));

    this->currUnit = Enums::MAN_AT_ARMS;

    //make the player money text
    //right [3]
    position.x = resolution.x - (resolution.x * 0.93f);
    position.y = resolution.y * 0.9f;
    std::unique_ptr<uiText> temp4(new uiText(this->game, position, 5));
    this->uiNumbers.push_back(std::move(temp4));

    position.y = position.y * 1.011f;
    this->uiElements.push_back(new Container(this->game, position, "mini_button"));

    //left [4]
    position.x = resolution.x * 0.93f;
    position.y = resolution.y * 0.9f;
    std::unique_ptr<uiText> temp5(new uiText(this->game, position, 5));
    this->uiNumbers.push_back(std::move(temp5));

    position.y = position.y * 1.011f;
    this->uiElements.push_back(new Container(this->game, position, "mini_button"));

    //player turn text [5]
    position.x = (resolution.x / 2.0);
    position.y = resolution.y - (resolution.y * 0.95);
    std::unique_ptr<uiText> temp6(new uiText(this->game, position, ""));
    this->uiNumbers.push_back(std::move(temp6));
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

    this->uiElements[3]->draw(this->game->window);

    // Phase dependent draws (mainly for outline)
    switch(roundManager.phase) {
        case roundManager.Phase::PLACE:
            this->uiElements[2]->draw(this->game->window);
            if (roundManager.currTeam == Enums::RIGHT) {
                this->uiElements[1]->draw(this->game->window);
            } else {
                this->uiElements[0]->draw(this->game->window);
            }
            break;
    }

    this->uiElements[4]->draw(this->game->window);
    this->uiElements[5]->draw(this->game->window);
    this->uiElements[6]->draw(this->game->window);

    int uilen = uiNumbers.size();
    for(int i = 0; i < uilen; i++){
        this->uiNumbers[i]->draw(this->game->window);
    }
    // Unit drawing handled by roundmanager, do this last as they should be on top
    this->roundManager.draw(this->game->window);
    
    return;
}

void GameStateMain::update(const float dt)
{
    this->roundManager.update(dt);

    //update the clock
    float newTime = this->roundManager.time;
    this->uiNumbers[0]->updateText((int) (newTime + 1));
    this->uiNumbers[0]->updateOrigin();

    //update the money of each player
    int newShek = this->roundManager.leftTeam.shekels;
    this->uiNumbers[3]->updateText(newShek);
    this->uiNumbers[0]->updateOrigin();
    newShek = this->roundManager.rightTeam.shekels;
    this->uiNumbers[4]->updateText(newShek);
    this->uiNumbers[0]->updateOrigin();

    //update the current players turn
    // if (roundManager.phase == RoundManager::Phase::PLACE) {
    //     if(this->roundManager.currTeam == Enums::LEFT){
    //         this->uiNumbers[5]->updateText("LEFT");
    //     }
    //     else{
    //         this->uiNumbers[5]->updateText("RIGHT");
    //     }
    // } else {
    //     this->uiNumbers[5]->updateText("");
    // }

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
                //pause the game
                else if(event.key.code == sf::Keyboard::P) {
                    game->pushState(new GameStatePause(this->game));
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

                    bool placing = roundManager.phase == RoundManager::Phase::PLACE;

                    if (placing) {
                        std::string leftBoardClicked = board[0]->isClicked(clickPos);
                        if (leftBoardClicked == "left_board") {
                                //std::cout << "Trying to place unit on left side" << std::endl;
                                if (roundManager.currTeam == Enums::LEFT) {
                                    roundManager.leftTeam.addUnit(
                                        this->game->units.getUnitWithPos(this->currUnit, &this->game->texmgr, 
                                            sf::Vector2f((float)clickPos.x, (float)clickPos.y), Enums::LEFT));
                                }
                        }

                        std::string rightBoardClicked = board[1]->isClicked(clickPos);
                        if (rightBoardClicked == "right_board") {
                                //std::cout << "Trying to place unit on right side" << std::endl;
                                if (roundManager.currTeam == Enums::RIGHT) {
                                    roundManager.rightTeam.addUnit(
                                        this->game->units.getUnitWithPos(this->currUnit, &this->game->texmgr, 
                                            sf::Vector2f((float)clickPos.x, (float)clickPos.y), Enums::RIGHT));
                                }
                        }
                    }

                    int butlen = buttons.size();
                    for(int i = 0; i < butlen; i++)
                    {
                        std::string validClick = buttons[i]->isClicked(clickPos);
                        if(validClick == "man_at_arms")
                        {
                            //std::cout << "Man at arms" << std::endl;
                            if (placing) {
                                this->game->setCursorSprite("man_at_arms", this->roundManager.currTeam);
                            }
                            this->currUnit = Enums::MAN_AT_ARMS;
                        }
                        else if(validClick == "bow_archer")
                        {
                            //std::cout << "Bow archer" << std::endl;
                            if (placing) {
                                this->game->setCursorSprite("bow_archer", this->roundManager.currTeam);
                            }
                            this->currUnit = Enums::BOW_ARCHER;
                        }
                    }

                }
                if (event.mouseButton.button == sf::Mouse::Right){
                    return;
                }
                break;
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
