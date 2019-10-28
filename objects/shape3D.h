#ifndef shape3DH
#define shape3DH

#include "object.h"
#include "edge.h"

class Polyedron : public Object{
private:
	static int id;
    vector<Point3D *> P;
    vector<Edge> edges; 

    Point2D * getProjection(Point3D * p);
public:
    Polyedron(vector<Point3D *> P, vector<Edge> edges, DrawMethod drawMethod);
    Polyedron(vector<Point3D *> P, DrawMethod drawMethod);

	vector<String> toStrings();
	vector<Point2D *> getPoints(){return vector<Point2D*>();}
	vector<Point3D *> get3DPoints();
	vector<Edge> getEdges();
	BasePoint * getReference();

    void addEdge(int a, int b);
    void draw(WorkSpace * work, bool drawPoints, bool erase = false);
};

Polyedron * getCube(Point3D * center, double edgeSize, DrawMethod drawMethod);

Polyedron * getPyramid(Point3D * center, double edgeBase, double height, DrawMethod drawMethod);

int Polyedron::id = 0;

#endif