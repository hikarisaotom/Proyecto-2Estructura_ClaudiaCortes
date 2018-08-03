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
 descripcion: Constructor que crea el nodo de árbol con los datos
del parámetro
 Params: TreeElement &data, representa el Treelement del cual sacaremos los datos para crear el objeto
 Retorna: N/A
 Errores: N/A*/

TreeNode::TreeNode(const TreeElement &data)
{
    this->_data = new TreeElement(data.element, data.frequency);
    _parent == nullptr;
}

/* 
 descripcion:Constructor que crea el nodo de árbol con los datos
del primer parámetro y con padre parent
 Params: const TreeElement &data, permitira un acceso a crear el elemento del aebol
        TreeNode *parent, sera el nuevo padre
 Retorna: N/A
 Errores: N/A*/

TreeNode::TreeNode(const TreeElement &data, TreeNode *parent)
{
    this->_data = new TreeElement(data.element, data.frequency);
    this->_parent = parent;
}

/* 
 descripcion:libera la memoria del objeto 
 Params: N/A
 Retorna:N/A 
 Errores: si un nodo ya ha liberado memoria para evitar run time errors no se liberara*/

TreeNode::~TreeNode()
{
}

/* 
 descripcion: Recupera la referencia a la lista de hijos
 Params: N/A
 Retorna: Vector <TreeNode*>, que representa a la lista de hijos del arbol
 Errores: */

vector<TreeNode *> &TreeNode::GetChildren()
{
    return _children;
}

/* 
 descripcion: Establece el padre del nodo
 Params: TreeNode *parent, representa el nuevo padre del nodo
 Retorna: N/A
 Errores: N/A*/

void TreeNode::SetParent(TreeNode *parent)
{
    this->_parent = parent;
}

/* 
 descripcion:Agrega un hijo a la izquierda del último hijo agregado, usando el dato del parámetro
 Params:const TreeElement &data, sera el elemento del cual podremos extraerlos datos y crear un nuevo hijo 
 Retorna: N/A
 Errores: N/A*/

void TreeNode::AddChild(const TreeElement &data)
{
    _children.insert(_children.begin(), new TreeNode(*new TreeElement(data.element, data.frequency), this));
}

/* 
 descripcion:Agrega un subárbol  a la “izquierda” del último hijo agregado
 Params: TreeNode* child, sera el subarbol que insertaremos la lista de hijos del nodo
 Retorna: N/A 
 Errores: N/A*/

void TreeNode::AddChild(TreeNode *child)
{
    child->SetParent(this);
    _children.insert(_children.begin(), child);
}

/* 
 descripcion: Recupera los datos almacenados en el nodo
 Params: N/A
 Retorna: TreeElement* _data, que contiene los datos almacenados del arbol
 Errores: N/A*/

TreeElement *TreeNode::GetData()
{
    return _data;
}

/* 
 descripcion:Establece los datos a almacenar en el nodo
 Params: const TreeElement &newData, contiene los nuevos datos que se almacenaran en el nodo
 Retorna: N/A
 Errores: N/A*/

void TreeNode::SetData(const TreeElement &newData)
{
    _data = new TreeElement(newData.element, newData.frequency);
}

/* 
 descripcion:Verifica si un nodo es raíz
 Params: N/A
 Retorna: true si determina que el nodo es una raiz, false en caso contrario
 Errores: N/A*/

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
 descripcion:Verifica si un nodo es una hoja 
 Params: N/A
 Retorna: true si determina que el nodo es una hoja, false en caso contrario
 Errores: N/A*/

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