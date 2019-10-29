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

#include "cglib.h"
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
	TStringGrid *gridNewPoint;
	TStringGrid *gridOldPoint;
	TGroupBox *GroupBox1;
	TColorBox *cmbColor;
	TComboBox *cmbDrawMethod;
	TLabel *Label3;
	TLabel *Label4;
	TTimer *timer;
	TPanel *pnlCoord;
	TLabel *lblUserX;
	TLabel *lblUserY;
	TLabel *lblScrX;
	TLabel *lblScrY;
	TLabel *Label5;
	TLabel *Label6;
	TBevel *Bevel1;
	void __fastcall timerTimer(TObject *Sender);
	void __fastcall desktopMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall cmbColorChange(TObject *Sender);
	void __fastcall cmbDrawMethodChange(TObject *Sender);
	void __fastcall lstHistoryClick(TObject *Sender);

private:	// User declarations
	WorkSpace * work;
	vector<Matrix*> historyMatrix;
	vector<Matrix> stateMatrix;
public:		// User declarations
	__fastcall TformProperties(TComponent* Owner);
	TformProperties(TComponent* Owner, Object * obj);
	void showMatrixOperation(int idTransf, int idPoint);
};
//---------------------------------------------------------------------------
extern PACKAGE TformProperties *formProperties;
//---------------------------------------------------------------------------
#endif
