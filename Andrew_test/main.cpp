#include "game.hpp"
#include "game_state_start.hpp"

int main()
{
    Game game;

    // destructor in game will free this memory allocated by new
    game.pushState(new GameStateStart(&game));
    game.gameLoop();

    return 0;
}