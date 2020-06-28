#include "IntroModule.h"
#include "Constants.h"
#include "MovieModule.h"
#include "MusicPlayer.h"
#include "ResourcesManager.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <sstream>

using namespace std;
using namespace sc;

IntroModule::IntroModule()
{
	mainLabelSurface = nullptr;
	mainLabelTexture = nullptr;
	font = nullptr;
}

IntroModule::~IntroModule()
{
	SDL_FreeSurface(mainLabelSurface);
	SDL_DestroyTexture(mainLabelTexture);
	TTF_CloseFont(font);
}

void IntroModule::Start(GameState& state)
{
	font = TTF_OpenFont("Fonts/CrimsonText-Bold.ttf", 14);
	SDL_Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;
	stringstream text;
	text << "É chegado o momento em que a escolha mais "
		<< "importante dos próximos dias deve ser feita: "
		<< "o filme da semana da SEGUNDA CINÉFILA." << endl << endl
		<< "Consulte os filmes a seguir e vote "
		<< "com sabedoria.";
	mainLabelSurface = TTF_RenderText_Blended_Wrapped(font, text.str().c_str(), whiteColor, 300);
	hands.Ok = true;
	MusicPlayer::Get()->PlayGameMusic();
}

void IntroModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
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

void IntroModule::Finish(GameState& state)
{
}

void IntroModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
	{
		result.NextGameModule = new MovieModule;
		Mix_PlayChannel(1, ResourcesManager::Get()->EnterSound, 0);
	}
}
