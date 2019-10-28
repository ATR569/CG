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
	//  Título da janela
	this->Caption = "Propriedades do objeto: " + obj->getName();
	//  Método de rasterização
	cmbDrawMethod->ItemIndex = obj->getMethod();
	//  Cor do objeto
	cmbColor->Selected = TColor(obj->getColor());

		//  Exibe o histórico de transformações
		list<Transformation> history = obj->getHistory();
		list<Transformation>::iterator it;
		for (it = history.begin(); it != history.end(); it++) {
			TListItem * item = lstHistory->Items->Add();
			item->Caption = it->getName();


		}

		lstHistory->ItemIndex = history.size()-1;


	//  Armazena as matrizes de transformação num array e
	//  Precomputa todas as matrizes de estado do objeto
	Matrix * state = getIdentityMatrix();
	for (it = history.begin(); it != history.end(); it++) {
		historyMatrix.push_back(it->getMatrix());
		*state = (*it->getMatrix()) * (*state);
		stateMatrix.push_back(state);
	}

	//  Vetor com as strings que definem o objeto
	vector<String> strings = obj->toStrings();

	//  Pontos do objeto
	for	(int i = 1; i < strings.size(); i++){
		TListItem * item = lstPoints->Items->Add();
		item->Caption = strings[i];
	}



	//  Inicialização do workspace
	work = new WorkSpace(DEFAULT_SCR_SIZE, desktop->Width, desktop->Height, GetDC(desktop->Handle));
	work->setDrawGrid(false);
	work->setDrawAxis(false);
	work->setDrawPoints(false);
	work->setMode(MODE_2D);

	work->addObject(obj);
	work->update();
}
//---------------------------------------------------------------------------

void __fastcall TformProperties::FormShow(TObject *Sender)
{
	gridNewPoint->Cells[0][0] = "125.00";
	gridNewPoint->Cells[0][1] = "999.00";
	gridNewPoint->Cells[0][2] = "999.99";

	gridTransform->Cells[0][0] = "125.00";
	gridTransform->Cells[0][1] = "999.00";
	gridTransform->Cells[0][2] = "999.99";
	gridTransform->Cells[1][0] = "125.00";
	gridTransform->Cells[1][1] = "999.00";
	gridTransform->Cells[1][2] = "999.99";
	gridTransform->Cells[2][0] = "125.00";
	gridTransform->Cells[2][1] = "999.00";
	gridTransform->Cells[2][2] = "999.99";

	gridOldPoint->Cells[0][0] = "125.00";
	gridOldPoint->Cells[0][1] = "999.00";
	gridOldPoint->Cells[0][2] = "999.99";

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


