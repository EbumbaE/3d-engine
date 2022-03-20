#pragma once
#include "phys_object.h"
#include "vector"

class phys_eng {

public:

	phys_eng() {}

	void add(const phys_object &object);
	void simulate(float delta);
	void inter_colis();

	inline const phys_object& get_object(int i) const {

		return objects[i];

	}

	inline unsigned int get_num() const {

		return objects.size();

	}

private:

	vector<phys_object> objects;

};