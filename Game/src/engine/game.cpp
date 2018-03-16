#include <stack>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.hpp"
#include "game_state.hpp"

Game::Game() : windowsCursorVisible(true)
{
    this->loadTextures();
    this->units = Units();

    std::vector<sf::Vector2i> sixteenNine;
    // Small list of valid 16:9 resolutions
    // sixteenNine.push_back(sf::Vector2i(1920, 1080));
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

    // if(validResolutions.size() > 1) { // choose second smallest if it exists
    //     this->window.create(sf::VideoMode(this->validResolutions[1].x, this->validResolutions[1].y, maxBPP), "BG3", sf::Style::Close);
    //     this->currentResolution = 1;
    // } else {
    //     this->window.create(sf::VideoMode(maxWidth, maxHeight, maxBPP), "BG3", sf::Style::Close);
    //     this->currentResolution = 0;
    // }

    // Dynamic resolution scaling is taking too much time so for now lets just use 720p
    // Most of the logic is there just some bugs to iron out
    this->window.create(sf::VideoMode(this->validResolutions[1].x, this->validResolutions[1].y, maxBPP), "BG3", sf::Style::Close);
    this->currentResolution = 1;

    this->bitsPerPixel = maxBPP;

    this->window.setFramerateLimit(60);
    
    this->window.setPosition(sf::Vector2i(this->window.getPosition().x / 2, this->window.getPosition().y / 2));
    
    this->icon.loadFromFile("assets/images/icon.png");
    this->window.setIcon(32, 32, this->icon.getPixelsPtr());
}

Game::~Game()
{
    while(!this->states.empty()) popState();
}

void Game::loadTextures()
{
    // remember paths are relative to the generated executable! (not the cpp file)

    // Backgrounds
    texmgr.loadTexture("background", "assets/images/background.png");
    texmgr.loadTexture("background_main", "assets/images/game_field_background.png");
    texmgr.loadTexture("left_board", "assets/images/left_field.png");
    texmgr.loadTexture("right_board", "assets/images/right_field.png");
    texmgr.loadTexture("under_build_grass", "assets/images/under_build_grass.png");

    // Gui elements
    texmgr.loadTexture("logo", "assets/images/logo.png");
    texmgr.loadTexture("start", "assets/images/start_button.png");
    texmgr.loadTexture("quit", "assets/images/quit_button.png");
    texmgr.loadTexture("unit_background", "assets/images/unit_button.png");
    texmgr.loadTexture("outline", "assets/images/outline.png");

    // Units
    texmgr.loadTexture("man_at_arms", "assets/images/man_at_arms.png");
    texmgr.loadTexture("bow_archer", "assets/images/bow_archer.png");

    // Base units
    texmgr.loadTexture("castle", "assets/images/castle.png");
    texmgr.loadTexture("tower", "assets/images/tower.png");
}

void Game::pushState(GameState* state)
{
    this->states.push(state);

    return;
}

void Game::popState()
{
    // delete this->states.top();
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
        // if you want to implement this globally you would need a timer so you can't hold keys down
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
        //         this->cycleResolution(true);  
        //     } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
        //         this->cycleResolution(false);
        //     }
        // }
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        if (this->windowsCursorVisible) {
            window.setMouseCursorVisible(true);
        } else {
            window.setMouseCursorVisible(false);
            this->cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(this->window)));
        }

        if(peekState() == nullptr) continue;
        peekState()->handleInput();
        peekState()->update(dt);
        //this->window.clear(sf::Color::Black);
        peekState()->draw(dt);
        if (!this->windowsCursorVisible) {
            this->window.draw(this->cursor);
        }
        
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
    this->window.setIcon(32, 32, this->icon.getPixelsPtr());
}

sf::Vector2i Game::getResolution()
{
    return this->validResolutions[this->currentResolution];
}

void Game::resetCursor() {
    this->windowsCursorVisible = true;
}

void Game::setCursorSprite(std::string textureName, Enums::Teams team) {
    this->windowsCursorVisible = false;
    this->cursor.setTexture(this->texmgr.getRef(textureName));
    this->cursor.setScale(sf::Vector2f(3.0, 3.0));
    if (team == Enums::RIGHT) {
        this->cursor.setScale(-3.f, 3.f);
    }
}