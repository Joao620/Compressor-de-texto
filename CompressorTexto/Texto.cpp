#include "Texto.h"

Texto::Texto(Texto& original, int inicio, int fim)
{
	//copia parte do texto
	/*int primeiroIndiceTexto = copia.getExtremidadePalavras().at(inicio);
	int extensaoCopia = (copia.getExtremidadePalavras().at(fim + 1) - primeiroIndiceTexto);*/

	string::iterator primeiraPlavraCopia = original.getTexto().begin() +
		original.getExtremidadePalavras().at(inicio * 2);


	string::iterator ultimaPalavraCopia = original.getTexto().begin() +
		original.getExtremidadePalavras().at(fim * 2 + 1) + 1;

	m_pTexto = new string(primeiraPlavraCopia, ultimaPalavraCopia);

	//copia parte da lista
	vector<int>::iterator fatiaInicio = original.getExtremidadePalavras().begin() + inicio * 2;
	vector<int>::iterator fatiaFinal = original.getExtremidadePalavras().begin() + fim * 2 + 1;

	m_ExtremidadePalavras.assign(fatiaInicio, fatiaFinal + 1);

	//subitrai a lista toda por primeiroIndiceTexto pra ela comecar com base 0

	int removerOffset = m_ExtremidadePalavras.at(0);

	for (auto& valor : m_ExtremidadePalavras)
	{
		valor -= removerOffset;
	}


}