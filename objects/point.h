#ifndef pointH
#define pointH

#include <math.h>

class Matrix;

class BasePoint{
public:
	virtual void aplly(Matrix * t) = 0;
	virtual Matrix * asMatrix() = 0;
};

class Point2D : public BasePoint{

public:
	double X, Y;
	Point2D();
	Point2D(double X, double Y);

	void aplly(Matrix * t);
	Matrix * asMatrix();
};

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

double dist(Point2D * p1, Point2D * p2);
double dist(Point3D * p1, Point3D * p2);

#endif