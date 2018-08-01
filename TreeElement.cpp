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
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
TreeElement::TreeElement(string element, size_t frequency)
{
    this->element = element;
    this->frequency = frequency;
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

TreeElement::TreeElement()
{
    element = "";
    frequency = 0;
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

TreeElement::~TreeElement()
{
    /*eliminara de la memoria los elementos*/
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
void TreeElement::SetFrequency(size_t newFrequency)
{
    frequency = newFrequency;
}

/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
void TreeElement::SetElement(string newElement)
{
    element = newElement;
}

void TreeElement::setcode(string newElement)
{
    code = newElement;
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

string TreeElement::GetElement()
{
    return element;
}
string TreeElement::Getcode()
{
    if(code==""){
        return "NA";
    }else{
        return code;
    }
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */
size_t TreeElement::GetFrequency()
{
    return frequency;
}