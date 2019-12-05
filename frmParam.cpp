//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmParam.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformParam *formParam;
//---------------------------------------------------------------------------
__fastcall TformParam::TformParam(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
TformParam::TformParam(TComponent* Owner, WorkSpace * work, ParamType paramType) : TForm(Owner){
	this->paramType = paramType;
    this->work = work;

	switch (paramType) {
	case ptTranslate:
		edtParamX->EditLabel->Caption = "Translação em X: ";
		edtParamY->EditLabel->Caption = "Translação em Y: ";
		edtParamZ->EditLabel->Caption = "Translação em Z: ";
		rdgReference->Visible = false;
		Height = 200;
		break;
	case ptScale:
		edtParamX->EditLabel->Caption = "Escala em X: ";
		edtParamY->EditLabel->Caption = "Escala em Y: ";
		edtParamZ->EditLabel->Caption = "Escala em Z: ";
		edtParamX->Text = "1,000";
		edtParamY->Text = "1,000";
		edtParamZ->Text = "1,000";
		break;
	case ptShear:
		edtParamX->EditLabel->Caption = "Cisalhamento em X: ";
		edtParamY->EditLabel->Caption = "Cisalhamento em Y: ";
		edtParamZ->EditLabel->Caption = "Cisalhamento em Z: ";

		if (work->getMode() == MODE_3D) {
			grpRefPoint->Visible = false;
			rdgReference->Items->Strings[0] = "Cisalhamento em relação ao Eixo X";
			rdgReference->Items->Strings[1] = "Cisalhamento em relação ao Eixo Y";
			rdgReference->Items->Strings[2] = "Cisalhamento em relação ao Eixo Z";
		}
		break;
	case ptRotate:
		edtParamX->EditLabel->Caption = "Ângulo de Rotação: ";
		edtParamY->Visible = false;
		edtParamZ->Visible = false;

		if (work->getMode() == MODE_2D) {
			pnlParams->Height = 41;
			Height -= 45;
		}else{
			grpRefPoint->Visible = false;
			rdgReference->Items->Strings[0] = "Rotação em relação ao Eixo X";
			rdgReference->Items->Strings[1] = "Rotação em relação ao Eixo Y";
			rdgReference->Items->Strings[2] = "Rotação em relação ao Eixo Z";
		}
		break;
	case ptReflect:
		pnlParams->Visible = false;
		if (work->getMode() == MODE_2D) {
			rdgReference->Items->Strings[0] = "Refletir em relação ao Eixo X";
			rdgReference->Items->Strings[1] = "Refletir em relação ao Eixo Y";
			rdgReference->Items->Strings[2] = "Refletir em relação a uma reta";
			grpRefPoint->Caption = "Reta: Y = mX + B";
			edtX->EditLabel->Caption = "m";
			edtY->EditLabel->Caption = "B";
			Height = 250;
		}else{
			grpRefPoint->Visible = false;
			rdgReference->Items->Strings[0] = "Refletir em relação ao Plano XY";
			rdgReference->Items->Strings[1] = "Refletir em relação ao Plano YZ";
			rdgReference->Items->Strings[2] = "Refletir em relação ao Plano XZ";
		}

		break;
	case ptNewEllipse:
		edtParamX->EditLabel->Caption = "Parâmetro A: ";
		edtParamY->EditLabel->Caption = "Parâmetro B: ";
		rdgReference->Visible = false;
		Height = 200;
		break;

	case ptNewCube:
		edtParamY->Visible = false;
	case ptNewPolyedron:
		edtParamX->EditLabel->Caption = "Aresta da base: ";
		edtParamY->EditLabel->Caption = "Altura: ";

		edtParamZ->Visible = false;
		rdgReference->Visible = false;
		grpRefPoint->Visible = true;

		Height = 250;
		pnlParams->Height = edtParamY->Visible ? 75 : 41;

		break;
	}

	if (work == NULL || work->getMode() == MODE_2D) {
		edtParamZ->Visible = false;
		edtZ->Visible = false;
		edtX->Left += 35;
		edtY->Left += 35;
	}
}
//---------------------------------------------------------------------------
void __fastcall TformParam::rdgReferenceClick(TObject *Sender)
{
	grpRefPoint->Visible = (rdgReference->ItemIndex == 2);
}
//---------------------------------------------------------------------------


void __fastcall TformParam::edtParamXKeyPress(TObject *Sender, System::WideChar &Key)

{
	if (Key == '.') {
		Key = ',';
	}else if (Key != ',' && Key != '-' && Key != 8 && (Key < '0' || Key > '9')) {
		Key = 0;
	}

	TLabeledEdit * edit = (TLabeledEdit *) Sender;

	if (Key == ',' && edit->Text.Pos(",") != NULL){
		Key = 0;
	}else if (Key == '-' && ((edit->Text.Pos("-") != NULL) || edit->SelStart != 0)){
		Key = 0;
	}else if (Key >= '0' && Key <= '9' && (edit->Text.Pos("-") != NULL) && edit->SelStart == 0){
		Key = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TformParam::fixValues(TObject *Sender){
	TLabeledEdit * edit = (TLabeledEdit *) Sender;
	if (edit->Text == "") {
	   edit->Text = "0,000";
	}else{
		if (*edit->Text.FirstChar() == ',') {
			edit->Text = "0" + edit->Text;
		}
		edit->Text = FormatFloat("0.000", StrToFloat(edit->Text));
	}

}
//---------------------------------------------------------------------------

void __fastcall TformParam::btnOkClick(TObject *Sender)
{
	fixValues(edtParamX);
	fixValues(edtParamY);
	fixValues(edtParamZ);
	fixValues(edtX);
	fixValues(edtY);
	fixValues(edtZ);
}
//---------------------------------------------------------------------------

Point2D * TformParam::getReference(Object * obj){
	Point2D * ref;

	//  Origem
	if (rdgReference->ItemIndex == 0) {
		ref = new Point2D(0, 0);
	//  Centro do objeto
	}else if (rdgReference->ItemIndex == 1) {
		ref = (Point2D*)obj->getReference();
	//  Ponto espec�fico
	}else{
		double x = StrToFloat(edtX->Text);
		double y = StrToFloat(edtY->Text);

		ref = new Point2D(x,y);
	}

	return ref;
}