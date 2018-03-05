#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Button{
public:
	Button(sf::Vector2f pos, sf::Vector2f size, std::string msg, std::string op);
	~Button(){}

	void updatePos(float scale);
	std::string isClicked(sf::Vector2i cPos);
	void Draw(sf::RenderWindow &window);

	//button info
	sf::Font font; //the font for the label
	sf::Text label;
	std::string operation;
	sf::RectangleShape hitbox;
};

#endif