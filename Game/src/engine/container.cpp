#include <SFML/Graphics.hpp>
#include <string>
#include "container.hpp"
#include <iostream>


Container::Container(Game* game, sf::Vector2f pos, std::string textureName)
{
	//game
	this->game = game;
	//texture
	this->buttTexture = game->texmgr.getRef(textureName);
	sf::Vector2u textureSize = this->buttTexture.getSize();
	sf::Vector2f texSize;
	texSize.x = textureSize.x;
	texSize.y = textureSize.y;
	//hitbox
	this->hitbox.setPosition(pos);
	this->hitbox.setSize(texSize);
	this->hitbox.setOrigin(texSize.x/2, texSize.y/2);
	this->hitbox.setTexture(&this->buttTexture);
}

Container::Container(){
	return;
}
void Container::updatePos(float scale)
{
	//hitbox size
	sf::Vector2f hbs = this->hitbox.getSize();
	float newHeight = hbs.x*scale;
	float newWidth = hbs.y*scale;

	hbs.x = newHeight;
	hbs.y = newWidth;
	this->hitbox.setSize(hbs);
	this->hitbox.setOrigin(newHeight / 2, newWidth / 2);

	//hitbox pos
	sf::Vector2f hbp = this->hitbox.getPosition();
	hbp.x *= scale;
	hbp.y *= scale;
	this->hitbox.setPosition(hbp);
}

void Container::draw(sf::RenderWindow &window)
{
	window.draw(hitbox);
}