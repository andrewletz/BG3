#ifndef TEAM_HPP
#define TEAM_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Team{
public:
	Team(int teamNum);
	~Team();

	//std::vector<Unit> units; TODO: add this in when the unit code gets integrated
	int shekels;

};

#endif