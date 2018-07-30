// Titulo: Proyecto #2 Codificación usando Árbol de Huffman
//Codificacion de caracteres mediante arbol de huffman
//
// Proposito: Crear una aplicacion capaz de leer de un archivo y codificar una serie de datos
//
// Clase: CCC209 – Q3 – 2018
//
// Author: Claudia Patricia Cortes Pavon

#include <string>
#include <typeinfo>
#include <iostream>
using namespace std;
using std::string;
#include "TreeElement.h"

TreeElement::TreeElement(string element, size_t frequency)
{
    this->element = element;
    this->frequency = frequency;
}
TreeElement::TreeElement()
{
    element = "";
    frequency = 0;
}
TreeElement::~TreeElement()
{
    /*eliminara de la memoria los elementos*/
}

void TreeElement::SetFrequency(size_t newFrequency)
{
    frequency = newFrequency;
}

void TreeElement::SetElement(string newElement)
{
    element = newElement;
}
string TreeElement::GetElement()
{
    return element;
}
size_t TreeElement::GetFrequency()
{
    return frequency;
}