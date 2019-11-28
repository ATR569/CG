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
	ifstream file("C:\\Users\\Agnsoft\\Desktop\\CG\\example\\lena.pgm");

	string str;

	file >> str;

	int w, h;

	file >> w >> h;

	file >> str;

	std::vector<std::vector<int> > data;

	for (int i = 0; i < h; i++){
		data.push_back(vector<int>());
		for (int j= 0; j < w; j++){
			int l;
			file >> l;
			data[i].push_back(l);
		}
	}

	file.close();
	ImageGS * image = new ImageGS(10, 180, data, 256);
	HDC hdc = GetDC(Panel1->Handle);
	drawImageGS(hdc, 10, 20, data);

	vector<double> histogram = image->getHistogramValues();

	HDC dc = GetDC(Panel2->Handle);

	double maxProb = 0;
	for (int i = 0; i < histogram.size(); i++)
		if (histogram[i] > maxProb) {
			maxProb = histogram[i];
		}

	double multip = 120/maxProb;

	for (int i = 0; i < histogram.size(); i++) {
		MoveToEx(dc, i, 130, NULL);
		int value = (int)round(multip*histogram[i]);
		LineTo(dc, i, 130-value);
	}

	ShowMessage("Equalizando o histograma...");

	image->equalizeHistogram();
	data = image->getData();
	drawImageGS(hdc, 10, 300, data);

	histogram = image->getHistogramValues();

	dc = GetDC(Panel4->Handle);

	maxProb = 0;
	for (int i = 0; i < histogram.size(); i++)
		if (histogram[i] > maxProb) {
			maxProb = histogram[i];
		}

	multip = 120/maxProb;

	for (int i = 0; i < histogram.size(); i++) {
		MoveToEx(dc, i, 130, NULL);
		int value = (int)round(multip*histogram[i]);
		LineTo(dc, i, 130-value);
	}
}
//---------------------------------------------------------------------------

