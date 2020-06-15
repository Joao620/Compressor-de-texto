#pragma once
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Indices {
public:
	vector<string> Palavras;
	vector<int> Quantidade;

	Indices(int tamanho);
	void reduzirEmOrdemCresente(int novoTamanho);
};