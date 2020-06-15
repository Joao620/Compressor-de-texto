#pragma once
#include <string>
#include <vector>

using namespace std;

class Texto {
	string* m_pTexto;
	vector<int> m_ExtremidadePalavras;
public:
	void setTexto(string* pTexto) { m_pTexto = pTexto; }
	string& getTexto() { return *m_pTexto; }

	void setExtremidadePalavras(vector<int> extremidadePalavras) { m_ExtremidadePalavras = extremidadePalavras; }
	vector<int>& getExtremidadePalavras() { return m_ExtremidadePalavras; }

	//inico inclusido fim exclusivo
	Texto(Texto& original, int inicio, int fim);

	Texto() {}

	~Texto()
	{
		delete m_pTexto;
	}
};

