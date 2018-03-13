#include "team.hpp"
#include <vector>

Team::Team() {
	this->shekels = 5;
	this->alive = this->units.size();
	// initialize base units
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

void Team::reset() {
	this->alive = units.size();
}