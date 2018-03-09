#ifndef UNIT_BUTTON_HPP
#define UNIT_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "button.hpp"

class UnitButton : public Button{
public:
	UnitButton(Game* game, sf::Vector2f pos, std::string backgroundName, std::string op, std::string foregroundName);
	~UnitButton();

	void Draw(sf::RenderWindow &window);

	//the hitbox and texture of the unit image
	sf::RectangleShape secondbox;
	sf::Texture secondTexture;
};

#endif