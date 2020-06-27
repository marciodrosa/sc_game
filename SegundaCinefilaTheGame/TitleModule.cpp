#include "TitleModule.h"
#include "CharacterSelectionModule.h"
#include <SDL_image.h>

using namespace sc;

TitleModule::TitleModule()
{
	logoImage = nullptr;
	logoTexture = nullptr;
}

TitleModule::~TitleModule()
{
	SDL_FreeSurface(logoImage);
	SDL_DestroyTexture(logoTexture);
}

void TitleModule::Start(GameState& state)
{
	logoImage = IMG_Load("Images/Logo.png");
}

void TitleModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	if (logoTexture == nullptr)
		logoTexture = SDL_CreateTextureFromSurface(render, logoImage);
	SDL_RenderCopy(render, logoTexture, nullptr, nullptr);
}

void TitleModule::Finish(GameState& state)
{
}

void TitleModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
		result.NextGameModule = new CharacterSelectionModule;
}
