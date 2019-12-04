//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmCredits.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformCredits *formCredits;
//---------------------------------------------------------------------------
__fastcall TformCredits::TformCredits(TComponent* Owner)
	: TForm(Owner)
{
    this->canClose = false;
}
//---------------------------------------------------------------------------
void __fastcall TformCredits::Timer1Timer(TObject *Sender)
{
    this->canClose = true;
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TformCredits::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = this->canClose;
}
//---------------------------------------------------------------------------
