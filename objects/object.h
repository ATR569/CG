#ifndef objectH
#define objectH

#include <vector>
#include <string>
#include <stack>
#include <windows.h>
#include "graphics.h"
#include "../transformation/transform2D.h"

using namespace std;

enum DrawMethod {DM_BRESENHAN, DM_DDA, DM_POLYNOMIAL, DM_TRIGONOMETRIC};

class Matrix;
class WorkSpace;

class Object{
protected:
	string name;
	DrawMethod drawMethod;
	DrawColor color;
	
	stack<Matrix*> history;
	Matrix * stateMatrix;
public:
	Object(string name, DrawMethod drawMethod);
	string getName();
	DrawMethod getMethod();

	virtual void draw(WorkSpace * work, bool drawPoints, bool erase = false) = 0;
	virtual Point2D * getReference() = 0;

    void apply(Matrix * M);
	void setColor(DrawColor color);

	DrawColor getColor();
	void setColor();
};

#endif