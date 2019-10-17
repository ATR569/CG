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
TformParam::TformParam(TComponent* Owner, Object * obj, ParamType paramType) : TForm(Owner){
	this->paramType = paramType;
    this->obj = obj;
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
		ref = obj->getReference();
	//  Ponto específico
	}else{
		double x = StrToFloat(edtX->Text);
		double y = StrToFloat(edtY->Text);

		ref = new Point2D(x,y);
	}

	return ref;
}
