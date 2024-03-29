// TerrainGenerator.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//
#include "Utils.h"
#include "Terrain.h"
#include "DiamondSquare.h"
#include "StandardSmoother.h"

/**********************************/
/*      Tuning Parameters         */
/**/#define ROUGHNESS 1.0       /**/
/**/#define SDEV 1.0            /**/
/**/#define SMOOTHER_RADIUS 3   /**/
/**/#define NUM_OF_SMOOTHING 3  /**/
/*      Tuning Parameters         */
/**********************************/
/*********************************************************************************************************************/
/*                                                  Textures                                                         */
/**/  const wchar_t* grass   = (TEXT("../../../../external/textures/gras15.jpg"));                                 /**/
/**/  const wchar_t* mud     = (TEXT("../../../../external/textures/mud02.jpg"));                                  /**/
/**/  const wchar_t* pebble  = (TEXT("../../../../external/textures/pebble03.jpg"));                               /**/
/**/  const wchar_t* rock    = (TEXT("../../../../external/textures/rock5.jpg"));                                  /**/
/*                                                  Textures                                                         */
/*********************************************************************************************************************/


int _tmain(int argc, _TCHAR* argv[])
{
	int resolution = 0;
	_TCHAR* heightfield_filename;
	_TCHAR* color_filename;
	_TCHAR* normal_filename;

	if (!parse_args(argc, argv, resolution, heightfield_filename, color_filename, normal_filename))
	{
		return 0;
	}
	
	DiamondSquare diamondSquareGenerator(SDEV, ROUGHNESS);
	Standard2DSmoother smoother(SMOOTHER_RADIUS);

	Terrain part2(resolution, heightfield_filename, color_filename, normal_filename, grass, mud, pebble, rock);

	part2.setGenerator(&diamondSquareGenerator);
	part2.setSmoother(&smoother);

	//Apply Diamond and Square
	part2.generateTerrainHeight();
	part2.normalizeTerrain();

	//Smooth the terrain
	for (int i = 0; i < NUM_OF_SMOOTHING; i++) part2.smoothTerrain();

	//Produce Outputs
	part2.generateTextures();
	part2.heightFieldDownSizing();
	part2.saveDownSizedTerrainHeight();

	system("PAUSE");

	return 0;
}

