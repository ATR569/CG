#ifndef stateH
#define stateH

class StateMachine;

class State{
public:
	virtual void onClick(StateMachine * machine, int X, int Y) = 0;
	virtual void onDblClick(StateMachine * machine) = 0;
	virtual void onLineClick(StateMachine * machine) = 0;
	virtual void onCircleClick(StateMachine * machine) = 0;
	virtual void onPolygonClick(StateMachine * machine) = 0;
};

class StateNone : public State{
	void onClick(StateMachine * machine, int X, int Y);
	void onDblClick(StateMachine * machine);
	void onLineClick(StateMachine * machine);
	void onCircleClick(StateMachine * machine);
	void onPolygonClick(StateMachine * machine);
};

class StateDrawing : public State{
	void onLineClick(StateMachine * machine){};
	void onCircleClick(StateMachine * machine){};
	void onPolygonClick(StateMachine * machine){};
};

class StateDrawingFirstPointLine : public StateDrawing{
	void onClick(StateMachine * machine, int X, int Y);
	void onDblClick(StateMachine * machine){}
};

class StateDrawingSecondPointLine : public StateDrawing{
	void onClick(StateMachine * machine, int X, int Y);
	void onDblClick(StateMachine * machine){}
};

class StateDrawingCircleCenter : public StateDrawing{
	void onClick(StateMachine * machine, int X, int Y);
	void onDblClick(StateMachine * machine){}
};

class StateDrawingCircleRadius : public StateDrawing{
	void onClick(StateMachine * machine, int X, int Y);
	void onDblClick(StateMachine * machine){}
};

class StateDrawingPolygon2D : public StateDrawing{
	void onClick(StateMachine * machine, int X, int Y);
	void onDblClick(StateMachine * machine);
};

#endif