#ifndef UITEXT_HPP
#define UITEXT_HPP

#include <SFML/Graphics.hpp>
#include "container.hpp"

class uiText : public Container{
public:
	uiText(Game* game, sf::Vector2f pos, int time);
	~uiText();

	void updateText(int newText);
	void updatePos(float scale);
	void updateOrigin();
	void draw(sf::RenderWindow &window);

	sf::Text _text;
	sf::Font _font;
};

#endif