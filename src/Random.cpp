#include "Random.h"


RandomNormal::RandomNormal(float mean, float sigma, float min, float max) : 
_mean(mean),
_sigma(sigma),
_min(min),
_max(max),
generator(42),
s_dist(_mean, _sigma) {
}

float RandomNormal::generate() {

	float rand_num = _min - 1;

	while (rand_num < _min || rand_num > _max) rand_num = s_dist(generator);

	return rand_num;
}