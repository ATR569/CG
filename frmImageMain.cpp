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
	ifstream file("D:\\projetos\\projetos c++\\cg\\example\\airplane.pgm");

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
	ImageGS * image = new ImageGS(10, 10, data);
	HDC hdc = GetDC(Panel1->Handle);
	drawImageGS(hdc, 10, 10, data);

}
//---------------------------------------------------------------------------
