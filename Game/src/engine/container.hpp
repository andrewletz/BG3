#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "texture_manager.hpp"
#include "game.hpp"

class Container{
public:
	Container(Game* game, sf::Vector2f pos, std::string filename);
	~Container(){}

	void updatePos(float scale);
	void draw(sf::RenderWindow &window);

	sf::RectangleShape hitbox;
	sf::Texture buttTexture;
	Game* game;
};

#endif