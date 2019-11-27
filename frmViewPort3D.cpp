//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmViewPort3D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformViewPort3D *formViewPort3D;
//---------------------------------------------------------------------------
__fastcall TformViewPort3D::TformViewPort3D(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TformViewPort3D::TformViewPort3D(TComponent* Owner, Object * obj) : TForm(Owner){
	work = new WorkSpace(150, desktop->Width, desktop->Height, GetDC(desktop->Handle));
	work->setDrawGrid(false);
	work->setDrawAxis(false);
	work->setMode(MODE_3D);
	work->setHdcFront(GetDC(front->Handle));
	work->setHdcSide(GetDC(side->Handle));
	work->setHdcTop(GetDC(top->Handle));

	work->addObject(obj);

}
//---------------------------------------------------------------------------

void __fastcall TformViewPort3D::timerTimer(TObject *Sender){
	timer->Enabled = false;
	work->update();
}
//---------------------------------------------------------------------------

