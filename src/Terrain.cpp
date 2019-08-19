#include "Terrain.h"

Terrain::Terrain() {
	_res = 512;
	_height = TEXT("height.png");
	_color = TEXT("color.png");
	_normal = TEXT("normal.png");
	_size = (_res + 1)*(_res + 1);
	_terrain.resize(_size);

}

Terrain::Terrain(int res, _TCHAR* height, _TCHAR* color, _TCHAR* normal) : _res(res),
																		  _height(height),
																		  _color(color),
																		  _normal(normal) {
	_size = (_res + 1)*(_res + 1);
	_terrain.resize(_size);
}

Terrain::Terrain(int res, _TCHAR* height, _TCHAR* color, _TCHAR* normal, 
	   const wchar_t* grass, const  wchar_t* mud, 
	   const wchar_t* pebble, const wchar_t* rock) : _res(res),
    												 _height(height),
													 _color(color),
													 _normal(normal) {
	_size = (_res + 1)*(_res + 1);
	_terrain.resize(_size);
	_tex_pack.grass = grass;
	_tex_pack.mud = mud;
	_tex_pack.pebble = pebble;
	_tex_pack.rock = rock;
}

Terrain::~Terrain() {
	std::vector<float>().swap(_terrain);
}

int Terrain::getResolution() {
	return _res;
}

float Terrain::getHeight(int x, int y) {
	return _terrain[IDX(x, y, _res + 1)];
}

void Terrain::setHeight(int x, int y, float height) {
	_terrain[IDX(x, y, _res + 1)] = height;
}

void Terrain::setGenerator(AbsGenerator* terrainGenerator) {
	_terrainGenerator = terrainGenerator;
}

void Terrain::setSmoother(AbsSmoother* smoother) {
	_smoother = smoother;
}

void Terrain::setTexturePack(wchar_t* grass, wchar_t* mud, wchar_t* pebble, wchar_t* rock) {
	
	_tex_pack.grass = grass;
	_tex_pack.mud = mud;
	_tex_pack.pebble = pebble;
	_tex_pack.rock = rock;
}

void Terrain::printInfo() {
	std::cout << _res << std::endl;
	_tprintf(_T("height: %s"), _height);
	std::cout << std::endl;
	_tprintf(_T("color: %s"), _color);
	std::cout << std::endl;
	_tprintf(_T("normal: %s"), _normal);
	std::cout << std::endl;

	long int p[10] = {};
	for (u_int i = 0; i < _terrain.size(); i++) {
		++p[max(min(int(_terrain[i] * 10), 9), 0)];
	}
	float n_star = _res / 1024.0f * 10000;
	for (int i = 0; i < 10; i++) {
		std::cout << std::fixed << std::setprecision(1) << std::setw(2)
			<< i / 10.0 << "-" << (i + 1) / 10.0 << " : "
			<< std::string(max(int(p[i] / n_star), 0), '*') << std::endl;
	}

}

void Terrain::printTerrainHeight() {
	_smoother->print_out(this);
}

void Terrain::fillTheArray() {

	RandomNormal normalDist(0.0, 1.0, 0.0, 1.0);

	for (auto it = _terrain.begin(); it != _terrain.end(); ++it) {
		*it = normalDist.generate();
	}
}

void Terrain::terrainSwap(std::vector<float> terrain) {
	_terrain.swap(terrain);
}

void Terrain::generateTerrainHeight() {
	_terrainGenerator->generate(this);
}

void Terrain::normalizeTerrain() {
	auto minimax = std::minmax_element(_terrain.begin(), _terrain.end());
	float diff = _terrain[minimax.second - _terrain.begin()] - _terrain[minimax.first - _terrain.begin()];
	float base = -1 * _terrain[minimax.first - _terrain.begin()];
	for (auto it = _terrain.begin(); it != _terrain.end(); it++) {
		*it = (*it + base) / diff;
	}
}

void Terrain::smoothTerrain() {
	_smoother->smooth_out(this);
}

void Terrain::saveTerrainHeight() {
	GEDUtils::SimpleImage height_image(_res, _res);
	for (int i = 0; i < _res; i++) {
		for (int j = 0; j < _res; j++) {
			height_image.setPixel(i, j, _terrain[IDX(i, j, _res + 1)]);
		}
	}
	height_image.save(_height);
}

void Terrain::saveDownSizedTerrainHeight() {
	GEDUtils::SimpleImage height_image(_res / 4, _res / 4);
	for (int i = 0; i < _res / 4; i++) {
		for (int j = 0; j < _res / 4; j++) {
			height_image.setPixel(i, j, _downsizeterrain[IDX(i, j, _res / 4)]);
		}
	}
	height_image.save(_height);
}

void Terrain::generateTextures() {
	TextureGenerator text_gen(_tex_pack.grass, _tex_pack.mud, _tex_pack.pebble, _tex_pack.rock);
	text_gen.GenerateTexure(_terrain, _res, _color, _normal);
}

void Terrain::heightFieldDownSizing() {

	int downSize = (_res / 4) * (_res / 4);
	_downsizeterrain.resize(downSize);
	float average = 0;
	
	for (int x = 0; x < _res; x += 4) {
		for (int y = 0; y < _res; y += 4) {
			
			for (int i = x; i < x + 4; i++) {
				for (int j = y; j < y + 4; j++) {
					average += _terrain[IDX(i, j, _res + 1)];
				}
			}

			average /= 16;
			_downsizeterrain[IDX(x / 4, y / 4, _res / 4)] = average;
			average = 0;

		}
	}

}