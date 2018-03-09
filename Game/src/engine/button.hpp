#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "container.hpp"

class Button : public Container{
public:
	Button(Game* game, sf::Vector2f pos, std::string textureName, std::string op);
	~Button(){}

	std::string isClicked(sf::Vector2i cPos);

	//button info
	std::string operation;
};

#endif