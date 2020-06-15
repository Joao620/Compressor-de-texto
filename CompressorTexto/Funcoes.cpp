#include "funcoes.h"
#include "Texto.h"
#include "Indices.h"

string* abrirTextoNaMemoria(string pathArquivo)
{
	streampos size;
	char* memblock;

	fstream file(pathArquivo, ios::in | ios::ate);
	size = file.tellg();
	int joao = (int)size;
	memblock = new char[(int)size];
	file.seekg(0, ios::beg);
	file.read(memblock, size);
	file.close();

	string* texto = new string(memblock, (int)size);

	return texto;
}

vector<int> definirEspacos(string& texto)
{
	char listaLetras[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
	'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '\0' };

	int quantLetras = 52 + 1;

	int quantEspacos = 0;

	for (unsigned int i = 0; i < texto.size(); i++)
	{
		if (texto[i] == ' ')
			quantEspacos++;
	}

	int tamanhoVector = floor(quantEspacos * 3);

	vector<int> posicaoEspaco(tamanhoVector);
	int indiceLista = 0;

	char* posicaoEncontrada;
	bool foraPalavra = true;

	for (unsigned int i = 0; i < texto.size(); i++)
	{
		posicaoEncontrada = find(listaLetras, listaLetras + quantLetras, texto[i]);
		if (posicaoEncontrada != listaLetras + quantLetras)
		{
			if (foraPalavra)
			{
				posicaoEspaco.at(indiceLista) = i;
				indiceLista++;
				foraPalavra = false;
			}
		}
		else
		{
			if (!foraPalavra)
			{
				posicaoEspaco.at(indiceLista) = i - 1;
				indiceLista++;
				foraPalavra = true;
			}
		}
	}

	posicaoEncontrada = find(listaLetras, listaLetras + quantLetras, texto[texto.size()]);

	if (posicaoEncontrada != listaLetras + quantLetras && !foraPalavra)
	{
		posicaoEspaco.at(indiceLista) = texto.size() - 1;
		indiceLista++;
	}

	if (indiceLista < tamanhoVector)
	{
		posicaoEspaco.resize(indiceLista);
	}

	posicaoEspaco.shrink_to_fit();
	return posicaoEspaco;
}

vector<string> dividirTextoEmPalavras(string& texto, vector<int>& extremidadePalavras, int inicio, int fim)
{
	if (inicio > fim)
		throw "inicio maior que o final";

	if (fim > extremidadePalavras.size() / 2 - 1)
		fim = extremidadePalavras.size() / 2 - 1;

	int primeiraPalavra = inicio * 2;
	int ultimaPalavra = fim * 2; //+1
	int larguraPalavra = 0;

	//todo resolver problemas do tamanho da lista de palavras
	vector<string> listaDePalavras(fim - inicio + 1);
	int indiceLista = 0;

	for (int i = primeiraPalavra; i <= ultimaPalavra; i += 2)
	{
		larguraPalavra = extremidadePalavras[i + 1] - extremidadePalavras[i] + 1; //testado
		listaDePalavras.at(indiceLista) = texto.substr(extremidadePalavras[i], larguraPalavra);
		indiceLista++;
	}

	return listaDePalavras;
}

void criarArquivoComCabecalho(ofstream& arquivo, string& pathArqNovo, short int tamanhoChunks, char quantIndices)
{
	arquivo.open(pathArqNovo, ios::trunc | ios::binary);
	arquivo.write((char*)&tamanhoChunks, 2);
	arquivo.write(&quantIndices, 1);
}

void catalogarPalavras(vector<string>& listaPalavras, vector<string>& palavrasIsoladas, vector<int>& quantRepeticoes)
{
	for (unsigned int indcPalavraLista = 0; indcPalavraLista < listaPalavras.size(); indcPalavraLista++)
	{
		string palavraEscolida = listaPalavras.at(indcPalavraLista);
		//ve se a string é grande o suficiente para ser abreviada
		if (palavraEscolida.size() > 2)
		{
			//interar em palavrasIsolada para ver se ela ja ta la
			bool naLista = false;
			int indiceEncontrado = 0;
			for (unsigned int i = 0; i < palavrasIsoladas.size(); i++)
			{
				if (palavraEscolida == palavrasIsoladas.at(i))
				{
					naLista = true;
					indiceEncontrado = i;
				}
			}

			if (naLista)
			{
				quantRepeticoes.at(indiceEncontrado) += 1;
			}
			else
			{
				//ja que nao tem ele vai achar um lugar vazio e se colocar la
				for (unsigned int i = 0; i < quantRepeticoes.size(); i++)
				{
					if (quantRepeticoes.at(i) == 0)
					{
						palavrasIsoladas.at(i) = palavraEscolida;
						quantRepeticoes.at(i) += 1;
						break;
					}
				}
			}

		}

	}

	vector<int>::iterator pPosicaoEspacoVazio = find(quantRepeticoes.begin(), quantRepeticoes.end(), 0);

	if (pPosicaoEspacoVazio != quantRepeticoes.end())
	{
		int quantEspacosVazios = quantRepeticoes.end() - pPosicaoEspacoVazio;
		quantRepeticoes.resize(quantRepeticoes.size() - quantEspacosVazios);
		palavrasIsoladas.resize(palavrasIsoladas.size() - quantEspacosVazios);
	}
}

void escreverChunk(ofstream& arquivo, Texto& texto, Indices& indice)
{
	for (string& x : indice.Palavras)
	{
		arquivo << x;
		arquivo.put(0);
	}

	char escape = 6;

	for (char i = 0; i < indice.Palavras.size(); i++)
	{
		size_t posicaoEncontrada = texto.getTexto().find(indice.Palavras.at(i));
		while (posicaoEncontrada != string::npos)
		{
			string textoSubstituicao;
			textoSubstituicao += escape;
			textoSubstituicao += i;
			texto.getTexto().replace(posicaoEncontrada, indice.Palavras.at(i).size(), textoSubstituicao);
			posicaoEncontrada = texto.getTexto().find(indice.Palavras.at(i));
		}
	}

	arquivo << texto.getTexto();
}