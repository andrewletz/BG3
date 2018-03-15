#ifndef GAME_STATE_PAUSE_HPP
#define GAME_STATE_PAUSE_HPP

#include <SFML/Graphics.hpp>
#include "game_state.hpp"
#include "uitext.hpp"

class GameStatePause : public GameState{
public:

	GameStatePause(Game* game);

	virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    sf::Text _text;
    sf::Font _font;
    bool drawn;
};
#endif