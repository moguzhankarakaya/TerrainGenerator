#pragma once

#include <tchar.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <vector>
#include <array>
#include "SimpleImage.h"

typedef struct Color {
	float red;
	float green;
	float blue;
	float max_color() {

		float max = 0;

		if (red > max) {
			max = red;
		}
		if (green > max) {
			max = green;
		}
		if (blue > max) {
			max = blue;
		}

		return max;
	}
} Color;

class Texture
{
private:
	GEDUtils::SimpleImage image;
	UINT height;
	UINT width;

public:
	Texture();
	Texture(const wchar_t* fileName);
	~Texture();
	Color getColor(int u, int v);

};

