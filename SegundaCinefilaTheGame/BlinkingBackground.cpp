#include "BlinkingBackground.h"
#include <stdlib.h> 

using namespace sc;

BlinkingBackground::BlinkingBackground()
{

}

BlinkingBackground::~BlinkingBackground()
{

}

void BlinkingBackground::Render(SDL_Renderer* render)
{
	SDL_SetRenderDrawColor(render, RandomComponent(), RandomComponent(), RandomComponent(), 255);
	SDL_RenderFillRect(render, nullptr);
}

int BlinkingBackground::RandomComponent()
{
	return rand() % 150;
}
