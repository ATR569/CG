//---------------------------------------------------------------------------

#ifndef frmViewPort3DH
#define frmViewPort3DH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "cglib.h"
//---------------------------------------------------------------------------
class TformViewPort3D : public TForm
{
__published:	// IDE-managed Components
	TPanel *desktop;
	TPanel *Panel1;
	TButton *btnOk;
	TPanel *front;
	TPanel *side;
	TPanel *top;
	TTimer *timer;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	void __fastcall timerTimer(TObject *Sender);
private:	// User declarations
    WorkSpace * work;
public:		// User declarations
	__fastcall TformViewPort3D(TComponent* Owner);
	__fastcall TformViewPort3D(TComponent* Owner, Object * obj);
};
//---------------------------------------------------------------------------
extern PACKAGE TformViewPort3D *formViewPort3D;
//---------------------------------------------------------------------------
#endif
