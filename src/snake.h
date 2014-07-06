#ifndef SNAKE_H
#define SNAKE_H 

#include <SDL.h>

class Snake
{
public:
	Snake();
	// ~Snake();

	struct snake_part{
		int pos_x;
		int pos_y;
	};

	bool didCollide(snake_part a, snake_part b);
	bool foundEgg(int egg_pos_x, int egg_pos_y);

	bool moveSnake(int direction);
	void addSnakePart();

	typedef void (*RenderCallback)(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
	void renderSnake(SDL_Texture *tex, SDL_Renderer *ren, RenderCallback callback);


private:

	snake_part snake_array[10];
	int snake_length;
};


#endif