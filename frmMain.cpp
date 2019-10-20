#include <vcl.h>
#include <vector>
#pragma hdrstop

#include "frmMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TformMain * formMain;

//---------------------------------------------------------------------------
__fastcall TformMain::TformMain(TComponent* Owner) : TForm(Owner){
	work = new WorkSpace(DEFAULT_SCR_SIZE, desktop->Width, desktop->Height, GetDC(desktop->Handle));
	work->setDrawGrid(false);

	this->machine = new StateMachine(this);
}
//---------------------------------------------------------------------------

void __fastcall TformMain::FormDestroy(TObject *Sender){
	work->clearObjects();
	free(work);
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actPolygonExecute(TObject *Sender){
	machine->performDrawPolygonClick();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actMoveExecute(TObject *Sender)
{
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		Object * obj = work->getObject(id);
		TformParam * param = getParamWindow(ptTranslate);
		if (param->ShowModal() == mrOk){
			Object * obj = work->getObject(id);

			double tx = StrToFloat(param->edtParamX->Text);
			double ty = StrToFloat(param->edtParamY->Text);

			work->translateObject(obj, tx, ty);
		}

		param->Release();
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actScaleExecute(TObject *Sender)
{
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		TformParam * param = getParamWindow(ptScale);

		if (param->ShowModal() == mrOk){
			Object * obj = work->getObject(id);

			double sx = StrToFloat(param->edtParamX->Text);
			double sy = StrToFloat(param->edtParamY->Text);

			Point2D * ref = param->getReference(obj);

			work->scaleObject(obj, ref, sx, sy);
		}

		param->Release();
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::timerTimer(TObject *Sender)
{
	timer->Enabled = false;
	work->update();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::desktopResize(TObject *Sender)
{
	if (work != NULL){
		work->setCanvasSize(desktop->Width, desktop->Height);
		timer->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::treeObjectsClick(TObject *Sender)
{
	int id = treeObjects->Selected->Index;
}
//---------------------------------------------------------------------------


void __fastcall TformMain::desktopMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	Point2D * p = work->CoordScrToUser(new Point2D(X,Y));
	lblScrX->Caption = "X: " + IntToStr(X);
	lblScrY->Caption = "Y: " + IntToStr(Y);

	UnicodeString s1 = "X: " + FormatFloat("#,###0.000", p->X);
	UnicodeString s2 = "Y: " + FormatFloat("#,###0.000", p->Y);
	lblUserX->Caption = s1;
	lblUserY->Caption = s2;

	desktop->Hint = s1 + "\n" + s2;
}
//---------------------------------------------------------------------------

void __fastcall TformMain::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight,
		  bool &Resize)
{
	if (NewWidth < 500 || NewHeight < 500) {
		Resize = false;
	}else{
		desktop->Margins->Left = 30 - (NewWidth%2 == 0);
		desktop->Margins->Top = 30 - (NewHeight%2 == 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actLineExecute(TObject *Sender){
	machine->performDrawLineClick();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actCircleExecute(TObject *Sender){
	machine->performDrawCircleClick();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::desktopDblClick(TObject *Sender){
	machine->performDblClick();
}
//---------------------------------------------------------------------------


void __fastcall TformMain::desktopMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	this->machine->performClick(X, Y);
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actRotateExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		TformParam * param = getParamWindow(ptRotate);

		if (param->ShowModal() == mrOk){
			Object * obj = work->getObject(id);

			double theta = StrToFloat(param->edtParamX->Text);

			Point2D * ref = param->getReference(obj);

			work->rotateObject(obj, ref, theta);
		}

		param->Release();
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::chkShowAxisClick(TObject *Sender){
	work->setDrawAxis(chkShowAxis->Checked);
	work->setDrawGrid(chkShowGrid->Checked);
	work->setDrawPoints(chkShowPoints->Checked);
	desktop->Repaint();
	work->update();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actPropertiesExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		Object * obj = work->getObject(id);
		TformProperties * properties = new TformProperties(this, obj);

		properties->ShowModal();
		properties->Release();
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actShearExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		TformParam * param = getParamWindow(ptShear);

		if (param->ShowModal() == mrOk){
			Object * obj = work->getObject(id);

			double shx = StrToFloat(param->edtParamX->Text);
			double shy = StrToFloat(param->edtParamY->Text);

			Point2D * ref = param->getReference(obj);

			work->shearObject(obj, ref, shx, shy);
		}

		param->Release();
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actReflectExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		TformParam * param = getParamWindow(ptReflect);

		if (param->ShowModal() == mrOk){
			Object * obj = work->getObject(id);

			int axis = param->rdgReference->ItemIndex;

			if (axis == 2) {
				double m = StrToFloat(param->edtX->Text);
				double b = StrToFloat(param->edtY->Text);

				work->reflectObject(obj, m, b);
			}else{
				work->reflectObject(obj, axis);
			}
		}

		param->Release();
	}
}
//---------------------------------------------------------------------------

TformParam * TformMain::getParamWindow(ParamType paramType){
	TformParam * param = new TformParam(this);

	switch (paramType) {
	case ptTranslate:
		param->edtParamX->EditLabel->Caption = "Translação em X: ";
		param->edtParamY->EditLabel->Caption = "Translação em Y: ";
		param->edtParamZ->EditLabel->Caption = "Translação em Z: ";
		param->rdgReference->Visible = false;
		param->Height = 200;
		break;
	case ptScale:
		param->edtParamX->EditLabel->Caption = "Escala em X: ";
		param->edtParamY->EditLabel->Caption = "Escala em Y: ";
		param->edtParamZ->EditLabel->Caption = "Escala em Z: ";
		param->edtParamX->Text = "1,000";
		param->edtParamY->Text = "1,000";
		param->edtParamZ->Text = "1,000";
		break;
	case ptShear:
		param->edtParamX->EditLabel->Caption = "Cisalhamento em X: ";
		param->edtParamY->EditLabel->Caption = "Cisalhamento em Y: ";
		param->edtParamZ->EditLabel->Caption = "Cisalhamento em Z: ";
		break;
	case ptRotate:
		param->edtParamX->EditLabel->Caption = "Ângulo de Rotação: ";
		param->edtParamY->Visible = false;
		param->edtParamZ->Visible = false;
		param->pnlParams->Height = 41;
        param->Height -= 45;
		break;
	case ptReflect:
		param->pnlParams->Visible = false;
		param->rdgReference->Items->Strings[0] = "Refletir em relação ao Eixo X";
		param->rdgReference->Items->Strings[1] = "Refletir em relação ao Eixo Y";
		param->rdgReference->Items->Strings[2] = "Refletir em relação a uma reta";
		param->grpRefPoint->Caption = "Reta: Y = mX + B";
		param->edtX->EditLabel->Caption = "m";
		param->edtY->EditLabel->Caption = "B";
        param->Height = 250;
	}

	if (work->getMode() == MODE2D) {
		param->edtParamZ->Visible = false;
		param->edtZ->Visible = false;
		param->edtX->Left += 35;
		param->edtY->Left += 35;
	}

	return param;
}

void __fastcall TformMain::actRemoveExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		Object * obj = work->getObject(id);
		UnicodeString msg = "Deseja realmente remover o objeto " + UnicodeString(obj->getName().data()) + "?";

		if (MessageDlg(msg, mtConfirmation, mbYesNo, 0, mbNo) == mrYes) {
			work->deleteObject(id);
            treeObjects->Selected->Delete();
		}

	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actCentralizeExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		Object * obj = work->getObject(id);
		Point2D * ref = obj->getReference();
		work->translateObject(obj, -ref->X, -ref->Y);
	}
}
//---------------------------------------------------------------------------

void TformMain::addCircle(Circle * C){
	this->work->addObject(C);

	TTreeNode * item = treeObjects->Items->Add(NULL, UnicodeString(C->getName().data()));
	item->ImageIndex = 0;
	item->ImageIndex = 0;

	TTreeNode * sub = treeObjects->Items->AddChild(item, "C = (" + FormatFloat("0.00, ", C->getCenter()->X)+FormatFloat("0.00)", C->getCenter()->Y));
	sub->ImageIndex = -1;
	sub->SelectedIndex = -1;
	sub = treeObjects->Items->AddChild(item, "R = " + FormatFloat("0.00", C->getRadius()));
	sub->ImageIndex = -1;
	sub->SelectedIndex = -1;
}

void TformMain::addLine(Line * l){
	this->work->addObject(l);

	TTreeNode * item = treeObjects->Items->Add(NULL, UnicodeString(l->getName().data()));
	item->ImageIndex = 1;
	item->SelectedIndex = 1;

	TTreeNode * sub = treeObjects->Items->AddChild(item, "A = (" + FormatFloat("0.00, ", l->getA()->X)+FormatFloat("0.00)", l->getA()->Y));
	sub->ImageIndex = -1;
	sub->SelectedIndex = -1;
	sub = treeObjects->Items->AddChild(item, "B = (" + FormatFloat("0.00, ", l->getB()->X)+FormatFloat("0.00)", l->getB()->Y));
	sub->ImageIndex = -1;
	sub->SelectedIndex = -1;
}

void TformMain::addPolygon(Polygon2D * p){
	work->addObject(p);

	TTreeNode * item = treeObjects->Items->Add(NULL, UnicodeString(p->getName().data()));
	item->ImageIndex = 2;
	item->SelectedIndex = 2;

	TTreeNode * sub;
	vector<Point2D*> points = p->getPoints();

	for (int i = 0; i < points.size(); i++) {
		TTreeNode * sub = treeObjects->Items->AddChild(item, "(" + FormatFloat("0.00, ", points[i]->X)+FormatFloat("0.00)", points[i]->Y));
		sub->ImageIndex = -1;
		sub->SelectedIndex = -1;
	}
}

