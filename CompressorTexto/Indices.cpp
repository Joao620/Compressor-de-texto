#include "Indices.h"

using namespace std;

Indices::Indices(int tamanho)
{
	Palavras.resize(tamanho);
	Quantidade.resize(tamanho, 0);
}

void Indices::reduzirEmOrdemCresente(int novoTamanho)
{
	if (novoTamanho > Quantidade.size())
		return;

	int maiorQuantidade = 0;
	int indiceMaiorQuant = 0;

	for (unsigned int i = 0; i < Quantidade.size(); i++)
	{
		if (Quantidade.at(i) > maiorQuantidade)
		{
			maiorQuantidade = Quantidade.at(i);
			indiceMaiorQuant = i;
		}
	}

	//coloca os n primeiro numeros da lista em ordem
	//n sendo o novoTamanho
	for (int interacoes = 0; interacoes < novoTamanho; interacoes++)
	{
		vector<int>::iterator posicaoEncontrada;
		posicaoEncontrada = find(Quantidade.begin() + interacoes, Quantidade.end(), maiorQuantidade);
		while (posicaoEncontrada == Quantidade.end() && maiorQuantidade > 0)
		{
			maiorQuantidade--;
			posicaoEncontrada = find(Quantidade.begin() + interacoes, Quantidade.end(), maiorQuantidade);
		}

		//fazer um caso de quando maior Quantidade == 0/

		int indiceEncontrado = distance(Quantidade.begin(), posicaoEncontrada);

		//pula o swap se o valor ja estiver no lugar certo
		if (indiceEncontrado == interacoes) continue;

		//swapa a quantidade
		int intTempTroca = Quantidade.at(interacoes);
		Quantidade.at(interacoes) = *posicaoEncontrada;
		*posicaoEncontrada = intTempTroca;

		//swapa a palavras
		string strTempTroca = Palavras.at(interacoes);
		Palavras.at(interacoes) = Palavras.at(indiceEncontrado);
		Palavras.at(indiceEncontrado) = strTempTroca;
	}

	Palavras.resize(novoTamanho);
	Quantidade.resize(novoTamanho);
}
