#ifndef ROUND_MANAGER_HPP
#define ROUND_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "team.hpp"

class RoundManager{
public:
	enum Teams {LEFT, RIGHT};

	Team leftTeam;
	Team rightTeam;
	int roundNumber = 0;
	int roundTime; //the length of time the player gets to place units for
	RoundManager::Teams currTeam = LEFT;
};

#endif