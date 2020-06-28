#include "MovieModule.h"
#include "Constants.h"
#include "ImagesProvider.h"
#include "EndingModule.h"
#include "ExtraModule.h"
#include <SDL_image.h>

using namespace std;
using namespace sc;

MovieModule::MovieModule()
{
	mainLabelSurface = nullptr;
	mainLabelTexture = nullptr;
	movieTexture = nullptr;
	font = nullptr;
}

MovieModule::~MovieModule()
{
	SDL_FreeSurface(mainLabelSurface);
	SDL_DestroyTexture(mainLabelTexture);
	SDL_DestroyTexture(movieTexture);
	TTF_CloseFont(font);
}

void MovieModule::Start(GameState& state)
{
	font = TTF_OpenFont("Fonts/CrimsonText-Bold.ttf", 11);
	SDL_Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;
	Movie& movie = state.Movies[state.CurrentMovieIndex];
	mainLabelSurface = TTF_RenderText_Blended_Wrapped(font, movie.GetFullDescription().c_str(), whiteColor, 160);
}

void MovieModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	Movie& movie = state.Movies[state.CurrentMovieIndex];
	SDL_Surface* movieImage = ImagesProvider::Get()->GetMovieImage(movie.Id);
	if (movieTexture == nullptr)
		movieTexture = SDL_CreateTextureFromSurface(render, movieImage);
	if (mainLabelTexture == nullptr)
		mainLabelTexture = SDL_CreateTextureFromSurface(render, mainLabelSurface);
	SDL_Rect destRect;
	destRect.x = 10;
	destRect.y = (SC_SCREEN_HEIGHT - movieImage->h) / 2;
	destRect.w = movieImage->w;
	destRect.h = movieImage->h;
	SDL_RenderCopy(render, movieTexture, nullptr, &destRect);
	destRect.x += destRect.w + 10;
	destRect.y = (SC_SCREEN_HEIGHT - mainLabelSurface->h) / 2;
	destRect.w = mainLabelSurface->w;
	destRect.h = mainLabelSurface->h;
	SDL_RenderCopy(render, mainLabelTexture, nullptr, &destRect);
}

void MovieModule::Finish(GameState& state)
{
}

void MovieModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RIGHT || inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		state.CurrentMovieIndex++;
		if (state.CurrentMovieIndex >= state.Movies.size())
		{
			state.CurrentMovieIndex = state.Movies.size() - 1;
			result.NextGameModule = new EndingModule;
		}
		else
		{
			if (state.Movies[state.CurrentMovieIndex].IsExtra)
				result.NextGameModule = new ExtraModule;
			else
				result.NextGameModule = new MovieModule;
		}
	}
	else if (inputEvent.keysym.sym == SDLK_LEFT)
	{
		state.CurrentMovieIndex--;
		if (state.CurrentMovieIndex < 0)
			state.CurrentMovieIndex = 0;
		else
			result.NextGameModule = new MovieModule;
	}
}
