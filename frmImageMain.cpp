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
	rdgElemento->Items->Add("|1 1 1|\n|1 1 1|\n|1 1 1|");
	rdgElemento->Items->Add("|0 1 0|\n|1 1 1|\n|0 1 0|");
    rdgElemento->ItemIndex = 0;
}
//---------------------------------------------------------------------------

bool TformImageMain::loadOriginalImage(){
	if (openDialog->Execute()){
		imgOriginal = new ImageGS(openDialog->FileName);
		imgOriginal->draw(GetDC(originalImgCanvas->Handle), 0,0);
		showHistogram((ImageGS*)imgOriginal, originalHistCanvas);

		imgTransformed = new ImageGS(imgOriginal->getData(), ((ImageGS*)imgOriginal)->getColorDepth());

		return true;
	}else{
		return false;
	}
}
//---------------------------------------------------------------------------
void TformImageMain::showHistogram(ImageGS * image, TPanel * panel){
	vector<double> histValues = image->getHistogramValues();
	panel->Repaint();

	double maxProb = 0;
	for (int i = 0; i < histValues.size(); i++)
		if (histValues[i] > maxProb)
			maxProb = histValues[i];

	int height = panel->Height;
	double multip = (height - 10)/maxProb;
	HDC dc = GetDC(panel->Handle);

	for (int i = 0; i < histValues.size(); i++) {
		MoveToEx(dc, i, height, NULL);
		int value = (int)round(multip*histValues[i]);
		LineTo(dc, i, height-value);
	}
}

void __fastcall TformImageMain::originalImgCanvasMouseEnter(TObject *Sender){
	canUpdateGrid = true;
}
//---------------------------------------------------------------------------

void __fastcall TformImageMain::originalImgCanvasMouseMove(TObject *Sender, TShiftState Shift,
		  int X, int Y)
{
	if (imgOriginal != NULL && imgTransformed != NULL && canUpdateGrid) {
		int limit = gridImage1->RowCount / 2;
		for (int i = -limit; i <= limit; i++) {
			for (int j = -limit; j <= limit; j++) {
				if (imgOriginal->isValid(X+i,Y+j)) {
					gridImage1->Cells[i+limit][j+limit] = imgOriginal->getPixel(Y+j, X+i);
					gridImage2->Cells[i+limit][j+limit] = imgTransformed->getPixel(Y+j, X+i);
				}else{
					gridImage1->Cells[i+limit][j+limit] = 0;
					gridImage2->Cells[i+limit][j+limit] = 0;
				}
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TformImageMain::originalImgCanvasClick(TObject *Sender){
	canUpdateGrid = !canUpdateGrid;
}
//---------------------------------------------------------------------------

void __fastcall TformImageMain::actHistEqualizeExecute(TObject *Sender) {
	if (loadOriginalImage()){
		((ImageGS*)imgTransformed)->equalizeHistogram();

		imgTransformed->draw(GetDC(transformImgCanvas->Handle), 0,0);
		showHistogram((ImageGS*)imgTransformed, transformHistCanvas);
	}
}
//---------------------------------------------------------------------------

void __fastcall TformImageMain::actHighBoostExecute(TObject *Sender){
	if (loadOriginalImage()){
		HighBoostFilter((ImageGS*)imgTransformed, 1.3);

		imgTransformed->draw(GetDC(transformImgCanvas->Handle), 0,0);
		showHistogram((ImageGS*)imgTransformed, transformHistCanvas);
	}
}
//---------------------------------------------------------------------------

void __fastcall TformImageMain::actMeanFilterExecute(TObject *Sender){
	if (loadOriginalImage()){
		meanFilter((ImageGS*)imgTransformed);

		imgTransformed->draw(GetDC(transformImgCanvas->Handle), 0,0);
		showHistogram((ImageGS*)imgTransformed, transformHistCanvas);
	}
}
//---------------------------------------------------------------------------



void __fastcall TformImageMain::actMedianFilterExecute(TObject *Sender){
	if (loadOriginalImage()){
		medianFilter((ImageGS*)imgTransformed);

		imgTransformed->draw(GetDC(transformImgCanvas->Handle), 0,0);
		showHistogram((ImageGS*)imgTransformed, transformHistCanvas);
	}
}
//---------------------------------------------------------------------------



void __fastcall TformImageMain::actHighPassFilterExecute(TObject *Sender){
	if (loadOriginalImage()){
		HighPassFilter((ImageGS*)imgTransformed);

		imgTransformed->draw(GetDC(transformImgCanvas->Handle), 0,0);
		showHistogram((ImageGS*)imgTransformed, transformHistCanvas);
	}
}
//---------------------------------------------------------------------------

void __fastcall TformImageMain::actRobertsFilterExecute(TObject *Sender){
	if (loadOriginalImage()){
		RobertsFilter((ImageGS*)imgTransformed);

		imgTransformed->draw(GetDC(transformImgCanvas->Handle), 0,0);
		showHistogram((ImageGS*)imgTransformed, transformHistCanvas);
	}
}
//---------------------------------------------------------------------------

void __fastcall TformImageMain::actRobertsCrossedFilterExecute(TObject *Sender){
	if (loadOriginalImage()){
		RobertsCrossedFilter((ImageGS*)imgTransformed);

		imgTransformed->draw(GetDC(transformImgCanvas->Handle), 0,0);
		showHistogram((ImageGS*)imgTransformed, transformHistCanvas);
	}
}
//---------------------------------------------------------------------------

void __fastcall TformImageMain::actSobelFilterExecute(TObject *Sender){
	if (loadOriginalImage()){
		SobelFilter((ImageGS*)imgTransformed);

		imgTransformed->draw(GetDC(transformImgCanvas->Handle), 0,0);
		showHistogram((ImageGS*)imgTransformed, transformHistCanvas);
	}
}
//---------------------------------------------------------------------------

void __fastcall TformImageMain::actPrewittExecute(TObject *Sender){
	if (loadOriginalImage()){
		PrewittFilter((ImageGS*)imgTransformed);

		imgTransformed->draw(GetDC(transformImgCanvas->Handle), 0,0);
		showHistogram((ImageGS*)imgTransformed, transformHistCanvas);
	}
}
//---------------------------------------------------------------------------

void __fastcall TformImageMain::actArnoldsCatTransformExecute(TObject *Sender){
	if (loadOriginalImage()){
		showHistogram((ImageGS*)imgTransformed, transformHistCanvas);
		int iter = arnoldsCatTransform(GetDC(transformImgCanvas->Handle), 0, 0, (ImageGS*)imgTransformed);

        ShowMessage("Transformada do Gato de Arnold: " + IntToStr(iter) + " iterações.");
	}
}
//---------------------------------------------------------------------------

