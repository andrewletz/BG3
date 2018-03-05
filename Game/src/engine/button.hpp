#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Button{
public:
	Button(sf::Vector2f pos, std::string filename, std::string op);
	~Button(){}

	void updatePos(float scale);
	std::string isClicked(sf::Vector2i cPos);
	void Draw(sf::RenderWindow &window);

	//button info
	std::string operation;
	sf::RectangleShape hitbox;
	sf::Texture buttTexture;
};

#endif