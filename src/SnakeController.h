#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H 

#include <SDL.h>
#include <deque>

class SnakeController
{
public:
	SnakeController();
	SnakeController(int pos_x, int pos_y);
	// ~SnakeController();

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

	int getLength();


private:
	std::deque <snake_part> snake_deque;
	snake_part getSnakeHead();
};


#endif