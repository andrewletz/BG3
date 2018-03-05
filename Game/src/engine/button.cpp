#include "button.hpp"
#include <string>
#include <iostream>

Button::Button(float x, float y, std::string msg, std::string op)
{
	//operation
	this->operation = op;
	//hitbox
	this->hitbox.setPosition(x, y);
	this->hitbox.setSize(sf::Vector2f(100.0f, 50.0f));
	this->hitbox.setFillColor(sf::Color::Green);
	this->hitbox.setOutlineColor(sf::Color::Black);
	this->hitbox.setOutlineThickness(1.0f);
	//font
	this->font.loadFromFile("assets/texts/ALGER.TTF");
	//Text
	this->label.setFont(font);
	this->label.setString(msg);
	this->label.setPosition(x, y);
	this->label.setColor(sf::Color::Black);
}

void Button::Draw(sf::RenderWindow &window)
{
	window.draw(hitbox);
	window.draw(label);
}

std::string Button::isClicked(int cX, int cY, int rX, int rY)
{
	std::cout << "TODO: make this check if the click and release are both inside of the hitbox" << std::endl;
	return "null";
}