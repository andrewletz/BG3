#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Button{
public:
	Button(float x, float y, std::string msg, std::string op);
	~Button(){}

	void setPos(int x, int y);
	std::string PressButton();
	void Draw(sf::RenderWindow &window);

	//button info
	sf::Font font; //the font for the label
	sf::Text label;
	std::string operation;
	sf::RectangleShape hitbox;
};

#endif