#pragma once
#include "AbsGenerator.h"
#include "Random.h"
#include "Terrain.h"

//class Diamond&Square
class DiamondSquare : public AbsGenerator {
public:
	float _s_dev;
	float _roughness;
public:
	DiamondSquare(float s_dev, float roughness);
	int  calc_steps(Terrain* _terrain);
	void generate(Terrain* _terrain);
	void initGrid(Terrain* _terrain, RandomNormal& s_rand);
	void diamond(Terrain* _terrain, int step, RandomNormal& s_dist, float s_dev);
	void square(Terrain* _terrain, int step, RandomNormal& s_dist, float s_dev);
};

