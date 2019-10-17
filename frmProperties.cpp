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
    this->Caption = "Propriedades do objeto: " + UnicodeString(obj->getName().data());
}
//---------------------------------------------------------------------------

