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
#include <fstream> //lectura
#include <sstream>
#include <bits/stdc++.h>
#include <algorithm>
#include "TreeNode.h"
#include "TreeElement.h"
using namespace std;

/*Prototipos de los metodos.*/
int IndexOf(vector<TreeElement *>, string);
string CodeGenerator(TreeNode *, TreeNode *);
void Imprimir(vector<TreeNode *>);
bool orderbyfrequency(TreeNode *, TreeNode *);
bool orderbyletter(TreeNode *, TreeNode *);
bool FileExist(char *);
bool Contains(vector<TreeElement *>, string);
vector<TreeElement *> ReadFile(string);
vector<TreeNode *> Ordenar(vector<TreeNode *>);
vector<TreeNode *> Ordenar1(vector<TreeNode *>);
vector<TreeNode *> poner(vector<TreeNode *>, TreeNode *);
vector<TreeNode *> Fill(vector<TreeElement *>);
vector<TreeElement *> create(string);
TreeNode *CreateTree(vector<TreeNode *>);

/********************Inicio del main*************************/
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Parametros insuficientes :(-" << endl;
	}
	else
	{
		if (FileExist(argv[1]))
		{ //el archivo se abrio exitosamente

			string path;
			vector<TreeElement *> generalElements = ReadFile(path = argv[1]);
			vector<TreeNode *> nodes = Fill(generalElements);
			sort(nodes.begin(), nodes.end(), orderbyletter);/***/
			TreeNode *root = CreateTree(nodes);
			cout << root->GetData()->GetElement() << endl;
			for (int i = 0; i < nodes.size(); i++)
			{
				nodes.at(i)->GetData()->setcode(CodeGenerator(root, nodes.at(i)));
			}
			sort(nodes.begin(), nodes.end(), orderbyfrequency);
			Imprimir(nodes);
			for (int i = 0; i < generalElements.size(); i++)
			{
				delete generalElements.at(i);
				delete nodes.at(i);
			}
		}
		else
		{ //el archivo no existe
			cout << "Archivo inexistente, verifique la ruta" << endl;
		}
	}
}
/********************Fin del Main*************************/
/* 
 descripcion: Crea los Treelements necesarios para poder crear los nodos que conforman el arbol.
 Params: string de texto que contiene todos los caracteres del archivo para su clasificacion y conteo
 Retorna: un vector con los TreeElements que estaran contenidos dentro de los nodos del arbol.
 Errores: si encuentra un caracter no valido en el archivo no lo agrega */

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
				elements.at(elements.size() - 1)->setAscii(x);
			}
			else if (x == 10)
			{ //salto linea
				elements.push_back(new TreeElement("LF", 1));
				elements.at(elements.size() - 1)->setAscii(x);
			}
			else if (x == 13)
			{ //enter
				elements.push_back(new TreeElement("CR", 1));
				elements.at(elements.size() - 1)->setAscii(x);
			}
			else if (x < 0)
			{ //Caracteres no validos
			}
			else
			{ ///Otros caracteres
				elements.push_back(new TreeElement(letter.str(), 1));
				elements.at(elements.size() - 1)->setAscii(x);
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
					elements.at(elements.size() - 1)->setAscii(x);
				}
				else if (x == 10)
				{ //salto linea
					elements.push_back(new TreeElement("LF", 1));
					elements.at(elements.size() - 1)->setAscii(x);
				}
				else if (x == 13)
				{ //enter
					elements.push_back(new TreeElement("CR", 1));
					elements.at(elements.size() - 1)->setAscii(x);
				}
				else if (x < 0)
				{ //otros
				}
				else
				{
					elements.push_back(new TreeElement(letter.str(), 1));
					elements.at(elements.size() - 1)->setAscii(x);
				}
			}
			else
			{
				int pos = IndexOf(elements, letter.str());
				(elements.at(pos))->SetFrequency(elements.at(pos)->GetFrequency() + 1);
			}
		}
	}

	return elements;
}

/* 
 descripcion: Abre el archivo y crea una cadena de texto que contiene todos los caracteres para luego clasificarlos 
 Params: string path, representa la ruta del archivo que deseamos cargar 
 Retorna: un vector con los TreeElements que estaran contenidos dentro de los nodos del arbol.
 Errores:  */

vector<TreeElement *> ReadFile(string relativePath)
{
	ifstream archivo;
	vector<TreeElement *> elements;
	string texto = "";
	stringstream LF_Concat;
	archivo.open(relativePath, ios::in);
	/*metodos de la clase algorithm para crear el buffer*/
	archivo.seekg(0, archivo.end);
	int length = archivo.tellg();
	archivo.seekg(0, archivo.beg);
	char *buffer = new char[length];

	archivo.read(buffer, length);

	for (int i = 0; i < length; i++)
	{
		LF_Concat << buffer[i];
	}
	texto = LF_Concat.str();
	stable_sort(texto.begin(), texto.end());
	delete[] buffer;
	elements = create(texto);
	archivo.close();
	return elements;
}
/* 
 descripcion:Determina si el archivo existe dentro del directorio
 Params: char * Path, la ruta del archivo a comprobar 
 Retorna: false si no se encuentra el archivo, true en caso contrario 
 Errores:si no encuentra el archivo retornara false */
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
 descripcion:Determina si un elemento ya esta dentro de un arreglo
 Params: Vector con los elemntos que forman los nodos, el simbolo del que queremos agregar
 Retorna: true si se encuentra una coincidencia de elementos, false si no se encuentra
 Errores: se omite el manejo de caracteres espciales ya que esos fueron descartados en metodos anteriores 
 que se encargan de construir los parametros de este metodo*/
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
 descripcion: Retorna  la posicion dentro del arreglo de un determinado elemento
 Params: Vector con los elemntos que forman los nodos, el simbolo del que queremos encontrar
 Retorna: un entero que representa la posicio dentro del arreglo de Tree Elements
 Errores: retorna -1 si no encuentra un elemento*/
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
 descripcion: Crea asigna los elementos a los nodos que formaran el arbol 
 Params: Vector de TreeElementos* para insertarlos en los nodos
 Retorna: el arreglo de nodos ordenado.
 Errores: NA */
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
 descripcion:Ordena los elementos del arreglo de nodos en orden descente
 Params: Vector de TreeNode * que deseamos ordenar 
 Retorna: Vector de Nodos* ordenado 
 Errores: NA*/
vector<TreeNode *> Ordenar(vector<TreeNode *> elements)
{
	return elements;
}

/* 
 descripcion: Crea el Arbol con el cual se generara la codificacion 
 Params: Vector de Nodes * para generar cada subarbol
 Retorna: Tree Node* que sera la raiz del arbol
 Errores: */
TreeNode *CreateTree(vector<TreeNode *> Nodes)
{
	vector<TreeNode *> tempNodes = Nodes;
	tempNodes = Ordenar1(tempNodes);
	//sort(Nodes.begin(), Nodes.end(), orderbyfrequency);
	while (tempNodes.size() > 1)
	{
		stringstream root;
		bool flag = false;
		TreeNode *childLeft = tempNodes.at(tempNodes.size() - 1);
		TreeNode *childRight = tempNodes.at(tempNodes.size() - 2);
		size_t newFrequency = childLeft->GetData()->GetFrequency() + childRight->GetData()->GetFrequency();

		if (childLeft->GetData()->GetFrequency() < childRight->GetData()->GetFrequency() || childRight->GetData()->GetFrequency() == childLeft->GetData()->GetFrequency())
		{
			root << childLeft->GetData()->GetElement() << childRight->GetData()->GetElement();
			flag = true;
		} /*
		else if (childLeft->GetData()->GetFrequency() > childRight->GetData()->GetFrequency())
		{ //
			root << childRight->GetData()->GetElement() << childLeft->GetData()->GetElement();
		}*/

		TreeNode *Nodex = new TreeNode(*new TreeElement(root.str(), newFrequency));
		if (flag)
		{
			Nodex->AddChild(childRight);
			Nodex->AddChild(childLeft);
		}
		else
		{
			Nodex->AddChild(childLeft);
			Nodex->AddChild(childRight);
		}
		tempNodes.pop_back();
		tempNodes.pop_back();
		tempNodes.push_back(Nodex);
		sort(tempNodes.begin(), tempNodes.end(), orderbyletter);
		//tempNodes = Ordenar1(tempNodes);
	}
	return tempNodes.at(0);
}
/* 
 descripcion: Imprime el vector de TreeNodes que forman el arbol 
 Params: Vector de TreeNode* que se desea visualizar  
 Retorna: N/A 
 Errores: N/A*/
void Imprimir(vector<TreeNode *> tempElements)
{
	for (int i = 0; i < tempElements.size(); i++)
	{
		cout << "{key: " << tempElements.at(i)->GetData()->GetElement() << ", code: " << tempElements.at(i)->GetData()->Getcode() << "}" << endl;
	}
}
/* 
 descripcion: Ordena por frecuancia los elemntos del arreglo 
 Params: TreeNode* NodeL, TreeNode * NodeR que seran los elemntos a comparar  
 Retorna: true si nodeL es mayor al node R, false en caso contrario
 Errores: NA*/
bool orderbyfrequency(TreeNode *nodeL, TreeNode *nodeR)
{
	return nodeL->GetData()->GetFrequency() > nodeR->GetData()->GetFrequency();
}

/* 
 descripcion: Ordena por caracteres los elemntos del arreglo 
 Params: TreeNode* NodeL, TreeNode * NodeR que seran los elemntos a comparar  
 Retorna: true si nodeL es mayor al node R, false en caso contrario
 Errores: NA*/
bool orderbyletter(TreeNode *nodeL, TreeNode *nodeR)
{
	if (nodeL->GetData()->GetFrequency() == nodeR->GetData()->GetFrequency())
	{
		return nodeL->GetData()->GetElement()> nodeR->GetData()->GetElement();
	}
	else
	{
		return nodeL->GetData()->GetFrequency() > nodeR->GetData()->GetFrequency();
	}
}

/* 
 descripcion: Genera la codificacion de cada uno de los nodos del arbol. 
 Params: TreeNode* root, la raiz del arbol y TReeNode* toGenerate que sera el elmento al cual se le generara el codigo
 Retorna: string con la codificacion del elemento
 Errores: Si encuentra el elemntos o llegamos hasta una hoja entonces salimos del ciclo*/

string CodeGenerator(TreeNode *root, TreeNode *toGenerate)
{
	stringstream concat;
	TreeNode *temp = root;
	while (!temp->IsLeaf())
	{
		vector<TreeNode *> childrens;
		childrens = temp->GetChildren();
		if (childrens.at(0)->GetData()->GetElement().find(toGenerate->GetData()->GetElement()) != std::string::npos)
		{//izquierda
			if (childrens.at(0)->GetData()->GetElement() == toGenerate->GetData()->GetElement())
			{
				concat << "1";
				temp = root;
				break;
			}
			else
			{
				concat << "1";
				temp = childrens.at(0);
			}
		}
		else
		{ //derecha
			if (childrens.at(1)->GetData()->GetElement() == toGenerate->GetData()->GetElement())
			{
				concat << "0";
				temp = root;
				break;
			}
			else
			{

				concat << "0";
				temp = childrens.at(1);
			}
		}
	}
	return concat.str();
}
/* 
 descripcion:Ordena los elemntos vector que conforman los nodos del arbol
 Params: Vector TreeNode* que deseamos ordenar 
 Retorna: el vector ordenado 
 Errores: NA*/
vector<TreeNode *> Ordenar1(vector<TreeNode *> nodos)
{
	TreeNode *tempNodo;
	for (int i = 0; i < nodos.size(); i++)
	{

		for (int i = 0; i < nodos.size() - 1; i++)
		{
			TreeElement *temp1 = nodos[i]->GetData();
			TreeElement *temp2 = nodos[i + 1]->GetData();

			if (temp1->GetFrequency() < temp2->GetFrequency())
			{
				tempNodo = nodos[i];
				nodos[i] = nodos[i + 1];
				nodos[i + 1] = tempNodo;
			}
		}
	}
	return nodos;
}
