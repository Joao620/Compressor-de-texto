#pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Texto;
class Indices;

//abre um arquivo de texto no heap e retorna ptr para ele
string* abrirTextoNaMemoria(string pathArquivo);
//pathArquivo = endereco que o arquivo esta no sistema

//pega uma string e retorna uma lista com o comeco e o final de todas as palavras
vector<int> definirEspacos(string& texto);
//texto = a string que vai ser identificada os espacos

//retorna uma lista com todas as palavras de uma string
vector<string> dividirTextoEmPalavras(string& texto, vector<int>& extremidadePalavras, int inicio, int fim);
//texto = o texto que vai ter as palavras divididas
//extremidadePalavras = os comecos e finais das palavras do texto
//inicio = a primeira palavra que vai ser separada (base 0)
//final = a ultima palavra que vai ser separada

//cria uma arquivo ofstream e inicia ele com os valores de tamanhoChunks e quantIndices
void criarArquivoComCabecalho(ofstream& arquivo, string& pathArqNovo, short int tamanhoChunks, char quantIndices);
//arquivo = referencia ao arquivo pra ser inicializado, já que ele vai ser criado no stack
//pathArquivo = o endereco que esse novo arquivo vai ter
//tamanhoChunks = quantidade de palavras que vai ter por chunks
//quantIndices = quantidade de indices que vai ter por chunk

//pega 
void catalogarPalavras(vector<string>& listaPalavras, vector<string>& palavrasIsoladas, vector<int>& quantRepeticoes);

void escreverChunk(ofstream& arquivo, Texto& texto, Indices& indice);
