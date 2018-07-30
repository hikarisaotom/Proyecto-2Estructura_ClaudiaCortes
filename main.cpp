// Titulo: Proyecto #2 Codificación usando Árbol de Huffman
//Codificacion de caracteres mediante arbol de huffman
//
// Proposito: Crear una aplicacion capaz de leer de un archivo y codificar una serie de datos
//
// Clase: CCC209 – Q3 – 2018
//
// Author: Claudia Patricia Cortes Pavon
#include <iostream>
#include <stdio.h> //exist
#include <string>
#include <vector>
#include <fstream>   //lectura
#include <algorithm> //contains
#include "TreeNode.h"
#include "TreeElement.h"
#include <sstream>
using namespace std;

/*Prototipos de los metodos.*/
vector<TreeElement *> ReadFile(string);
bool FileExist(char *);
bool Contains(vector<TreeElement *>, string);
int IndexOf(vector<TreeElement *>, string);
vector<TreeElement *> Ordenar(vector<TreeElement *>);

/********************MAIN*************************/
int main(int argc, char *argv[])
{

	if (argc < 2)
	{
		cout << "Parametros insuficientes :(-" << endl;
	}
	else
	{
		if (FileExist(argv[1]))
		{
			string path;
			vector<TreeElement *> generalNodes = ReadFile(path = argv[1]);
			generalNodes = Ordenar(generalNodes);
			for (int i = 0; i < generalNodes.size(); i++)
			{
				cout << "Letra: " << generalNodes.at(i)->GetElement() << "  Frecuencia :" << generalNodes.at(i)->GetFrequency() << endl;
			}
			
			for (int i = 0; i < generalNodes.size(); i++)
			{
				delete generalNodes.at(i);
			}
		}
		else
		{
			cout << "Archivo inexistente, verifique la ruta" << endl;
		}
	}
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
vector<TreeElement *> ReadFile(string relativePath)
{
	vector<TreeElement *> elements;
	ifstream archivo;
	string texto = "";

	archivo.open(relativePath, ios::in);
	while (!archivo.eof())
	{
		stringstream LF_Concat;
		getline(archivo, texto);
		LF_Concat << texto;
		LF_Concat << endl;
		texto = LF_Concat.str();
		for (int i = 0; i < texto.length(); i++)
		{
			stringstream letter;
			letter << texto[i];
			if (elements.size() == 0)
			{
				int x = texto[i];
				if (x == 32)
				{ //Espacio
					elements.push_back(new TreeElement("SP", 1));
				}
				else if (x == 10)
				{ //salto linea
					elements.push_back(new TreeElement("LF", 1));
				}
				else if (x == 13)
				{ //enter
					elements.push_back(new TreeElement("CR", 1));
				}
				else
				{ //otros
					elements.push_back(new TreeElement(letter.str(), 1));
				}
			}
			else
			{

				if (!Contains(elements, letter.str()))
				{
					int x = texto[i];
					if (x == 32)
					{ //Espacio
						elements.push_back(new TreeElement("SP", 1));
					}
					else if (x == 10)
					{ //salto linea
						elements.push_back(new TreeElement("LF", 1));
					}
					else if (x == 13)
					{ //enter
						elements.push_back(new TreeElement("CR", 1));
					}
					else
					{ //otros
						elements.push_back(new TreeElement(letter.str(), 1));
					}
				}
				else
				{
					int pos = IndexOf(elements, letter.str());
					(elements.at(pos))->SetFrequency(elements.at(pos)->GetFrequency() + 1);
				}
			}
		}
	}
	archivo.close();
	return elements;
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
bool FileExist(char *Path)
{
	bool flag = false;
	FILE *archivo = fopen(Path, "rb"); //abriendo el archivo en lectura de bytes
	if (archivo != NULL)
	{
		flag = true;
		fclose(archivo);
	}
	return flag;
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
bool Contains(vector<TreeElement *> elements, string toCompare)
{
	for (int i = 0; i < elements.size(); i++)
	{
		int x = toCompare[0];
		if (x == 32 && elements.at(i)->GetElement() == "SP")
		{ //Espacio
			return true;
		}
		else if (x == 10 && elements.at(i)->GetElement() == "LF")
		{ //salto linea
			return true;
		}
		else if (x == 13 && elements.at(i)->GetElement() == "CR")
		{ //enter
			return true;
		}
		else if (elements.at(i)->GetElement() == toCompare)
		{
			return true;
		}
	}
	return false;
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
int IndexOf(vector<TreeElement *> elements, string toCompare)
{
	for (int i = 0; i < elements.size(); i++)
	{
		int x = toCompare[0];
		if (x == 32 && elements.at(i)->GetElement() == "SP")
		{ //Espacio
			return i;
		}
		else if (x == 10 && elements.at(i)->GetElement() == "LF")
		{ //salto linea
			return i;
		}
		else if (x == 13 && elements.at(i)->GetElement() == "CR")
		{ //enter
			return i;
		}
		else if (elements.at(i)->GetElement() == toCompare)
		{
			return i;
		}
	}
	return -1;
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
vector<TreeElement *> Ordenar(vector<TreeElement *> elements)
{
	TreeElement *temp;
	vector<TreeElement *> tempElements;
	for (int i = 1; i < elements.size(); i++)
	{
		for (int j = 0; j < elements.size() - 1; j++)
		{
			if (elements.at(j)->GetFrequency() > elements.at(j + 1)->GetFrequency())
			{
				temp = elements.at(j);
				elements.at(j) = elements.at(j + 1);
				elements.at(j + 1) = temp;
			}
		}
	}

	for (int i = elements.size() - 1; i >= 0; i--)
	{
		tempElements.push_back(elements.at(i));
	}
	elements = tempElements;
	return elements;
}
