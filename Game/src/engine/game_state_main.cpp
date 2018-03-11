#include <SFML/Graphics.hpp>
#include <iostream>

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
    //draw the buttons
    int butlen = buttons.size();
    for(int i = 0; i < butlen; i++)
    {
        buttons[i]->Draw(this->game->window);
    }
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

    //unit one
    sf::Vector2i currRes = this->game->getResolution();
    sf::Vector2f currPos(currRes.x * 0.11f, currRes.y / 2 + 300);
    UnitButton *unitOne = new UnitButton(this->game, currPos, "unit_background", "unit_one", "unit_one"); 
    this->buttons.push_back(unitOne);

    //unit two
    sf::Vector2f currPos2(currRes.x * 0.22f, currRes.y / 2 + 300);
    UnitButton *unitTwo = new UnitButton(this->game, currPos2, "unit_background", "unit_two", "unit_two");
    this->buttons.push_back(unitTwo);

    //unit three
    sf::Vector2f currPos3(currRes.x * 0.33f, currRes.y / 2 + 300);
    UnitButton *unitThree = new UnitButton(this->game, currPos3, "unit_background", "unit_three", "unit_three");
    this->buttons.push_back(unitThree);

    //unit four
    sf::Vector2f currPos4(currRes.x * 0.44f, currRes.y / 2 + 300);
    UnitButton *unitFour = new UnitButton(this->game, currPos4, "unit_background", "unit_four", "unit_four");
    this->buttons.push_back(unitFour);

    //unit five
    sf::Vector2f currPos5(currRes.x * 0.55f, currRes.y / 2 + 300);
    UnitButton *unitFive = new UnitButton(this->game, currPos5, "unit_background", "unit_five", "unit_five");
    this->buttons.push_back(unitFive);

    //unit six
    sf::Vector2f currPos6(currRes.x * 0.66f, currRes.y / 2 + 300);
    UnitButton *unitSix = new UnitButton(this->game, currPos6, "unit_background", "unit_six", "unit_six");
    this->buttons.push_back(unitSix);

    //unit seven
    sf::Vector2f currPos7(currRes.x * 0.77f, currRes.y / 2 + 300);
    UnitButton *unitSeven = new UnitButton(this->game, currPos7, "unit_background", "unit_seven", "unit_seven");
    this->buttons.push_back(unitSeven);

    //unit eight
    sf::Vector2f currPos8(currRes.x * 0.88f, currRes.y / 2 + 300);
    UnitButton *unitEight = new UnitButton(this->game, currPos8, "unit_background", "unit_eight", "unit_eight");
    this->buttons.push_back(unitEight);

    this->currUnit = UNIT_ONE;
}