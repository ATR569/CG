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
Line::Line(Point2D * A, Point2D * B, DrawMethod drawMethod) : Object("Reta " + IntToStr(++id), drawMethod){
	this->A = A;
	this->B = B;
	this->stateMatrix = getIdentityMatrix();
	this->history.push_back(Transformation("Estado inicial", getIdentityMatrix()));
}

/**
 * Desenha o objeto Reta no hdc
 * @param work - WorkSpace onde será desenhada a reta
 */
void Line::draw(WorkSpace * work, bool drawPoints, bool erase){
	DrawColor color = erase ? CL_WHITE : this->getColor();

	//  Transforma os pontos em matrizes colunas e multiplica pela matriz de estado
	Matrix MA = ((*this->stateMatrix) * (*A->asMatrix()));
	Matrix MB = ((*this->stateMatrix) * (*B->asMatrix()));

	//  Conversão em coordenadas de tela
	Point2D * p1 = work->CoordUserToScr(MA.asPoint2D());
	Point2D * p2 = work->CoordUserToScr(MB.asPoint2D());

	//  Desenha os pontos extremos da reta
	if (drawPoints){
		drawPoint(work->hdc, p1, color);
		drawPoint(work->hdc, p2, color);
	}

	//  Se a reta for aceita pelo algoritmo de corte
	if (cut(p1, p2, 0, work->getCanvasH(), 0, work->getCanvasV())){
		if (this->getMethod() == DM_DDA){
			drawLineDDA(work->hdc, p1, p2, color);
		}else{
			drawLineBresenhan(work->hdc, p1, p2, color);
		}
	}
}

/**
 * Retorna um array de strings com os pontos (3 casas decimais de precisão) do objeto
 */ 
vector<String> Line::toStrings(){
	vector<String> strings;
	strings.push_back(this->getName());

	//  Obtém o ponto A atual através da multiplicação de A pela matriz estado
	Point2D * p = ( (*stateMatrix) * (*A->asMatrix()) ).asPoint2D();
	strings.push_back("A = (" + FormatFloat("0.000", p->X) + ", " + FormatFloat("0.000", p->Y) + ")");

	//  Obtém o ponto B atual através da multiplicação de B pela matriz estado
	p = ( (*stateMatrix) * (*B->asMatrix()) ).asPoint2D();
	strings.push_back("B = (" + FormatFloat("0.000", p->X) + ", " + FormatFloat("0.000", p->Y) + ")");

	return strings;
}

Point2D * Line::getA(){
	return this->A;
}

Point2D * Line::getB(){
	return this->B;
}

/**
 * Retorna o ponto de referência do objeto (ponto central)
 */
BasePoint * Line::getReference(){
	//  Obtém os pontos atualizados pela matriz de estado
	Point2D * ref1 = ((*stateMatrix) * (*A->asMatrix())).asPoint2D();
	Point2D * ref2 = ((*stateMatrix) * (*B->asMatrix())).asPoint2D();

	//  Retorna o ponto médio entre A e B (centro da reta)
	return new Point2D((ref1->X + ref2->X)/2, (ref1->Y + ref2->Y)/2);
}

vector<Point2D*> Line::getPoints(){
	vector<Point2D*> P;
	P.push_back(A);
	P.push_back(B);
	return P;
}

//Circle-----------------------------------------------------------------------------
/**
 * Construtor de Círculo
 * @param center - Centro do círculo
 * @param radius - Raio do círculo
 * @param drawMethod - Algoritmo usado na rasterização
 */
Circle::Circle(Point2D * center, double radius, DrawMethod drawMethod) : Object("Círculo " + IntToStr(++id), drawMethod){
	this->center = center;
	this->radius = radius;
	this->stateMatrix = getIdentityMatrix();
	this->history.push_back(Transformation("Estado inicial", getIdentityMatrix()));
}

/**
 * Desenha o objeto Circle no hdc
 * @param work - WorkSpace onde será desenhada a reta
 */
void Circle::draw(WorkSpace * work, bool drawPoints, bool erase){
	DrawColor color = erase ? CL_WHITE : this->getColor();

	//  Transforma o ponto em matriz coluna e multiplica pela matriz de estado
	Matrix M = ((*this->stateMatrix) * (*center->asMatrix()));
	//  Obtém o ponto em coordenadas de tela
	Point2D * p = work->CoordUserToScr(M.asPoint2D());
	//  Calcula o raio proporcionalmente ao tamanho da tela
	double r = work->CoordUserToScr(this->radius);

	if (this->getMethod() == DM_BRESENHAN){
		drawCircleBresenhan(work->hdc, p, r, color);
	}else if (this->getMethod() == DM_POLYNOMIAL){
		drawCirclePolynomial(work->hdc, p, r, color);
	}else{
		drawCircleTrigonometric(work->hdc, p, r, color);
	}
}

/**
 * Retorna um array de strings com os pontos (2 casas decimais de precisão) do objeto
 */
vector<String> Circle::toStrings(){
	vector<String> strings;
	strings.push_back(this->getName());

	char X[16], Y[16];

	Point2D * p = ((*stateMatrix) * (*center->asMatrix())).asPoint2D();
	strings.push_back("A = (" + FormatFloat("0.000", p->X) + ", " + FormatFloat("0.000", p->Y) + ")");
	strings.push_back("R = " + FormatFloat("0.000", radius));

	return strings;
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

vector<Point2D*> Circle::getPoints(){
	vector<Point2D*> P;
	P.push_back(center);
	return P;
}

//Polygon2D-----------------------------------------------------------------------
/**
 * Construtor de Polygon2D
 * @param P - Vértices  do polígono
 * @param drawMethod - Algoritmo usado na rasterização
 */
Polygon2D::Polygon2D(vector<Point2D*> P, DrawMethod drawMethod) : Object("Polígono " + IntToStr(++id), drawMethod){
	this->P = P;
	this->stateMatrix = getIdentityMatrix();
	this->history.push_back(Transformation("Estado inicial", getIdentityMatrix()));
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

/**
 * Retorna um array de strings com os pontos (2 casas decimais de precisão) do objeto
 */
vector<String> Polygon2D::toStrings(){
	vector<String> strings;
	strings.push_back(this->getName());

	char X[16], Y[16];

	for	(int i = 0; i < P.size(); i++){
		Point2D * p = ((*stateMatrix) * (*P[i]->asMatrix())).asPoint2D();
		strings.push_back("(" + FormatFloat("0.000", p->X) + ", " + FormatFloat("0.000", p->Y) + ")");
	}

	return strings;
}

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
