#include "CharacterSelectionModule.h"
#include "IntroModule.h"
#include "Constants.h"
#include <SDL_image.h>

using namespace std;
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
	for (CharacterSelectionIcon* characterIcon : characterIcons)
	{
		delete characterIcon;
	}
}

void CharacterSelectionModule::Start(GameState& state)
{
	font = TTF_OpenFont("Fonts/CrimsonText-Bold.ttf", 24);
	SDL_Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;
	mainLabelSurface = TTF_RenderText_Blended(font, "Selecione o seu cinéfilo:", whiteColor);
	for (Character& character : state.Characters)
	{
		characterIcons.push_back(new CharacterSelectionIcon(&character));
	}
	hands.Left = true;
	hands.Right = true;
	hands.Ok = true;
}

void CharacterSelectionModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	if (mainLabelTexture == nullptr)
		mainLabelTexture = SDL_CreateTextureFromSurface(render, mainLabelSurface);
	SDL_Rect destRect;
	destRect.x = (SC_SCREEN_WIDTH - mainLabelSurface->w) / 2;
	destRect.y = 10;
	destRect.w = mainLabelSurface->w;
	destRect.h = mainLabelSurface->h;
	SDL_RenderCopy(render, mainLabelTexture, nullptr, &destRect);
	int totalCharactersWidth = (characterIcons.size() * 42) - 10;
	int x = (SC_SCREEN_WIDTH - totalCharactersWidth) / 2;
	int y = (SC_SCREEN_HEIGHT / 2) - 16;
	for (CharacterSelectionIcon* characterIcon : characterIcons)
	{
		characterIcon->Render(state, render, x, y);
		x += 42;
	}
	DrawCharacterName(state, render);
	hands.Render(render, (SC_SCREEN_WIDTH - hands.GetWidth()) / 2, SC_SCREEN_HEIGHT - hands.GetHeight());
}

void CharacterSelectionModule::DrawCharacterName(GameState& state, SDL_Renderer* render)
{
	string name = state.Characters[state.SelectedCharacterIndex].Name;
	SDL_Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;
	SDL_Surface* surface = TTF_RenderText_Blended(font, name.c_str(), whiteColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_Rect destRect;
	destRect.x = (SC_SCREEN_WIDTH - surface->w) / 2;
	destRect.y = (SC_SCREEN_HEIGHT / 2) + 26;
	destRect.w = surface->w;
	destRect.h = surface->h;
	SDL_RenderCopy(render, texture, nullptr, &destRect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void CharacterSelectionModule::Finish(GameState& state)
{
}

void CharacterSelectionModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
		result.NextGameModule = new IntroModule;
	else if (inputEvent.keysym.sym == SDLK_LEFT)
	{
		state.SelectedCharacterIndex--;
		if (state.SelectedCharacterIndex < 0)
			state.SelectedCharacterIndex = state.Characters.size() - 1;
	}
	else if (inputEvent.keysym.sym == SDLK_RIGHT)
	{
		state.SelectedCharacterIndex++;
		if (state.SelectedCharacterIndex >= state.Characters.size())
			state.SelectedCharacterIndex = 0;
	}
}
