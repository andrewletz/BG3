#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "game_state.hpp"
#include "unit_button.hpp"

class GameStateMain : public GameState
{
    private:

    sf::View gameView;
    sf::View guiView;

    public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    std::vector<UnitButton*> buttons;
    enum Units {UNIT_ONE, UNIT_TWO, UNIT_THREE, UNIT_FOUR, UNIT_FIVE, UNIT_SIX, UNIT_SEVEN, UNIT_EIGHT};
    GameStateMain::Units currUnit;

    GameStateMain(Game* game);
};

#endif /* GAME_STATE_EDITOR_HPP */