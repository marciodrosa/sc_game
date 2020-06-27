#include "CharacterSelectionModule.h"
#include <SDL_image.h>

using namespace sc;

CharacterSelectionModule::CharacterSelectionModule()
{
	mainLabelSurface = nullptr;
	mainLabelTexture = nullptr;
	font = nullptr;
}

CharacterSelectionModule::~CharacterSelectionModule()
{
	SDL_FreeSurface(mainLabelSurface);
	SDL_DestroyTexture(mainLabelTexture);
	TTF_CloseFont(font);
}

void CharacterSelectionModule::Start(GameState& state)
{
	font = TTF_OpenFont("Fonts/CrimsonText-Bold.ttf", 24);
	SDL_Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;
	mainLabelSurface = TTF_RenderUTF8_Blended(font, "Selecione o seu cinefilo:", whiteColor);
}

void CharacterSelectionModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	if (mainLabelTexture == nullptr)
		mainLabelTexture = SDL_CreateTextureFromSurface(render, mainLabelSurface);
	SDL_Rect destRect;
	destRect.x = (320 - mainLabelSurface->w) / 2;
	destRect.y = 10;
	destRect.w = mainLabelSurface->w;
	destRect.h = mainLabelSurface->h;
	SDL_RenderCopy(render, mainLabelTexture, nullptr, &destRect);
}

void CharacterSelectionModule::Finish(GameState& state)
{
}

void CharacterSelectionModule::HandleInput(SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
		result.FinishGame = true;
}
