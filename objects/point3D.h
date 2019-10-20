#ifndef point3dH
#define point3dH

#include <math.h>

class Matrix;

class Point3D{

public:
	double X;
	double Y;
    double Z;
	Point3D();
	Point3D(double X, double Y, double Z);

	void aplly(Matrix * t);
	Matrix * asMatrix();
};

double dist(Point3D * p1, Point3D * p2);

#endif