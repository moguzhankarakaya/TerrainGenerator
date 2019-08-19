#pragma once

#include <tchar.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <vector>
#include <array>
#include "SimpleImage.h"
#include "Texture.h"


int idx(int x, int y, int w);

typedef struct Vector3d {
	float delx;
	float dely;
	float delz;
	float size;
	void normalize() {
		size = sqrt(delx*delx + dely*dely + delz*delz);
		delx = delx / size;
		dely = dely / size;
		delz = delz / size;
	}
	float slope() {
		return sqrt(pow(delx, 2) + pow(dely, 2));
	}
} Vector3d;

typedef struct AlphaChnl {
	float alpha1;
	float alpha2;
	float alpha3;
	void calculateAlpha(float height, float slope) {
		alpha1 = (1 - height) * slope;
		alpha2 = height;
		alpha3 = height * slope;
	}
} AlhpaChnl;

class TextureGenerator {
private:
	Texture _grass;
	Texture _mud;
	Texture _pebble;
	Texture _rock;
	std::array<float, 4> _alphaValues;
	bool _isTexturePackLoad;
	std::vector<Vector3d> _normalField;
	std::vector<AlphaChnl> _alphaField;
	std::vector<Color> _blendedTexture;
public:
	TextureGenerator();
	TextureGenerator(const wchar_t* grass, const wchar_t* mud,
		const wchar_t* pebble, const wchar_t* rock);
	~TextureGenerator();
	void GenerateTexure(std::vector<float>& terrain, int res, _TCHAR* color, _TCHAR* normal);
	void CalculateNormal(std::vector<float>& terrain, int res);
	void CalculateAlphas(std::vector<float>& terrain, int res);
	void TextureBlender(int res);
	void ColorBlender(int side, int x, int y, std::array<Color, 4>& ColorArray, Color& BlendedColor);
	void normalizeTextureRGBValue();
	void saveTextureImage(int res, _TCHAR* texture);
	void normalizeNormalRGBValues();
	void saveNormalImage(int res, _TCHAR* normal);
};
