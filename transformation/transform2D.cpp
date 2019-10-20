//---------------------------------------------------------------------------

#pragma hdrstop

#include "transform2D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "../objects/matrix.h"
#include "../objects/point.h"

using namespace std;

/**
 * Translada um objeto geométrico.
 * @param tx - deslocamento em  X
 * @param ty - deslocamento em y
 * @return Matrix de translação
 */
Matrix * getTranslationMatrix(double tx, double ty){
	vector<vector<double> > data;

	data.push_back(vector<double>({1,0,tx}));
	data.push_back(vector<double>({0,1,ty}));
	data.push_back(vector<double>({0,0,1}));

	return new Matrix(data);
}

/**
 * Escala um objeto geométrico, dado os fatores de escala para X e/ou para Y
 *
 * @param sx - fator de escala em X
 * @param sy - fator de escala em y
 */
Matrix * getScaleMatrix(double sx, double sy){

	vvd data;

	data.push_back(vector<double>({sx, 0, 0}));
	data.push_back(vector<double>({0, sy, 0}));
	data.push_back(vector<double>({0, 0, 1}));

	return new Matrix(data);
}

/**
 * Escala um objeto geométrico com relação a um ponto p
 *
 * @param Ponto p - ponto de referência ao qual o objeto será escalado
 * @param sx - fator de escala em X
 * @param sy - fator de escala em y
 */
Matrix * getScaleMatrix(double sx, double sy, Point2D * p){

	vvd data;

	// obtidos após as multiplicações de matrizes
	double a = p->X*(-sx + 1);
	double b = p->Y*(-sy + 1);

	data.push_back(vector<double>({sx, 0, a}));
	data.push_back(vector<double>({0, sy, b}));
	data.push_back(vector<double>({0, 0, 1}));

	return new Matrix(data);

}

/**
 * Cisalha um objeto geométrico.
 *
 * @param shx - cisalhamento em  X
 * @param shy - cisalhamento em y
 */
Matrix * getShearMatrix(double shx, double shy){

	vvd data;

	data.push_back(vector<double>({1, shx, 0}));
	data.push_back(vector<double>({shy, 1, 0}));
	data.push_back(vector<double>({0, 0, 1}));

	return new Matrix(data);
}

/**
 * Cisalha um objeto geométrico.
 *
 * @param Ponto - ponto de referência para o cisalhamento
 * @param shx - cisalhamento em  X
 * @param shy - cisalhamento em y
 */
Matrix * getShearMatrix(double shx, double shy, Point2D * p){

	vvd data;

	// obtidos após as multiplicações de matrizes
	double a = -(p->Y * shx);
	double b = -(p->X * shy);

	data.push_back(vector<double>({1, shx, a}));
	data.push_back(vector<double>({shy, 1, b}));
	data.push_back(vector<double>({0, 0, 1}));

	return new Matrix(data);
}

/** 
* Função que realiza a rotação de um objeto em torno da origem dos eixos cordenados
*  
* @param theta double - Ângulo que será aplicada a rotação 
* @return Matrix - matriz que realiza a rotação do objeto
*/
Matrix * getRotationMatrix(double theta){
	theta = M_PI * (theta/180); 
	vector<std::vector<double>> data;

	data.push_back(vector<double>({cos(theta), -sin(theta), 0}));
	data.push_back(vector<double>({sin(theta), cos(theta), 0}));
	data.push_back(vector<double>({0, 0, 1}));

	return new Matrix(data);
}

/** 
* Função que realiza a rotação de um objeto em torno de um ponto fixado
* 
* @param theta double - Ângulo que será aplicada a rotação
* @param p Point2D - ponto em que o objeto irá rotacionar em torno
* @return Matrix - matriz que realiza a rotação do objeto em torno do ponto fixado
*/
Matrix * getRotationMatrix(double theta, Point2D * p){
	theta = M_PI * (theta/180); 
	vector<std::vector<double>> data;

	data.push_back(vector<double>({cos(theta), -sin(theta), ((-p->X*cos(theta)) + (p->Y*sin(theta)) + p->X)}));
	data.push_back(vector<double>({sin(theta), cos(theta), ((-p->X*sin(theta)) + (-p->Y*cos(theta)) + p->Y)}));
	data.push_back(vector<double>({0, 0, 1}));

	return new Matrix(data);
}

/**
 * Reflete um objeto geométrico em relação a um eixo.
 * @param axis - Eixo de reflexão 0: Eixo X, 1: Eixo Y
 */
Matrix * getReflectionMatrix(int axis){
	vvd data;
	
	double a = axis == 0 ? 1 : -1;
	double b = -a;

	data.push_back(vector<double>({a, 0, 0}));
	data.push_back(vector<double>({0, b, 0}));
	data.push_back(vector<double>({0, 0, 1}));

	return new Matrix(data);
}

/**
 * Reflete um objeto geométrico em relação à reta Y = mX + b.
 * @param m - Inclinação da reta de reflexão
 * @param b - Y do ponto em que a reta toca o eixo Y
 */
Matrix * getReflectionMatrix(double m, double b){
	vvd data;

	double den = (1+m*m);

	data.push_back(vector<double>({(1-m*m)/den,   (2*m)/den, (-2*b*m)/den}));
	data.push_back(vector<double>({  (2*m)/den, (m*m-1)/den,    (2*b)/den}));
	data.push_back(vector<double>({        0, 		    0,        	 1}));

	return new Matrix(data);
}

/**
 * Retorna uma matriz identidade
 */
Matrix * getIdentityMatrix(){
	vvd data;

	data.push_back(vector<double>({1,0,0}));
	data.push_back(vector<double>({0,1,0}));
	data.push_back(vector<double>({0,0,1}));

	return new Matrix(data);
}

/**
 * Retorna uma matriz de transformação da viewport
 */
Matrix * getWinVPMatrix(double uMin, double uMax, double vMin, double vMax, int xMin, int xMax, int yMin, int yMax){
	double sx = (uMax-uMin)/(xMax-xMin);
	double sy = (vMax-vMin)/(yMax-yMin);

	Matrix  * M = new Matrix(3,3);

	*M = (*getTranslationMatrix(uMin, vMin))*(*getScaleMatrix(sx, sy))*(*getTranslationMatrix(-xMin, -yMin));

	return M;
}

/**
 * 	Atribui um código de posicionamento ao ponto
 *  @param p - Ponto ao qual será atribuído o código
 *  @param bounds - limites horizontais e verticais da tela
 */ 
int getCode(Point2D * p, int * bounds){
	int code = 0;						// 0000
	
	code |= ((p->X < bounds[0]) << 0);	// 0001
	code |= ((p->X > bounds[1]) << 1);	// 0010
	code |= ((p->Y < bounds[2]) << 2);	// 0100
	code |= ((p->Y > bounds[3]) << 3);	// 1000

	return code;
}

void updatePoint(Point2D * p1, Point2D * p2, int & code, int * bounds){
	double dx = p2->X - p1->X;
	double dy = p2->Y - p1->Y;

	for (int i = 0; i < 4; i++){
		if (code & (1 << i)){
			//	Cruzamento em Y = b
			if (i <= 1){	
				p2->X = bounds[i];
				p2->Y = p1->Y + (bounds[i] - p1->X)*dy/dx;	//	y = y1 + t(y2 - y1)
			
			//	Cruzamento em X = a
			} else{ 		
				p2->X = p1->X + (bounds[i] - p1->Y)*dx/dy;	//	x = x1 + t(x2 - x1)
				p2->Y = bounds[i];
			}
			
			dx = p2->X - p1->X;
			dy = p2->Y - p1->Y;
		}
	}	

	code = getCode(p2, bounds);
}

/**
 *	Algoritmo de recorte Sutherland
 * 
 */
bool cut(Point2D * p1, Point2D * p2, int xMin, int xMax, int yMin, int yMax){
	int bounds[] = {xMin, xMax, yMin, yMax};

	//	Código inicial de capa ponto
	int code1 = getCode(p1, bounds);
	int code2 = getCode(p2, bounds);
	
	//	Enquanto não for trivialmente aceita
	while (code1 || code2){
		if (code1 & code2){
			return false;	//	Trivialmente rejeitada
		}else{
			if (code1) 
				updatePoint(p2, p1, code1, bounds);
			if (code2)
				updatePoint(p1, p2, code2, bounds);
		}
	}

	return true;
}