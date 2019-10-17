//---------------------------------------------------------------------------

#ifndef frmParamH
#define frmParamH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "objects/point2D.h"
#include "objects/object.h"

enum ParamType{ptTranslate, ptScale, ptRotate, ptShear, ptReflect};

//---------------------------------------------------------------------------
class TformParam : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *btnCancel;
	TButton *btnOk;
	TRadioGroup *rdgReference;
	TGroupBox *grpRefPoint;
	TPanel *pnlParams;
	TLabeledEdit *edtParamX;
	TLabeledEdit *edtParamY;
	TLabeledEdit *edtX;
	TLabeledEdit *edtY;
	TLabeledEdit *edtParamZ;
	TLabeledEdit *edtZ;
	void __fastcall rdgReferenceClick(TObject *Sender);
	void __fastcall edtParamXKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall fixValues(TObject *Sender);
	void __fastcall btnOkClick(TObject *Sender);
private:	// User declarations
	Object * obj;
	ParamType paramType;
public:		// User declarations
	__fastcall TformParam(TComponent* Owner);
	TformParam(TComponent* Owner, Object * obj, ParamType paramType);

	Point2D * getReference(Object * obj);
};
//---------------------------------------------------------------------------
extern PACKAGE TformParam *formParam;
//---------------------------------------------------------------------------
#endif
