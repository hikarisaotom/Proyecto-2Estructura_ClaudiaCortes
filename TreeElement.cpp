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
 descripcion: Crea el objeto agregando su elemento y su frecuencia 
 Params: string element que es el caracter que servira para identificar al elemento , size_t frecuencia la cantidad de veces que esta letra aparece en el documento
 Retorna: NA 
 Errores: NA */
TreeElement::TreeElement(string element, size_t frequency)
{
    this->element = element;
    this->frequency = frequency;
}
/* 
 descripcion:constructor vacio del elemento, inicializara el obejto con una frecuencia 0 y caracter vacio
 Params: NA
 Retorna: NA
 Errores: NA*/

TreeElement::TreeElement()
{
    element = "";
    frequency = 0;
}
/* 
 descripcion:Destructor de la clase, eliminara de memoria el objeto
 Params: NA
 Retorna: NA
 Errores: NA*/

TreeElement::~TreeElement()
{
}

/* 
 descripcion:Cambia la frecuencia del elementos por una nueva
 Params: size_t new FRequency, sera el nuevo valor de la frecuenica
 Retorna: NA
 Errores: NA*/
void TreeElement::SetFrequency(size_t newFrequency)
{
    frequency = newFrequency;
}

/* 
 descripcion:Cambia la elsimbolo  del elementos por uno nuevo.
 Params: string newelement, sera el nuevo valor del simbolo.
 Retorna: NA
 Errores: NA*/
void TreeElement::SetElement(string newElement)
{
    element = newElement;
}
/* 
 descripcion:Cambia el codigo del elementos por una nuevo.
 Params: string newelement, sera el nuevo valor del codigo del elemento.
 Retorna: NA
 Errores: NA*/
void TreeElement::setcode(string newElement)
{
    code = newElement;
}

/* 
 descripcion:Retorna el simbolo del elemento en el que estamos
 Params: NA
 Retorna: string element, que representa el simbolo del elemento
 Errores: NA*/

string TreeElement::GetElement()
{
    return element;
}

/* 
 descripcion:Retorna el codigo del elemento en el que estamos
 Params: NA
 Retorna: string code, que representa el codigo del elemento
 Errores: Si el codigo estuviese vacio se retornaria NA*/
string TreeElement::Getcode()
{
    if (code == "")
    {
        return "NA";
    }
    else
    {
        return code;
    }
}
/* 
 descripcion:retorna la frecuencia con la que se encuentra un elemento
 Params: NA
 Retorna: size_t Frequency, que representa la frecuencia con la que paarece el elemento en el archivo
 Errores: NA*/
size_t TreeElement::GetFrequency()
{
    return frequency;
}

/* 
 descripcion:Cambia el codigo ascii del elementos por una nuevo.
 Params: int newelement, sera el nuevo valor del codigo ascii del elemento.
 Retorna: NA
 Errores: NA*/
void TreeElement::setAscii(int newElement)
{
    asciicoce = newElement;
}

/* 
 descripcion:retorna el codigo ascii del elemento 
 Params: NA
 Retorna: int asccicode que equivale al valor en codigo ascci del elemento actual.
 Errores: NA*/
int TreeElement::GetAsciicode()
{
    return asciicoce;
}