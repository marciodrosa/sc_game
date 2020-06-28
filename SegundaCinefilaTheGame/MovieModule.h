#pragma once

#include "GameModule.h"
#include "Hands.h"
#include "BlinkingBackground.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

namespace sc
{
	/** Module that shows the data of a movie. */
	class MovieModule : public GameModule
	{
	public:
		MovieModule();
		virtual ~MovieModule();
		void Start(GameState& state) override;
		void Update(GameState& state, SDL_Renderer* render, ModuleResult& result) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;

	private:
		SDL_Texture* movieTexture;
		SDL_Surface* mainLabelSurface;
		SDL_Texture* mainLabelTexture;
		TTF_Font* font;
		Hands hands;
		BlinkingBackground blinkingBackground;
	};
}
