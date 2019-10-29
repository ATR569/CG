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
Object::Object(String name, DrawMethod drawMethod){
    this->name = name;
	this->drawMethod = drawMethod;
	this->color = CL_BLACK;
}

/**
 * Getter para o nome do objeto 
 * return String
 */
String Object::getName(){
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

list<Transformation> Object::getHistory(){
    return this->history;
}

Matrix * Object::getStateMatrix(){
	return this->stateMatrix;
}

/**
 * Aplica uma transformação ao objeto
 * @param M - Matriz de transformação
 */
void Object::apply(Matrix * M, String caption){
	//	Atualiza a matriz estado do objeto
	stateMatrix->assign((*M)*(*this->stateMatrix));
	//	Armazena no histórico do objeto
	this->history.push_back(Transformation(caption, M));
}

void Object::setDrawMethod(DrawMethod drawMethod){
	this->drawMethod = drawMethod;
}

void Object::setStateMatrix(Matrix * stateMatrix){
	this->stateMatrix->assign(*stateMatrix);
}

void Object::cropHistory(unsigned maxSize){
	while (this->history.size() > maxSize){
		this->history.pop_back();
	}
}


//Transformation----------------------------------------------------------------
Transformation::Transformation(String name, Matrix * M){
	this->name = name;
	this->M = M;
}

String Transformation::getName(){
    return this->name;
}

Matrix * Transformation::getMatrix(){
    return this->M;
}
