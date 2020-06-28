#pragma once

#include "GameModule.h"
#include "Hands.h"
#include "AnimatedText.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

namespace sc
{
	/** Module that shows an intro text. */
	class IntroModule : public GameModule
	{
	public:
		IntroModule();
		virtual ~IntroModule();
		void Start(GameState& state) override;
		void Update(GameState& state, SDL_Renderer* render, ModuleResult& result) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;

	private:
		AnimatedText text;
		Hands hands;
	};
}
