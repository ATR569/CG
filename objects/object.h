#ifndef objectH
#define objectH

#include <vector>
#include <string>
#include <list>
#include <windows.h>
#include "graphics.h"
#include "../transformation/transform2D.h"

using namespace std;

enum DrawMethod {DM_BRESENHAN, DM_DDA, DM_POLYNOMIAL, DM_TRIGONOMETRIC};

class Matrix;
class WorkSpace;
class BasePoint;

class Transformation{
private:
	string name;
	Matrix * M;
public:
	Transformation(string name, Matrix * M);

	string getName();
	Matrix * getMatrix();
};

class Object{
private:
	list<Transformation> history;
	string name;
	DrawMethod drawMethod;
	DrawColor color;
protected:
	Matrix * stateMatrix;
public:
	Object(string name, DrawMethod drawMethod);
	virtual void draw(WorkSpace * work, bool drawPoints, bool erase = false) = 0;
	virtual BasePoint * getReference() = 0;
	
	string getName();
	DrawMethod getMethod();
	DrawColor getColor();

    void apply(Matrix * M, std::string caption);
	void setColor(DrawColor color);
};

#endif