//---------------------------------------------------------------------------

#ifndef frmComposeH
#define frmComposeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include "frmMain.h"
#include "cglib.h"
#include <Vcl.ToolWin.hpp>
#include <list>

//---------------------------------------------------------------------------
class TformCompose : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *btnCancel;
	TButton *btnOk;
	TListView *lstHistory;
	TPanel *Panel2;
	TPanel *Panel5;
	TPanel *Panel10;
	TStringGrid *gridTransform;
	TPanel *Panel11;
	TLabel *Label1;
	TToolBar *barTransformations;
	TToolButton *btnTranslate;
	TToolButton *btnScale;
	TToolButton *btnRotate;
	TToolButton *btnShear;
	TToolButton *btnReflect;
	TToolButton *btnDelete;
	TToolButton *ToolButton2;
	void __fastcall btnTranslateClick(TObject *Sender);
	void __fastcall btnScaleClick(TObject *Sender);
	void __fastcall btnRotateClick(TObject *Sender);
	void __fastcall btnShearClick(TObject *Sender);
	void __fastcall btnReflectClick(TObject *Sender);
	void __fastcall btnDeleteClick(TObject *Sender);
private:	// User declarations
	list<Transformation> history;
	WorkSpace * work;
	TComponent * Owner;
	Object * obj;
	void showMatrixOperation();
public:		// User declarations
	__fastcall TformCompose(TComponent* Owner);
	__fastcall TformCompose(TComponent* Owner, WorkSpace * work, Object * obj);

	Matrix * getStateMatrix();
};
//---------------------------------------------------------------------------
extern PACKAGE TformCompose *formCompose;
//---------------------------------------------------------------------------
#endif
