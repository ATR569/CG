//---------------------------------------------------------------------------

#pragma hdrstop

#include "shape3D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "matrix.h"
#include "point.h"
#include "workspace.h"

Polyedron::Polyedron(vector<Point3D *> P, vector<Edge> edges, DrawMethod drawMethod): Object("Poliedro " + to_string(++id), drawMethod){
    this->P = P;
    this->edges = edges;
	this->stateMatrix = getIdentity3DMatrix();
	this->history.push_back(Transformation(string("Estado inicial"), getIdentity3DMatrix()));
}

Polyedron::Polyedron(vector<Point3D *> P, DrawMethod drawMethod) : Object("Poliedro " + to_string(++id), drawMethod){
    this->P = P;
	this->stateMatrix = getIdentity3DMatrix();
	this->history.push_back(Transformation(string("Estado inicial"), getIdentity3DMatrix()));
}

Point2D * Polyedron::getProjection(Point3D * p){
    Matrix M = (*getProjectionMatrix())*(*p->asMatrix());

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

vector<Point3D *> Polyedron::getPoints(){
    return this->P;
}

vector<Edge> Polyedron::getEdges(){
    return this->edges;
}

void Polyedron::addEdge(int a, int b){
    this->edges.push_back(Edge(a,b));
}

void Polyedron::draw(WorkSpace * work, bool drawPoints, bool erase){
    vector<Point2D*> vertices;

    for (int i = 0; i < P.size(); i++) {
		Matrix MA = ((*this->stateMatrix)*(*P[i]->asMatrix()));
        vertices.push_back(getProjection(MA.asPoint3D()));
    }

	int N = edges.size();

	DrawColor color = erase ? CL_WHITE : this->getColor();

	//	Para cada par de pontos (A,B), aplica a stateMatrix e rasteriza na tela
	for (int i = 0; i < N; i++) {
        int v1 = edges[i].A;
        int v2 = edges[i].B;

		Point2D * p1 = work->CoordUserToScr(vertices[v1]);
		Point2D * p2 = work->CoordUserToScr(vertices[v2]);

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