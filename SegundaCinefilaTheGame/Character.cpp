#include "Character.h"

using namespace std;
using namespace sc;

vector<Character> Character::GetCharacters()
{
	vector<Character> result;
	
	Character felipe;
	felipe.Id = CharacterId::FELIPE;
	felipe.Name = "Felipe";
	felipe.EndingLine = "Winners don't lose!";
	result.push_back(felipe);

	Character julia;
	julia.Id = CharacterId::JULIA;
	julia.Name = "Julia";
	julia.EndingLine = "Winners don't lose!";
	result.push_back(julia);

	Character marcio;
	marcio.Id = CharacterId::MARCIO;
	marcio.Name = "Marcio";
	marcio.EndingLine = "Winners don't lose!";
	result.push_back(marcio);

	Character rafa;
	rafa.Id = CharacterId::RAFA;
	rafa.Name = "Rafa";
	rafa.EndingLine = "Winners don't lose!";
	result.push_back(rafa);

	Character gabi;
	gabi.Id = CharacterId::GABI;
	gabi.Name = "Gabi";
	gabi.EndingLine = "Winners don't lose!";
	result.push_back(gabi);

	return result;
}
