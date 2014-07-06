#include "egg.h"
#include "settings.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

	Egg::Egg(){
		srand (time(NULL));
		placeEgg();
	}

	void Egg::renderEgg(SDL_Texture *tex, SDL_Renderer *ren, RenderCallback callback){
		int x = (pos_x-1) * Settings::TILE_SIZE;
		int y = (pos_y-1) * Settings::TILE_SIZE;
		callback(tex, ren, x, y);
	}

	void Egg::placeEgg(){
		pos_x = rand() % 10 + 1;
		pos_y = rand() % 10 + 1;
	}