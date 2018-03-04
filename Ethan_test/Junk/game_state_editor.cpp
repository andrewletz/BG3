#include <SFML/Graphics.hpp>
#include "game_state.hpp"
#include "game_state_editor.hpp"

void GameStateEditor::draw(const float dt){
	this->game->window.clear(sf::Color::Black);
	this->game->window.draw(this->game->background);

	return;
}

void GameStateEditor::update(const float dt){
	return;
}

void GameStateEditor::handleInput(){
	sf::Event event;

	while(this->game->window.pollEvent(event)){
		switch(event.type){
			//close the window
			case sf::Event::Closed:{
				game->window.close();
				break
			}
			//resize the window
			case sf::Event::Resized:{
				this->gameView.setSize(event.size.width, even.size.height);
				this->guiView.setSize(event.size.width, even.size.height);
				this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0,0)));
				
				this->game->background.setScale(
					float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
					float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
				break;
			}
			case sf::Event::KeyPressed:{
				if(event.key.code == sf::Keyboard::Escape){ this->game->window.close();}
				break;
			}
			default:{break;}
		}
	}
	return;
}

GameStateEditor::GameStateEditor(Game* game){
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->guiView.setCenter(pos);
	this->gameView.setCenter(pos);
}