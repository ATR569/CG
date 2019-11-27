//---------------------------------------------------------------------------

#pragma hdrstop

#include "shape3D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "matrix.h"
#include "point.h"
#include "workspace.h"

Polyedron::Polyedron(vector<Point3D *> P, vector<Edge> edges, DrawMethod drawMethod): Object("Poliedro " + IntToStr(++id), drawMethod){
    this->P = P;
    this->edges = edges;
	this->stateMatrix = getIdentity3DMatrix();
	this->history.push_back(Transformation(String("Estado inicial"), getIdentity3DMatrix()));
}

Polyedron::Polyedron(vector<Point3D *> P, DrawMethod drawMethod) : Object("Poliedro " + IntToStr(++id), drawMethod){
    this->P = P;
	this->stateMatrix = getIdentity3DMatrix();
	this->history.push_back(Transformation(String("Estado inicial"), getIdentity3DMatrix()));
}

Point2D * Polyedron::getProjection(Point3D * p, int projectionType){
    Matrix M(3,3);
	if (projectionType == 0) 
		M = (*getProjectionMatrix()) * (*p->asMatrix());
	else if (projectionType == 1)
		M = (*getFrontalProjectionMatrix()) * (*p->asMatrix());
	else if (projectionType == 2)
		M = (*getSideProjectionMatrix()) * (*p->asMatrix());
	else
		M = (*getTopProjectionMatrix()) * (*p->asMatrix());

    return M.asPoint2D();
}

BasePoint * Polyedron::getReference(){
	double maxX, minX, maxY, minY, maxZ, minZ;
	
	Point3D * ref = ((*stateMatrix)*(*P[0]->asMatrix())).asPoint3D();
	
	maxX = minX = ref->X; 
	maxY = minY = ref->Y; 
	maxZ = minZ = ref->Z; 

	for (int i = 1; i < this->P.size(); i++){
		ref = ((*stateMatrix)*(*P[i]->asMatrix())).asPoint3D();
		minX = min(minX, ref->X);
		maxX = max(maxX, ref->X);
		minY = min(minY, ref->Y);
		maxY = max(maxY, ref->Y);
		minZ = min(minZ, ref->Z);
		maxZ = max(maxZ, ref->Z);
	}

	return new Point3D((minX+maxX)/2, (minY+maxY)/2, (minZ+maxZ)/2);
}

vector<Point3D *> Polyedron::get3DPoints(){
    return this->P;
}

vector<Edge> Polyedron::getEdges(){
    return this->edges;
}

void Polyedron::addEdge(int a, int b){
    this->edges.push_back(Edge(a,b));
}


/**
 * Método auxiliar de rasterização
 */
void Polyedron::draw(WorkSpace * work, HDC hdc, vector<Point2D*> & vertices, DrawColor color){
	int N = edges.size();
	//	Para cada par de pontos (A,B), rasteriza na tela
	for (int i = 0; i < N; i++) {
        int v1 = edges[i].A;
        int v2 = edges[i].B;

		Point2D * p1 = work->CoordUserToScr(vertices[v1]);
		Point2D * p2 = work->CoordUserToScr(vertices[v2]);

		if (cut(p1, p2, 0, work->getCanvasH(), 0, work->getCanvasV())){
			if (this->getMethod() == DM_DDA)
				drawLineDDA(hdc, p1, p2, color);
			else
				drawLineBresenhan(hdc, p1, p2, color);
		}
	}
}

void Polyedron::draw(WorkSpace * work, bool drawPoints, bool erase){
    vector<Point2D*> vertices;
	DrawColor color = erase ? CL_WHITE : this->getColor();

	//	Projeção ortográfica
    for (int i = 0; i < P.size(); i++) {
		Matrix MA = ((*this->stateMatrix)*(*P[i]->asMatrix()));
        vertices.push_back(getProjection(MA.asPoint3D()));
    }

	draw(work, work->hdc, vertices, color);	

	//	Projeção frontal
	if (work->hdcFront != NULL){
		vertices.clear();
		for (int i = 0; i < P.size(); i++) {
			Matrix MA = ((*this->stateMatrix)*(*P[i]->asMatrix()));
			vertices.push_back(getProjection(MA.asPoint3D(), 1));
		}

		draw(work, work->hdcFront, vertices, color);	
	}

	//	Projeção lateral
	if (work->hdcFront != NULL){
		vertices.clear();
		for (int i = 0; i < P.size(); i++) {
			Matrix MA = ((*this->stateMatrix)*(*P[i]->asMatrix()));
			vertices.push_back(getProjection(MA.asPoint3D(), 2));
		}

		draw(work, work->hdcSide, vertices, color);	
	}

	//	Projeção superior
	if (work->hdcFront != NULL){
		vertices.clear();
		for (int i = 0; i < P.size(); i++) {
			Matrix MA = ((*this->stateMatrix)*(*P[i]->asMatrix()));
			vertices.push_back(getProjection(MA.asPoint3D(), 3));
		}

		draw(work, work->hdcTop, vertices, color);	
	}
}

/**
 * Retorna um array de strings com os pontos (2 casas decimais de precisão) do objeto
 */ 
vector<String> Polyedron::toStrings(){
	vector<String> strings;
	strings.push_back(this->getName());
	char X[16], Y[16], Z[16];
	
	for	(int i = 0; i < P.size(); i++){
		Point3D * p = ((*stateMatrix) * (*P[i]->asMatrix())).asPoint3D();  
		strings.push_back("(" + FormatFloat("0.000", p->X) + ", " + FormatFloat("0.000", p->Y) + ", " + FormatFloat("0.000", p->Z) + ")");
	}

	return strings;
}


/**
 * Retorna um cubo dados o ponto central do cubo e o tamanho da aresta
 */
Polyedron * getCube(Point3D * center, double edgeSize, DrawMethod drawMethod){
	vector<Point3D *> P;

	double X[2] = {center->X - edgeSize/2, center->X + edgeSize/2};
	double Y[2] = {center->Y - edgeSize/2, center->Y + edgeSize/2};
	double Z[2] = {center->Z - edgeSize/2, center->Z + edgeSize/2};

	for (int i = 0; i < 2; i++)  {
		for (int j = 0; j < 2; j++)  {
			for (int k = 0; k < 2; k++)  {
				P.push_back(new Point3D(X[i], Y[j], Z[k]));
			}
		}
	}

	vector<Edge> edges;

	edges.push_back(Edge(0,1));
	edges.push_back(Edge(0,2));
	edges.push_back(Edge(0,4));
	edges.push_back(Edge(1,3));
	edges.push_back(Edge(1,5));
	edges.push_back(Edge(2,3));
	edges.push_back(Edge(2,6));
	edges.push_back(Edge(3,7));
	edges.push_back(Edge(4,5));
	edges.push_back(Edge(4,6));
	edges.push_back(Edge(5,7));
	edges.push_back(Edge(6,7));

	return new Polyedron(P, edges, drawMethod);
}

/**
 * Retorna uma pirâmide dados o tamanho da aresta da base
 * a altura e o ponto central da base da pirâmide
 */
Polyedron * getPyramid(Point3D * baseCenter, double edgeBase, double height, DrawMethod drawMethod){
    vector<Point3D *> P;

    double X[2] = {baseCenter->X - edgeBase/2, baseCenter->X + edgeBase/2};
    double Y[2] = {baseCenter->Y - edgeBase/2, baseCenter->Y + edgeBase/2};

    //  Vértices da base da pirâmide
    for (int i = 0; i < 2; i++)  {
        for (int j = 0; j < 2; j++)  {
			P.push_back(new Point3D(X[i], Y[j], baseCenter->Z));
        }
    }

    P.push_back(new Point3D(baseCenter->X, baseCenter->Y, baseCenter->Z + height));
    vector<Edge> edges;

    edges.push_back(Edge(0,1));
    edges.push_back(Edge(0,2));
    edges.push_back(Edge(2,3));
    edges.push_back(Edge(3,1));
    edges.push_back(Edge(0,4));
    edges.push_back(Edge(1,4));
    edges.push_back(Edge(2,4));
    edges.push_back(Edge(3,4));

    return new Polyedron(P, edges, drawMethod);
}

Polyedron * getPrism(Point3D * center, double edgeBase, double height, DrawMethod drawMethod){
    vector<Point3D *> P;
    vector<Edge> edges;

	double k = edgeBase*sqrt(3)/3;
	P.push_back(new Point3D(center->X, center->Y + k, center->Z));
	P.push_back(new Point3D(center->X - edgeBase/2, center->Y - k/2, center->Z));
	P.push_back(new Point3D(center->X + edgeBase/2, center->Y - k/2, center->Z));

	P.push_back(new Point3D(center->X, center->Y + k, center->Z + height));
	P.push_back(new Point3D(center->X - edgeBase/2, center->Y - k/2, center->Z + height));
	P.push_back(new Point3D(center->X + edgeBase/2, center->Y - k/2, center->Z + height));

	edges.push_back(Edge(0,1));
	edges.push_back(Edge(1,2));
	edges.push_back(Edge(0,2));
	edges.push_back(Edge(3,4));
	edges.push_back(Edge(4,5));
	edges.push_back(Edge(3,5));

	edges.push_back(Edge(0,3));
	edges.push_back(Edge(1,4));
	edges.push_back(Edge(2,5));

	return new Polyedron(P, edges, drawMethod);
}