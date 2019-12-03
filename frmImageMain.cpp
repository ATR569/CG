//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmImageMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformImageMain *formImageMain;
//---------------------------------------------------------------------------
__fastcall TformImageMain::TformImageMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TformImageMain::Button1Click(TObject *Sender){

	ImageGS * image = new ImageGS("D:/Projetos/Projetos c++/CG/example/lena.pgm");
	vector<double> histogram1 = image->getHistogramValues();
	image->draw(GetDC(Panel1->Handle), 10, 20);

	image->equalizeHistogram();
	vector<double> histogram2 = image->getHistogramValues();
	image->draw(GetDC(Panel1->Handle), 10, 300);


	double maxProb = 0;
	for (int i = 0; i < histogram1.size(); i++)
		if (histogram1[i] > maxProb) {
			maxProb = histogram1[i];
		}

	double multip = 120/maxProb;

	HDC dc = GetDC(Panel2->Handle);
	for (int i = 0; i < histogram1.size(); i++) {
		MoveToEx(dc, i, 130, NULL);
		int value = (int)round(multip*histogram1[i]);
		LineTo(dc, i, 130-value);
	}

	dc = GetDC(Panel4->Handle);

	maxProb = 0;
	for (int i = 0; i < histogram2.size(); i++)
		if (histogram2[i] > maxProb) {
			maxProb = histogram2[i];
		}

	multip = 120/maxProb;

	for (int i = 0; i < histogram2.size(); i++) {
		MoveToEx(dc, i, 130, NULL);
		int value = (int)round(multip*histogram2[i]);
		LineTo(dc, i, 130-value);
	}

}
//---------------------------------------------------------------------------

