#include "button.hpp"
#include <string>

Button::Button(float x, float y, std::string msg, std::string op)
{
	this->operation = op;
	this->hitbox.setPosition(x, y);
	this->hitbox.setSize(sf::Vector2f(150.0f, 100.0f));
	this->label.setString(msg);
	this->font.loadFromFile("C:\\Windows\\Fonts\\Arial\\Arial Regular.ttf");
	this->label.setFont(font);
	this->label.setPosition(x, y);
}

void Button::Draw(sf::RenderWindow &window)
{
	window.draw(hitbox);
	window.draw(label);
}

std::string Button::PressButton()
{
	return this->operation;
}