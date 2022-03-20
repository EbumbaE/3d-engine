#pragma once
#include "phys_eng.h"

class phys_eng_comp{

public:

	phys_eng_comp(const phys_eng &eng) :
		phys_engine(eng) {}

	virtual void update(float delta);

	inline const phys_eng &get_phys_eng() {

		return phys_engine;

	}

private:

	phys_eng phys_engine;

};