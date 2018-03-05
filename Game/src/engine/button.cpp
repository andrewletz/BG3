#include "button.hpp"
#include <string>
#include <iostream>

Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string msg, std::string op)
{
	//operation
	this->operation = op;
	//hitbox
	this->hitbox.setPosition(pos);
	this->hitbox.setSize(size);
	this->hitbox.setFillColor(sf::Color::Green);
	this->hitbox.setOutlineColor(sf::Color::Black);
	this->hitbox.setOutlineThickness(1.0f);
	//font
	this->font.loadFromFile("assets/texts/ALGER.TTF");
	//Text
	this->label.setFont(font);
	this->label.setString(msg);
	this->label.setPosition(pos);
	this->label.setColor(sf::Color::Black);
}

void Button::updatePos(float scale)
{
	//hitbox pos
	sf::Vector2f hbp = this->hitbox.getPosition();
	hbp.x *= scale;
	hbp.y *= scale;
	this->hitbox.setPosition(hbp);

	//text pos
	sf::Vector2f tp = this->label.getPosition();
	tp.x *= scale;
	tp.y *= scale;
	this->label.setPosition(tp);
}

void Button::Draw(sf::RenderWindow &window)
{
	window.draw(hitbox);
	window.draw(label);
}

std::string Button::isClicked(sf::Vector2i cPos)
{
	//hitbox size
	sf::Vector2f hbs = this->hitbox.getSize();
	//hitbox pos
	sf::Vector2f hbp = this->hitbox.getPosition();
	if(cPos.x >= hbp.x && cPos.y >= hbp.y && cPos.x <= (hbp.x + hbs.x) && cPos.y <= (hbp.y + hbs.y))
	{
		return operation;
	}
	return "null";
}