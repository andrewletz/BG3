#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "unit_button.hpp"

UnitButton::UnitButton(Game* game, sf::Vector2f pos, std::string backgroundName, std::string op, std::string foregroundName) 
: Button(game, pos, backgroundName, op){
	//texture
	this->secondTexture = game->texmgr.getRef(foregroundName);
	sf::Vector2u textureSize = this->secondTexture.getSize();
	sf::Vector2f texSize;
	texSize.x = textureSize.x;
	texSize.y = textureSize.y;
	//hitbox
	this->secondbox.setPosition(pos);
	this->secondbox.setSize(texSize);
	this->secondbox.setOrigin(texSize.x/2, texSize.y/2);
	this->secondbox.setTexture(&this->secondTexture);
}

void UnitButton::Draw(sf::RenderWindow &window){
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