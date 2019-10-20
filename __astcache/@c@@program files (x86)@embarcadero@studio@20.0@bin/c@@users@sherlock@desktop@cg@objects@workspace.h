#ifndef workspaceH
#define workspaceH

#include <vector>
#include <string>
#include <windows.h>
#include "../transformation/transform2D.h"

typedef unsigned DrawColor;

class Object;
class Point2D;

const int MODE2D = 0;
const int MODE3D = 1;

class WorkSpace{
private:
	double userH, userV;
	double canvasH, canvasV;
	std::vector<Object*> objects;
	bool drwAxis;
	bool drwGrid;
	bool drwPoints;

	int mode;
public:
	HDC hdc;

    WorkSpace(double userH, int canvasH, int canvasV, HDC hdc);

	void drawAxis();
	void setCanvasSize(int width, int height);
	Point2D * CoordScrToUser(Point2D * p);
	Point2D * CoordUserToScr(Point2D * p);
	double CoordUserToScr(double x);

	void update();
	void eraseObject(Object * obj);

	void clearObjects();
	void addObject(Object * obj);
	Object * getObject(int id);
	void deleteObject(int id);

	int getMode();
	int getCanvasH();
	int getCanvasV();
	
	void setDrawPoints(bool drwPoints);
	void setDrawAxis(bool drwAxis);
	void setDrawGrid(bool drwGrid);
	void setMode(int mode);
	
	void apply(Object * obj, Matrix * M, std::string caption);
	void translateObject(Object * obj, double tx, double ty);
	void rotateObject(Object * obj, Point2D * ref, double theta);
	void scaleObject(Object * obj, Point2D * ref, double sx, double sy);
	void shearObject(Object * obj, Point2D * ref, double shx, double shy);
	void reflectObject(Object * obj, int axis);
	void reflectObject(Object * obj, double m, double b);
};

#endif