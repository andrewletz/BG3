#include "team.hpp"
#include <iostream>

Team::Team(Game* game, Enums::Teams team) : side(team) {
	this->game = game;
	this->shekels = 5;
	this->alive = this->units.size();

    // Variables used to set up buttons
    sf::Vector2i resolution = this->game->getResolution();
    sf::Vector2f position(resolution.x, resolution.y / 2 - (resolution.y * 0.04f));

    switch (this->side) {
    	case Enums::LEFT:
    	{
    		position.x = resolution.x * 0.1f;
            Unit castle = this->game->units.getUnitWithPos(Enums::CASTLE, &game->texmgr, position, Enums::LEFT);

    		position.x = resolution.x * 0.18f;
    		position.y = resolution.y * 0.2f;
			Unit towerTop = this->game->units.getUnitWithPos(Enums::TOWER, &game->texmgr, position, Enums::LEFT);

			position.y = resolution.y * 0.65f;
			Unit towerBottom = this->game->units.getUnitWithPos(Enums::TOWER, &game->texmgr, position, Enums::LEFT);

			this->baseUnits.push_back(castle);
			this->baseUnits.push_back(towerTop);
			this->baseUnits.push_back(towerBottom);
    		break;
    	}
    	case Enums::RIGHT:
    	{
    		position.x = resolution.x * 0.9f;
    		Unit castle = this->game->units.getUnitWithPos(Enums::CASTLE, &game->texmgr, position, Enums::LEFT);

    		position.x = resolution.x * 0.82f;
    		position.y = resolution.y * 0.2f;
			Unit towerTop = this->game->units.getUnitWithPos(Enums::TOWER, &game->texmgr, position, Enums::LEFT);

			position.y = resolution.y * 0.65f;
			Unit towerBottom = this->game->units.getUnitWithPos(Enums::TOWER, &game->texmgr, position, Enums::LEFT);

			this->baseUnits.push_back(castle);
			this->baseUnits.push_back(towerTop);
			this->baseUnits.push_back(towerBottom);
    		break;
    	}
    }
}

bool Team::hasUnitsAlive() {
	return alive > 0;
}

bool Team::hasLostGame() {
	return this->baseUnits.size() > 0;
}

void Team::addUnit(Unit unit) {
	if (unit.attributes.cost <= shekels) {
		this->units.push_back(unit);
		this->shekels -= unit.attributes.cost;
                this->alive++;
	}
}

/*
void Team::start() {
    for (auto unit : baseUnits) {
        unit.start();
    }
    for (auto unit : units) {
        unit.start();
    }
}
*/

void Team::reset() {
    /*
    for (auto unit : baseUnits)
        unit.reset();
    */

    for (int i = 0; i < units.size(); i++)
        units[i].reset();

    this->alive = units.size();
}

void Team::giveShekels(int numShekels) {
    this->shekels += numShekels;
}
