#ifndef objectH
#define objectH

#include <System.Classes.hpp>
#include <windows.h>
#include <vector>
#include <string>
#include <list>
#include "graphics.h"
#include "../transformation/transform2D.h"
#include "../transformation/transform3D.h"

using namespace std;

enum DrawMethod {DM_BRESENHAN, DM_DDA, DM_POLYNOMIAL, DM_TRIGONOMETRIC};

class Matrix;
class WorkSpace;
class BasePoint;

class Transformation{
private:
	String name;
	Matrix * M;
public:
	Transformation(String name, Matrix * M);

	String getName();
	Matrix * getMatrix();
};

class Object{
private:
	String name;
	DrawMethod drawMethod;
	DrawColor color;
protected:
	list<Transformation> history;
	Matrix * stateMatrix;
public:
	Object(String name, DrawMethod drawMethod);
	virtual void draw(WorkSpace * work, bool drawPoints, bool erase = false) = 0;
	virtual BasePoint * getReference() = 0;
	virtual vector<String> toStrings() = 0;
	virtual vector<Point2D *> getPoints() = 0;

	String getName();
	DrawMethod getMethod();
	DrawColor getColor();
    list<Transformation> getHistory();
    Matrix * getStateMatrix();

    void apply(Matrix * M, String caption);
	void setColor(DrawColor color);
	void setDrawMethod(DrawMethod drawMethod);
    void setStateMatrix(Matrix * stateMatrix);
	void cropHistory(unsigned maxSize);
};

#endif