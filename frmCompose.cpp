//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmCompose.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TformCompose *formCompose;
//---------------------------------------------------------------------------
__fastcall TformCompose::TformCompose(TComponent* Owner): TForm(Owner){
    this->Owner = Owner;
}
//---------------------------------------------------------------------------
__fastcall TformCompose::TformCompose(TComponent* Owner, WorkSpace * work, Object * obj): TForm(Owner){
	this->work = work;
	this->Owner = Owner;
	this->obj = obj;
}
//---------------------------------------------------------------------------

Matrix * TformCompose::getStateMatrix(){
	list<Transformation>::iterator it;
	Matrix * stateMatrix;

	if (work->getMode() == MODE_2D) {
		stateMatrix = getIdentityMatrix();
	}else{
		stateMatrix = getIdentity3DMatrix();
	}

	for (it = history.begin(); it != history.end(); it++) {
		stateMatrix->assign((*(it->getMatrix())) * (*stateMatrix));
	}

	return stateMatrix;
}

void __fastcall TformCompose::btnTranslateClick(TObject *Sender){
	TformParam * param = new TformParam(this, this->work, ptTranslate);

	if (param->ShowModal() == mrOk){
		Matrix * M;
		String caption;

		double tx = StrToFloat(param->edtParamX->Text);
		double ty = StrToFloat(param->edtParamY->Text);

		if (work->getMode() == MODE_2D) {
			M = getTranslationMatrix(tx, ty);
			caption = "Translação(" + FormatFloat("0.000", tx) + ", " + FormatFloat("0.000", ty) + ")";
		}else{
			double tz = StrToFloat(param->edtParamZ->Text);
			M = getTranslation3DMatrix(tx, ty, tz);
			caption = "Translação(" + FormatFloat("0.000", tx) + ", " + FormatFloat("0.000", ty) + ", " + FormatFloat("0.000", tz) + ")";
		}

		this->history.push_back(Transformation(caption, M));

		TListItem * item = lstHistory->Items->Add();
		item->Caption = caption;
    	showMatrixOperation();
	}

	param->Release();
}
//---------------------------------------------------------------------------

void __fastcall TformCompose::btnScaleClick(TObject *Sender){
	TformParam * param = new TformParam(this, this->work, ptScale);

	if (param->ShowModal() == mrOk){
		Matrix * M;
		String caption;

		double sx = StrToFloat(param->edtParamX->Text);
		double sy = StrToFloat(param->edtParamY->Text);

		if (work->getMode() == MODE_2D) {
			M = getScaleMatrix(sx, sy, param->getReference(this->obj));
			caption = "Escala(" + FormatFloat("0.000", sx) + ", " + FormatFloat("0.000", sy) + ")";
		}else{
			double sz = StrToFloat(param->edtParamZ->Text);
			M = getScale3DMatrix(sx, sy, sz, (Point3D*)param->getReference(this->obj));
			caption = "Escala(" + FormatFloat("0.000", sx) + ", " + FormatFloat("0.000", sy) + ", " + FormatFloat("0.000", sz) + ")";
		}

		this->history.push_back(Transformation(caption, M));

		TListItem * item = lstHistory->Items->Add();
		item->Caption = caption;
		showMatrixOperation();
	}

	param->Release();
}
//---------------------------------------------------------------------------


void __fastcall TformCompose::btnRotateClick(TObject *Sender) {
	TformParam * param = new TformParam(this, this->work, ptRotate);

	if (param->ShowModal() == mrOk){
		Matrix * M;
		String caption;

		double theta = StrToFloat(param->edtParamX->Text);

		if (work->getMode() == MODE_2D) {
			M = getRotationMatrix(theta, param->getReference(this->obj));
			caption = "Rotação(" + FormatFloat("0.000", theta) + ")";
		}else{
			int axis = param->rdgReference->ItemIndex;

			M = getRotation3DMatrix(theta, axis);

			caption = "Rotação(" + FormatFloat("0.000", theta) + "em torno de ";
			if(axis == 0){
				caption += "X)";
			}else if(axis == 1){
				caption += "Y)";
			}else {
				caption += "Z)";
			}
		}

		this->history.push_back(Transformation(caption, M));

		TListItem * item = lstHistory->Items->Add();
		item->Caption = caption;
		showMatrixOperation();
	}

	param->Release();
}
//---------------------------------------------------------------------------

void __fastcall TformCompose::btnShearClick(TObject *Sender){
	TformParam * param = new TformParam(this, this->work, ptShear);

	if (param->ShowModal() == mrOk){
		Matrix * M;
		String caption;

		double shx = StrToFloat(param->edtParamX->Text);
		double shy = StrToFloat(param->edtParamY->Text);

		if (work->getMode() == MODE_2D) {
			M = getShearMatrix(shx, shy, param->getReference(this->obj));
			caption = "Cisalhamento(" + FormatFloat("0.000", shx) + ", " + FormatFloat("0.000", shy) + ")";
		}else{
			double shz = StrToFloat(param->edtParamZ->Text);
			M = getScale3DMatrix(shx, shy, shz, (Point3D*)param->getReference(this->obj));
			caption = "Cisalhamento(" + FormatFloat("0.000", shx) + ", " + FormatFloat("0.000", shy) + ", " + FormatFloat("0.000", shz) + ")";
		}

		this->history.push_back(Transformation(caption, M));

		TListItem * item = lstHistory->Items->Add();
		item->Caption = caption;
		showMatrixOperation();
	}

	param->Release();
}
//---------------------------------------------------------------------------

void __fastcall TformCompose::btnReflectClick(TObject *Sender){
	TformParam * param = new TformParam(this, this->work, ptReflect);

	if (param->ShowModal() == mrOk){
		Matrix * M;
		String caption;

		int axis = param->rdgReference->ItemIndex;

		if(work->getMode() == MODE_2D){

			if (axis == 2) {
				double m = StrToFloat(param->edtX->Text);
				double b = StrToFloat(param->edtY->Text);

				M = getReflectionMatrix(m, b);
				caption = "Reflexão(Y = " + FormatFloat("0.000", m) + "X + " + FormatFloat("0.000", b) + ")";
			}else{
				M = getReflectionMatrix(axis);
				caption = "Reflexão(Eixo ";
				if (axis == 0) {
					caption += "X)";
				}else{
					caption += "Y)";
				}
			}
		}else{
			int plan = param->rdgReference->ItemIndex;

			M = getReflectionMatrixAxis(axis);
			caption = "Reflexão(Eixo ";
			if(axis == 0){
				caption += "X)";
			}else if(axis == 1){
				caption += "Y)";
			}else {
				caption += "Z)";
			}
		}

		this->history.push_back(Transformation(caption, M));

		TListItem * item = lstHistory->Items->Add();
		item->Caption = caption;
		showMatrixOperation();
	}

	param->Release();
}
//---------------------------------------------------------------------------

void TformCompose::showMatrixOperation(){
	Matrix * stateMatrix = getStateMatrix();

	vvd data = stateMatrix->getData();
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			gridTransform->Cells[j][i] = FormatFloat("0.00", data[i][j]);
		}
	}

}

void __fastcall TformCompose::btnDeleteClick(TObject *Sender){
	int id = lstHistory->Selected->Index;

	if (id >= 0) {
		lstHistory->Selected->Delete();

		list<Transformation>::iterator it = history.begin();
		for (int i = 0; i < id; i++) {
			it++;
		}

		history.erase(it);
        showMatrixOperation();
	}
}
//---------------------------------------------------------------------------

