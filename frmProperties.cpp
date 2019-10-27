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

	list<Transformation> history = obj->getHistory();
	list<Transformation>::iterator it;

	for (it = history.begin(); it != history.end(); it++) {
		TListItem * item = lstHistory->Items->Add();
		item->Caption = it->getName();
	}

	lstHistory->ItemIndex = history.size()-1;
}
//---------------------------------------------------------------------------



