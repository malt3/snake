#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:

	static const int TILE_SIZE = 50;
	static const int TILES_HOR = 10;
	static const int TILES_VER = 10;
	static const int TILES_NUM = TILES_HOR * TILES_VER;

	enum direction {UP, DOWN, LEFT, RIGHT, NONE};
};

#endif