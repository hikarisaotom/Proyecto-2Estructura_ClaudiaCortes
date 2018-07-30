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
#include "TreeNode.h"
#include "TreeElement.h"
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

TreeNode::TreeNode(const TreeElement &data)
{
    this->_data = new TreeElement(data.element, data.frequency);
    _parent == nullptr;
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

TreeNode::TreeNode(const TreeElement &data, TreeNode *parent)
{
    this->_data = new TreeElement(data.element, data.frequency);
    this->_parent = parent;
}

/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

TreeNode::~TreeNode()
{
    cout << "eliminando..." << endl;
}

/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

vector<TreeNode *> &TreeNode::GetChildren()
{
    return _children;
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

void TreeNode::SetParent(TreeNode *parent)
{
    this->_parent = parent;
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

void TreeNode::AddChild(const TreeElement &data)
{
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

void TreeNode::AddChild(TreeNode *child)
{
    _children.insert(_children.begin(), child);
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

TreeElement *TreeNode::GetData()
{
    return _data;
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

void TreeNode::SetData(const TreeElement &newData)
{
    _data = new TreeElement(newData.element, newData.frequency);
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

bool TreeNode::IsRoot()
{
    if (_parent == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/* 
 descripcion:
 Params: 
 Retorna: 
 Errores: */

bool TreeNode::IsLeaf()
{
    if (_children.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}