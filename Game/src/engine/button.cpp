#include "button.hpp"
#include <string>
#include <iostream>
#include "game.hpp"


Button::Button(Game* game, sf::Vector2f pos, std::string textureName, std::string op) : Container(game, pos, textureName)
{
	//operation
	this->operation = op;
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

void Button::draw(sf::RenderWindow &window){
	Container::draw(window);
}

//just in case UnitButton needs to overload this function
void Button::updatePos(float scale){
	Container::updatePos(scale);
}