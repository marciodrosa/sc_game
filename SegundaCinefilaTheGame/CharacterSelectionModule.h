#pragma once

#include "GameModule.h"
#include <SDL.h>
#include <SDL_ttf.h>

namespace sc
{
	/** Module that shows the character selection screen. */
	class CharacterSelectionModule : public GameModule
	{
	public:
		CharacterSelectionModule();
		virtual ~CharacterSelectionModule();
		void Start(GameState& state) override;
		void Update(GameState& state, SDL_Renderer* render, ModuleResult& result) override;
		void Finish(GameState& state) override;
		void HandleInput(SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;

	private:
		SDL_Surface* mainLabelSurface;
		SDL_Texture* mainLabelTexture;
		TTF_Font* font;
	};
}
