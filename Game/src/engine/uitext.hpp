#ifndef UITEXT_HPP
#define UITEXT_HPP

#include <SFML/Graphics.hpp>
#include "container.hpp"

class uiText : public Container{
public:
	uiText(Game* game, sf::Vector2f pos, int time);
	uiText(Game* game, sf::Vector2f pos, std::string string);
	~uiText();

	void updateText(int newText);
	void updateText(std::string string);

	void updatePos(float scale);
	void updateOrigin();
	
	void draw(sf::RenderWindow &window);

	sf::Text _text;
	sf::Font _font;
};

#endif