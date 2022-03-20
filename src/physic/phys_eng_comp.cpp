#include "phys_eng_comp.h"

void phys_eng_comp::update(float delta) {

	phys_engine.simulate(delta);
	phys_engine.inter_colis();

}