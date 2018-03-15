#include "units.hpp"

Units::Units() {
	castle.cost = 0;    
	castle.attackRadius = 200.f;    
	castle.visionRadius = 200.f;    
	castle.attackDamage = 0;    
	castle.moveSpeed = 0.0f;    
	castle.max_hp = 1000;
        castle.bodyScale = 1.0f;

	tower.cost = 0; 
	tower.attackRadius = 200.f; 
	tower.visionRadius = 200.f; 
	tower.attackDamage = 0; 
	tower.moveSpeed = 0.0f; 
	tower.max_hp = 500;
        tower.bodyScale = 1.0f;

	manAtArms.cost = 2; 
	manAtArms.attackRadius = 30.f; 
	manAtArms.visionRadius = 300.f; 
	manAtArms.attackDamage = 1; 
	manAtArms.moveSpeed = 1.0f; 
	manAtArms.max_hp = 20;
        manAtArms.bodyScale = 3.0f;

	bowArcher.cost = 3; 
	bowArcher.attackRadius = 60.f; 
	bowArcher.visionRadius = 80.f; 
	bowArcher.attackDamage = 1; 
	bowArcher.moveSpeed = 0.1f; 
	bowArcher.max_hp = 8;
        manAtArms.bodyScale = 3.0f;
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
