//---------------------------------------------------------------------------

#pragma hdrstop
#include "state.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include "../frmMain.h"
#include "statemachine.h"

//  None.Click
void StateNone::onClick(StateMachine * machine, int X, int Y){
//  TO DO

}

//  None.DblClick
void StateNone::onDblClick(StateMachine * machine){
//  TO DO

}

//  None.LineClick
void StateNone::onLineClick(StateMachine * machine){
//  TO DO

	machine->setState(new StateDrawingFirstPointLine());
}

//  None.Circle
void StateNone::onCircleClick(StateMachine * machine){
//  TO DO

	machine->setState(new StateDrawingCircleCenter());
}

//  None.PolygonClick
void StateNone::onPolygonClick(StateMachine * machine){
//  TO DO

	machine->setState(new StateDrawingPolygon2D());
}

//  DrawingFirstPointLine.Click
void StateDrawingFirstPointLine::onClick(StateMachine * machine, int X, int Y){
	machine->pointBuffer.push_back(machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));
	machine->setState(new StateDrawingSecondPointLine());
}

//  DrawingSecondPointLine.Click
void StateDrawingSecondPointLine::onClick(StateMachine * machine, int X, int Y){
	machine->pointBuffer.push_back(machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));

	machine->formMain->addLine(new Line(machine->pointBuffer[0], machine->pointBuffer[1], DM_BRESENHAN));
	machine->pointBuffer.clear();
	machine->setState(new StateNone());
}

//  DrawingPolygon.Click
void StateDrawingPolygon2D::onClick(StateMachine * machine, int X, int Y){
	machine->pointBuffer.push_back(machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));
}
//  DrawingSecondPointLine.DblClick
void StateDrawingPolygon2D::onDblClick(StateMachine * machine){
	machine->formMain->addPolygon(new Polygon2D(machine->pointBuffer, DM_BRESENHAN));
	machine->pointBuffer.clear();
	machine->setState(new StateNone());
}

//  StateDrawingCircleCenter.Click
void StateDrawingCircleCenter::onClick(StateMachine * machine, int X, int Y){
	machine->pointBuffer.push_back(machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));
	machine->setState(new StateDrawingCircleRadius());
}

//  StateDrawingCircleRadius.Click
void StateDrawingCircleRadius::onClick(StateMachine * machine, int X, int Y){
	double radius = dist(machine->pointBuffer[0], machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));
	machine->formMain->addCircle(new Circle(machine->pointBuffer[0], radius, DM_BRESENHAN));

	machine->pointBuffer.clear();
	machine->setState(new StateNone());
}

