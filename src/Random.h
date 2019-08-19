#pragma once
#include <random>
#include <chrono>
#include <iostream>
#include <Windows.h>

class RandomNormal {
private:
	float _mean;
	float _sigma;
	float _min;
	float _max;
	std::default_random_engine generator;
	std::normal_distribution<float> s_dist;
public:
	RandomNormal(float mean, float sigma, float min, float max);
	float generate();

};

extern RandomNormal randomNormal;