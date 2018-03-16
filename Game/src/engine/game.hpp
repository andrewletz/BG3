#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
#include <SFML/Graphics.hpp>
#include "texture_manager.hpp"
#include "units.hpp"
#include "global_enum.hpp"

class Units;
class GameState;

class Game
{
    public:
    Game();
    ~Game();

    std::stack<GameState*> states;

    std::vector<sf::Vector2i> validResolutions;
    int bitsPerPixel;
    int currentResolution;

    Units units;

    sf::Image icon;
    bool windowsCursorVisible;
    sf::Sprite cursor;

    sf::RenderWindow window;
    TextureManager texmgr;

    void resetCursor();
    void setCursorSprite(std::string textureName, Enums::Teams team);

    void pushState(GameState* state);
    void popState();
    void changeState(GameState* state);
    GameState* peekState();

    void cycleResolution(bool forward);
    sf::Vector2i getResolution();

    void gameLoop();

    private:

    void loadTextures();
};

#endif /* GAME_HPP */