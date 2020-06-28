#pragma once

#include <SDL.h>
#include <map>
#include "Character.h"
#include "Movie.h"

namespace sc
{
	/** Utility class that loads and handles images. */
	class ImagesProvider
	{
	private:
		ImagesProvider();
	public:
		virtual ~ImagesProvider();
		static ImagesProvider* Get();
		static void Release();
		void LoadImages();
		SDL_Surface* GetMovieImage(MovieId id);
		SDL_Surface* GetCharacterImage(CharacterId id);
		SDL_Surface* GetCharacterSmallImage(CharacterId id);
		SDL_Surface* GetCharacterCursorImage();

	private:
		std::map<MovieId, SDL_Surface*> moviesImages;
		std::map<CharacterId, SDL_Surface*> charactersImages;
		std::map<CharacterId, SDL_Surface*> smallCharactersImages;
		SDL_Surface* characterCursorImage;
		static ImagesProvider* singleton;
	};
}
