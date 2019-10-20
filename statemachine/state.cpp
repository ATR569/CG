//---------------------------------------------------------------------------

#pragma hdrstop
#include "state.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#include "../frmMain.h"
#include "statemachine.h"


State::State(int btnStateMask){
	this->btnStateMask = btnStateMask;
}

int State::getBtnStateMask(){
    return this->btnStateMask;
}

//  None.LineClick
void StateNone::onLineClick(StateMachine * machine){
//  TO DO
	machine->formMain->btnObjectCancel->Visible = true;
	machine->setState(new StateDrawingFirstPointLine());
}

//  None.Circle
void StateNone::onCircleClick(StateMachine * machine){
//  TO DO
	machine->formMain->btnObjectCancel->Visible = true;
	machine->setState(new StateDrawingCircleCenter());
}

//  None.PolygonClick
void StateNone::onPolygonClick(StateMachine * machine){
//  TO DO
	machine->formMain->btnObjectCancel->Visible = true;
	machine->setState(new StateDrawingPolygon2D());
}

//  DrawingFirstPointLine.Click
void StateDrawingFirstPointLine::onClick(StateMachine * machine, int X, int Y){
	machine->pointBuffer.push_back(machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));
	machine->setState(new StateDrawingSecondPointLine());
}

//  Drawing.ObjectCancelClick
void StateDrawing::onObjectCancelClick(StateMachine * machine){
	machine->formMain->btnObjectCancel->Visible = false;

	machine->pointBuffer.clear();
	machine->setState(new StateNone());
}

//  DrawingSecondPointLine.Click
void StateDrawingSecondPointLine::onClick(StateMachine * machine, int X, int Y){
	machine->pointBuffer.push_back(machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));

	machine->formMain->addLine(new Line(machine->pointBuffer[0], machine->pointBuffer[1], DM_BRESENHAN));
	onObjectCancelClick(machine);
}

//  DrawingPolygon.Click
void StateDrawingPolygon2D::onClick(StateMachine * machine, int X, int Y){
	machine->pointBuffer.push_back(machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));
}
//  DrawingSecondPointLine.DblClick
void StateDrawingPolygon2D::onDblClick(StateMachine * machine){
	machine->formMain->addPolygon(new Polygon2D(machine->pointBuffer, DM_BRESENHAN));
	onObjectCancelClick(machine);
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

	onObjectCancelClick(machine);
}

