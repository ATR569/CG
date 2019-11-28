//---------------------------------------------------------------------------

#ifndef frmImageMainH
#define frmImageMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------

#include "cglib.h"
#include "imagelib.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <iostream>
#include <fstream>

class TformImageMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *Button2;
	TPanel *hist1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TformImageMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformImageMain *formImageMain;
//---------------------------------------------------------------------------
#endif