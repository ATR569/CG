#ifndef shape2DH
#define shape2DH

#include "object.h"

class Line : public Object{
private:
	static int id;
	Point2D * A;
	Point2D * B;
public:
	Line(Point2D * A, Point2D * B, DrawMethod drawMethod);
	void draw(WorkSpace * work, bool drawPoints, bool erase);

	Point2D * getA();
	Point2D * getB();
	Point2D * getReference();
};

class Circle : public Object{
private:
	static int id;
	Point2D * center;
	double radius;
public:
	Circle(Point2D * center, double radius, DrawMethod drawMethod);

	double getRadius();
    Point2D * getCenter();
	Point2D * getReference();

	void draw(WorkSpace * work, bool drawPoints, bool erase);
};

class Polygon2D : public Object{
private:
	static int id;
	vector<Point2D*> P;
public:
	Polygon2D(vector<Point2D*> P, DrawMethod drawMethod);

	vector<Point2D*> getPoints();
	Point2D * getReference();

	void draw(WorkSpace * work, bool drawPoints, bool erase);
};

int Line::id = 0;
int Circle::id = 0;
int Polygon2D::id = 0;

#endif