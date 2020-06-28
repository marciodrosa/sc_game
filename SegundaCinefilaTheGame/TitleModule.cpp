#include "TitleModule.h"
#include "CharacterSelectionModule.h"
#include "Constants.h"
#include "MusicPlayer.h"
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
	SDL_FreeSurface(mainLabelSurface);
	SDL_DestroyTexture(mainLabelTexture);
	TTF_CloseFont(font);
}

void TitleModule::Start(GameState& state)
{
	logoImage = IMG_Load("Images/Logo.png");
	font = TTF_OpenFont("Fonts/CrimsonText-Bold.ttf", 11);
	SDL_Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;
	mainLabelSurface = TTF_RenderText_Blended_Wrapped(font, "Comandos: teclas para esquerda, direita e Enter", whiteColor, 300);
	MusicPlayer::Get()->PlayTitleMusic();
}

void TitleModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	if (logoTexture == nullptr)
		logoTexture = SDL_CreateTextureFromSurface(render, logoImage);
	if (mainLabelTexture == nullptr)
		mainLabelTexture = SDL_CreateTextureFromSurface(render, mainLabelSurface);
	SDL_RenderCopy(render, logoTexture, nullptr, nullptr);
	SDL_Rect destRect;
	destRect.x = (SC_SCREEN_WIDTH - mainLabelSurface->w) / 2;
	destRect.y = 200;
	destRect.w = mainLabelSurface->w;
	destRect.h = mainLabelSurface->h;
	SDL_RenderCopy(render, mainLabelTexture, nullptr, &destRect);
}

void TitleModule::Finish(GameState& state)
{
}

void TitleModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
		result.NextGameModule = new CharacterSelectionModule;
}
