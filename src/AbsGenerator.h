#pragma once

class Terrain; //Forward declaration

class AbsGenerator {
public:
	virtual void generate(Terrain* _terrain) = 0;
};
