#include "StandardSmoother.h"


Standard2DSmoother::Standard2DSmoother(int radius) : _radius(radius) {

}

void Standard2DSmoother::smooth_out(Terrain* _terrain) {

	int res = _terrain->getResolution();
	std::vector<float> smoothed_terrain((res + 1)*(res + 1));
	float height = 0;
	float localSum = 0.0;
	int numElements = 0;

	for (int i = 0; i < res + 1; i++)
		for (int j = 0; j < res + 1; j++) {
			localSum = 0.0;
			numElements = 0;
			for (int _i = -_radius; _i <= _radius; _i++)
				for (int _j = -_radius; _j <= _radius; _j++)
					if ((i + _i) >= 0 && (i + _i) < res + 1 && (j + _j) >= 0 && (j + _j) < res + 1) {
						localSum = localSum + _terrain->getHeight(i + _i, j + _j);
						numElements++;
					}
			height = localSum / numElements;
			smoothed_terrain[IDX(i, j, res + 1)] = height;
		}
	_terrain->terrainSwap(smoothed_terrain);
	std::vector<float>().swap(smoothed_terrain);
}

void Standard2DSmoother::print_out(Terrain* _terrain) {
	int res = _terrain->getResolution();

	for (int i = 0; i < res + 1; i++) {
		for (int j = 0; j < res + 1; j++) {
			std::cout << std::fixed << std::setprecision(4) << std::setw(5)
				<< _terrain->getHeight(i, j);
			std::cout << "   ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;

}