#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Button{
public:
	Button(float x, float y, std::string msg, void (*func)());
	~Button(){}

	void setPos(int x, int y);
	void PressButton();
	void Draw(sf::RenderWindow window);

	//button info
	sf::Text label;
	void (*operation)();
	sf::RectangleShape hitbox;
};

#endif