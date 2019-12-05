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
 * 	Rasteriza os eixos ortogonais no R3
 *  @param hdc HDC - Manipulador da tela
 *  @param width int - Largura da tela
 *  @param height int - Altura da tela
 *  @param color DrawColor - Cor da linha
 */
void printAxis3D(HDC & hdc, int width, int height, DrawColor color){
	int xAxis = round(width/2);
	int yAxis = round(height/2);

	for (int i = 0; i < height/2; i++) {
		SetPixel(hdc, xAxis, i, color);
	}

	double tan35 = tan(35.0/180*M_PI);

	drawLineBresenhan(hdc, new Point2D(xAxis, yAxis), new Point2D(xAxis + 2*yAxis*tan35, height), color);
	drawLineBresenhan(hdc, new Point2D(xAxis, yAxis), new Point2D(xAxis - 2*yAxis*tan35, height), color);
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
	p1->X = round(p1->X);
	p1->Y = round(p1->Y);
	p2->X = round(p2->X);
	p2->Y = round(p2->Y);
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
    if (p1->X > p2->X) swap(p1, p2);

	double X = p1->X, Y = p1->Y;
    double dx = p2->X - p1->X,  dy = p2->Y - p1->Y;

    if(X == p2->X){
		for(int i = min(Y, p2->Y); i <= max(Y, p2->Y); i++)
			SetPixel(hdc, X, i, color);
	}else{
		double length = max(abs(dx), abs(dy));

		double xInc = dx / length;
		double yInc = dy / length;

		while(X <= p2->X){
			SetPixel(hdc, round(X), round(Y), color);

			X += xInc;
			Y += yInc;
		}
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

/**
 * Desenha uma elipse utilizando o algoritmo do ponto médio (Bresenhan)
 * @param hdc HDC - Manipulador da tela
 * @param center Point2D - Pontos (x,y) em que a elipse está centrada
 * @param radius Point2D - Pontos (x,y) distância da origem até os pontos x e y
 * @param color unsigned - Cor da elipse
 */
void drawElipseBresenhan(HDC & hdc, Point2D * center, double a, double b, DrawColor color){
	double dx, dy, d1, d2, x, y, rx, ry, rx2, ry2;
	rx = a;
	ry = b;
	rx2 = rx*rx;
	ry2 = ry*ry;
	x = 0;
	y = b;

	// Parâmetro de decisão inicial da 1º região
	d1 = ry2 - (rx2 * ry) + (0.25 * rx2);
	dx = 2 * ry2 * x; // incremento em x 
	dy = 2 * rx2 * y; // incremento em y

	// Para a primeira região
	while(dx < dy){
		circlePoints(hdc, x, y, center, color); // rasterização a primeira região

		// Verificando e atualizando a variavel de decisão 
		if(d1 < 0){
			x++;
			dx = dx + (2 * ry2);
			d1 = d1 + dx + ry2;
		}else{
			x++;
			y--;
			dx = dx + (2 * ry2);
			dy = dy - (2 * rx2);
			d1 = d1 + dx - dy + ry2;
		}
	}
	
	// Parâmetro de decisão da 2º região
	d2 = (ry2 * ((x + 0.5) * (x + 0.5))) + (rx2 * ((y - 1) * (y - 1))) - (rx2 * ry2);

	// Para a segunda região
	while(y >= 0){
		circlePoints(hdc, x, y, center, color); // rasterização a segunda região

		if(d2 > 0){
			y--;
			dy = dy - (2 * rx2); 
            d2 = d2 + rx2 - dy; 
		}else{
			y--; 
            x++; 
            dx = dx + (2 * ry2); 
            dy = dy - (2 * rx2); 
            d2 = d2 + dx - dy + rx2; 
		}
	}
}

void drawImageGS(HDC & hdc, int X, int Y, std::vector< std::vector<int> > & data){
	for (int i = 0; i < data.size(); i++)
		for (int j = 0; j < data[i].size(); j++){
			unsigned l = (unsigned)data[i][j];
			SetPixel(hdc, Y+j, X+i, RGB(l,l,l));
		}
}

void drawImageBW(HDC & hdc, int X, int Y, std::vector< std::vector<int> > & data){
	for (int i = 0; i < data.size(); i++)
		for (int j = 0; j < data[i].size(); j++){
			SetPixel(hdc, Y+j, X+i, data[i][j] ? 0 : RGB(255,255,255));
		}
}
