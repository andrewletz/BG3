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
                        leftTeam.reset();
                        rightTeam.reset();
			break;

		case FIGHT:
		        leftTeam.start();
                        rightTeam.start();
			break;
	}
}

void RoundManager::step() {

    for (int left = 0; left < leftTeam.units.size(); left++) {
        // left unit reference
        Unit& leftUnit = leftTeam.units[left];

        // get collider for left unit comparison
        Collider leftCollider = leftUnit.getCollider();

        /* LEFT TEAM INNER COLLISIONS */
        for (int left2 = 0; left2 < leftTeam.units.size(); left2++) {
            if (left != left2) {
                Collider leftCollider2 = leftTeam.units[left2].getCollider();
                leftCollider.checkUnitCollision(leftCollider2, 0.0f);
            }
        }

        for (int right = 0; right < rightTeam.units.size(); right++) {
            // get collider for right unit comparison
            Collider rightCollider = rightTeam.units[right].getCollider();

            /* RIGHT TEAM INNER COLLISIONS */ 
            for (int right2 = 0; right2 < rightTeam.units.size(); right2++) {
                if (right != right2) {
                    Collider rightCollider2 = rightTeam.units[right2].getCollider();
                    rightCollider.checkUnitCollision(rightCollider2, 0.0f);
                }
            }

            // check for vision collision LEFT -> RIGHT
            if (leftCollider.checkVisionCollision(rightCollider)) {
               if (!leftUnit.hasTarget() && rightUnit.isLiving()) {
                   leftUnit.setTarget(&rightUnit);
                   leftUnit.advanceTarget();
               }
            }

            // check for vision collision RIGHT -> LEFT
            if (rightCollider.checkVisionCollision(leftCollider)) {
               if (!rightUnit.hasTarget() && leftUnit.isLiving()) {
                   rightUnit.setTarget(&leftUnit);
                   rightUnit.advanceTarget();
               }
            }
        }
    }
}

void RoundManager::draw(sf::RenderWindow& window) {
	// switch (this->phase) {
	// 	case PLACE:
			
	// 		break;

	// 	case FIGHT:
			
	// 		break;
	// }

        for (int i = 0; i < 3; i++) {
            if (leftTeam.baseUnits[i].isLiving())
                leftTeam.baseUnits[i].draw(window);
            if (rightTeam.baseUnits[i].isLiving())
                rightTeam.baseUnits[i].draw(window);
        }
        
        for (auto leftUnit : leftTeam.baseUnits) {
            if (leftUnit.isLiving())
                leftUnit.draw(window);
        }
        for (auto rightUnit : rightTeam.baseUnits) {
            if (rightUnit.isLiving())
                rightUnit.draw(window);
        }
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
