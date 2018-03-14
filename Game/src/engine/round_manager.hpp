#ifndef ROUND_MANAGER_HPP

#define ROUND_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "team.hpp"
#include "global_enum.hpp"

class RoundManager {

public:
	RoundManager(Game* game);
	~RoundManager() {};
	
	enum Phase {PLACE, FIGHT};

	Game* game;

	Team leftTeam;
	Team rightTeam;

	Phase phase;

	int roundNumber;

	float maxPlacingTime; //the length of time the player gets to place units for
	float time;

	Enums::Teams currTeam;

	void update(const float dt);
	void draw(sf::RenderWindow& window);

	bool areUnitsAlive();
	bool hasLostGame(Enums::Teams team);

};

#endif