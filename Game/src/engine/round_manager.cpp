#include "round_manager.hpp"
#include <iostream>

RoundManager::RoundManager(Game* game) : leftTeam(game, Enums::LEFT), rightTeam(game, Enums::RIGHT) {
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
                    step();
		    break;
	}
}

void RoundManager::step() {
    
    for (int left = 0; left < leftTeam.units.size(); left++) {
        // left unit reference
        Unit& leftUnit = leftTeam.units[left];

        // step left unit
        if (leftUnit.isLiving()) {
            if (leftUnit.step()) leftTeam.alive--;
        }

        // get left unit collider
        Collider leftCollider = leftUnit.getCollider();

        // LEFT TEAM INNER COLLISIONS
        for (int left2 = 0; left2 < leftTeam.units.size(); left2++) {
            if (left != left2) {
                Collider leftCollider2 = leftTeam.units[left2].getCollider();
                leftCollider.checkUnitCollision(leftCollider2, 0.0f);
            }
        }

        for (int right = 0; right < rightTeam.units.size(); right++) {
            // right unit reference
            Unit& rightUnit = rightTeam.units[right];

            // step right unit
            if (rightUnit.isLiving()) {
                if (rightUnit.step()) rightTeam.alive--;
            }

            // get right unit collider
            Collider rightCollider = rightUnit.getCollider();

            // RIGHT TEAM INNER COLLISIONS
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
    for (int i = 0; i < 3; i++) {
        if (leftTeam.baseUnits[i].isLiving())
            leftTeam.baseUnits[i].draw(window);
        if (rightTeam.baseUnits[i].isLiving())
            rightTeam.baseUnits[i].draw(window);
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
