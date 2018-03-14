#ifndef TEAM_HPP
#define TEAM_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "global_enum.hpp"
#include "unit.hpp"
#include "game.hpp"

class Team {

public:
	Team(Game* game);
	~Team() {};

	Game* game;

	std::vector<Unit> baseUnits;
	std::vector<Unit> units;

	int alive;
	int shekels;

	void addUnit(Unit unit);
	void reset();

	bool hasUnitsAlive();
	bool hasLostGame();

};

#endif