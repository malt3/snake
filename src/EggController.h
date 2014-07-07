#ifndef EGGCONTROLLER_H
#define EGGCONTROLLER_H

#include <SDL.h>

class EggController
{
public:
	EggController();

	int pos_x;
	int pos_y;

	void placeEgg();

	typedef void (*RenderCallback)(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
	void renderEgg(SDL_Texture *tex, SDL_Renderer *ren, RenderCallback callback);
};




#endif