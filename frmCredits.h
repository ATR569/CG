//---------------------------------------------------------------------------

#ifndef frmCreditsH
#define frmCreditsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
//---------------------------------------------------------------------------
class TformCredits : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TPanel *Panel1;
	TTimer *Timer1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
    bool canClose;
public:		// User declarations
	__fastcall TformCredits(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TformCredits *formCredits;
//---------------------------------------------------------------------------
#endif
