#pragma once
#include "AbsSmoother.h"
#include <vector>
#include "Terrain.h"


//class 2D vector smoothing
class Standard2DSmoother : public AbsSmoother {
private:
	int _radius;
public:
	Standard2DSmoother(int radius);
	void smooth_out(Terrain* _terrain);
	void print_out(Terrain* _terrain);
};
