#include "round_manager.hpp"
#include <iostream>

RoundManager::RoundManager(Game* game) : leftTeam(game, Enums::LEFT), rightTeam(game, Enums::RIGHT) {
	this->game = game;
	this->roundNumber = 1;
	this->maxPlacingTime = 1.0;
	this->incomeInterval = 2.5;
    this->incomeTime = 0.0;
	this->currTeam = Enums::LEFT;
	this->time = 0.0;
	this->phase = PLACE;
}

void RoundManager::update(const float dt) {
	this->time += dt;
	switch (this->phase) {
		case PLACE:
			if (this->time >= this->maxPlacingTime) {
				if (this->currTeam == Enums::LEFT) { // need to switch to right team
					this->currTeam = Enums::RIGHT;
					std::cout << "Switching to right team\n";
				} else {
					std::cout << "Fighting begins\n";
					this->phase = FIGHT;
                    this->game->resetCursor();
                    std::cout << "left team start unit cnt: " << leftTeam.alive;
                    std::cout << ", right team start unit cnt: " << rightTeam.alive << std::endl;
                 }
				this->time = 0;
			}
			break;

		case FIGHT:
                    this->incomeTime += dt;

                    step();
		    if (this->areUnitsAlive()) { // there is still fighting
                        //std::cout << "left team unit cnt: " << leftTeam.alive;
                        //std::cout << ", right team unit cnt: " << rightTeam.alive << std::endl;
                        if (this->incomeTime >= this->incomeInterval) {
		    		this->leftTeam.giveShekels(1);
		    		this->rightTeam.giveShekels(1);
		    		this->incomeTime = 0;
		    	}
		    } else if (this->gameOver()) { // no base units left on some side
		    	this->phase = OVER;
		    	bool rightWon = hasLostGame(Enums::LEFT);
		    	if (rightWon) {
		    		this->winner = Enums::RIGHT;
		    	} else {
		    		this->winner = Enums::LEFT;
		    	}
		    } else { // only base units are left alive
		    	this->phase = PLACE;
		    	this->time = 0;
                        leftTeam.reset();
		        rightTeam.reset();
		    }
                    
			break;

		case OVER:
		    break;
	}
}

void RoundManager::step() {
    
    for (int left = 0; left < leftTeam.units.size(); left++) {
        // left unit reference
        Unit& leftUnit = leftTeam.units[left];

        // get left unit collider
        Collider leftCollider = leftUnit.getCollider();

        if (leftUnit.step()) leftTeam.alive--;

        // LEFT TEAM INNER COLLISIONS
        for (int left2 = 0; left2 < leftTeam.units.size(); left2++) {
            if (left != left2) {
                Collider leftCollider2 = leftTeam.units[left2].getCollider();
                leftCollider.checkUnitCollision(leftCollider2, 0.0f);
            }
        }

        for (int i = 0; i < 3; i++) {
            Unit& rightBaseUnit = rightTeam.baseUnits[i];
            Collider rightBaseCollider = rightBaseUnit.getCollider();

            if (leftCollider.checkVisionCollision(rightBaseCollider)) {
                if (!leftUnit.hasTarget() && rightBaseUnit.isLiving()) {
                    leftUnit.setTarget(&rightBaseUnit);
                    leftUnit.advanceTarget();
                }
            }

            if (rightBaseCollider.checkVisionCollision(leftCollider)) {
                if (!rightBaseUnit.hasTarget() && leftUnit.isLiving()) {
                    rightBaseUnit.setTarget(&leftUnit);
                    rightBaseUnit.advanceTarget();
                }
            }
        }

        for (int right = 0; right < rightTeam.units.size(); right++) {
            // right unit reference
            Unit& rightUnit = rightTeam.units[right];

            // get right unit collider
            Collider rightCollider = rightUnit.getCollider();

            if (rightUnit.step()) rightTeam.alive--;

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

            for (int i = 0; i < 3; i++) {
                Unit& leftBaseUnit = leftTeam.baseUnits[i];
                Collider leftBaseCollider = leftBaseUnit.getCollider();

                if (rightCollider.checkVisionCollision(leftBaseCollider)) {
                    if (!rightUnit.hasTarget() && leftBaseUnit.isLiving()) {
                        rightUnit.setTarget(&leftBaseUnit);
                        rightUnit.advanceTarget();
                    }
                }

                if (leftBaseCollider.checkVisionCollision(rightCollider)) {
                    if (!leftBaseUnit.hasTarget() && rightUnit.isLiving()) {
                        leftBaseUnit.setTarget(&rightUnit);
                        leftBaseUnit.advanceTarget();
                    }
                }


                rightTeam.baseUnits[i].step();
                leftTeam.baseUnits[i].step();
            }
        }

        /*
        for (auto lUnit : leftTeam.units)
            // step left unit
            if (lUnit.step()) leftTeam.alive--;
        for (auto rUnit : rightTeam.units)
            // step right unit
            if (rUnit.step()) rightTeam.alive--;

        for (int i = 0; i < 3; i++) {
            rightTeam.baseUnits[i].step();
            leftTeam.baseUnits[i].step();
        }
        */

    }
}

void RoundManager::draw(sf::RenderWindow& window) {
    for (int i = 0; i < 3; i++) {
        if (leftTeam.baseUnits[i].isLiving())
            leftTeam.baseUnits[i].draw(window);
        if (rightTeam.baseUnits[i].isLiving())
            rightTeam.baseUnits[i].draw(window);
    }
    for (Unit leftUnit : leftTeam.units) {
    	if (leftUnit.isLiving())
    		leftUnit.draw(window);
    }
    for (Unit rightUnit : rightTeam.units) {
    	if (rightUnit.isLiving())
    		rightUnit.draw(window);
    }
}

bool RoundManager::areUnitsAlive() {
	return leftTeam.hasUnitsAlive() || rightTeam.hasUnitsAlive();
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

bool RoundManager::gameOver() {
	return !hasLostGame(Enums::RIGHT) && !hasLostGame(Enums::LEFT);
}
