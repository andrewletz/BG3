#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "texture_manager.hpp"

void TextureManager::loadTexture(const std::string& name, const std::string& filename){
	sf::Texture text;
	tex.loadFromFile(filename);

	this->textures[name] = tex;

	return;
}

sf::Texture& TextureManager::getRef(const std::string& texture){
	return this->textures.at(texture);
}