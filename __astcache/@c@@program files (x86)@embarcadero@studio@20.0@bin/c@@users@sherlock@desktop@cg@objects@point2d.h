#ifndef point2dH
#define point2dH

#include <math.h>

class Matrix;

class Point2D{

public:
	double X;
	double Y;
	Point2D();
	Point2D(double X, double Y);

	void aplly(Matrix * t);
	Matrix * asMatrix();
};

double dist(Point2D * p1, Point2D * p2);

#endif