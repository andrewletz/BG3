#include "units.hpp"

Units::Units() {
	castle.cost = 0;    
	castle.attackRadius = 200.f;    
	castle.visionRadius = 200.f;    
	castle.attackDamage = 1;    
	castle.moveSpeed = 0.0f;    
	castle.max_hp = 1000;
    castle.bodyScale = 1.0f;

	tower.cost = 0; 
	tower.attackRadius = 200.f; 
	tower.visionRadius = 200.f; 
	tower.attackDamage = 1; 
	tower.moveSpeed = 0.0f; 
	tower.max_hp = 500;
    tower.bodyScale = 1.0f;

	manAtArms.cost = 2; 
	manAtArms.attackRadius = 50.f; 
	manAtArms.visionRadius = 100.f; 
	manAtArms.attackDamage = 1; 
	manAtArms.moveSpeed = 0.52f; 
	manAtArms.max_hp = 100;
    manAtArms.bodyScale = 3.0f;

	bowArcher.cost = 3; 
	bowArcher.attackRadius = 150.f; 
	bowArcher.visionRadius = 150.f; 
	bowArcher.attackDamage = 1; 
	bowArcher.moveSpeed = 0.4f; 
	bowArcher.max_hp = 100;
    bowArcher.bodyScale = 3.0f;
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
			return Unit(&(texmgr->getRef("man_at_arms")), pos, team, this->bowArcher);
			break;
		}
	}
}
