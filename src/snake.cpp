#include "snake.h"
// #include "cleanup.h"
#include "settings.h"
#include <iostream>

Snake::Snake() : snake_length(1) {
	snake_array[0] = snake_part{1, 1};
}

bool Snake::moveSnake(int direction){
	if (direction == Settings::direction::NONE)
	{
		return false;
	}
	// Shift the rest of the snake
	for (int i = snake_length-1; i > 0 ; i--)
	{
		snake_array[i].pos_x = snake_array[i-1].pos_x;
		snake_array[i].pos_y = snake_array[i-1].pos_y;
	}

	// Move the Snake Head
	switch(direction){
		case Settings::direction::NONE:
			break;
		case Settings::direction::UP:
			this->snake_array[0].pos_y--;
			break;
		case Settings::direction::DOWN:
			this->snake_array[0].pos_y++;
			break;
		case Settings::direction::LEFT:
			this->snake_array[0].pos_x--;
			break;
		case Settings::direction::RIGHT:
			this->snake_array[0].pos_x++;
			break;
		default:
			break;
	}

	for (int a = 1; a < snake_length; ++a)
	{
		if (didCollide(snake_array[0], snake_array[a])){
			return true;
		}
	}

	
}

void Snake::addSnakePart(){
	snake_part newPart = snake_array[snake_length-1];
	snake_array[snake_length] = newPart;
	snake_length++;
}

void Snake::renderSnake(SDL_Texture *tex, SDL_Renderer *ren, RenderCallback callback){
	for (int i = 0; i < snake_length; ++i)
	{
		int x = (snake_array[i].pos_x-1) * Settings::TILE_SIZE;
		int y = (snake_array[i].pos_y-1) * Settings::TILE_SIZE;
		callback(tex, ren, x, y);
	};
}

bool Snake::didCollide(snake_part a, snake_part b){
	if (a.pos_x == b.pos_x && a.pos_y == b.pos_y)
	{
		return true;
	}
	return false;
}

bool Snake::foundEgg(int egg_pos_x, int egg_pos_y){
	if (snake_array[0].pos_x == egg_pos_x && snake_array[0].pos_y == egg_pos_y)
	{
		return true;
	}
	return false;
}