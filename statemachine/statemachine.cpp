//---------------------------------------------------------------------------

#pragma hdrstop
#include "statemachine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "state.h"
#include "cstdlib"
#include "../frmMain.h"

StateMachine::StateMachine(TformMain * formMain){
    this->state = new StateNone();
    this->formMain = formMain;
}

void StateMachine::performClick(int X, int Y){
    this->state->onClick(this, X, Y);
}

void StateMachine::performDblClick(){
    this->state->onDblClick(this);
}

void StateMachine::performDrawLineClick(){
	this->state->onLineClick(this);
}

void StateMachine::performDrawCircleClick(){
	this->state->onCircleClick(this);
}

void StateMachine::performDrawEllipseClick(){
	this->state->onEllipseClick(this);
}

void StateMachine::performDrawPolygonClick(){
	this->state->onPolygonClick(this);
}

void StateMachine::setState(State * state){
	free(this->state);
	this->state = state;

	int btnStateMask = state->getBtnStateMask();

	for (int i = 0; i < formMain->action_manager->ActionCount; i++) {
		formMain->action_manager->Actions[i]->Enabled = ((1 << i)&btnStateMask);
	}

}

void StateMachine::performObjectCancelClick(){
	this->state->onObjectCancelClick(this);
}

