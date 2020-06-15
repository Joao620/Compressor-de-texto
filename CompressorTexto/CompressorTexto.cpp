#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Indices.h"
#include "Texto.h"
#include "Funcoes.h"

using namespace std;

int main()
{
	short int cTamanhoChunks = 32767;
	char cQuantIndices = 100;
	string cPathArqBase = "Textos/testes/bee.txt";
	string cPathArqNovo = "rola.rola";

	Texto textoObj;

	textoObj.setTexto(abrirTextoNaMemoria(cPathArqBase));

	textoObj.setExtremidadePalavras(definirEspacos(textoObj.getTexto()));

	ofstream arqNovo;
	criarArquivoComCabecalho(arqNovo, cPathArqNovo, cTamanhoChunks, cQuantIndices);

	//it = interações

	int quantPalavrasLista = textoObj.getExtremidadePalavras().size() / 2;
	int quantChunks = ceil(quantPalavrasLista / cTamanhoChunks);

	for (int indiceChunks = 0; indiceChunks <= quantChunks; indiceChunks++)
	{
		Indices indice(quantPalavrasLista);

		int inicioChunk = cTamanhoChunks * indiceChunks;
		int finalChunk = cTamanhoChunks * (indiceChunks + 1);

		if (finalChunk > quantPalavrasLista)
			finalChunk = quantPalavrasLista;

		
		//dentro de chaves so pra matar esse demonio de listaTodasPalavras
		vector<string> listaTodasPalavras = dividirTextoEmPalavras(textoObj.getTexto(), textoObj.getExtremidadePalavras(),
			inicioChunk, finalChunk);

		//vai interar por todas as palavras da lista
		catalogarPalavras(listaTodasPalavras, indice.Palavras, indice.Quantidade);
		

		indice.reduzirEmOrdemCresente(cQuantIndices);

		Texto textoRecortado(textoObj, inicioChunk, finalChunk - 1);//ve se esses valores estão certos aaaaaaaaaaa

		//escreve o chunk bem legal mesmo
		escreverChunk(arqNovo, textoRecortado, indice);
	}
	arqNovo.close();

	return 0;
}

