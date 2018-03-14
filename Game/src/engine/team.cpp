#include "team.hpp"
#include <vector>

Team::Team(Game* game, Enums::Teams team) : side(team) {
	this->game = game;
	this->shekels = 5;
	this->alive = this->units.size();

	Attributes castleAttr;	
    castleAttr.cost = 0;	
    castleAttr.attackRadius = 100.f;	
    castleAttr.visionRadius = 200.f;	
    castleAttr.attackDamage = 5;	
    castleAttr.moveSpeed = 0.0f;	
    castleAttr.max_hp = 500;

	Attributes towerAttr;	
    towerAttr.cost = 0;	
    towerAttr.attackRadius = 100.f;	
    towerAttr.visionRadius = 200.f;	
    towerAttr.attackDamage = 5;	
    towerAttr.moveSpeed = 0.0f;	
    towerAttr.max_hp = 500;

    // Variables used to set up buttons
    sf::Vector2i resolution = this->game->getResolution();
    sf::Vector2f position(resolution.x, resolution.y / 2);

    switch (this->side) {
    	case Enums::LEFT:
    	{
    		position.x = resolution.x * 0.1f;
    		Unit castle(game->texmgr.getRef("castle"), position, Enums::LEFT, castleAttr);

    		position.x = resolution.x * 0.3f;
    		position.y = resolution.y * 0.2f;
			Unit towerTop(game->texmgr.getRef("castle"), position, Enums::LEFT, towerAttr);

			position.y = resolution.y * 0.8f;
			Unit towerBottom(game->texmgr.getRef("castle"), position, Enums::LEFT, towerAttr);

			this->baseUnits.push_back(castle);
			this->baseUnits.push_back(towerTop);
			this->baseUnits.push_back(towerBottom);
    		break;
    	}
    	case Enums::RIGHT:
    	{
    		position.x = resolution.x * 0.9f;
    		Unit castle(game->texmgr.getRef("castle"), position, Enums::RIGHT, castleAttr);

    		position.x = resolution.x * 0.7f;
    		position.y = resolution.y * 0.2f;
			Unit towerTop(game->texmgr.getRef("castle"), position, Enums::RIGHT, towerAttr);

			position.y = resolution.y * 0.8f;
			Unit towerBottom(game->texmgr.getRef("castle"), position, Enums::RIGHT, towerAttr);

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
	if (unit.attributes.cost < shekels) {
		this->units.push_back(unit);
		this->shekels -= unit.attributes.cost;
	}
}

void Team::start() {
    for (auto unit : baseUnits) {
        unit.start();
    }
    for (auto unit : units) {
        unit.start();
    }
}

void Team::reset() {
    this->alive = units.size();
        
    for (auto unit : baseUnits) {
        unit.reset();
    }
    for (auto unit : units) {
        unit.reset();
    }
}
