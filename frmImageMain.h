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
#include <Vcl.ButtonGroup.hpp>
#include <Vcl.CategoryButtons.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <iostream>
#include <fstream>

class TformImageMain : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel5;
	TCategoryButtons *CategoryButtons1;
	TActionManager *acttions;
	TAction *actHistEqualize;
	TPanel *Panel2;
	TPanel *hist1;
	TPanel *originalHistCanvas;
	TPanel *Panel3;
	TPanel *transformHistCanvas;
	TOpenDialog *openDialog;
	TPanel *pnlImages;
	TPanel *transformImgCanvas;
	TPanel *originalImgCanvas;
	TPanel *Panel4;
	TStringGrid *gridImage2;
	TStringGrid *gridImage1;
	TAction *actHighBoost;
	TAction *actMeanFilter;
	TAction *actMedianFilter;
	TAction *actHighPassFilter;
	TAction *actRobertsFilter;
	TAction *actRobertsCrossedFilter;
	TAction *actSobelFilter;
	TAction *actPrewitt;
	TRadioGroup *rdgElemento;
	void __fastcall actHistEqualizeExecute(TObject *Sender);
	void __fastcall originalImgCanvasMouseEnter(TObject *Sender);
	void __fastcall originalImgCanvasMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall originalImgCanvasClick(TObject *Sender);
	void __fastcall actHighBoostExecute(TObject *Sender);
	void __fastcall actMeanFilterExecute(TObject *Sender);
	void __fastcall actMedianFilterExecute(TObject *Sender);
	void __fastcall actHighPassFilterExecute(TObject *Sender);
	void __fastcall actRobertsFilterExecute(TObject *Sender);
	void __fastcall actRobertsCrossedFilterExecute(TObject *Sender);
	void __fastcall actSobelFilterExecute(TObject *Sender);
	void __fastcall actPrewittExecute(TObject *Sender);


private:	// User declarations
	void showHistogram(ImageGS * image, TPanel * panel);
	bool loadOriginalImage();
	bool canUpdateGrid;
	Image * imgOriginal;
    Image * imgTransformed;
public:		// User declarations
	__fastcall TformImageMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformImageMain *formImageMain;
//---------------------------------------------------------------------------
#endif
