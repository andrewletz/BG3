#ifndef ROUND_MANAGER_HPP

#define ROUND_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "team.hpp"

class RoundManager {

public:
	RoundManager();
	~RoundManager() {};
	
	enum Teams {LEFT, RIGHT};
	enum Phase {PLACE, FIGHT};

	Team leftTeam;
	Team rightTeam;

	Phase phase;

	int roundNumber;

	float maxPlacingTime; //the length of time the player gets to place units for
	float time;

	Teams currTeam;

	void update(const float dt);
	bool areUnitsAlive();
	bool hasLostGame(Teams team);

};

#endif