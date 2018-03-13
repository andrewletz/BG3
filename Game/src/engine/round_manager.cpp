#include "round_manager.hpp"

RoundManager::RoundManager() {
	this->roundNumber = 1;
	this->maxPlacingTime = 10.0;
	this->leftTeam = Team();
	this->rightTeam = Team();
	this->currTeam = LEFT;
	this->time = 0.0;
	this->phase = PLACE;
}

void RoundManager::update(const float dt) {
	switch (this->phase) {
		case PLACE:
			this->time += dt;
			if (this->time >= this->maxPlacingTime) {
				this->phase = FIGHT;
			}
			break;

		case FIGHT:
			
			break;
	}
}

bool RoundManager::areUnitsAlive() {
	return leftTeam.hasUnitsAlive() && rightTeam.hasUnitsAlive();
}

bool RoundManager::hasLostGame(Teams team) {
	switch(team) {
		case LEFT: {
			return leftTeam.hasLostGame();
			break;
		}
		case RIGHT: {
			return rightTeam.hasLostGame();
			break;
		}
		default: break;
	}
}
