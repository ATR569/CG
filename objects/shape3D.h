#ifndef shape3DH
#define shape3DH

#include "object.h"
#include "edge.h"

class Polyedron : public Object{
private:
	static int id;
    vector<Point3D *> P;
    vector<Edge> edges; 
public:
    Polyedron(vector<Point3D *> P, vector<Edge *> edges);
    Polyedron(vector<Point3D *> P);

	vector<Point3D *> getPoints();
	BasePoint * getReference();

    void addEdge(int a, int b);
    void draw(WorkSpace * work, bool drawPoints, bool erase = false);
};

Polyedron * getCube(Point3D * center, double edgeSize);

int Polyedron::id = 0;

#endif