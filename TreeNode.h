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
using namespace std;

#ifndef TREENODE_H
#define TREENODE_H

class TreeNode
{
private:
  TreeElement *_head;
  vector<TreeNode *> _children;
  TreeNode *_parent;
  TreeElement*  _data;

public:
  TreeNode(const TreeElement&);
  TreeNode(const TreeElement&, TreeNode *);
  ~TreeNode();
  vector<TreeNode *> &GetChildren();
  void SetParent(TreeNode *);
  void AddChild(const TreeElement&);
  void AddChild(TreeNode *);
  TreeElement*  GetData();
  void SetData(const TreeElement&);
  bool IsRoot();
  bool IsLeaf();
  void elimanar(TreeNode*);
};
#endif