//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmProperties.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformProperties *formProperties;
//---------------------------------------------------------------------------
__fastcall TformProperties::TformProperties(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
TformProperties::TformProperties(TComponent* Owner, Object * obj) : TForm(Owner){
	this->Caption = "Propriedades do objeto: " + obj->getName();
	cmbDrawMethod->ItemIndex = obj->getMethod();
	cmbColor->Selected = TColor(obj->getColor());

	list<Transformation> history = obj->getHistory();
	list<Transformation>::iterator it;
	for (it = history.begin(); it != history.end(); it++) {
		TListItem * item = lstHistory->Items->Add();
		item->Caption = it->getName();
	}

	lstHistory->ItemIndex = history.size()-1;

	Matrix state = *getIdentityMatrix();
	stateMatrix.push_back(state);

	for (it = history.begin(); it != history.end(); it++) {
		historyMatrix.push_back(it->getMatrix());
		state = (*it->getMatrix()) * (state);
		stateMatrix.push_back(state);
	}

	vector<String> strings = obj->toStrings();

	for	(int i = 1; i < strings.size(); i++){
		TListItem * item = lstPoints->Items->Add();
		item->Caption = strings[i];
	}
	lstPoints->ItemIndex = 0;

	work = new WorkSpace(DEFAULT_SCR_SIZE, desktop->Width, desktop->Height, GetDC(desktop->Handle));
	work->setDrawGrid(false);
	work->setDrawAxis(false);
	work->setDrawPoints(false);
	work->setMode(MODE_2D);

	work->addObject(obj);
	work->update();

    lstHistoryClick(NULL);
}
//---------------------------------------------------------------------------


void __fastcall TformProperties::timerTimer(TObject *Sender){
	timer->Enabled = false;
	work->update();
}
//---------------------------------------------------------------------------

void __fastcall TformProperties::desktopMouseMove(TObject *Sender, TShiftState Shift,
		  int X, int Y){
	Point2D * p = work->CoordScrToUser(new Point2D(X,Y));
	lblScrX->Caption = "X: " + IntToStr(X);
	lblScrY->Caption = "Y: " + IntToStr(Y);

	lblUserX->Caption = "X: " + FormatFloat("#,###0.000", p->X);
	lblUserY->Caption = "Y: " + FormatFloat("#,###0.000", p->Y);

	desktop->Hint = lblScrX->Caption + "\n" + lblScrY->Caption;
}
//---------------------------------------------------------------------------

void __fastcall TformProperties::cmbColorChange(TObject *Sender)
{
	work->getObject(0)->setColor(cmbColor->Selected);
	desktop->Repaint();
	work->update();
}
//---------------------------------------------------------------------------


void __fastcall TformProperties::cmbDrawMethodChange(TObject *Sender){
	work->getObject(0)->setDrawMethod(DrawMethod(cmbDrawMethod->ItemIndex));
	desktop->Repaint();
	work->update();
}
//---------------------------------------------------------------------------

void __fastcall TformProperties::lstHistoryClick(TObject *Sender)
{
	int idTransf = lstHistory->ItemIndex;
	int idPoint = lstPoints->ItemIndex;

	showMatrixOperation(idTransf, idPoint);
}
//---------------------------------------------------------------------------
void TformProperties::showMatrixOperation(int idTransf, int idPoint){
	Object * obj = work->getObject(0);
	vector<Point2D *> points = obj->getPoints();

	if (idTransf >= 0 && idTransf < stateMatrix.size() && idPoint >= 0 && idPoint < points.size()){
		Point2D * pNew = ((stateMatrix[idTransf+1]) * (*points[idPoint]->asMatrix())).asPoint2D();
		Point2D * pOld = ((stateMatrix[idTransf]) * (*points[idPoint]->asMatrix())).asPoint2D();

		gridNewPoint->Cells[0][0] = FormatFloat("0.00", pNew->X);
		gridNewPoint->Cells[0][1] = FormatFloat("0.00", pNew->Y);
		gridNewPoint->Cells[0][2] = "1,00";

		gridOldPoint->Cells[0][0] = FormatFloat("0.00", pOld->X);
		gridOldPoint->Cells[0][1] = FormatFloat("0.00", pOld->Y);
		gridOldPoint->Cells[0][2] = "1,00";

		vvd data = historyMatrix[idTransf]->getData();
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				gridTransform->Cells[j][i] = FormatFloat("0.00", data[i][j]);
			}
		}

		obj->getStateMatrix()->assign(stateMatrix[idTransf+1]);

		desktop->Repaint();
		work->update();
	}
}


