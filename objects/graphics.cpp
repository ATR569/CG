//---------------------------------------------------------------------------

#pragma hdrstop

#include "graphics.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "point.h"

/**
 * 	Rasteriza os eixos ortogonais
 *  @param hdc HDC - Manipulador da tela
 *  @param width int - Largura da tela
 *  @param height int - Altura da tela
 *  @param color DrawColor - Cor da linha
 */
void printAxis(HDC & hdc, int width, int height, DrawColor color){
	int xAxis = round(height/2);
	int yAxis = round(width/2);

	for (int i = 0; i < width; i++) {
		SetPixel(hdc, i, xAxis, color);
	}

	for (int i = 0; i < height; i++) {
		SetPixel(hdc, yAxis, i, color);
	}
}
/**
 * 	Rasteriza uma grade
 *  @param hdc HDC - Manipulador da tela
 *  @param width int - Largura da tela
 *  @param height int - Altura da tela
 *  @param color DrawColor - Cor da linha
 *  @param bg DrawColor[][] - Matriz de pixels do background
 */
void drawGrid(HDC & hdc, double canvasH, double canvasV, double userH, double userV, DrawColor color){
	
	int xAxis = round(canvasV/2);
	int yAxis = round(canvasH/2);

	//	Linhas pontilhadas
	double incLine = 10*canvasH/userH;
	for (int i = round(incLine); i+xAxis <= (int)canvasV; i += round(incLine)) {
		for (int j = 0; j <= canvasH; j+=10){
			for (int k = 0; k < 5; k++){
				//	Rasteriza a linha pontilhada
				SetPixel(hdc, j+k, xAxis+i, color);
				SetPixel(hdc, j+k, xAxis-i, color);
				//	Armazena os pixels na matriz
			}
		}
	}

	//	Colunas pontilhadas
	double incRow = 10*canvasV/userV;
	for (int i = round(incRow); i+yAxis <= (int)canvasH; i += round(incRow)) {
		for (int j = 0; j <= canvasV; j+=10){
			for (int k = 0; k < 5; k++){
				//	Rasteriza a coluna pontilhada
				SetPixel(hdc, yAxis+i, j+k, color);
				SetPixel(hdc, yAxis-i, j+k, color);
				//	Armazena os pixels na matriz
			}
		}
	}
}

/**
 * 	Rasteriza uma reta usando o algoritmo do ponto médio (Bresenhan)
 *  @param hdc HDC - Manipulador da tela
 *  @param p1 Ponto - Ponto inicial da reta
 *  @param p2 Ponto - Ponto final da reta
 *  @param color unsigned - Cor da reta
 */
void drawLineBresenhan(HDC & hdc, Point2D * p1, Point2D * p2, DrawColor color){
	int dX = abs(p2->X - p1->X);
	int dY = abs(p2->Y - p1->Y);

	//	oitantes 1, 4, 5, 8
	if (dY < dX) {
		if (p2->X < p1->X) swap(p1, p2);

		int X = (p1->X);
		int Y = (p1->Y);

		//	Inclinação negativa => yInc = -1
		int yInc = p2->Y < p1->Y ? -1 : 1;
		int p = 2*dY - dX;

		while (X <= p2->X){
			SetPixel(hdc, X, Y, color);

			if (p < 0){
				p += 2*dY;
			}else{
				p += 2*(dY-dX);
				Y += yInc;
			}
			X++;
		}
	}else{	//	oitantes 2, 3, 6 e 7
		if (p2->Y < p1->Y) swap(p1, p2);

		int X = (p1->X);
		int Y = (p1->Y);

		//	Inclinação negativa => xInc = -1
		int xInc = p2->X < p1->X ? -1 : 1;
		int p = 2*dX - dY;

		while (Y <= p2->Y){
			SetPixel(hdc, X, Y,color);

			if (p < 0){
				p += 2*dX;
			}else{
				p += 2*(dX-dY);
				X += xInc;
			}
			Y++;
		}
	}
}


/**
* Rasteriza uma reta através do algoritmo DDA.
* @param hdc HDC - manipulador da tela.
* @param p1, p2 Ponto - ponto inicial e final da reta.
* @param color unsigned - cor na qual a reta será impressa.
*/
void drawLineDDA(HDC & hdc, Point2D * p1, Point2D * p2, DrawColor color){
    double X = p1->X, Y = p1->Y;
    double dx = p2->X - p1->X,  dy = p2->Y - p1->Y;

    if(X == p2->X){
		for(int i = min(Y, p2->Y); i <= max(Y, p2->Y); i++)
			SetPixel(hdc, X, i, color);
	}else{
		int length = max(abs(dx), abs(dy));

		double xInc = dx / length;
		double yInc = dy / length;

		while(round(X) != round(p2->X)){
			SetPixel(hdc, round(X), round(Y), color);

			X += xInc;
			Y += yInc;
		}
		SetPixel(hdc, round(X), round(Y), color);
	}
}

/**
 * Método auxiliar para setar os pixels do círculo
 * @param hdc HDC - Manipulador da tela
 * @param X double - Variavel auxiliar centrada na origem
 * @param Y double - Raio do círculo
 * @param center Ponto - Pontos (x,y) em que o círculo está centrado
 * @param color unsigned - Cor do círculo
 * @param oct bool - Indica se a simetria é de ordem 8
 */
void circlePoints(HDC & hdc, double X, double Y, Point2D * center, DrawColor color, bool oct){
	double xValues[] = {-X,X};
	double yValues[] = {-Y,Y};

	//  Simetria de ordem 4
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			SetPixel(hdc, round(xValues[i] + center->X), round(yValues[j] + center->Y), color);

	//  Simetria de ordem 8
	if (oct) {
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				SetPixel(hdc, round(yValues[i] + center->X), round(xValues[j] + center->Y), color);
	}
}

/**
 * Desenha um círculo utilizando o algoritmo do ponto médio (Bresenhan)
 * @param hdc HDC - Manipulador da tela
 * @param center Ponto - Pontos (x,y) em que o círculo está centrado
 * @param radius double - Raio da circunferência
 * @param color unsigned - Cor do círculo
 */
void drawCircleBresenhan(HDC & hdc, Point2D * center, double radius, DrawColor color){
	int X = 0;
	int Y = round(radius);
	int d = (1 - round(radius));
	circlePoints(hdc, X, Y, center, color, true);

	while(Y > X){
		if(d < 0){
			d += 2 * X + 3;
		}else{
			d += 2 * (X - Y) + 5;
			Y--;
		}
		X++;
		circlePoints(hdc, X, Y, center, color, true);
	}
}

/**
 * Desenha um círculo utilizando o método polinomial
 * @param hdc HDC - Manipulador da tela
 * @param center Ponto - Pontos (x,y) em que o círculo está centrado
 * @param radius double - Raio da circunferência
 * @param color unsigned - Cor do círculo
*/
void drawCirclePolynomial(HDC & hdc, Point2D * center, double radius, DrawColor color){
	double X = 0, Y = radius;
	double xEnd = radius;

	//  Rasterização com simetria de ordem 4
	while(X <= xEnd){
		Y = sqrt((radius*radius) - (X*X));
		circlePoints(hdc, X, Y, center, color);

		X++;
	}
}

/**
 * Desenha um círculo utilizando o método trigonométrico
 * @param hdc HDC - Manipulador da tela
 * @param center Ponto - Pontos (x,y) em que o círculo está centrado
 * @param radius double - Raio da circunferência
 * @param color unsigned - Cor do círculo
 */
void drawCircleTrigonometric(HDC & hdc, Point2D * center, double radius, DrawColor color){
	double X = 0, Y = radius;
	double theta = 0;
	double thetaEnd = M_PI_4;
	double thetaInc = 1/radius;

	while(theta <= thetaEnd){
		X = radius * cos(theta);
		Y = radius * sin(theta);

		circlePoints(hdc, X, Y, center, color, true);
		theta += thetaInc;
	}
}

/**
 * Desenha um ponto
 * @param hdc HDC - Manipulador da tela
 * @param Ponto - Ponto (x,y) a ser desenhado
 * @param color DrawColor - Cor do ponto
 */
void drawPoint(HDC & hdc, Point2D * P, DrawColor color){
	for (int i = 0; i <= 2; i++){
		for (int j = 0; j <= 2; j++){
			SetPixel(hdc, round(P->X-j), round(P->Y+i), color);
			SetPixel(hdc, round(P->X+j), round(P->Y+i), color);
			SetPixel(hdc, round(P->X+j), round(P->Y-i), color);
			SetPixel(hdc, round(P->X-j), round(P->Y-i), color);
		}
	}
}
