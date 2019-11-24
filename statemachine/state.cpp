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

//  None.Ellipse
void StateNone::onEllipseClick(StateMachine * machine){
//  TO DO
	machine->formMain->btnObjectCancel->Visible = true;
	machine->setState(new StateDrawingEllipseCenter());
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
	//	Adiciona o ponto ao vetor de pontos
	machine->pointBuffer.push_back(machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));
	//	Instancia uma nova reta
	Line * l = new Line(machine->pointBuffer[0], machine->pointBuffer[1], DM_BRESENHAN);
	//	Adiciona o objeto ao workspace
	machine->formMain->work->addObject(l);
	//	Cria os nós na árvore (ícone de reta = 1)
	TTreeNode * item = machine->formMain->addTreeItem(machine->pointBuffer.size(), 1);
	//	Atualiza a descrição do objeto na árvore de visualização
	machine->formMain->updateTreeView(item, l);

	onObjectCancelClick(machine);
}

//  DrawingPolygon.Click
void StateDrawingPolygon2D::onClick(StateMachine * machine, int X, int Y){
	//	Adiciona um novo ponto ao vetor de
	machine->pointBuffer.push_back(machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));
}

//  DrawingSecondPointLine.DblClick
void StateDrawingPolygon2D::onDblClick(StateMachine * machine){
	//	Instancia uma nova reta
	Polygon2D * obj = new Polygon2D(machine->pointBuffer, DM_BRESENHAN);
	//	Adiciona o objeto ao workspace
	machine->formMain->work->addObject(obj);
	//	Cria os nós na árvore (ícone de polígono = 2)
	TTreeNode * item = machine->formMain->addTreeItem(machine->pointBuffer.size(), 2);
	//	Atualiza a descrição do objeto na árvore de visualização
	machine->formMain->updateTreeView(item, obj);

	onObjectCancelClick(machine);
}

//  StateDrawingCircleCenter.Click
void StateDrawingCircleCenter::onClick(StateMachine * machine, int X, int Y){
	machine->pointBuffer.push_back(machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));
	machine->setState(new StateDrawingCircleRadius());
}

//  StateDrawingCircleRadius.Click
void StateDrawingCircleRadius::onClick(StateMachine * machine, int X, int Y){
	//	Adiciona o ponto ao vetor de pontos
	machine->pointBuffer.push_back(machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));
	//	Calcula o raio do círculo
	double radius = dist(machine->pointBuffer[0], machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));
	//	Instancia uma nova reta
	Circle * obj = new Circle(machine->pointBuffer[0], radius, DM_BRESENHAN);
	//	Adiciona o objeto ao workspace
	machine->formMain->work->addObject(obj);
	//	Cria os nós na árvore (ícone de círculo = 0)
	TTreeNode * item = machine->formMain->addTreeItem(machine->pointBuffer.size(), 0);
	//	Atualiza a descrição do objeto na árvore de visualização
	machine->formMain->updateTreeView(item, obj);

	onObjectCancelClick(machine);
}

//  StateDrawingEllipseCenter.Click
void StateDrawingEllipseCenter::onClick(StateMachine * machine, int X, int Y){
	TformParam * param = new TformParam(machine->formMain, machine->formMain->work, ptNewEllipse);

	if (param->ShowModal() == mrOk){
		double a = StrToFloat(param->edtParamX->Text);
		double b = StrToFloat(param->edtParamY->Text);

		//	Adiciona o ponto ao vetor de pontos
		machine->pointBuffer.push_back(machine->formMain->work->CoordScrToUser((new Point2D(X, Y))));
		//	Instancia uma nova reta
		Elipse * obj = new Elipse(machine->pointBuffer[0], a, b, DM_BRESENHAN);
		//	Adiciona o objeto ao workspace
		machine->formMain->work->addObject(obj);
		//	Cria os nós na árvore (ícone de círculo = 0)
		TTreeNode * item = machine->formMain->addTreeItem(machine->pointBuffer.size(), 0);
		//	Atualiza a descrição do objeto na árvore de visualização
		machine->formMain->updateTreeView(item, obj);

		onObjectCancelClick(machine);
	}

	param->Release();

}
