#pragma once
#include <tchar.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <vector>
#include "SimpleImage.h"
#include "TextureGenerator.h"
#include "AbsGenerator.h"
#include "AbsSmoother.h"
#include "Random.h"

#define IDX(x, y, w) ((x) + (y) * (w))

//class terrain
class Terrain {
private:
	//Terrain Resolution
	int _res;
	//File Names
	_TCHAR* _height;
	_TCHAR* _color;
	_TCHAR* _normal;
	//Texture Files
	typedef struct {
		const wchar_t* grass;
		const wchar_t* mud;
		const wchar_t* pebble;
		const wchar_t* rock;
	} Textures;
	Textures _tex_pack;
	//Prive Calculated Class Memebers
	int _size;
	std::vector<float> _terrain;
	std::vector<float> _downsizeterrain;
	AbsGenerator* _terrainGenerator;
	AbsSmoother* _smoother;
public:
	Terrain();
	Terrain::Terrain(int res, _TCHAR* height, _TCHAR* color, _TCHAR* normal);
	Terrain::Terrain(int res, _TCHAR* height, _TCHAR* color, _TCHAR* normal,
					 const wchar_t* grass, const wchar_t* mud, 
		             const wchar_t* pebble, const wchar_t* rock);
	~Terrain();
	int getResolution();
	float getHeight(int x, int y);
	void setHeight(int x, int y, float height);
	void setGenerator(AbsGenerator* terrainGenerator);
	void setSmoother(AbsSmoother* smoother);
	void setTexturePack(wchar_t* grass, wchar_t* mud, wchar_t* pebble, wchar_t* rock);
	void printInfo();
	void printTerrainHeight();
	void fillTheArray();
	void terrainSwap(std::vector<float> terrain);
	void generateTerrainHeight();
	void normalizeTerrain();
	void smoothTerrain();
	void saveTerrainHeight();
	void saveDownSizedTerrainHeight();
	void generateTextures();
	void heightFieldDownSizing();
};