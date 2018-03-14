#include "round_manager.hpp"

RoundManager::RoundManager(Game* game) : leftTeam(game), rightTeam(game) {
	this->game = game;
	this->roundNumber = 1;
	this->maxPlacingTime = 10.0;
	this->currTeam = Enums::LEFT;
	this->time = 0.0;
	this->phase = PLACE;
}

void RoundManager::update(const float dt) {
	switch (this->phase) {
		case PLACE:
			this->time += dt;
			if (this->time >= this->maxPlacingTime) {
				this->phase = FIGHT;
				this->time = 0;
			}
			break;

		case FIGHT:
			
			break;
	}
}

void RoundManager::draw(sf::RenderWindow& window) {
	// for (int i = 0; i < 3; i++) {
	// 	this->leftTeam.baseUnits[i].draw(window);
	// 	this->rightTeam.baseUnits[i].draw(window);
	// }
	// for (Unit unit : leftTeam.units) {
	// 	unit.draw(window);
	// }
	// for (Unit unit : rightTeam.units) {
	// 	unit.draw(window);
	// }
	// switch (this->phase) {
	// 	case PLACE:
			
	// 		break;

	// 	case FIGHT:
			
	// 		break;
	// }
}

bool RoundManager::areUnitsAlive() {
	return leftTeam.hasUnitsAlive() && rightTeam.hasUnitsAlive();
}

bool RoundManager::hasLostGame(Enums::Teams team) {
	switch(team) {
		case Enums::LEFT: {
			return leftTeam.hasLostGame();
			break;
		}
		case Enums::RIGHT: {
			return rightTeam.hasLostGame();
			break;
		}
		default: break;
	}
}
