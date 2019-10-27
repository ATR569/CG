//---------------------------------------------------------------------------

#ifndef frmPropertiesH
#define frmPropertiesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "objects/object.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TformProperties : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *btnCancel;
	TButton *btnOk;
	TPanel *Panel12;
	TListView *lstHistory;
	TPanel *Panel2;
	TLabel *Label1;
	TLabel *Label2;
	TPanel *Panel3;
	TPanel *Panel6;
	TPanel *Panel7;
	TPanel *Panel4;
	TPanel *Panel8;
	TPanel *Panel9;
	TPanel *Panel5;
	TPanel *Panel10;
	TPanel *Panel11;
	TPanel *desktop;
	TStringGrid *gridTransform;
	TListView *lstPoints;
	TStringGrid *gridOrigem;
	TStringGrid *gridTarget;
private:	// User declarations
public:		// User declarations
	__fastcall TformProperties(TComponent* Owner);
	TformProperties(TComponent* Owner, Object * obj);
};
//---------------------------------------------------------------------------
extern PACKAGE TformProperties *formProperties;
//---------------------------------------------------------------------------
#endif
