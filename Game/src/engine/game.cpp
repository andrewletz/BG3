#include <stack>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.hpp"
#include "game_state.hpp"

void Game::loadTextures()
{
    // remember paths are relative to the generated executable! (not the cpp file)
    texmgr.loadTexture("background", "assets/images/background.png");
    texmgr.loadTexture("background_main", "assets/images/mainbackground.png");
}

void Game::pushState(GameState* state)
{
    this->states.push(state);

    return;
}

void Game::popState()
{
    delete this->states.top();
    this->states.pop();

    return;
}

void Game::changeState(GameState* state)
{
    if(!this->states.empty())
        popState();
    pushState(state);

    return;
}

GameState* Game::peekState()
{
    if(this->states.empty()) return nullptr;
    return this->states.top();
}

void Game::gameLoop()
{
    sf::Clock clock;

    while(this->window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        if(peekState() == nullptr) continue;
        peekState()->handleInput();
        peekState()->update(dt);
        this->window.clear(sf::Color::Black);
        peekState()->draw(dt);
        this->window.display();
    }
}
void Game::cycleResolution(bool forward) {
    int resSize = validResolutions.size();
    if (!forward) {
        if (currentResolution == resSize - 1) {
            currentResolution = 0;
            this->window.create(sf::VideoMode(this->validResolutions[0].x, this->validResolutions[0].y, this->bitsPerPixel), "BG3", sf::Style::Close);
        } else {
            currentResolution += 1;
            this->window.create(sf::VideoMode(this->validResolutions[currentResolution].x, this->validResolutions[currentResolution].y, this->bitsPerPixel), "BG3", sf::Style::Close);
        }
    } else {
        if (currentResolution == 0) {
            currentResolution = resSize - 1;
            this->window.create(sf::VideoMode(this->validResolutions[resSize - 1].x, this->validResolutions[resSize - 1].y, this->bitsPerPixel), "BG3", sf::Style::Close);
        } else {
            currentResolution -= 1;
            this->window.create(sf::VideoMode(this->validResolutions[currentResolution].x, this->validResolutions[currentResolution].y, this->bitsPerPixel), "BG3", sf::Style::Close);
        }
    }
}

Game::Game()
{
    this->loadTextures();
    std::vector<sf::Vector2i> sixteenNine;
    // Small list of valid 16:9 resolutions
    sixteenNine.push_back(sf::Vector2i(1920, 1080));
    sixteenNine.push_back(sf::Vector2i(1536, 864));
    sixteenNine.push_back(sf::Vector2i(1280, 720));
    sixteenNine.push_back(sf::Vector2i(896, 504));
    sixteenNine.push_back(sf::Vector2i(512, 288));

    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    int maxHeight = modes[0].height; // get the monitors max information
    int maxWidth = modes[0].width;
    int maxBPP = modes[0].bitsPerPixel;
    for (sf::Vector2i res : sixteenNine) {
        if (res.x <= maxWidth && res.y <= maxHeight) { // if the given 16:9 resolution is smaller than monitors max
            this->validResolutions.push_back(res);
        }
    }

    if(validResolutions.size() > 1) { // choose second smallest if it exists
        this->window.create(sf::VideoMode(this->validResolutions[1].x, this->validResolutions[1].y, maxBPP), "BG3", sf::Style::Close);
        this->currentResolution = 1;
    } else {
        this->window.create(sf::VideoMode(maxWidth, maxHeight, maxBPP), "BG3", sf::Style::Close);
        this->currentResolution = 0;
    }
    this->bitsPerPixel = maxBPP;

    this->window.setFramerateLimit(60);

    this->background.setTexture(this->texmgr.getRef("background"));
}

Game::~Game()
{
    while(!this->states.empty()) popState();
}

sf::Vector2i Game::getResolution()
{
    return this->validResolutions[this->currentResolution];
}