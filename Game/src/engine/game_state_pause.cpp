#include <SFML/Graphics.hpp>
#include "game_state_pause.hpp"

GameStatePause::GameStatePause(Game* game){
	this->game = game;

	this->_text.setString("Paused");
	this->_font.loadFromFile("assets/font/ALGER.TTF");
	this->_text.setFont(_font);
	this->_text.setPosition(0.0, 0.0);

	this->drawn = false;
}

void GameStatePause::update(const float dt){
	return;
}

void GameStatePause::handleInput(){
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
            	//unpause when p is pressed
            	if(event.key.code == sf::Keyboard::P) {
                    game->popState();
                }
            }
        }
    }

}

void GameStatePause::draw(const float dt){
	this->game->window.draw(this->_text);
}