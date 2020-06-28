#include "Character.h"

using namespace std;
using namespace sc;

vector<Character> Character::GetCharacters()
{
	vector<Character> result;
	
	Character felipe;
	felipe.Id = CharacterId::FELIPE;
	felipe.Name = "Felipe";
	felipe.EndingLine = "Nenhum filme de espadinha, aprovei!";
	result.push_back(felipe);

	Character julia;
	julia.Id = CharacterId::JULIA;
	julia.Name = "J�lia";
	julia.EndingLine = "Senti falta de algum filme com o Redmayne, mas bacana fora isso.";
	result.push_back(julia);

	Character marcio;
	marcio.Id = CharacterId::MARCIO;
	marcio.Name = "M�rcio";
	marcio.EndingLine = "Vencedores n�o perdem!";
	result.push_back(marcio);

	Character rafa;
	rafa.Id = CharacterId::RAFA;
	rafa.Name = "Rafa";
	rafa.EndingLine = "Agora bora jogar de novo para listar os filmes no Letterboxd.";
	result.push_back(rafa);

	Character gabi;
	gabi.Id = CharacterId::GABI;
	gabi.Name = "Gabi";
	gabi.EndingLine = "S� filmes bons? N�o � a Segunda Cin�fila que eu conhe�o...";
	result.push_back(gabi);

	return result;
}
