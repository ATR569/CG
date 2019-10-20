#ifndef statemachineH
#define statemachineH

#include <vector>

class State;
class TformMain;
class Point2D;

class StateMachine{
private:
	State * state;
public:
	TformMain * formMain;
	std::vector<Point2D*> pointBuffer;

	StateMachine(TformMain * formMain);

	void performClick(int X, int Y);
	void performDblClick();
	void performDrawCircleClick();
	void performDrawLineClick();
	void performDrawPolygonClick();
	void performObjectCancelClick();

	void setState(State * state);

};

#endif