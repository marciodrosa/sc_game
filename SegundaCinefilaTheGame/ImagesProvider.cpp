#include "ImagesProvider.h"
#include <SDL_image.h>

using namespace sc;
using namespace std;

ImagesProvider* ImagesProvider::singleton = nullptr;

ImagesProvider::ImagesProvider()
{
}

ImagesProvider::~ImagesProvider()
{
	for (pair<CharacterId, SDL_Surface*> element : charactersImages)
	{
		SDL_FreeSurface(element.second);
	}
	for (pair<CharacterId, SDL_Surface*> element : smallCharactersImages)
	{
		SDL_FreeSurface(element.second);
	}
}

ImagesProvider* ImagesProvider::Get()
{
	if (singleton == nullptr)
		singleton = new ImagesProvider;
	return singleton;
}

void ImagesProvider::Release()
{
	if (singleton != nullptr)
	{
		delete singleton;
		singleton = nullptr;
	}
}

void ImagesProvider::LoadImages()
{
	charactersImages[CharacterId::FELIPE] = IMG_Load("Images/Felipe.png");
	charactersImages[CharacterId::JULIA] = IMG_Load("Images/Julia.png");
	charactersImages[CharacterId::MARCIO] = IMG_Load("Images/Marcio.png");
	charactersImages[CharacterId::RAFA] = IMG_Load("Images/Rafa.png");
	charactersImages[CharacterId::GABI] = IMG_Load("Images/Gabi.png");
	smallCharactersImages[CharacterId::FELIPE] = IMG_Load("Images/FelipeSmall.png");
	smallCharactersImages[CharacterId::JULIA] = IMG_Load("Images/JuliaSmall.png");
	smallCharactersImages[CharacterId::MARCIO] = IMG_Load("Images/MarcioSmall.png");
	smallCharactersImages[CharacterId::RAFA] = IMG_Load("Images/RafaSmall.png");
	smallCharactersImages[CharacterId::GABI] = IMG_Load("Images/GabiSmall.png");
	characterCursorImage = IMG_Load("Images/CharacterCursor.png");
}

SDL_Surface* ImagesProvider::GetCharacterImage(CharacterId id)
{
	return charactersImages[id];
}

SDL_Surface* ImagesProvider::GetCharacterSmallImage(CharacterId id)
{
	return smallCharactersImages[id];
}

SDL_Surface* ImagesProvider::GetCharacterCursorImage()
{
	return characterCursorImage;
}