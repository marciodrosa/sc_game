#include "ExtraModule.h"
#include "Constants.h"
#include "MovieModule.h"
#include "MusicPlayer.h"
#include <SDL_image.h>
#include <sstream>

using namespace std;
using namespace sc;

ExtraModule::ExtraModule()
{
	mainLabelSurface = nullptr;
	mainLabelTexture = nullptr;
	font = nullptr;
}

ExtraModule::~ExtraModule()
{
	SDL_FreeSurface(mainLabelSurface);
	SDL_DestroyTexture(mainLabelTexture);
	TTF_CloseFont(font);
}

void ExtraModule::Start(GameState& state)
{
	font = TTF_OpenFont("Fonts/CrimsonText-Bold.ttf", 20);
	SDL_Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;
	mainLabelSurface = TTF_RenderText_Blended_Wrapped(font, "EXTRA x1", whiteColor, 300);
	hands.Left = true;
	hands.Right = true;
	hands.Ok = true;
	MusicPlayer::Get()->PlayExtraMusic();
}

void ExtraModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	blinkingBackground.Render(render);
	if (mainLabelTexture == nullptr)
		mainLabelTexture = SDL_CreateTextureFromSurface(render, mainLabelSurface);
	SDL_Rect destRect;
	destRect.x = (SC_SCREEN_WIDTH - mainLabelSurface->w) / 2;
	destRect.y = (SC_SCREEN_HEIGHT - mainLabelSurface->h) / 2;
	destRect.w = mainLabelSurface->w;
	destRect.h = mainLabelSurface->h;
	SDL_RenderCopy(render, mainLabelTexture, nullptr, &destRect);
	hands.Render(render, (SC_SCREEN_WIDTH - hands.GetWidth()) / 2, SC_SCREEN_HEIGHT - hands.GetHeight());
}

void ExtraModule::Finish(GameState& state)
{
}

void ExtraModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RIGHT || inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		result.NextGameModule = new MovieModule;
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
