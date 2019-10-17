#include <vcl.h>
#include <vector>
#pragma hdrstop

#include "frmMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TformMain * formMain;

//---------------------------------------------------------------------------
__fastcall TformMain::TformMain(TComponent* Owner)
	: TForm(Owner)
{
	work = new WorkSpace(DEFAULT_SCR_SIZE, desktop->Width, desktop->Height, GetDC(desktop->Handle));
	work->setDrawGrid(false);
	changeState(st_None);
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actPolygonExecute(TObject *Sender)
{
/*	std::vector<Point2D*> P;

	P.push_back(new Point2D(3,3));
	P.push_back(new Point2D(30,20));
	P.push_back(new Point2D(-25,30));
	P.push_back(new Point2D(-20,3));
	P.push_back(new Point2D(-10,-50));

	Object * o = new Polygon2D(P, DM_BRESENHAN);
	work->addObject(o);
*/
	changeState(st_DrawPolygon);
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


void __fastcall TformMain::actLineExecute(TObject *Sender){

//	Ponto p1(StrToInt(Edit1->Text), StrToInt(Edit2->Text));
//	Ponto p2(StrToInt(Edit3->Text), StrToInt(Edit4->Text));

//	ShowMessage(UnicodeString(r->getName().data()));

	//  Teste de inserção de retas
/*	int v[] = {-30,-20,-10,0,10,20,30};

	Point2D * p1 = new Point2D(0, 0);
	for (int i = 0; i < 7; i++) {
		Point2D * p2 = new Point2D(v[0], v[i]);
		Object * r = new Line(p1, p2, DM_BRESENHAN);
		work->addObject(r);

		Point2D * p3 = new Point2D(v[6], v[i]);
		r = new Line(p1, p3, DM_DDA);
		work->addObject(r);
	}
	for (int i = 1; i < 6; i++) {
		Point2D * p2 = new Point2D(v[i], v[0]);
		Object * r = new Line(p1, p2, DM_BRESENHAN);
		work->addObject(r);

		Point2D * p3 = new Point2D(v[i], v[6]);
		r = new Line(p1, p3, DM_DDA);
		work->addObject(r);
	}

	Point2D * p1 = new Point2D(-30, -10);
	Point2D * p2 = new Point2D(10, -20);
	Object * o = new Line(p1, p2, DM_DDA);
	work->addObject(o);

	btnLine->Down = true;
	*/



	changeState(st_DrawLine);
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


void __fastcall TformMain::actCircleExecute(TObject *Sender)
{
/*	btnCircle->Down = true;
	barTransformations->Enabled = false;
	mainMenu->Enabled = false;

	Point2D * p = new Point2D(20, 10);

	Object * o = new Circle(p, 35, DM_BRESENHAN);
	work->addObject(o);

	TTreeNode * item = treeObjects->Items->Add(NULL, UnicodeString(o->getName().data()));
	item->ImageIndex = 0;

	TTreeNode * sub = treeObjects->Items->AddChild(item, "C = " + FormatFloat("(0.00, ", p->X)+FormatFloat("0.00)", p->Y));
	sub->ImageIndex = -1;
	sub->SelectedIndex = -1;
	sub = treeObjects->Items->AddChild(item, "R = " + FormatFloat("0.00", ((Circle*)o)->getRadius()));
	sub->ImageIndex = -1;
	sub->SelectedIndex = -1;
	*/

	changeState(st_DrawCircle);
}
//---------------------------------------------------------------------------

void __fastcall TformMain::FormDestroy(TObject *Sender)
{
	work->clearObjects();
	free(work);
    Application->Terminate();
}
//---------------------------------------------------------------------------

void TformMain::changeState(State state){
	if (state == st_None) {
		for (int i = 0; i < action_manager->ActionCount; i++) {
			action_manager->Actions[i]->Enabled = true;
		}
		this->limitClick = -1;
		this->pointBuffer.clear();
	}else{
		if (state == st_DrawPolygon) {
			this->limitClick = -1;
		}else{
			this->limitClick = 2;
		}

		for (int i = 0; i < action_manager->ActionCount; i++) {
			action_manager->Actions[i]->Enabled = false;
		}
	}

	this->state = state;
}
//---------------------------------------------------------------------------

void __fastcall TformMain::desktopDblClick(TObject *Sender)
{
	if (state == st_DrawPolygon) {
		addPolygon(new Polygon2D(pointBuffer, DM_BRESENHAN));
		changeState(st_None);
	}
}
//---------------------------------------------------------------------------


void __fastcall TformMain::desktopMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	switch (this->state) {
		case st_DrawLine:{
			pointBuffer.push_back(this->work->CoordScrToUser((new Point2D(X,Y))));
			this->limitClick--;

			if (this->limitClick == 0) {
				addLine(new Line(pointBuffer[0], pointBuffer[1], DM_BRESENHAN));
				changeState(st_None);
			}

			break;
		}
		case st_DrawCircle:{
			pointBuffer.push_back(this->work->CoordScrToUser((new Point2D(X,Y))));
			this->limitClick--;
			if (this->limitClick == 0) {
				double radius = dist(pointBuffer[0], pointBuffer[1]);
				addCircle(new Circle(pointBuffer[0], radius, DM_BRESENHAN));
				changeState(st_None);
			}

			break;
		}
		case st_DrawPolygon:
			pointBuffer.push_back(this->work->CoordScrToUser((new Point2D(X,Y))));
		case st_None:;

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

void __fastcall TformMain::actRotateExecute(TObject *Sender)
{
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


void __fastcall TformMain::chkShowAxisClick(TObject *Sender)
{
	work->setDrawAxis(chkShowAxis->Checked);
	work->setDrawGrid(chkShowGrid->Checked);
	work->setDrawPoints(chkShowPoints->Checked);
	desktop->Repaint();
	work->update();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actPropertiesExecute(TObject *Sender)
{
/*	Object * o = work->getObject(treeObjects->Selected->Index);
	ShowMessage(UnicodeString(o->getName().data()));
	work->eraseObject(o);
	o->getReference()->X = 0;
	o->getReference()->Y = 0;
	work->update();

	Point2D * p1 = new Point2D(-1,5);
	Point2D * p2 = new Point2D(3,8);

	cut(p1, p2, -3,2,1,6);


	ShowMessage("P1 = " + FormatFloat("0.000", p1->X) + ", " + FormatFloat("0.000", p1->Y) + "\nP2 = " + FormatFloat("0.000", p2->X) + ", " + FormatFloat("0.000", p2->Y));
	*/

	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		Object * obj = work->getObject(id);
		TformProperties * properties = new TformProperties(this, obj);

        properties->ShowModal();
		properties->Release();
	}
}
//---------------------------------------------------------------------------


void __fastcall TformMain::actShearExecute(TObject *Sender)
{
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


void __fastcall TformMain::actReflectExecute(TObject *Sender)
{
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

void __fastcall TformMain::actRemoveExecute(TObject *Sender)
{
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


void __fastcall TformMain::actCentralizeExecute(TObject *Sender)
{
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		Object * obj = work->getObject(id);
		Point2D * ref = obj->getReference();
		work->translateObject(obj, -ref->X, -ref->Y);
	}
}
//---------------------------------------------------------------------------

