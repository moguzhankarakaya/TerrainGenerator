#include "DiamondSquare.h"

DiamondSquare::DiamondSquare(float s_dev, float roughness) : _s_dev(s_dev), 
															 _roughness(roughness) {

}

int DiamondSquare::calc_steps(Terrain* _terrain) {
	int num_of_steps = 0;
	int div = _terrain->getResolution();
	while (div > 0) {
		div /= 2;
		++num_of_steps;
	}
	return num_of_steps;
}

void DiamondSquare::initGrid(Terrain* _terrain, RandomNormal& s_rand) {
	int res = _terrain->getResolution();
	_terrain->setHeight(0, 0, s_rand.generate());
	_terrain->setHeight(0, res, s_rand.generate());
	_terrain->setHeight(res, 0, s_rand.generate());
	_terrain->setHeight(res, res, s_rand.generate());
}

void DiamondSquare::generate(Terrain* _terrain) {
	RandomNormal s_dist_pos(0, _s_dev, 0, 1);
	initGrid(_terrain, s_dist_pos);

	RandomNormal s_dist(0, _s_dev, -1, 1);
	int max_step = calc_steps(_terrain);
	float s_dev = 1;
	for (int step = 1; step < max_step; step++) {
		s_dev /= float(pow(2, _roughness));
		square(_terrain, step, s_dist, s_dev);
		diamond(_terrain, step, s_dist, s_dev);

	}

}

void DiamondSquare::diamond(Terrain* _terrain, int step, RandomNormal& s_dist, float s_dev) {
	int res = _terrain->getResolution();
	int foot_length = int(res / pow(2, step));
	int loop_length = int(pow(2, step) + 1);
	int inner_loop =  int(pow(2, step - 1));
	float height = 0;
	int idx_x = 0;
	int idx_y = 0;
	for (int i = 0; i < loop_length; i++) {
		if ((i + 1) % 2 == 1) {
			for (int j = 0; j < inner_loop; j++) {
				idx_x = i*(foot_length);
				idx_y = foot_length + j*(2 * foot_length);
				if (idx_x == 0) {
					height += _terrain->getHeight(idx_x, idx_y - foot_length);
					height += _terrain->getHeight(idx_x, idx_y + foot_length);
					height += _terrain->getHeight(idx_x + foot_length, idx_y);
					height /= 3;
					height += s_dist.generate()*s_dev;
					_terrain->setHeight(idx_x, idx_y, height);
					height = 0;
				}
				else if (idx_x == res) {
					height += _terrain->getHeight(idx_x, idx_y - foot_length);
					height += _terrain->getHeight(idx_x, idx_y + foot_length);
					height += _terrain->getHeight(idx_x - foot_length, idx_y);
					height /= 3;
					height += s_dist.generate()*s_dev;
					_terrain->setHeight(idx_x, idx_y, height);
					height = 0;
				}
				else {
					height += _terrain->getHeight(idx_x - foot_length, idx_y);
					height += _terrain->getHeight(idx_x, idx_y - foot_length);
					height += _terrain->getHeight(idx_x, idx_y + foot_length);
					height += _terrain->getHeight(idx_x + foot_length, idx_y);
					height /= 4;
					height += s_dist.generate()*s_dev;
					_terrain->setHeight(idx_x, idx_y, height);
					height = 0;
				}
			}
		}
		else {
			for (int j = 0; j < inner_loop + 1; j++) {
				idx_x = i*(foot_length);
				idx_y = j*(2 * foot_length);
				if (idx_y == 0) {
					height += _terrain->getHeight(idx_x, idx_y + foot_length);
					height += _terrain->getHeight(idx_x + foot_length, idx_y);
					height += _terrain->getHeight(idx_x - foot_length, idx_y);
					height /= 3;
					height += s_dist.generate()*s_dev;
					_terrain->setHeight(idx_x, idx_y, height);
					height = 0;
				}
				else if (idx_y == res) {
					height += _terrain->getHeight(idx_x, idx_y - foot_length);
					height += _terrain->getHeight(idx_x + foot_length, idx_y);
					height += _terrain->getHeight(idx_x - foot_length, idx_y);
					height /= 3;
					height += s_dist.generate()*s_dev;
					_terrain->setHeight(idx_x, idx_y, height);
					height = 0;
				}
				else {
					height += _terrain->getHeight(idx_x - foot_length, idx_y);
					height += _terrain->getHeight(idx_x, idx_y - foot_length);
					height += _terrain->getHeight(idx_x, idx_y + foot_length);
					height += _terrain->getHeight(idx_x + foot_length, idx_y);
					height /= 4;
					height += s_dist.generate()*s_dev;
					_terrain->setHeight(idx_x, idx_y, height);
					height = 0;
				}
			}
		}
	}
}

void DiamondSquare::square(Terrain* _terrain, int step, RandomNormal& s_dist, float s_dev) {
	int res = _terrain->getResolution();
	int foot_length = int(res / pow(2, step));
	int loop_length = int(pow(2, step - 1));
	float height = 0;
	int idx_x = 0;
	int idx_y = 0;
	for (int i = 0; i < loop_length; i++) {
		for (int j = 0; j < loop_length; j++) {
			idx_x = foot_length + i*(2 * foot_length);
			idx_y = foot_length + j*(2 * foot_length);
			height += _terrain->getHeight(idx_x - foot_length, idx_y - foot_length);
			height += _terrain->getHeight(idx_x - foot_length, idx_y + foot_length);
			height += _terrain->getHeight(idx_x + foot_length, idx_y - foot_length);
			height += _terrain->getHeight(idx_x + foot_length, idx_y + foot_length);
			height /= 4;
			height += s_dist.generate()*s_dev;
			_terrain->setHeight(idx_x, idx_y, height);
			height = 0;
		}
	}
}