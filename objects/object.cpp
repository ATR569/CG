//---------------------------------------------------------------------------

#pragma hdrstop

#include "object.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "workspace.h"
#include "matrix.h"

//Object------------------------------------------------------------------------
/**
 * Construtor de Object
 * @param name - Nome do objeto
 * @param drawMethod - Algoritmo usado na rasterização
 */
Object::Object(string name, DrawMethod drawMethod){
    this->name = name;
	this->drawMethod = drawMethod;
	this->color = CL_BLACK;
	this->stateMatrix = getIdentityMatrix();
	this->history.push(getIdentityMatrix());
}

/**
 * Getter para o nome do objeto 
 * return string
 */
string Object::getName(){
    return this->name;
}

void Object::setColor(DrawColor color){
	this->color = color;
}

DrawColor Object::getColor(){
	return this->color;
}

/**
 * Aplica uma transformação ao objeto
 * @param M - Matriz de transformação
 */
void Object::apply(Matrix * M){
	//	Atualiza a matriz estado do objeto
	*this->stateMatrix = (*M)*(*this->stateMatrix);
	//	Armazena no histórico do objeto
	this->history.push(M);
}

