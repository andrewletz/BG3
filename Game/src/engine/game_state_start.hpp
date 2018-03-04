#ifndef GAME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include <SFML/Graphics.hpp>

#include "game_state.hpp"
#include "button.hpp"
#include <vector>

class GameStateStart : public GameState
{
    private:

    sf::View view;

    void loadgame();

    public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    std::vector<Button> buttons;

    GameStateStart(Game* game);
};

#endif /* GAME_STATE_START_HPP */