#include <SFML/Graphics.hpp>
#include "uitext.hpp"
#include <string>
#include <iostream>

uiText::uiText(Game* game, sf::Vector2f pos, int num){
	this->game = game;

	std::string temp = std::to_string(num);
	this->_text.setString(temp);
	this->_font.loadFromFile("assets/font/ALGER.TTF");
	this->_text.setFont(_font);
	this->_text.setPosition(pos);
	this->_text.setColor(sf::Color::White);
	sf::Rect<float> bounds = this->_text.getLocalBounds();
	this->_text.setOrigin(bounds.width / 2, bounds.height / 2);
}

void uiText::draw(sf::RenderWindow &window){
	window.draw(this->_text);
}

void uiText::updatePos(float scale){
	sf::Vector2f tbp = this->_text.getPosition();
	tbp.x *= scale;
	tbp.y *= scale;
	this->_text.setPosition(tbp);
}

void uiText::updateOrigin(){
	sf::Rect<float> bounds = this->_text.getLocalBounds();
	this->_text.setOrigin(bounds.width / 2, bounds.height / 2);
}

void uiText::updateText(int newText){
	std::string temp = std::to_string(newText);
	this->_text.setString(temp);
}

uiText::~uiText(){
	std::cout << "text deleted" << std::endl;
}