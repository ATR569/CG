﻿//---------------------------------------------------------------------------

#pragma hdrstop

#include "transform3D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "../objects/matrix.h"
#include "../objects/point.h"

using namespace std;

/**
 * Translada um objeto geométrico.
 * @param tx - deslocamento em  X
 * @param ty - deslocamento em y
 * @param tz - deslocamento em z
 * @return Matrix de translação
 */
Matrix * getTranslation3DMatrix(double tx, double ty, double tz){
	vector<vector<double> > data;

	data.push_back(vector<double>({1,0,0,tx}));
	data.push_back(vector<double>({0,1,0,ty}));
	data.push_back(vector<double>({0,0,1,tz}));
	data.push_back(vector<double>({0,0,0,1}));

	return new Matrix(data);
}

/**
 * Escala um objeto geométrico, dado os fatores de escala para X e/ou para Y e/ou para Z
 *
 * @param sx - fator de escala em X
 * @param sy - fator de escala em y
 * @param sz - fator de escala em z
 */
Matrix * getScale3DMatrix(double sx, double sy, double sz){

	vvd data;

	data.push_back(vector<double>({sx, 0, 0, 0}));
	data.push_back(vector<double>({0, sy, 0, 0}));
	data.push_back(vector<double>({0, 0, sz, 0}));
	data.push_back(vector<double>({0, 0,  0, 1}));

	return new Matrix(data);
}

/**
 * Escala um objeto geométrico com relação a um ponto p
 *
 * @param Ponto p - ponto de referência ao qual o objeto será escalado
 * @param sx - fator de escala em X
 * @param sy - fator de escala em y
 * @param sz - fator de escala em z
 */
Matrix * getScale3DMatrix(double sx, double sy, double sz, Point3D * p){	

	vvd data;

	// obtidos após as multiplicações de matrizes
	double a = p->X*(-sx + 1);
	double b = p->Y*(-sy + 1);
	double c = p->Z*(-sz + 1);

	data.push_back(vector<double>({sx, 0, 0, a}));
	data.push_back(vector<double>({0, sy, 0, b}));
	data.push_back(vector<double>({0, 0, sz, c}));
	data.push_back(vector<double>({0, 0, 0,  1}));

	return new Matrix(data);

}

/**
 * Cisalha um objeto geométrico em relação ao Eixo X.
 * @param Ponto - ponto de referência para o cisalhamento
 * @param shy - cisalhamento em  Y
 * @param shz - cisalhamento em Z
 */
Matrix * getShearMatrixAroundAxisX(double shy, double shz, Point3D * p){

	vvd data;

	double a = -(p->X * shy);
	double b = -(p->X * shz);

	data.push_back(vector<double>({1,   0, 0, 0}));
	data.push_back(vector<double>({shy, 1, 0, a}));
	data.push_back(vector<double>({shz, 0, 1, b}));
	data.push_back(vector<double>({0,   0, 0, 1}));

	return new Matrix(data);
}

/**
 * Cisalha um objeto geométrico em relação ao Eixo Y.
 * @param Ponto - ponto de referência para o cisalhamento
 * @param shx - cisalhamento em  X
 * @param shz - cisalhamento em Z
 */
Matrix * getShearMatrixAroundAxisY(double shx, double shz, Point3D * p){

	vvd data;

	double a = -(p->Y * shx);
	double b = -(p->Y * shz);

	data.push_back(vector<double>({1, shx, 0, a}));
	data.push_back(vector<double>({0,   1, 0, 0}));
	data.push_back(vector<double>({0, shz, 1, b}));
	data.push_back(vector<double>({0, 0,   0, 1}));

	return new Matrix(data);
}

/**
 * Cisalha um objeto geométrico em relação ao Eixo Z.
 * @param Ponto - ponto de referência para o cisalhamento
 * @param shx - cisalhamento em  X
 * @param shy - cisalhamento em Y
 */
Matrix * getShearMatrixAroundAxisZ(double shx, double shy, Point3D * p){
	vvd data;

	double a = -(p->Z * shx);
	double b = -(p->Z * shy);

	data.push_back(vector<double>({1, 0, shx, a}));
	data.push_back(vector<double>({0, 1, shy, b}));
	data.push_back(vector<double>({0, 0,   1, 0}));
	data.push_back(vector<double>({0, 0,   0, 1}));

	return new Matrix(data);
}

/**
* Função que realiza a rotação de um objeto em torno do eixo X
*
* @param theta double - Ângulo que será aplicada a rotação
* @param axis int - Eixo ao qual será aplicado a rotação
* @return Matrix - matriz que realiza a rotação do objeto
*/
Matrix * getRotationMatrixAroundAxisX(double theta, vvd & data){

	data.push_back(vector<double>({1, 0, 0, 0}));
	data.push_back(vector<double>({0, cos(theta), -sin(theta), 0}));
	data.push_back(vector<double>({0, sin(theta), cos(theta), 0}));
	data.push_back(vector<double>({0, 0, 0, 1}));

	return new Matrix(data);
}

/**
* Função que realiza a rotação de um objeto em torno do eixo Y
*
* @param theta double - Ângulo que será aplicada a rotação
* @param axis int - Eixo ao qual será aplicado a rotação
* @return Matrix - matriz que realiza a rotação do objeto
*/
Matrix * getRotationMatrixAroundAxisY(double theta, vvd & data){

	data.push_back(vector<double>({cos(theta), 0, sin(theta), 0}));
	data.push_back(vector<double>({0, 1, 0, 0}));
	data.push_back(vector<double>({-sin(theta), 0, cos(theta), 0}));
	data.push_back(vector<double>({0, 0, 0, 1}));

	return new Matrix(data);
}

/**
* Função que realiza a rotação de um objeto em torno do eixo Z
*
* @param theta double - Ângulo que será aplicada a rotação
* @param axis int - Eixo ao qual será aplicado a rotação
* @return Matrix - matriz que realiza a rotação do objeto
*/
Matrix * getRotationMatrixAroundAxisZ(double theta, vvd & data){

	data.push_back(vector<double>({cos(theta), -sin(theta), 0, 0}));
	data.push_back(vector<double>({sin(theta), cos(theta), 0, 0}));
	data.push_back(vector<double>({0, 0, 1, 0}));
	data.push_back(vector<double>({0, 0, 0, 1}));

	return new Matrix(data);
}

/**
* Função que realiza a rotação de um objeto em torno do eixo passado como parâmetro
*
* @param theta double - Ângulo que será aplicada a rotação
* @param axis int - Eixo ao qual será aplicado a rotação
* @return Matrix - matriz que realiza a rotação do objeto
*/
Matrix * getRotation3DMatrix(double theta, int axis){
	theta = M_PI * (theta/180);
	vector<std::vector<double>> data;

	if(axis == 0) return getRotationMatrixAroundAxisX(theta, data);
	else if(axis == 1) return getRotationMatrixAroundAxisY(theta, data);
	else return getRotationMatrixAroundAxisZ(theta, data);
}

/**
 * Reflete um objeto geométrico em relação a um Eixo.
 * @param axis - Eixo de reflexão 0: Eixo X, 1: Eixo Z, 2: Eixo Z
 */
Matrix * getReflectionMatrixAxis(int axis){
	vvd data;
	double a = -1, b = -1, c = -1;

	if(axis == 0) a = 1;
	else if(axis == 1) b = 1;
	else c = 1;
	
	data.push_back(vector<double>({a, 0, 0, 0}));
	data.push_back(vector<double>({0, b, 0, 0}));
	data.push_back(vector<double>({0, 0, c, 0}));
	data.push_back(vector<double>({0, 0, 0, 1}));

	return new Matrix(data);
}

/**
 * Reflete um objeto geométrico em relação a um plano.
 * @param plan - Plano de reflexão 0: Plano XY, 1: Plano YZ, 2: Plano XZ
 */
Matrix * getReflectionMatrixPlan(int plan){
	vvd data;
	double a = 1, b = 1, c = 1;

	if(plan == 0) c = -1;
	else if(plan == 1) a = -1;
	else b = -1;
	
	data.push_back(vector<double>({a, 0, 0, 0}));
	data.push_back(vector<double>({0, b, 0, 0}));
	data.push_back(vector<double>({0, 0, c, 0}));
	data.push_back(vector<double>({0, 0, 0, 1}));

	return new Matrix(data);
}

/**
 * Retorna uma matriz identidade
 */
Matrix * getIdentity3DMatrix(){
	vvd data;

	data.push_back(vector<double>({1,0,0,0}));
	data.push_back(vector<double>({0,1,0,0}));
	data.push_back(vector<double>({0,0,1,0}));
	data.push_back(vector<double>({0,0,0,1}));

	return new Matrix(data);
}
/**
 * Retorna uma matriz que alinha a câmera para executar a projeção
 */ 
Matrix * getProjectionMatrix(){
	Matrix * M = new Matrix(4,4);
	*M = (*getRotation3DMatrix(45, 0))*(*getRotation3DMatrix(-45, 1));
	return M;
}

/**
 * Retorna uma matriz que alinha a câmera para executar a projeção Frontal
 */ 
Matrix * getFrontalProjectionMatrix(){
	return getIdentity3DMatrix();
}

Matrix * getSideProjectionMatrix(){
	return getRotation3DMatrix(-90, 1);
}

Matrix * getTopProjectionMatrix(){
	return getRotation3DMatrix(90, 0);
}
