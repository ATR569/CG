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
//---------------------------------------------------------------------------
class TformProperties : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *btnCancel;
	TButton *btnOk;
private:	// User declarations
public:		// User declarations
	__fastcall TformProperties(TComponent* Owner);
	TformProperties(TComponent* Owner, Object * obj);
};
//---------------------------------------------------------------------------
extern PACKAGE TformProperties *formProperties;
//---------------------------------------------------------------------------
#endif
