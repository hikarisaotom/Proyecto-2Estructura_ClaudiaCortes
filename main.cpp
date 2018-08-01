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
		{//el archivo se abrio exitosamente 

			string path;
			vector<TreeElement *> generalElements = ReadFile(path = argv[1]);
			vector<TreeNode *> nodes = Fill(generalElements);
			//sort(nodes.begin(), nodes.end(), orderbyfrequency);
			TreeNode *root = CreateTree(nodes);
			cout << root->GetData()->GetElement()<<endl;
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
		{//el archivo no existe 
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
				elements.push_back(new TreeElement("LF", 0));
				elements.at(elements.size() - 1)->setAscii(x);
			}
			else if (x == 13)
			{ //enter
				elements.push_back(new TreeElement("CR", 1));
				elements.at(elements.size() - 1)->setAscii(x);
			}
			else if (x <0)
			{ //Caracteres no validos
			}
			else
			{///Otros caracteres 
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
					elements.push_back(new TreeElement("LF", 0));
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
	sort(Nodes.begin(), Nodes.end(), orderbyfrequency);
	//Imprimir(Nodes);
	//cout << "-------------------------------------------------------------------------" << endl;
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
		}
		else if (childLeft->GetData()->GetFrequency() > childRight->GetData()->GetFrequency())
		{ //esta mal ordenado :c
			root << childRight->GetData()->GetElement() << childLeft->GetData()->GetElement();
		}

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
			tempNodes=Ordenar1(tempNodes);
		//sort(tempNodes.begin(), tempNodes.end(), orderbyfrequency);
		//	cout << "-------------------------------------------------------------------------" << endl;
		//cout << "-------------------------------------------------------------------------" << endl;
	}
	return tempNodes.at(0);
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
void Imprimir(vector<TreeNode *> tempElements)
{
	size_t tot = 0;
	for (int i = 0; i < tempElements.size(); i++)
	{
		tot += tempElements.at(i)->GetData()->GetFrequency();
		cout << "{key: " << tempElements.at(i)->GetData()->GetElement() << ", code: " << tempElements.at(i)->GetData()->Getcode() << "}" << endl;
	}
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
bool orderbyfrequency(TreeNode *L1, TreeNode *L2)
{
	return L1->GetData()->GetFrequency() > L2->GetData()->GetFrequency();
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
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


string CodeGenerator(TreeNode *root, TreeNode *toGenerate)
{
	stringstream concat;
	TreeNode *temp = root;
	while (!temp->IsLeaf())
	{
		vector<TreeNode *> childrens;

		childrens = temp->GetChildren();
		if (childrens.at(0)->GetData()->GetElement().find(toGenerate->GetData()->GetElement()) != std::string::npos)
		{
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
		{ //esta a la derecha
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
 descripcion:
 Params: 
 Retorna: 
 Errores: */
vector<TreeNode *> Ordenar1(vector<TreeNode *> nodos)
{
	 TreeNode* tempNodo;
    for(int i=0;i<nodos.size();i++){
        
        for(int i = 0; i <nodos.size()-1; i++){
            TreeElement* temp1 = nodos[i]->GetData();
            TreeElement* temp2 = nodos[i+1]->GetData();
            
            if(temp1->GetFrequency() < temp2->GetFrequency()){
                tempNodo = nodos[i];
                nodos[i] = nodos[i+1];
                nodos[i+1] = tempNodo;

            } 
            
        }


    }
	return nodos;
}

/* MIO
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

		/*if (child1->GetData()->GetFrequency() <= child2->GetData()->GetFrequency())
		{*/
/*	root << child2->GetData()->GetElement() << child1->GetData()->GetElement();
		
		child1->GetData()->setcode("0");
		child2->GetData()->setcode("1");
		Nodex->AddChild(child2);
		Nodex->AddChild(child1);
		temptempNodes.push_back(Nodex);
		//}
		//cout << "----------------" << endl;
		sort(temptempNodes.begin(), temptempNodes.end(), orderbyfrequency);
		tempNodes = temptempNodes;
	//	Imprimir(temptempNodes);
	}
	return tempNodes.at(0);
}
*/
/*





*/
/*vector<TreeNode*> Ordenar(vector<TreeNode*>  nodos){
    TreeNode* tempNodo;
    for(int i=0;i<nodos.size();i++){
        
        for(int i = 0; i <nodos.size()-1; i++){
            TreeElement temp1 = nodos[i]->GetData();
            TreeElement temp2 = nodos[i+1]->GetData();
            
            if(temp1.GetFrequency() < temp2.GetFrequency()){
                tempNodo = nodos[i];
                nodos[i] = nodos[i+1];
                nodos[i+1] = tempNodo;

            } 
            
        }


    }

    return nodos;
}*/
