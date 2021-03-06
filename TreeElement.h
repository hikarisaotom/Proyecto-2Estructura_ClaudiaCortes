// Titulo: Proyecto #2 Codificación usando Árbol de Huffman
//Codificacion de caracteres mediante arbol de huffman
//
// Proposito: Crear una aplicacion capaz de leer de un archivo y codificar una serie de datos
//
// Clase: CCC209 – Q3 – 2018
//
// Author: Claudia Patricia Cortes Pavon
#pragma once
#include <iostream>
#include <vector>
#include "TreeElement.h"
#include <string>
using namespace std;

#ifndef TREEELEMENT_H
#define TREEELEMENT_H

class TreeElement
{
public:
  string element;
  string code;
  size_t frequency;
  int asciiCode;
  TreeElement(string element, size_t frequency);
  ~TreeElement();
  TreeElement();
  void SetFrequency(size_t newFRequency);
  void SetElement(string newElement);
  void setAscii(int x);
  void setcode(string);
  string GetElement();
  string Getcode();
  int GetAsciicode();
  size_t GetFrequency();
};
#endif