#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "game_state.hpp"
#include "unit_button.hpp"
#include "round_manager.hpp"
#include "uitext.hpp"
#include "global_enum.hpp"

class GameStateMain : public GameState
{
    private:

    sf::View gameView;

    public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    RoundManager roundManager;

    std::vector<UnitButton*> buttons;
    std::vector<Container*> uiElements;
    std::vector<std::unique_ptr<uiText> > uiNumbers;
    std::vector<Button*> board;

    sf::Sprite underBuilds;

    Enums::Units currUnit;

    GameStateMain(Game* game);
};

#endif /* GAME_STATE_EDITOR_HPP */