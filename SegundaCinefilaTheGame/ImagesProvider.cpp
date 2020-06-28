#include "ImagesProvider.h"
#include <SDL_image.h>

using namespace sc;
using namespace std;

ImagesProvider* ImagesProvider::singleton = nullptr;

ImagesProvider::ImagesProvider()
{
	characterCursorImage = nullptr;
	handRightImage = nullptr;
	handLeftImage = nullptr;
	handOkImage = nullptr;
}

ImagesProvider::~ImagesProvider()
{
	for (pair<MovieId, SDL_Surface*> element : moviesImages)
	{
		SDL_FreeSurface(element.second);
	}
	for (pair<CharacterId, SDL_Surface*> element : charactersImages)
	{
		SDL_FreeSurface(element.second);
	}
	for (pair<CharacterId, SDL_Surface*> element : smallCharactersImages)
	{
		SDL_FreeSurface(element.second);
	}
	SDL_FreeSurface(characterCursorImage);
	SDL_FreeSurface(handRightImage);
	SDL_FreeSurface(handLeftImage);
	SDL_FreeSurface(handOkImage);
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
	moviesImages[MovieId::DESTACAMENTO_BLOOD] = IMG_Load("Images/DestacamentoBlood.png");
	moviesImages[MovieId::UM_PEQUENO_FAVOR] = IMG_Load("Images/UmPequenoFavor.png");
	moviesImages[MovieId::NASCIDO_EM_4_DE_JULHO] = IMG_Load("Images/NascidoEm4DeJulho.png");
	moviesImages[MovieId::PERSONAL_SHOPPER] = IMG_Load("Images/PersonalShopper.png");
	moviesImages[MovieId::PSICOPATA_AMERICANO] = IMG_Load("Images/PsicopataAmericano.png");
	moviesImages[MovieId::EMBRIAGADO_DE_AMOR] = IMG_Load("Images/EmbriagadoDeAmor.png");
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
	handRightImage = IMG_Load("Images/HandRight.png");
	handLeftImage = IMG_Load("Images/HandLeft.png");
	handOkImage = IMG_Load("Images/HandOk.png");
}

SDL_Surface* ImagesProvider::GetMovieImage(MovieId id)
{
	return moviesImages[id];
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

SDL_Surface* ImagesProvider::GetHandRightImage()
{
	return handRightImage;
}

SDL_Surface* ImagesProvider::GetHandLeftImage()
{
	return handLeftImage;
}

SDL_Surface* ImagesProvider::GetHandOkImage()
{
	return handOkImage;
}
