#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
#include <SFML/Graphics.hpp>
#include "texture_manager.hpp"

class GameState;

class Game
{

    private:

    void loadTextures();

    public:

    std::stack<GameState*> states;

    std::vector<sf::Vector2i> validResolutions;
    int bitsPerPixel;
    int currentResolution;

    sf::Image icon;
    sf::RenderWindow window;
    TextureManager texmgr;

    void pushState(GameState* state);
    void popState();
    void changeState(GameState* state);
    void cycleResolution(bool forward);
    sf::Vector2i getResolution();
    GameState* peekState();

    void gameLoop();

    Game();
    ~Game();
};

#endif /* GAME_HPP */