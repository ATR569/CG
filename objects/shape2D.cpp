//---------------------------------------------------------------------------

#pragma hdrstop

#include "shape2D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "matrix.h"
#include "point.h"
#include "workspace.h"

//Line--------------------------------------------------------------------------
/**
 * Construtor do objeto Line
 * @param A - Ponto inicial da reta
 * @param B - Ponto final da reta
 * @param drawMethod - Algoritmo usado na rasterização.
 */
Line::Line(Point2D * A, Point2D * B, DrawMethod drawMethod) : Object("Reta " + to_string(++id), drawMethod){
	this->A = A;
	this->B = B;
}

/**
 * Desenha o objeto Reta no hdc
 * @param work - WorkSpace onde será desenhada a reta
 */
void Line::draw(WorkSpace * work, bool drawPoints, bool erase){
	DrawColor color = erase ? CL_WHITE : this->getColor();

	Matrix MA = ((*this->stateMatrix)*(*A->asMatrix()));
	Matrix MB = ((*this->stateMatrix)*(*B->asMatrix()));

	Point2D * p1 = work->CoordUserToScr(MA.asPoint2D());
	Point2D * p2 = work->CoordUserToScr(MB.asPoint2D());

	if (drawPoints){
		drawPoint(work->hdc, p1, color);
		drawPoint(work->hdc, p2, color);
	}

	if (cut(p1, p2, 0, work->getCanvasH(), 0, work->getCanvasV())){
		if (this->getMethod() == DM_DDA){
			drawLineDDA(work->hdc, p1, p2, color);
		}else{
			drawLineBresenhan(work->hdc, p1, p2, color);
		}
	}

}

Point2D * Line::getA(){
	return this->A;
}

Point2D * Line::getB(){
	return this->B;
}

BasePoint * Line::getReference(){
	Point2D * ref1 = ((*stateMatrix)*(*A->asMatrix())).asPoint2D();
	Point2D * ref2 = ((*stateMatrix)*(*B->asMatrix())).asPoint2D();
	return new Point2D((ref1->X + ref2->X)/2, (ref1->Y + ref2->Y)/2);
}

//Circle-----------------------------------------------------------------------------
/**
 * Construtor de Círculo
 * @param center - Centro do círculo
 * @param radius - Raio do círculo
 * @param drawMethod - Algoritmo usado na rasterização
 */
Circle::Circle(Point2D * center, double radius, DrawMethod drawMethod) : Object("Círculo " + to_string(++id), drawMethod){
	this->center = center;
	this->radius = radius;
}

/**
 * Desenha o objeto Circle no hdc
 * @param work - WorkSpace onde será desenhada a reta
 */
void Circle::draw(WorkSpace * work, bool drawPoints, bool erase){
	DrawColor color = erase ? CL_WHITE : this->getColor();

	Matrix M = ((*this->stateMatrix)*(*center->asMatrix()));
	Point2D * p = work->CoordUserToScr(M.asPoint2D());

	double r = work->CoordUserToScr(this->radius);

	if (this->getMethod() == DM_BRESENHAN){
		drawCircleBresenhan(work->hdc, p, r, color);
	}else if (this->getMethod() == DM_POLYNOMIAL){
		drawCirclePolynomial(work->hdc, p, r, color);
	}else{
		drawCircleTrigonometric(work->hdc, p, r, color);
	}
}

double Circle::getRadius(){
	return this->radius;
}

Point2D * Circle::getCenter(){
	return this->center;
}

BasePoint * Circle::getReference(){
	return ((*stateMatrix)*(*this->center->asMatrix())).asPoint2D();
}

//Polygon2D-----------------------------------------------------------------------
/**
 * Construtor de Polygon2D
 * @param P - Vértices  do polígono
 * @param drawMethod - Algoritmo usado na rasterização
 */
Polygon2D::Polygon2D(vector<Point2D*> P, DrawMethod drawMethod) : Object("Polígono " + to_string(++id), drawMethod){
	this->P = P;
}

/**
 * Desenha o objeto Polygon no hdc
 * @param hdc - Manipulador da tela
 * @param canvasH - Largura da tela
 * @param canvasV - Altura da tela
 * @param userH - Largura do espaço do usuário
 * @param userV - Altura do espaço do usuário
 */
void Polygon2D::draw(WorkSpace * work, bool drawPoints, bool erase){
	int N = P.size();

	DrawColor color = erase ? CL_WHITE : this->getColor();

	//	Para cada par de pontos (A,B), aplica a stateMatrix e rasteriza na tela
	for (int i = 0; i < N; i++) {
		Matrix MA = ((*this->stateMatrix)*(*P[i]->asMatrix()));
		Matrix MB = ((*this->stateMatrix)*(*P[(i+1)%N]->asMatrix()));

		Point2D * p1 = work->CoordUserToScr(MA.asPoint2D());
		Point2D * p2 = work->CoordUserToScr(MB.asPoint2D());

		if (drawPoints)
			drawPoint(work->hdc, p1, color);

		if (cut(p1, p2, 0, work->getCanvasH(), 0, work->getCanvasV())){
			if (this->getMethod() == DM_DDA)
				drawLineDDA(work->hdc, p1, p2, color);
			else
				drawLineBresenhan(work->hdc, p1, p2, color);
		}
	}
}

//----------------------------------------------------------------------------------

vector<Point2D*> Polygon2D::getPoints(){
	return this->P;
}

BasePoint * Polygon2D::getReference(){
	double maxX, minX, maxY, minY;
	
	Point2D * ref = ((*stateMatrix)*(*P[0]->asMatrix())).asPoint2D();
	
	maxX = minX = ref->X; 
	maxY = minY = ref->Y; 

	for (int i = 1; i < this->P.size(); i++){
		ref = ((*stateMatrix)*(*P[i]->asMatrix())).asPoint2D();
		minX = min(minX, ref->X);
		maxX = max(maxX, ref->X);
		minY = min(minY, ref->Y);
		maxY = max(maxY, ref->Y);
	}

	return new Point2D((minX+maxX)/2, (minY+maxY)/2);
}
