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
	vector<String> toStrings();
	vector<Point2D *> getPoints();

	Point2D * getA();
	Point2D * getB();
	BasePoint * getReference();
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
	BasePoint * getReference();

	vector<String> toStrings();
	void draw(WorkSpace * work, bool drawPoints, bool erase);
	vector<Point2D *> getPoints();
};

class Polygon2D : public Object{
private:
	static int id;
	vector<Point2D*> P;
public:
	Polygon2D(vector<Point2D*> P, DrawMethod drawMethod);
	
	BasePoint * getReference();

	void draw(WorkSpace * work, bool drawPoints, bool erase);
	vector<String> toStrings();
	vector<Point2D *> getPoints();
};

int Line::id = 0;
int Circle::id = 0;
int Polygon2D::id = 0;

#endif