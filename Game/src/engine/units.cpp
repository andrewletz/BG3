#include "units.hpp"

Units::Units() {
	castle.cost = 0;    
	castle.attackRadius = 150.f;    
	castle.visionRadius = 200.f;    
	castle.attackDamage = 6;    
	castle.moveSpeed = 0.0f;    
	castle.max_hp = 500;

	tower.cost = 0; 
	tower.attackRadius = 100.f; 
	tower.visionRadius = 200.f; 
	tower.attackDamage = 2; 
	tower.moveSpeed = 0.0f; 
	tower.max_hp = 250;

	manAtArms.cost = 0; 
	manAtArms.attackRadius = 100.f; 
	manAtArms.visionRadius = 200.f; 
	manAtArms.attackDamage = 2; 
	manAtArms.moveSpeed = 0.0f; 
	manAtArms.max_hp = 250;

	bowArcher.cost = 0; 
	bowArcher.attackRadius = 100.f; 
	bowArcher.visionRadius = 200.f; 
	bowArcher.attackDamage = 2; 
	bowArcher.moveSpeed = 0.0f; 
	bowArcher.max_hp = 250;
}

Unit Units::getUnitWithPos(Enums::Units unit_type, TextureManager* texmgr, sf::Vector2f pos, Enums::Teams team) {
	switch (unit_type) {
		case Enums::CASTLE: {
			return Unit(&(texmgr->getRef("castle")), pos, team, this->castle);
			break;
		}
		case Enums::TOWER: {
			return Unit(&(texmgr->getRef("tower")), pos, team, this->tower);
			break;
		}
		case Enums::MAN_AT_ARMS: {
			return Unit(&(texmgr->getRef("man_at_arms")), pos, team, this->manAtArms);
			break;
		}
		case Enums::BOW_ARCHER: {
			return Unit(&(texmgr->getRef("bow_archer")), pos, team, this->bowArcher);
			break;
		}
	}
}
