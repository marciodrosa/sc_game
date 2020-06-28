#pragma once

#include "GameModule.h"
#include "CharacterSelectionIcon.h"
#include "AnimationListener.h"
#include "Hands.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

namespace sc
{
	/** Module that shows the character selection screen. */
	class CharacterSelectionModule : public GameModule, public AnimationListener
	{
	public:
		CharacterSelectionModule();
		virtual ~CharacterSelectionModule();
		void Start(GameState& state) override;
		void Update(GameState& state, SDL_Renderer* render, ModuleResult& result) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;
		void OnAnimationEnded() override;

	private:
		void DrawCharacterName(GameState& state, SDL_Renderer* render);
		SDL_Surface* mainLabelSurface;
		SDL_Texture* mainLabelTexture;
		TTF_Font* font;
		std::vector<CharacterSelectionIcon*> characterIcons;
		Hands hands;
		bool selectionFinished;
	};
}
