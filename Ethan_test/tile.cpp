#include <SFML/Graphics.hpp>

#include "animation_handler.hpp"
#include "tile.hpp"

void Tile::draw(sf::RenderWindow& window, float dt){
	this->animHandler.changeAnim(this->tileVariant);

	this->animHandler.update(dt);

	this->sprite.setTextureRect(this->animHandler.bounds);

	window.draw(this->sprite);

	return;
}

void Tile::update(){
	if((this->tileType == TileType::RESIDENTIAL ||
	    this->tileType == TileType::COMMERCIAL ||
	    this->tileType == TileType::INDUSTRIAL) &&
	    this->population == this->maxPopPerLevel * (this->tileVariant+1) &&
	    this->tileVariant < this->maxLevels){
		if(rand() % int(1e4) < 1e2 / (this->tileVariant+1)) ++this->tileVariant;
	}
	return;
}

std::string tileTypeToStr(TileType type){
	switch(type){
		default:
		case TileType::VOID:            return "Void";
        	case TileType::GRASS:           return "Flatten";
        	case TileType::FOREST:          return "Forest";
        	case TileType::WATER:           return "Water";
        	case TileType::RESIDENTIAL:     return "Residential Zone";
        	case TileType::COMMERCIAL:      return "Commercial Zone";
        	case TileType::INDUSTRIAL:      return "Industrial Zone";
	}
}