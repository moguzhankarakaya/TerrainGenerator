#include "Texture.h"

Texture::Texture() : image(0, 0) {

	height = 0;
	width = 0;
}

Texture::Texture(const wchar_t* fileName) : image(fileName) {

	width = image.getWidth();
	height = image.getHeight();
}

Texture::~Texture()
{
}

Color Texture::getColor(int u, int v) {
	int x = u % width;
	int y = v % height;
	Color returnColor;
	image.getPixel(x, y, returnColor.red, returnColor.green, returnColor.blue);

	return returnColor;
}