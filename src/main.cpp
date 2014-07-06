#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL2_image/SDL_image.h>
#include "cleanup.h"
#include "logging.h"
#include "res_path.h"
#include "settings.h"
#include "snake.h"
#include "egg.h"

const int WIN_POS_X = 100;
const int WIN_POS_Y = 100;
const int WIN_W = 500;
const int WIN_H = 500;
const char* WIN_TITLE = "Snake v0.1";

/*
 * Loads an image into a texture on the rendering device
 * @param file The image file to load
 * @param ren The renderer to load the texture onto
 * @return the loaded texture, or nullptr if something went wrong.
 */
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr){	
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
* width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param w The width of the texture to draw
* @param h The height of the texture to draw
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

void renderBackground(SDL_Texture *tex, SDL_Renderer *ren){
	int x,y = 0;
	for (int i = 0; i < Settings::TILES_NUM; ++i)
	{
		x = (i % Settings::TILES_HOR) * Settings::TILE_SIZE;
		y = (i / Settings::TILES_HOR) * Settings::TILE_SIZE;
		renderTexture(tex, ren, x, y);
	}
}



int main(int argc, char const *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow(WIN_TITLE, WIN_POS_X, WIN_POS_Y, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		logSDLError(std::cout, "SDL_CreateWindow");
		cleanup(win);
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "SDL_CreateRenderer");
		// cleanup(win, renderer);
		SDL_Quit();
		return 1;
	}

	const std::string resPath = getResourcePath();

	SDL_Texture *tile_tex = loadTexture(resPath + "tile.png", renderer);
	if (tile_tex == nullptr)
	{
		logSDLError(std::cout, "loadTexture");
		// cleanup(win, renderer, tile_tex);
		return 1;
	}


	SDL_Texture *snake_tex = loadTexture(resPath + "snake.png", renderer);
	if (snake_tex == nullptr)
	{
		logSDLError(std::cout, "loadTexture");
		// cleanup(win, renderer, tile_tex, snake_tex);
		return 1;
	}

	SDL_Texture *egg_tex = loadTexture(resPath + "egg.png", renderer);
	if (egg_tex == nullptr)
	{
		logSDLError(std::cout, "loadTexture");
		// cleanup(win, renderer, tile_tex, snake_tex);
		return 1;
	}

	Snake snake;
	Egg egg;

	unsigned int lastTime = 0, currentTime;
	SDL_Event e;
	bool quit = false;
	int currentDirection = Settings::direction::NONE;
	int score = 0;
	while (!quit){
		//Event Polling
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
			if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym){
					case SDLK_ESCAPE:
						quit = true;
						break;
					case SDLK_w:
						if (currentDirection != Settings::direction::DOWN) currentDirection = Settings::direction::UP;
						break;
					case SDLK_a:
						if (currentDirection != Settings::direction::RIGHT) currentDirection = Settings::direction::LEFT;
						break;
					case SDLK_s:
						if (currentDirection != Settings::direction::UP) currentDirection = Settings::direction::DOWN;
						break;
					case SDLK_d:
						if (currentDirection != Settings::direction::LEFT) currentDirection = Settings::direction::RIGHT;
						break;
					default:
						break;
				}
			}
		}
		

		currentTime = SDL_GetTicks();
		 if (currentTime > lastTime + 400) {

		 	quit = snake.moveSnake(currentDirection);
		 	if (snake.foundEgg(egg.pos_x, egg.pos_y))
		 	{
		 		egg.placeEgg();
		 		snake.addSnakePart();
		 		score++;
		 	}

    		SDL_RenderClear(renderer);
			renderBackground(tile_tex, renderer);
			snake.renderSnake(snake_tex, renderer, &renderTexture);
			egg.renderEgg(egg_tex, renderer, &renderTexture);
			SDL_RenderPresent(renderer);
		    lastTime = currentTime;
		  }
	}

	cleanup(win, renderer, tile_tex, snake_tex, egg_tex);
	IMG_Quit();
	SDL_Quit();

	std::cout << "Your score is: " << score << std::endl;

	return 0;
}