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

DrawMethod Object::getMethod(){
    return this->drawMethod;
}

/**
 * Aplica uma transformação ao objeto
 * @param M - Matriz de transformação
 */
void Object::apply(Matrix * M, std::string caption){
	//	Atualiza a matriz estado do objeto
	stateMatrix->assign((*M)*(*this->stateMatrix));
	//	Armazena no histórico do objeto
	this->history.push_back(Transformation(caption, M));
}

//Transformation----------------------------------------------------------------
Transformation::Transformation(string name, Matrix * M){
	this->name = name;
	this->M = M;
}