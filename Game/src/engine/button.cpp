#include "button.hpp"
#include <string>
#include <iostream>

Button::Button(sf::Vector2f pos, std::string filename, std::string op)
{
	//operation
	this->operation = op;
	//texture
	this->buttTexture.loadFromFile(filename);
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

void Button::updatePos(float scale)
{
	//hitbox pos
	sf::Vector2f hbp = this->hitbox.getPosition();
	hbp.x *= scale;
	hbp.y *= scale;
	this->hitbox.setPosition(hbp);

	//hitbox size
	sf::Vector2f hbs = this->hitbox.getSize();
	float newHeight = hbs.x*scale;
	float newWidth = hbs.y*scale;

	hbs.x = newHeight/hbs.x;
	hbs.y = newWidth/hbs.y;
	this->hitbox.setScale(hbs);
}

void Button::Draw(sf::RenderWindow &window)
{
	window.draw(hitbox);
}

std::string Button::isClicked(sf::Vector2i cPos)
{
	//hitbox size
	sf::Vector2f hbs = this->hitbox.getSize();
	//hitbox pos
	sf::Vector2f hbp = this->hitbox.getPosition();
	//this adjust the position to the upper left hand corner to make calculations easier
	hbp.x -= hbs.x/2;
	hbp.y -= hbs.y/2;
	if(cPos.x >= hbp.x && cPos.y >= hbp.y && cPos.x <= (hbp.x + hbs.x) && cPos.y <= (hbp.y + hbs.y))
	{
		return operation;
	}
	return "null";
}