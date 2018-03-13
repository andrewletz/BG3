#ifndef TEAM_HPP
#define TEAM_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "unit.hpp"

class Team {

public:
	Team();
	~Team() {};

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