#ifndef workspaceH
#define workspaceH

#include <vector>
#include <System.Classes.hpp>
#include <windows.h>
#include "../transformation/transform2D.h"
#include "../transformation/transform3D.h"

typedef unsigned DrawColor;

class Object;
class Point2D;

const int MODE_2D = 0;
const int MODE_3D = 1;

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
	void deleteObject(int id);

	Object * getObject(int id);
    std::vector<Object*> getObjects();
	int getMode();
	int getCanvasH();
	int getCanvasV();

	void setDrawPoints(bool drwPoints);
	void setDrawAxis(bool drwAxis);
	void setDrawGrid(bool drwGrid);                      
	void setMode(int mode);
	
	void apply(Object * obj, Matrix * M, String caption);
	void translateObject(Object * obj, double tx, double ty);
	void rotateObject(Object * obj, Point2D * ref, double theta);
	void scaleObject(Object * obj, Point2D * ref, double sx, double sy);
	void shearObject(Object * obj, Point2D * ref, double shx, double shy);
	void reflectObject(Object * obj, int axis);
	void reflectObject(Object * obj, double m, double b);

	void translateObject3D(Object * obj, double tx, double ty, double tz);
	void rotateObject3D(Object * obj, int axis, double theta);
	void scaleObject3D(Object * obj, double sx, double sy, double sz);
	void scaleObject3DRelativePoint(Object * obj, Point3D * ref, double sx, double sy, double sz);
	void shearObject3DAroundX(Object * obj, Point3D * ref, double shy, double shz);
	void shearObject3DAroundY(Object * obj, Point3D * ref, double shx, double shz);
	void shearObject3DAroundZ(Object * obj, Point3D * ref, double shx, double shy);
	void refletObject3D(Object * obj, int axis);
	void refletObject3DRelativePlan(Object * obj, int plan);
};

#endif