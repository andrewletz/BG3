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