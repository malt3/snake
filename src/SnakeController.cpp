#include "SnakeController.h"
#include "settings.h"
#include <iostream>

SnakeController::SnakeController() {
	snake_deque.push_front(snake_part{1, 1});
}

SnakeController::SnakeController(int pos_x, int pos_y) {
	snake_deque.push_front(snake_part{pos_x, pos_y});
}


bool SnakeController::moveSnake(int direction){
	if (direction == Settings::direction::NONE)
	{
		return false;
	}

	// Get the current snake head and its position:
	snake_part head = getSnakeHead();
	int head_pos_x = head.pos_x;
	int head_pos_y = head.pos_y;

	// Get the new head position:
	switch(direction){
		case Settings::direction::NONE:
			break;
		case Settings::direction::UP:
			head_pos_y--;
			break;
		case Settings::direction::DOWN:
			head_pos_y++;
			break;
		case Settings::direction::LEFT:
			head_pos_x--;
			break;
		case Settings::direction::RIGHT:
			head_pos_x++;
			break;
		default:
			break;
	}

	// move tail of the snake to the new position:
	snake_part newHead = snake_part{head_pos_x, head_pos_y};
	snake_deque.push_front(newHead);
	snake_deque.pop_back();

	for (int a = 1; a < getLength(); ++a)
	{
		if (didCollide(getSnakeHead(), snake_deque.at(a))){
			return true;
		}
	}
	return false;

	
}

void SnakeController::addSnakePart(){
	snake_deque.push_back(snake_part{0, 0});
}

void SnakeController::renderSnake(SDL_Texture *tex, SDL_Renderer *ren, RenderCallback callback){
	for (int i = 0; i < getLength(); ++i)
	{
		snake_part currentSnakePart = snake_deque.at(i);
		int x = (currentSnakePart.pos_x-1) * Settings::TILE_SIZE;
		int y = (currentSnakePart.pos_y-1) * Settings::TILE_SIZE;
		callback(tex, ren, x, y);
	};
}

bool SnakeController::didCollide(snake_part a, snake_part b){
	if (a.pos_x == b.pos_x && a.pos_y == b.pos_y)
	{
		return true;
	}
	return false;
}

bool SnakeController::foundEgg(int egg_pos_x, int egg_pos_y){
	snake_part snakeHead = getSnakeHead();
	if (snakeHead.pos_x == egg_pos_x && snakeHead.pos_y == egg_pos_y)
	{
		return true;
	}
	return false;
}

int SnakeController::getLength(){
	return snake_deque.size();
}

SnakeController::snake_part SnakeController::getSnakeHead(){
	return snake_deque.front();
}