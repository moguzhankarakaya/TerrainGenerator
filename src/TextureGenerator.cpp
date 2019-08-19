#include "TextureGenerator.h"

int idx(int x, int y, int w) {

	if (x < 0) return 0;
	if (y < 0) return 0;
	if (x > w - 1) return 0;
	if (y > w - 1) return 0;

	return ((x)+(y) * (w));
}

TextureGenerator::TextureGenerator() {
	_isTexturePackLoad = false;
}

TextureGenerator::TextureGenerator(const wchar_t* grass, const wchar_t* mud,
	const wchar_t* pebble, const wchar_t* rock) :
	_grass(grass),
	_mud(mud),
	_pebble(pebble),
	_rock(rock) {

	_isTexturePackLoad = true;
}

TextureGenerator::~TextureGenerator() {

}

void TextureGenerator::GenerateTexure(std::vector<float>& terrain, int res,
	_TCHAR* color, _TCHAR* normal) {
	if (!_isTexturePackLoad) {
		std::cout << "Texture pack hasn't been initilized. Initialize texture pack " << std::endl
			<< "befor generating game texture content." << std::endl;
		return;
	}
	if (terrain.size() != (res + 1)*(res + 1)) {
		std::cout << "Given height height field has inconsistent dimension" << std::endl;
		return;
	}
	CalculateNormal(terrain, res);
	CalculateAlphas(terrain, res);
	TextureBlender(res);
	saveTextureImage(res, color);
	saveNormalImage(res, normal);
}

void TextureGenerator::CalculateNormal(std::vector<float>& terrain, int res) {
	Vector3d normalVector;
	int _side = res + 1;
	int _size = (res + 1)*(res + 1);
	_normalField.resize(_size);

	float stepSize = 1.0f / (_side);

	for (int x = 0; x < res; x++) {
		for (int y = 0; y < res; y++) {
			if(x == 0)
				normalVector.delx = -1 * (terrain[idx(x + 1, y, _side)] - terrain[idx(x, y, _side)]) / (stepSize);
			else if (x == res - 1)
				normalVector.delx = -1 * (terrain[idx(x, y, _side)] - terrain[idx(x - 1, y, _side)]) / (stepSize);
			else
				normalVector.delx = -1 * (terrain[idx(x + 1, y, _side)] - terrain[idx(x - 1, y, _side)]) / (2 * stepSize);
			if (y == 0)
				normalVector.dely = -1 * (terrain[idx(x, y + 1, _side)] - terrain[idx(x, y, _side)]) / (stepSize);
			else if (y == res - 1)
				normalVector.dely = -1 * (terrain[idx(x, y, _side)] - terrain[idx(x, y - 1, _side)]) / (stepSize);
			else
				normalVector.dely = -1 * (terrain[idx(x, y + 1, _side)] - terrain[idx(x, y - 1, _side)]) / (2 * stepSize);

			normalVector.delz = 1;
			normalVector.normalize();
			_normalField[idx(x, y, _side)] = normalVector;
		}
	}
}

void TextureGenerator::CalculateAlphas(std::vector<float>& terrain, int res) {
	AlphaChnl alphaGroup;
	int _side = res + 1;
	int _size = (res + 1)*(res + 1);
	_alphaField.resize(_size);

	float height = 0;
	float slope = 0;

	for (int x = 0; x < _side; x++) {
		for (int y = 0; y < _side; y++) {
			height = terrain[idx(x, y, _side)];
			slope = _normalField[idx(x, y, _side)].slope();
			alphaGroup.calculateAlpha(height, slope);
			_alphaField[idx(x, y, _side)].alpha1 = alphaGroup.alpha1;
			_alphaField[idx(x, y, _side)].alpha2 = alphaGroup.alpha2;
			_alphaField[idx(x, y, _side)].alpha3 = alphaGroup.alpha3;
		}
	}
}

void TextureGenerator::TextureBlender(int res) {
	int _side = res + 1;
	int _size = (res + 1)*(res + 1);
	std::array<Color, 4> ColorArray;
	Color blendedColor;
	_blendedTexture.resize(_size);

	for (int x = 0; x < _side; x++) {
		for (int y = 0; y < _side; y++) {
			ColorArray[0] = _grass.getColor(x, y);
			ColorArray[1] = _mud.getColor(x, y);
			ColorArray[2] = _pebble.getColor(x, y);
			ColorArray[3] = _rock.getColor(x, y);
			ColorBlender(_side, x, y, ColorArray, blendedColor);
			_blendedTexture[idx(x, y, _side)].blue = blendedColor.blue;
			_blendedTexture[idx(x, y, _side)].green = blendedColor.green;
			_blendedTexture[idx(x, y, _side)].red = blendedColor.red;
		}
	}
}

void TextureGenerator::ColorBlender(int side, int x, int y, std::array<Color, 4>& ColorArray, Color& BlendedColor) {

	BlendedColor.blue = _alphaField[idx(x, y, side)].alpha3 * ColorArray[3].blue +
		(1 - _alphaField[idx(x, y, side)].alpha3) *
		(_alphaField[idx(x, y, side)].alpha2 * ColorArray[2].blue +
		(1 - _alphaField[idx(x, y, side)].alpha2) *
			(_alphaField[idx(x, y, side)].alpha1 * ColorArray[1].blue +
			(1 - _alphaField[idx(x, y, side)].alpha1) * ColorArray[0].blue));
	BlendedColor.green = _alphaField[idx(x, y, side)].alpha3 * ColorArray[3].green +
		(1 - _alphaField[idx(x, y, side)].alpha3) *
		(_alphaField[idx(x, y, side)].alpha2 * ColorArray[2].green +
		(1 - _alphaField[idx(x, y, side)].alpha2) *
			(_alphaField[idx(x, y, side)].alpha1 * ColorArray[1].green +
			(1 - _alphaField[idx(x, y, side)].alpha1) * ColorArray[0].green));
	BlendedColor.red = _alphaField[idx(x, y, side)].alpha3 * ColorArray[3].red +
		(1 - _alphaField[idx(x, y, side)].alpha3) *
		(_alphaField[idx(x, y, side)].alpha2 * ColorArray[2].red +
		(1 - _alphaField[idx(x, y, side)].alpha2) *
			(_alphaField[idx(x, y, side)].alpha1 * ColorArray[1].red +
			(1 - _alphaField[idx(x, y, side)].alpha1) * ColorArray[0].red));

}

void TextureGenerator::normalizeTextureRGBValue() {
	float max = _blendedTexture[0].max_color();
	for (auto it = _blendedTexture.begin(); it != _blendedTexture.end(); it++) {
		if ((*it).max_color() > max)
			max = (*it).max_color();
	}
	for (auto it = _blendedTexture.begin(); it != _blendedTexture.end(); it++) {
		(*it).blue = (*it).blue / max;
		(*it).red = (*it).red / max;
		(*it).green = (*it).green / max;
	}
}

void TextureGenerator::saveTextureImage(int res, _TCHAR* texture) {
	normalizeTextureRGBValue();
	GEDUtils::SimpleImage texture_image(res, res);
	for (int i = 0; i < res; i++) {
		for (int j = 0; j < res; j++) {
			texture_image.setPixel(i, j, _blendedTexture[idx(i, j, res + 1)].red,
				_blendedTexture[idx(i, j, res + 1)].green,
				_blendedTexture[idx(i, j, res + 1)].blue);
		}
	}
	texture_image.save(texture);
}

void TextureGenerator::normalizeNormalRGBValues() {
	for (auto it = _normalField.begin(); it != _normalField.end(); it++) {
		(*it).delx = ((*it).delx + 1) / 2;
		(*it).dely = ((*it).dely + 1) / 2;
		(*it).delz = ((*it).delz + 1) / 2;
	}
}

void TextureGenerator::saveNormalImage(int res, _TCHAR* normal) {
	normalizeNormalRGBValues();
	GEDUtils::SimpleImage normal_image(res, res);
	for (int i = 0; i < res; i++) {
		for (int j = 0; j < res; j++) {
			normal_image.setPixel(i, j, _normalField[idx(i, j, res + 1)].delx,
				_normalField[idx(i, j, res + 1)].dely,
				_normalField[idx(i, j, res + 1)].delz);
		}
	}
	normal_image.save(normal);
}