#include <iostream>
#include <SDL.h>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("Segunda Cinefila", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, 0); // SDL_WINDOW_FULLSCREEN
	bool running = true;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
