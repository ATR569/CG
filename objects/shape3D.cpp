//---------------------------------------------------------------------------

#pragma hdrstop

#include "shape3D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "point.h"


Polyedron * getCube(Point3D * center, double edgeSize){
    vector<Point3D *> P;

    double X[2] = {center->X - edgeSize/2, center->X - edgeSize/2};
    double Y[2] = {center->Y - edgeSize/2, center->Y - edgeSize/2};
    double Z[2] = {center->Z - edgeSize/2, center->Z - edgeSize/2};

    for (int i = 0; i < 2; i++)  {
        for (int j = 0; j < 2; j++)  {
            for (int k = 0; k < 2; k++)  {
                P.push_back(new Point3D(X[i], Y[j], Z[k]));
            }
        }
    }

    vector<Edge> edges;

    edges.push_back(Edge(0,1));
    edges.push_back(Edge(2,3));
    edges.push_back(Edge(4,5));
    edges.push_back(Edge(6,7));

    edges.push_back(Edge(0,2));
    edges.push_back(Edge(0,2));
    
}