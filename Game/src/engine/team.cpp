#include "team.hpp"
#include <vector>

Team::Team(Game* game) {
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

	Unit castle(game->texmgr.getRef("castle"), sf::Vector2f(0, 0), Enums::RIGHT, castleAttr);
	Unit tower(game->texmgr.getRef("castle"), sf::Vector2f(0, 0), Enums::RIGHT, towerAttr);
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
