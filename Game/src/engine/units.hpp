#ifndef UNITS_HPP
#define UNITS_HPP

#include "unit.hpp"
#include "global_enum.hpp"
#include "texture_manager.hpp"

class Units {

public:
	Units();
	~Units() {};

	Attributes castle;
	Attributes tower;
	Attributes manAtArms;
	Attributes bowArcher;

	Unit getUnitWithPos(Enums::Units unit_type, TextureManager* texmgr, sf::Vector2f pos, Enums::Teams team);

};

#endif
