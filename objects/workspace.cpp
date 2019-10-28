//---------------------------------------------------------------------------

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
	this->mode = MODE_2D;
}

Object * WorkSpace::getObject(int id){
    return objects[id];
}

std::vector<Object*> WorkSpace::getObjects(){
    return this->objects;
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

int WorkSpace::getMode(){
	return this->mode;
}

void WorkSpace::setMode(int mode){
	this->mode = mode;
    update();
}

int WorkSpace::getCanvasH(){
	return this->canvasH;
}

int WorkSpace::getCanvasV(){
	return this->canvasV;
}

/**
 * Transforma as coordenadas do ponto de tela para usuário
 * @param p - Ponto a ser convertido
 */
Point2D * WorkSpace::CoordScrToUser(Point2D * p){
	//	Coordenadas normalizadas [-1, 1]
	Matrix * coordNorm = getWinVPMatrix(-1, 1, 1, -1, 0, canvasH, 0, canvasV);
	//	Coordenadas de usuário
	Matrix * coordUser = getWinVPMatrix(-userH/2, userH/2, userV/2, -userV/2, -1, 1, 1, -1);

	return ((*coordUser)*(*coordNorm)*(*p->asMatrix())).asPoint2D();
}

/**
 * Transforma as coordenadas do ponto de usuário para tela
 * @param p - Ponto a ser convertido
 */
Point2D * WorkSpace::CoordUserToScr(Point2D * p){
	//	Coordenadas normalizadas [-1, 1]
	Matrix * coordNorm = getWinVPMatrix(-1, 1, 1, -1, -userH/2, userH/2, userV/2, -userV/2);
	//	Coordenadas de tela
	Matrix * coordUser = getWinVPMatrix(0, canvasH, 0, canvasV, -1, 1, 1, -1);

	return ((*coordUser)*(*coordNorm)*(*p->asMatrix())).asPoint2D();
}

/**
 * Retorna a proporção entre coordenadas de usuário e coordenadas de tela
 * @param x - Valor a ser convertido
 */
double WorkSpace::CoordUserToScr(double x){
	return (x/userH)*(canvasH);
}

/**
 * Rasteriza os eixos ortogonais 2D ou 3D
 */
void WorkSpace::drawAxis(){
	if (this->drwAxis){
		if (mode == MODE_2D){
			printAxis(this->hdc, this->canvasH, this->canvasV, CL_GREY);
			if (this->drwGrid)
				drawGrid(this->hdc, this->canvasH, this->canvasV, this->userH, this->userV, CL_LIGHTGREY);
		}else{
			printAxis3D(this->hdc, this->canvasH, this->canvasV, CL_GREY);
		}
	}
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

	//	Rasteriza cada objeto na tela (os vértices só são rasterizados no modo 2D)
	for (int i = 0; i < objects.size(); i++) {
		objects[i]->draw(this, this->mode == MODE_2D && this->drwPoints);
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

/**
 * Remove um objeto no workspace
 * @param id - Índice do objeto a ser removido
 */
void WorkSpace::deleteObject(int id){
	eraseObject(objects[id]);           	//  Apaga o objeto da tela
	free(objects[id]);                  	//  Libera da memória
	objects.erase(objects.begin() + id);    //  Remove da lista de objetos
	update();                               //  Atualiza a tela
}

/**
 * Remove todos os objetos do workspace
 */
void WorkSpace::clearObjects(){
	for (int i = 0; i < objects.size(); i++)	{
		free(objects[i]);
	}

	objects.clear();	
}

/**
 * Apaga o objeto selecionado (apenas da tela, rasteriza em branco)
 * @param obj - Referência pra um objeto a ser apagado
 */
void WorkSpace::eraseObject(Object * obj){
	obj->draw(this, this->drwPoints, true);
}

/**
 * Aplica a matriz de transformação a um objeto
 * @param obj - Referência pra um objeto a ser transformado
 * @param M - Matriz de transformação
 * @param caption - Descrição da transformação para armazenar no histórico
 */
void WorkSpace::apply(Object * obj, Matrix * M, String caption){
	if (caption == "") caption = "Transformação";
	eraseObject(obj);
	obj->apply(M, caption);
	update();
}

/**
 * Translada o objeto 2D selecionado
 * @param obj - Referência pra um objeto a ser transladado
 * @param tx - Translação em X
 * @param ty - Translação em Y
 */
void WorkSpace::translateObject(Object * obj, double tx, double ty){
	Matrix * M = getTranslationMatrix(tx, ty);
	String caption = "Translação(" + FormatFloat("0.000", tx) + ", " + FormatFloat("0.000", ty) + ")";
	apply(obj, M, caption);
}

/**
 * Rotaciona o objeto selecionado
 * @param obj - Referência pra um objeto a ser transladado
 * @param tx - Translação em X
 * @param ty - Translação em Y
 */
void WorkSpace::rotateObject(Object * obj, Point2D * ref, double theta){
	Matrix * M = getRotationMatrix(theta, ref);
	String caption = "Rotação(" + FormatFloat("0.000", theta) + ")";
	apply(obj, M, caption);
}

void WorkSpace::scaleObject(Object * obj, Point2D * ref, double sx, double sy){
	Matrix * M = getScaleMatrix(sx, sy, ref);
	String caption = "Escala(" + FormatFloat("0.000", sx) + ", " + FormatFloat("0.000", sy) + ")";
	apply(obj, M, caption);
}

void WorkSpace::shearObject(Object * obj, Point2D * ref, double shx, double shy){
	Matrix * M = getShearMatrix(shx, shy, ref);
	String caption = "Cisalhamento(" + FormatFloat("0.000", shx) + ", " + FormatFloat("0.000", shy) + ")";
	apply(obj, M, caption);
}

void WorkSpace::reflectObject(Object * obj, int axis){
	Matrix * M = getReflectionMatrix(axis);
	String caption = "Reflexão(Eixo ";
	if (axis == 0) {
		caption += "X)";
	}else{
		caption += "Y)";
	}
	apply(obj, M, caption);
}

void WorkSpace::reflectObject(Object * obj, double m, double b){
	Matrix * M = getReflectionMatrix(m, b);
	String caption = "Reflexão(Y = " + FormatFloat("0.000", m) + "X + " + FormatFloat("0.000", b) + ")";
	apply(obj, M, caption);
}

/**
 * Translada o objeto 3D selecionado
 * @param obj - Referência pra um objeto a ser transladado
 * @param tx - Translação em X
 * @param ty - Translação em Y
 */
void WorkSpace::translateObject3D(Object * obj, double tx, double ty, double tz){
	Matrix * M = getTranslation3DMatrix(tx, ty, tz);
	String caption = "Translação(" + FormatFloat("0.000", tx) + ", " + FormatFloat("0.000", ty) + ", " + FormatFloat("0.000", tz) +")";
	apply(obj, M, caption);
}

/**
 * Rotaciona o objeto 3D selecionado
 * @param obj - Referência pra um objeto a ser rotacionado
 * @param axis - Eixo ao qual o objeto será rotacionado
 * @param theta - Ângulo que será aplicada a rotação
 */
void WorkSpace::rotateObject3D(Object * obj, int axis, double theta){
	Matrix * M = getRotation3DMatrix(theta, axis);
	String caption = "Rotação(" + FormatFloat("0.000", theta) + "em torno de ";
	if(axis == 0){
		caption += "X)";
	}
	else if(axis == 1){
		caption += "Y)";
	}
	else {
		caption += "Z)";
	}
	apply(obj, M, caption);
}

/**
 * Escala o objeto 3D selecionado
 * @param obj - Referência pra um objeto a ser escalado
 * @param sx - Fator de escala em X
 * @param sy - Fator de escala em Y
 * @param sz - Fator de escala em Z
 */
void WorkSpace::scaleObject3D(Object * obj, double sx, double sy, double sz){
	Matrix * M = getScale3DMatrix(sx, sy, sz);
	String caption = "Escala(" + FormatFloat("0.000", sx) + ", " + FormatFloat("0.000", sy) + ", " + FormatFloat("0.000", sz) +")";
	apply(obj, M, caption);
}

/**
 * Escala o objeto 3D selecionado com relação a um ponto
 * @param obj - Referência pra um objeto a ser escalado
 * @param ref - Referência pra um ponto ao qual o objeto será escalado em relação ao mesmo
 * @param sx - Fator de escala em X
 * @param sy - Fator de escala em Y
 * @param sz - Fator de escala em Z
 */
void WorkSpace::scaleObject3DRelativePoint(Object * obj, Point3D * ref, double sx, double sy, double sz){
	Matrix * M = getScale3DMatrix(sx, sy, sz, ref);
	String caption = "Escala(" + FormatFloat("0.000", sx) + ", " + FormatFloat("0.000", sy) + ", " + FormatFloat("0.000", sz) +")";
	apply(obj, M, caption);
}

/**
 * Cisalha o objeto 3D selecionado com relação ao eixo X
 * @param obj - Referência pra um objeto a ser cisalhado
 * @param ref - Referência pra um ponto ao qual o objeto será cisalhado em relação ao mesmo
 * @param shy - Fator de cisalhamento em Y
 * @param shz - Fator de cisalhamento em Z
 */
void WorkSpace::shearObject3DAroundX(Object * obj, Point3D * ref, double shy, double shz){
	Matrix * M = getShearMatrixAroundAxisX(shy, shz, ref);
    String caption = "Cisalhamento(" + FormatFloat("0.000", shy) + ", " + FormatFloat("0.000", shz) + " em torno de X)";
	apply(obj, M, caption);
}

/**
 * Cisalha o objeto 3D selecionado com relação ao eixo Y
 * @param obj - Referência pra um objeto a ser cisalhado
 * @param ref - Referência pra um ponto ao qual o objeto será cisalhado em relação ao mesmo
 * @param shx - Fator de cisalhamento em X
 * @param shz - Fator de cisalhamento em Z
 */
void WorkSpace::shearObject3DAroundY(Object * obj, Point3D * ref, double shx, double shz){
	Matrix * M = getShearMatrixAroundAxisX(shx, shz, ref);
    String caption = "Cisalhamento(" + FormatFloat("0.000", shx) + ", " + FormatFloat("0.000", shz) + " em torno de Y)";
	apply(obj, M, caption);
}

/**
 * Cisalha o objeto 3D selecionado com relação ao eixo Z
 * @param obj - Referência pra um objeto a ser cisalhado
 * @param ref - Referência pra um ponto ao qual o objeto será cisalhado em relação ao mesmo
 * @param shx - Fator de cisalhamento em X
 * @param shy - Fator de cisalhamento em Y
 */
void WorkSpace::shearObject3DAroundZ(Object * obj, Point3D * ref, double shx, double shy){
	Matrix * M = getShearMatrixAroundAxisX(shx, shy, ref);
    String caption = "Cisalhamento(" + FormatFloat("0.000", shx) + ", " + FormatFloat("0.000", shy) + " em torno de Z)";
	apply(obj, M, caption);
}

/**
 * Reflete o objeto 3D selecionado com relação a um eixo
 * @param obj - Referência pra um objeto a ser refletido
 * @param axis - Eixo ao qual o objeto será refletido
 */
void WorkSpace::refletObject3D(Object * obj, int axis){
	Matrix * M = getReflectionMatrixAxis(axis);
    String caption = "Reflexão(Eixo ";
	if(axis == 0){
		caption += "X)";
	}
	else if(axis == 1){
		caption += "Y)";
	}
	else {
		caption += "Z)";
	}
	apply(obj, M, caption);
}

/**
 * Reflete o objeto 3D selecionado com relação a um plano
 * @param obj - Referência pra um objeto a ser refletido
 * @param plan - Plano ao qual o objeto será refletido
 */
void WorkSpace::refletObject3DRelativePlan(Object * obj, int plan){
	Matrix * M = getReflectionMatrixPlan(plan);
    String caption = "Reflexão(Plano ";
	if(plan == 0){
		caption += "XY)";
	}
	else if(plan == 1){
		caption += "YZ)";
	}
	else {
		caption += "XZ)";
	}
	apply(obj, M, caption);
}