#pragma once


class Terrain; //Forward Decleration

class AbsSmoother {
public:
	virtual void smooth_out(Terrain* _terrain) = 0;
	virtual void print_out(Terrain* _terrain) = 0;
};
