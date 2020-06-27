#pragma once

#include <SDL.h>
#include "Character.h"
#include "GameState.h"

namespace sc
{
	/** Icon draw of a character. */
	class CharacterSelectionIcon
	{
	public:
		CharacterSelectionIcon(Character* character);
		virtual ~CharacterSelectionIcon();
		void Render(GameState& state, SDL_Renderer* render, int x, int y);

	private:
		SDL_Texture* characterTexture;
		SDL_Texture* selectionTexture;
		Character* character;
	};
}
