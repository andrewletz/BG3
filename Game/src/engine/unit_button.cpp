#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "unit_button.hpp"

UnitButton::UnitButton(Game* game, sf::Vector2f pos, std::string backgroundName, std::string op, std::string foregroundName) 
: Button(game, pos, backgroundName, op){
	//texture
	this->secondTexture = game->texmgr.getRef(foregroundName);
	//base the size on the size of the background
	sf::Texture tex = game->texmgr.getRef(backgroundName);
	sf::Vector2u textureSize = tex.getSize();
	sf::Vector2f texSize;
	texSize.x = textureSize.x - (textureSize.x * 0.2f);
	texSize.y = textureSize.y - (textureSize.y * 0.2f);
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