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
#include <bits/stdc++.h>
using namespace std;
/*Prototipos de los metodos.*/
vector<TreeElement *> ReadFile(string);
bool FileExist(char *);
bool Contains(vector<TreeElement *>, string);
int IndexOf(vector<TreeElement *>, string);
//vector<TreeElement *> Ordenar(vector<TreeElement *>);
vector<TreeNode *> Ordenar(vector<TreeNode *>);
vector<TreeNode *> poner(vector<TreeNode *>, TreeNode *);
TreeNode *CreateTree(vector<TreeNode *>);
vector<TreeNode *> Fill(vector<TreeElement *>);
vector<TreeElement *> create(string);
void CodeGenerator(TreeNode *);
void Imprimir(vector<TreeNode *>);
bool orderbyfrequency(TreeNode *, TreeNode *);
bool orderbyletter(TreeNode *, TreeNode *);
void reverseStr(string &str)
{
	int n = str.length();

	// Swap character starting from two
	// corners
	for (int i = 0; i < n / 2; i++)
		swap(str[i], str[n - i - 1]);
}

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
			vector<TreeElement *> generalElements = ReadFile(path = argv[1]);
			vector<TreeNode *> nodes = Fill(generalElements);
			sort(nodes.begin(), nodes.end(), orderbyfrequency);
			/*sort(nodes.begin(), nodes.end(), orderbyletter);*/
			Imprimir(nodes);
			TreeNode *root = CreateTree(nodes);
			cout << "Root: " << root->GetData()->GetElement() << " Peso: " << root->GetData()->GetFrequency() << endl;
			/*PUEDE SER LA DE EL MISMO Y AGREGARLE LA DEL PADRE*/

			for (int i = 0; i < generalElements.size(); i++)
			{

				delete generalElements.at(i);
				delete nodes.at(i);
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
vector<TreeElement *> create(string texto)
{

	vector<TreeElement *> elements;
	for (int i = 0; i < texto.length(); i++)
	{
		stringstream letter;
		letter << texto[i];
		if (elements.size() == 0)
		{
			int x = letter.str()[0];
			if (x == 32)
			{ //Espacio
				elements.push_back(new TreeElement("SP", 1));
			}
			else if (x == 10)
			{ //salto linea
				elements.push_back(new TreeElement("LF", 0));
			}
			else if (x == 13)
			{ //enter
				elements.push_back(new TreeElement("CR", 1));
			}
			else if (x == -108 || x == -30 || x == -103 || x == -109 || x == -128)
			{ //otros
			}
			else
			{
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
					elements.push_back(new TreeElement("LF", 0));
				}
				else if (x == 13)
				{ //enter
					elements.push_back(new TreeElement("CR", 1));
				}
				else if (x == -108 || x == -30 || x == -103 || x == -109 || x == -128)
				{ //otros
				}
				else
				{
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
	//sort(elements.begin(),elements.end());
	return elements;
}
vector<TreeElement *> ReadFile(string relativePath)
{
	ifstream archivo;
	vector<TreeElement *> elements;
	string texto = "";
	stringstream LF_Concat;
	archivo.open(relativePath, ios::in);
	/**/
	archivo.seekg(0, archivo.end);
	int length = archivo.tellg();
	archivo.seekg(0, archivo.beg);
	/**/
	char *buffer = new char[length];
	archivo.read(buffer, length);

	for (int i = 0; i < length; i++)
	{
		LF_Concat << buffer[i];
		texto = LF_Concat.str();
	}
	stable_sort(texto.begin(), texto.end());

	//reverseStr(texto);
	// cout << texto<<endl;
	delete[] buffer;
	elements = create(texto);
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
vector<TreeNode *> Fill(vector<TreeElement *> generalElements)
{
	vector<TreeNode *> temporal;
	for (int i = 0; i < generalElements.size(); i++)
	{
		temporal.push_back(new TreeNode(*generalElements.at(i)));
	}

	return Ordenar(temporal);
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
vector<TreeNode *> Ordenar(vector<TreeNode *> elements)
{
	//	sort(elements.begin(), elements.end(), orderbyfrequency);
	return elements;
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
TreeNode *CreateTree(vector<TreeNode *> Nodes)
{
	vector<TreeNode *> tempNodes = Nodes;
	int i = tempNodes.size();
	while (tempNodes.size() > 1) //Rendimiento log n
	{
		stringstream root;
		vector<TreeNode *> temptempNodes;
		TreeNode *child1 = tempNodes.at(tempNodes.size() - 1);
		TreeNode *child2 = tempNodes.at(tempNodes.size() - 2);
		size_t newFrequency = child1->GetData()->GetFrequency() + child2->GetData()->GetFrequency();
		for (int i = 0; i < tempNodes.size() - 2; i++)
		{
			temptempNodes.push_back(tempNodes.at(i));
		}

		if (child1->GetData()->GetFrequency() <= child2->GetData()->GetFrequency())
		{
			root << child1->GetData()->GetElement() << child2->GetData()->GetElement();
			TreeNode *Nodex = new TreeNode(*new TreeElement(root.str(), newFrequency));
			child1->GetData()->setcode("0");
			child2->GetData()->setcode("1");
			Nodex->AddChild(child2);
			Nodex->AddChild(child1);
			temptempNodes.push_back(Nodex);
		}
		else
		{ //child2<child1

			root << child2->GetData()->GetElement() << child1->GetData()->GetElement();
			TreeNode *Nodex = new TreeNode(*new TreeElement(root.str(), newFrequency));
			child1->GetData()->setcode("1");
			child2->GetData()->setcode("0");
			Nodex->AddChild(child1);
			Nodex->AddChild(child2);
			temptempNodes.push_back(Nodex);
		}

		cout << "----------------" << endl;
		sort(temptempNodes.begin(), temptempNodes.end(), orderbyfrequency);
		tempNodes = temptempNodes;
		Imprimir(temptempNodes);
	}
	return tempNodes.at(0);
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
void CodeGenerator(TreeNode *root)
{
	vector<TreeNode *> childrens = root->GetChildren();
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
void Imprimir(vector<TreeNode *> tempElements)
{
	size_t tot = 0;
	cout << "Imprimiento" << endl;
	for (int i = 0; i < tempElements.size(); i++)
	{
		tot += tempElements.at(i)->GetData()->GetFrequency();
		cout << i << "p: " << tempElements.at(i)->GetData()->GetElement() << " - " << tempElements.at(i)->GetData()->GetFrequency() << "hijo ";
		if (tempElements.at(i)->GetChildren().size() > 0)
		{
			for (int x = 0; x < tempElements.at(i)->GetChildren().size(); x++)
			{
				cout << tempElements.at(i)->GetChildren().at(x)->GetData()->GetElement() << " ";
			}
		}
		cout << endl;
	}
	cout << "TOTAL" << tot << endl;
}
bool orderbyfrequency(TreeNode *L1, TreeNode *L2)
{
	return L1->GetData()->GetFrequency() > L2->GetData()->GetFrequency();
}

bool orderbyletter(TreeNode *L1, TreeNode *L2)
{
	if (L1->GetData()->GetFrequency() == L2->GetData()->GetFrequency())
	{
		//cout<<L1->GetData()->GetElement()[0]<<">"<<L2->GetData()->GetElement()[0]<<endl;
		return L1->GetData()->GetElement()[0] > L2->GetData()->GetElement()[0];
	}
	else
	{
		return L1->GetData()->GetFrequency() > L2->GetData()->GetFrequency();
	}
}
/*
vector<TreeNode *> poner(vector<TreeNode *> nodes, TreeNode *element)
{
	bool flag = false;
	int x = 0;
	for (int i = nodes.size() - 1; i > 0; i--)
	{
		if (nodes.at(i)->GetData()->GetFrequency() == element->GetData()->GetFrequency())
		{
			flag = true;
			x = i;
			break;
		}
	}
	if (flag)
	{
		nodes.insert(nodes.begin() + (x - 1), element);
	}
	else
	{
		nodes.push_back(element);
	}
	return nodes;
}
*/
