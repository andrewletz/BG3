#include "units.hpp"

Units::Units() {
	castle.cost = 0;    
	castle.attackRadius = 200.f;    
	castle.visionRadius = 200.f;    
	castle.attackDamage = 8;    
	castle.moveSpeed = 0.0f;    
	castle.max_hp = 80;
    castle.bodyScale = 1.0f;
    castle.attackSpeed = 2.0f;

	tower.cost = 0; 
	tower.attackRadius = 200.f; 
	tower.visionRadius = 200.f; 
	tower.attackDamage = 1; 
	tower.moveSpeed = 0.0f; 
	tower.max_hp = 40;
    tower.bodyScale = 1.0f;
    tower.attackSpeed = 1.0f;

	manAtArms.cost = 2; 
	manAtArms.attackRadius = 35.f; 
	manAtArms.visionRadius = 100.f; 
	manAtArms.attackDamage = 2; 
	manAtArms.moveSpeed = 86.0f; 
	manAtArms.max_hp = 10;
    manAtArms.bodyScale = 3.0f;
    manAtArms.attackSpeed = 0.5f;

	bowArcher.cost = 3; 
	bowArcher.attackRadius = 135.f; 
	bowArcher.visionRadius = 175.f; 
	bowArcher.attackDamage = 2; 
	bowArcher.moveSpeed = 80.0f; 
	bowArcher.max_hp = 8;
    bowArcher.bodyScale = 3.0f;
    bowArcher.attackSpeed = 0.8f;
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
