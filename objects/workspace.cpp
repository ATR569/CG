﻿//---------------------------------------------------------------------------

#pragma hdrstop

#include "workspace.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "graphics.h"
#include "point.h"
#include "object.h"
#include "matrix.h"

/**
 * Construtor da classe WorkSpace
 */
WorkSpace::WorkSpace(double userH, int canvasH, int canvasV, HDC hdc){
	this->userH = userH;
	this->canvasH = canvasH;
	this->canvasV = canvasV;

	if (canvasH > 0)
		this->userV = userH*canvasV/canvasH;
	else
        this->userV = userH;
	
	this->hdc = hdc;
	this->drwAxis = true;
	this->drwGrid = true;
	this->drwPoints = true;
	this->mode = MODE2D;
}

Point2D * WorkSpace::CoordScrToUser(Point2D * p){
	Matrix * coordNorm = getWinVPMatrix(-1, 1, 1, -1, 0, canvasH, 0, canvasV);
	Matrix * coordUser = getWinVPMatrix(-userH/2, userH/2, userV/2, -userV/2, -1, 1, 1, -1);

	return ((*coordUser)*(*coordNorm)*(*p->asMatrix())).asPoint2D();
}

Point2D * WorkSpace::CoordUserToScr(Point2D * p){
	Matrix * coordNorm = getWinVPMatrix(-1, 1, 1, -1, -userH/2, userH/2, userV/2, -userV/2);
	Matrix * coordUser = getWinVPMatrix(0, canvasH, 0, canvasV, -1, 1, 1, -1);

	return ((*coordUser)*(*coordNorm)*(*p->asMatrix())).asPoint2D();
}

double WorkSpace::CoordUserToScr(double x){
	return (x/userH)*(canvasH);
}

int WorkSpace::getMode(){
	return this->mode;
}

void WorkSpace::setMode(int mode){
	this->mode = mode;
}

int WorkSpace::getCanvasH(){
	return this->canvasH;
}

int WorkSpace::getCanvasV(){
	return this->canvasV;
}

/**
 * Rasteriza os eixos ortogonais X e Y
 */
void WorkSpace::drawAxis(){
	if (this->drwAxis)
		printAxis(this->hdc, this->canvasH, this->canvasV, CL_GREY);
	if (this->drwGrid)
		drawGrid(this->hdc, this->canvasH, this->canvasV, this->userH, this->userV, CL_LIGHTGREY);
}

/**
 * Atualiza as dimensões da tela (em pixels)
 * @param width - Largura em pixels da tela
 * @param height - Altura em pixels da tela
 */ 
void WorkSpace::setCanvasSize(int width, int height){
    //  Atualiza as coordenadas de tela
    this->canvasH = width;
    this->canvasV = height;

    //  Ajusta a proporção das coordenadas de usuário
	if (width > 0)
		this->userV = userH*height/width;
}

/**
 * Método para atualizar a tela com o objetos criados
 */
void WorkSpace::update(){
	drawAxis();

	for (int i = 0; i < objects.size(); i++) {
		objects[i]->draw(this, this->drwPoints);
	}
}

/**
 * Adiciona um objeto no workspace
 * @param obj - Referência pra um objeto a ser inserido
 */
void WorkSpace::addObject(Object * obj){
	this->objects.push_back(obj);
	update();
}

void WorkSpace::deleteObject(int id){
	eraseObject(objects[id]);
	free(objects[id]);
	objects.erase(objects.begin() + id);
	update();
}

void WorkSpace::clearObjects(){
	for (int i = 0; i < objects.size(); i++)	{
		free(objects[i]);
	}

	objects.clear();	
}


Object * WorkSpace::getObject(int id){
    return objects[id];
}

void WorkSpace::setDrawPoints(bool drwPoints){
	this->drwPoints = drwPoints;
}
void WorkSpace::setDrawAxis(bool drwAxis){
	this->drwAxis = drwAxis;
}
void WorkSpace::setDrawGrid(bool drwGrid){
	this->drwGrid = drwGrid;
}

void WorkSpace::eraseObject(Object * obj){
	obj->draw(this, this->drwPoints, true);
}

// Transformations
void WorkSpace::apply(Object * obj, Matrix * M, std::string caption){
	if (caption == "") caption = "Transformação";
	eraseObject(obj);
	obj->apply(M, caption);
	update();
}

void WorkSpace::translateObject(Object * obj, double tx, double ty){
	Matrix * M = getTranslationMatrix(tx, ty);
	std::string caption = "Translação(" + to_string(tx) + ", " + to_string(ty) + ")";
	apply(obj, M, caption);
}

void WorkSpace::rotateObject(Object * obj, Point2D * ref, double theta){
	Matrix * M = getRotationMatrix(theta, ref);
	std::string caption = "Rotação(" + to_string(theta) + ")";
	apply(obj, M, caption);
}

void WorkSpace::scaleObject(Object * obj, Point2D * ref, double sx, double sy){
	Matrix * M = getScaleMatrix(sx, sy, ref);
	std::string caption = "Escala(" + to_string(sx) + ", " + to_string(sy) + ")";
	apply(obj, M, caption);
}

void WorkSpace::shearObject(Object * obj, Point2D * ref, double shx, double shy){
	Matrix * M = getShearMatrix(shx, shy, ref);
	std::string caption = "Cisalhamento(" + to_string(shx) + ", " + to_string(shy) + ")";
	apply(obj, M, caption);
}

void WorkSpace::reflectObject(Object * obj, int axis){
	Matrix * M = getReflectionMatrix(axis);
	std::string caption = "Reflexão(Eixo ";
	if (axis == 0) {
		caption += "X)";
	}else{
		caption += "Y)";
	}
	apply(obj, M, caption);
}

void WorkSpace::reflectObject(Object * obj, double m, double b){
	Matrix * M = getReflectionMatrix(m, b);
	std::string caption = "Reflexão(Y = " + to_string(m) + "X + " + to_string(b) + ")";
	apply(obj, M, caption);
}
