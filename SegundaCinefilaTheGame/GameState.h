#pragma once

#include <string>
#include <vector>
#include "Character.h"

namespace sc
{
	/** Main game state model. */
	class GameState
	{
	public:
		GameState();
		std::vector<Character> Characters;
		int SelectedCharacterIndex;
	};
}
