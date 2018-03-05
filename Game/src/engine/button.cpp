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

void Button::Draw(sf::RenderWindow &window)
{
	window.draw(hitbox);
	window.draw(label);
}

std::string Button::isClicked(sf::Vector2i cPos)
{
	int cX = cPos.x;
	int cY = cPos.y;
	//hitbox size
	sf::Vector2f hbs = this->hitbox.getSize();
	//hitbox pos
	sf::Vector2f hbp = this->hitbox.getPosition();
	std::cout << hbp.x << " " << hbp.y << std::endl;
	std::cout << cX << " " << cY << std::endl;
	return "null";
}