#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "unit_button.hpp"

UnitButton::UnitButton(Game* game, sf::Vector2f pos, std::string backgroundName, std::string op, std::string foregroundName) 
: Button(game, pos, backgroundName, op) {
	this->secondTexture = game->texmgr.getRef(foregroundName);

	// base the size on the size of the background
	sf::Texture buttonBackground = game->texmgr.getRef(backgroundName);
	sf::Vector2u buttonBackgroundSize = buttonBackground.getSize();

	sf::Vector2f innerImageSize;
	innerImageSize.x = secondTexture.getSize().x * 3.f;
	innerImageSize.y = secondTexture.getSize().y * 3.f;

	this->secondbox.setPosition(pos);
	this->secondbox.setSize(innerImageSize);
	this->secondbox.setOrigin(innerImageSize.x/2, innerImageSize.y/2);
	this->secondbox.setTexture(&this->secondTexture);
}

void UnitButton::draw(sf::RenderWindow &window){
	window.draw(hitbox);
	window.draw(secondbox);
}

void UnitButton::updatePos(float scale){
	Button::updatePos(scale);

	//secondbox size
	sf::Vector2f sbs = this->secondbox.getSize();
	float newHeight = sbs.x*scale;
	float newWidth = sbs.y*scale;

	sbs.x = newHeight;
	sbs.y = newWidth;
	this->secondbox.setSize(sbs);
	this->secondbox.setOrigin(newHeight / 2, newWidth / 2);

	//secondbox pos
	sf::Vector2f sbp = this->secondbox.getPosition();
	sbp.x *= scale;
	sbp.y *= scale;
	this->secondbox.setPosition(sbp);
}