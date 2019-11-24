#ifndef stateH
#define stateH

class StateMachine;

const int NONE_BTN_STATE = -1;
const int DRAWING_BTN_STATE = 8192;

class State{
	int btnStateMask;
public:
	State(int bntStateMask);

	virtual void onClick(StateMachine * machine, int X, int Y) = 0;
	virtual void onDblClick(StateMachine * machine) = 0;
	virtual void onLineClick(StateMachine * machine) = 0;
	virtual void onCircleClick(StateMachine * machine) = 0;
	virtual void onPolygonClick(StateMachine * machine) = 0;
	virtual void onEllipseClick(StateMachine * machine) = 0;
	virtual void onObjectCancelClick(StateMachine * machine) = 0;

    int getBtnStateMask();
};

class StateNone : public State{
protected:
	void onClick(StateMachine * machine, int X, int Y){}
	void onDblClick(StateMachine * machine){}
	void onObjectCancelClick(StateMachine * machine){}

	void onLineClick(StateMachine * machine);
	void onCircleClick(StateMachine * machine);
	void onEllipseClick(StateMachine * machine);
	void onPolygonClick(StateMachine * machine);
public:
	StateNone() : State(NONE_BTN_STATE){};
};

class StateDrawing : public State{
protected:
	void onLineClick(StateMachine * machine){};
	void onCircleClick(StateMachine * machine){};
	void onPolygonClick(StateMachine * machine){};
	void onEllipseClick(StateMachine * machine){};
	void onObjectCancelClick(StateMachine * machine);
public:
	StateDrawing() : State(DRAWING_BTN_STATE){};
};

class StateDrawingFirstPointLine : public StateDrawing{
protected:
	void onClick(StateMachine * machine, int X, int Y);
	void onDblClick(StateMachine * machine){}
};

class StateDrawingSecondPointLine : public StateDrawing{
protected:
	void onClick(StateMachine * machine, int X, int Y);
	void onDblClick(StateMachine * machine){}
};

class StateDrawingCircleCenter : public StateDrawing{
protected:
	void onClick(StateMachine * machine, int X, int Y);
	void onDblClick(StateMachine * machine){}
};

class StateDrawingEllipseCenter : public StateDrawing{
protected:
	void onClick(StateMachine * machine, int X, int Y);
	void onDblClick(StateMachine * machine){}
};

class StateDrawingCircleRadius : public StateDrawing{
protected:
	void onClick(StateMachine * machine, int X, int Y);
	void onDblClick(StateMachine * machine){}
};

class StateDrawingPolygon2D : public StateDrawing{
protected:
	void onClick(StateMachine * machine, int X, int Y);
	void onDblClick(StateMachine * machine);
};

#endif