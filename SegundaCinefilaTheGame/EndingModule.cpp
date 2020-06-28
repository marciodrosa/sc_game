#include "EndingModule.h"
#include "Constants.h"
#include "ResourcesManager.h"
#include "MovieModule.h"
#include "MusicPlayer.h"
#include <SDL_image.h>
#include <sstream>

using namespace std;
using namespace sc;

EndingModule::EndingModule()
{
	mainLabelSurface = nullptr;
	mainLabelTexture = nullptr;
	characterLabelSurface = nullptr;
	characterLabelTexture = nullptr;
	theEndLabelSurface = nullptr;
	theEndLabelTexture = nullptr;
	characterTexture = nullptr;
	font = nullptr;
}

EndingModule::~EndingModule()
{
	SDL_FreeSurface(mainLabelSurface);
	SDL_DestroyTexture(mainLabelTexture);
	SDL_FreeSurface(characterLabelSurface);
	SDL_DestroyTexture(characterLabelTexture);
	SDL_FreeSurface(theEndLabelSurface);
	SDL_DestroyTexture(theEndLabelTexture);
	SDL_DestroyTexture(characterTexture);
	TTF_CloseFont(font);
}

void EndingModule::Start(GameState& state)
{
	font = TTF_OpenFont("Fonts/CrimsonText-Bold.ttf", 11);
	SDL_Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;
	Character& character = state.Characters[state.SelectedCharacterIndex];
	stringstream endingLabel;
	stringstream characterLabel;
	endingLabel << "E assim, com muita sabedoria, " << character.Name << " fez a escolha de seus filmes favoritos para a SEGUNDA CINÉFILA vindoura.";
	characterLabel << '"' << character.EndingLine << '"';
	mainLabelSurface = TTF_RenderText_Blended_Wrapped(font, endingLabel.str().c_str(), whiteColor, SC_SCREEN_WIDTH - 20);
	characterLabelSurface = TTF_RenderText_Blended_Wrapped(font, characterLabel.str().c_str(), whiteColor, SC_SCREEN_WIDTH - 20);
	theEndLabelSurface = TTF_RenderText_Blended(font, "FIM", whiteColor);
	hands.Left = true;
	hands.Ok = true;
	MusicPlayer::Get()->PlayTitleMusic();
}

void EndingModule::Update(GameState& state, SDL_Renderer* render, ModuleResult& result)
{
	Character& Character = state.Characters[state.SelectedCharacterIndex];
	SDL_Surface* characterImage = ResourcesManager::Get()->GetCharacterImage(Character.Id);
	if (characterTexture == nullptr)
		characterTexture = SDL_CreateTextureFromSurface(render, characterImage);
	if (mainLabelTexture == nullptr)
		mainLabelTexture = SDL_CreateTextureFromSurface(render, mainLabelSurface);
	if (characterLabelTexture == nullptr)
		characterLabelTexture = SDL_CreateTextureFromSurface(render, characterLabelSurface);
	if (theEndLabelTexture == nullptr)
		theEndLabelTexture = SDL_CreateTextureFromSurface(render, theEndLabelSurface);
	SDL_Rect destRect;
	destRect.x = (SC_SCREEN_WIDTH - mainLabelSurface->w) / 2;
	destRect.y = 10;
	destRect.w = mainLabelSurface->w;
	destRect.h = mainLabelSurface->h;
	SDL_RenderCopy(render, mainLabelTexture, nullptr, &destRect);
	destRect.x = (SC_SCREEN_WIDTH / 2) - (characterImage->w / 2);
	destRect.y = (SC_SCREEN_HEIGHT / 2) - (characterImage->h / 2);
	destRect.w = characterImage->w;
	destRect.h = characterImage->h;
	SDL_RenderCopy(render, characterTexture, nullptr, &destRect);
	destRect.x = (SC_SCREEN_WIDTH - characterLabelSurface->w) / 2;
	destRect.y = destRect.y + destRect.h + 10;
	destRect.w = characterLabelSurface->w;
	destRect.h = characterLabelSurface->h;
	SDL_RenderCopy(render, characterLabelTexture, nullptr, &destRect);
	destRect.x = (SC_SCREEN_WIDTH - theEndLabelSurface->w) / 2;
	destRect.y = destRect.y + destRect.h + 10;
	destRect.w = theEndLabelSurface->w;
	destRect.h = theEndLabelSurface->h;
	SDL_RenderCopy(render, theEndLabelTexture, nullptr, &destRect);
	hands.Render(render, (SC_SCREEN_WIDTH - hands.GetWidth()) -10, SC_SCREEN_HEIGHT - hands.GetHeight());
}

void EndingModule::Finish(GameState& state)
{
}

void EndingModule::HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result)
{
	if (inputEvent.keysym.sym == SDLK_RETURN || inputEvent.keysym.sym == SDLK_KP_ENTER)
		result.FinishGame = true;
	else if (inputEvent.keysym.sym == SDLK_LEFT)
		result.NextGameModule = new MovieModule;
}
