#include <vcl.h>
#include <vector>
#pragma hdrstop

#include "frmMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TformMain * formMain;

//---------------------------------------------------------------------------
__fastcall TformMain::TformMain(TComponent* Owner) : TForm(Owner){
	work = new WorkSpace(DEFAULT_SCR_SIZE, desktop->Width, desktop->Height, GetDC(desktop->Handle));
	work->setDrawGrid(false);
    work->setMode(MODE_2D);

	this->machine = new StateMachine(this);
}
//---------------------------------------------------------------------------

void __fastcall TformMain::FormDestroy(TObject *Sender){
	work->clearObjects();
	free(work);
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actPolygonExecute(TObject *Sender){
	machine->performDrawPolygonClick();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actMoveExecute(TObject *Sender)
{
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		Object * obj = work->getObject(id);
		TformParam * param = new TformParam(this, work, ptTranslate);

		if (param->ShowModal() == mrOk){
			Object * obj = work->getObject(id);

			double tx = StrToFloat(param->edtParamX->Text);
			double ty = StrToFloat(param->edtParamY->Text);

			if (work->getMode() == MODE_2D) {
				work->translateObject(obj, tx, ty);
			}else{
				double tz = StrToFloat(param->edtParamZ->Text);
				work->translateObject3D(obj, tx, ty, tz);
			}

			updateTreeView(treeObjects->Selected, obj);
		}

		param->Release();
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actScaleExecute(TObject *Sender)
{
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		TformParam * param = new TformParam(this, work, ptScale);

		if (param->ShowModal() == mrOk){
			Object * obj = work->getObject(id);

			double sx = StrToFloat(param->edtParamX->Text);
			double sy = StrToFloat(param->edtParamY->Text);

			if (work->getMode() == MODE_2D) {
				Point2D * ref = param->getReference(obj);
				work->scaleObject(obj, ref, sx, sy);
			}else{
				Point3D * ref = (Point3D*)param->getReference(obj);
				double sz = StrToFloat(param->edtParamZ->Text);
				work->scaleObject3DRelativePoint(obj, ref, sx, sy, sz);
			}

			updateTreeView(treeObjects->Selected, obj);
		}

		param->Release();
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::timerTimer(TObject *Sender)
{
	timer->Enabled = false;
	work->update();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::desktopResize(TObject *Sender)
{
	if (work != NULL){
		work->setCanvasSize(desktop->Width, desktop->Height);
		timer->Enabled = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::treeObjectsClick(TObject *Sender)
{
	int id = treeObjects->Selected->Index;
}
//---------------------------------------------------------------------------


void __fastcall TformMain::desktopMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
	Point2D * p = work->CoordScrToUser(new Point2D(X,Y));
	lblScrX->Caption = "X: " + IntToStr(X);
	lblScrY->Caption = "Y: " + IntToStr(Y);

	UnicodeString s1 = "X: " + FormatFloat("#,###0.000", p->X);
	UnicodeString s2 = "Y: " + FormatFloat("#,###0.000", p->Y);
	lblUserX->Caption = s1;
	lblUserY->Caption = s2;

	desktop->Hint = s1 + "\n" + s2;
}
//---------------------------------------------------------------------------

void __fastcall TformMain::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight,
		  bool &Resize)
{
	if (NewWidth < 500 || NewHeight < 500) {
		Resize = false;
	}else{
		desktop->Margins->Left = 30 - (NewWidth%2 == 0);
		desktop->Margins->Top = 30 - (NewHeight%2 == 0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actLineExecute(TObject *Sender){
	machine->performDrawLineClick();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actCircleExecute(TObject *Sender){
	machine->performDrawCircleClick();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::desktopDblClick(TObject *Sender){
	machine->performDblClick();
}
//---------------------------------------------------------------------------


void __fastcall TformMain::desktopMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	this->machine->performClick(X, Y);
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actRotateExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		TformParam * param = new TformParam(this, work, ptRotate);

		if (param->ShowModal() == mrOk){
			Object * obj = work->getObject(id);

			double theta = StrToFloat(param->edtParamX->Text);
			
			if(work->getMode() == MODE_2D){
				Point2D * ref = param->getReference(obj);
				work->rotateObject(obj, ref, theta);
			}else{
				Point3D * ref = (Point3D*)param->getReference(obj);
				int axis = param->rdgReference->ItemIndex;
				work->rotateObject3D(obj, axis, theta);
			}

			updateTreeView(treeObjects->Selected, obj);
		}

		param->Release();
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::chkShowAxisClick(TObject *Sender){
	work->setDrawAxis(chkShowAxis->Checked);
	work->setDrawGrid(chkShowGrid->Checked);
	work->setDrawPoints(chkShowPoints->Checked);
	desktop->Repaint();
	work->update();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actPropertiesExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		Object * obj = work->getObject(id);
		Matrix * stateMatrix = new Matrix(obj->getStateMatrix()->getData());

		if (work->getMode() == MODE_2D) {
			TformProperties * properties = new TformProperties(this, obj);

			if (properties->ShowModal() == mrOk){
				int idTransf = properties->lstHistory->ItemIndex;
				obj->cropHistory(idTransf+1);
			}else{
				obj->setStateMatrix(stateMatrix);
			}

			properties->Release();
			desktop->Repaint();
			work->update();
		}else{
			TformViewPort3D * viewPort = new TformViewPort3D(this, obj);

            viewPort->ShowModal();
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actShearExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		TformParam * param = new TformParam(this, work, ptShear);

		if (param->ShowModal() == mrOk){
			Object * obj = work->getObject(id);

			double shx = StrToFloat(param->edtParamX->Text);
			double shy = StrToFloat(param->edtParamY->Text);
			
			if(work->getMode() == MODE_2D){
				Point2D * ref = param->getReference(obj);
				work->shearObject(obj, ref, shx, shy);
			}else{
				double shz = StrToFloat(param->edtParamZ->Text);
				Point3D * ref = (Point3D*)param->getReference(obj);
				int axis = param->rdgReference->ItemIndex;

				if(axis == 0){
					work->shearObject3DAroundX(obj, ref, shy, shz);
				}else if(axis == 1){
					work->shearObject3DAroundY(obj, ref, shx, shz);
				}else{
					work->shearObject3DAroundZ(obj, ref, shx, shy);
				} 
			}

			updateTreeView(treeObjects->Selected, obj);
		}

		param->Release();
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actReflectExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		TformParam * param = new TformParam(this, work, ptReflect);

		if (param->ShowModal() == mrOk){
			Object * obj = work->getObject(id);

			if(work->getMode() == MODE_2D){
				int axis = param->rdgReference->ItemIndex;
				if (axis == 2) {
					double m = StrToFloat(param->edtX->Text);
					double b = StrToFloat(param->edtY->Text);

					work->reflectObject(obj, m, b);
				}else{
					work->reflectObject(obj, axis);
				}
			}else{
				int plan = param->rdgReference->ItemIndex;
				work->refletObject3DRelativePlan(obj, plan);
			}	

			updateTreeView(treeObjects->Selected, obj);
		}

		param->Release();
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actRemoveExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		Object * obj = work->getObject(id);
		String msg = "Deseja realmente remover o objeto " + obj->getName() + "?";

		if (MessageDlg(msg, mtConfirmation, mbYesNo, 0, mbNo) == mrYes) {
			work->deleteObject(id);
			treeObjects->Selected->Delete();
		}

	}
}
//---------------------------------------------------------------------------
//  Centraliza o objeto em relação ao sistema de eixos ortogonais
void __fastcall TformMain::actCentralizeExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		Object * obj = work->getObject(id);

		BasePoint * ref = obj->getReference();  //  Centro do objeto
		if (work->getMode() == MODE_2D) {
			work->translateObject(obj, -((Point2D*)ref)->X, -((Point2D*)ref)->Y);
		}else{
			work->translateObject3D(obj, -((Point3D*)ref)->X, -((Point3D*)ref)->Y, -((Point3D*)ref)->Z);
		}

		updateTreeView(treeObjects->Selected, obj);
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actObjectCancelExecute(TObject *Sender)
{
	machine->performObjectCancelClick();
}
//---------------------------------------------------------------------------


void __fastcall TformMain::actMode2DExecute(TObject *Sender){
	if (((TAction*)Sender)->Checked) {
		if (MessageDlg("Deseja Mudar o modo para o modo 2D?\nIsso removerá todos os objetos criados!", mtConfirmation, mbYesNo, 0, mbNo) == mrYes) {
			desktop->Repaint();
			treeObjects->Items->Clear();
			work->clearObjects();
			work->setMode(MODE_2D);

			machine->setState(new StateNone(work->getMode()));

			action_manager->Actions[15]->Checked = false;
		}else{
			action_manager->Actions[14]->Checked = false;
		}
	}else{
		action_manager->Actions[14]->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actMode3DExecute(TObject *Sender){
	if (((TAction*)Sender)->Checked) {
		if (MessageDlg("Deseja Mudar o modo para o modo 3D?\nIsso removerá todos os objetos criados!", mtConfirmation, mbYesNo, 0, mbNo) == mrYes) {
			desktop->Repaint();
			treeObjects->Items->Clear();
			work->clearObjects();
			work->setMode(MODE_3D);
			machine->setState(new StateNone(work->getMode()));

			action_manager->Actions[14]->Checked = false;
		}else{
			action_manager->Actions[15]->Checked = false;
		}
	}else{
		action_manager->Actions[15]->Checked = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actModeImageExecute(TObject *Sender){
/*	if (((TAction*)Sender)->Checked) {
		if (MessageDlg("Deseja Mudar o modo para o modo Imagem?\nIsso removerá todos os objetos criados!", mtConfirmation, mbYesNo, 0, mbNo) == mrYes) {
			desktop->Repaint();
			treeObjects->Items->Clear();

			work->clearObjects();
			work->setMode(MODE_2D);
			action_manager->Actions[14]->Checked = false;
			action_manager->Actions[15]->Checked = false;
		}else{
			action_manager->Actions[16]->Checked = false;
		}
	}else{
		action_manager->Actions[16]->Checked = true;
	}
 */
    formImageMain->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actExitExecute(TObject *Sender){
	Application->Terminate();
}
//---------------------------------------------------------------------------

/**
 *  Atualiza o objeto na árvore de objetos
 */
void TformMain::updateTreeView(TTreeNode * node, Object * obj){
	//  Vetor com as strings que definem o objeto
	vector<String> strings = obj->toStrings();

	//  Primeira string é o nome do objeto
	node->Text = strings[0];

	//  Pontos do objeto
	TTreeNode * child = node->getFirstChild();
	for	(int i = 1; i < strings.size(); i++){
		child->Text = strings[i];
        child = node->GetNextChild(child);  //  Próximo subitem
	}
}

/**
 *  Cria um item na árvore de objetos
 */
TTreeNode * TformMain::addTreeItem(int numChilds, int imageIndex){
	//  Cria o item na árvore
	TTreeNode * item = treeObjects->Items->Add(NULL, "");
	item->ImageIndex = imageIndex;
	item->SelectedIndex = imageIndex;

    //  Cria os subitens da árvore
	for (int i = 0; i < numChilds; i++) {
		TTreeNode * sub = treeObjects->Items->AddChild(item, "");
		sub->ImageIndex = -1;
		sub->SelectedIndex = -1;
	}

    return item;
}

void __fastcall TformMain::treeObjectsDblClick(TObject *Sender)
{
    actPropertiesExecute(Sender);
}

void __fastcall TformMain::Timer1Timer(TObject *Sender)
{
	Object * obj = work->getObject(treeObjects->Selected->Index);
	work->rotateObject3D(obj, 1, 10);
}
//---------------------------------------------------------------------------


void __fastcall TformMain::actElipseExecute(TObject *Sender)
{
	machine->performDrawEllipseClick();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actComposedExecute(TObject *Sender)
{
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		Object * obj = work->getObject(id);
		TformCompose * compose = new TformCompose(this, this->work, obj);

		if (compose->ShowModal() == mrOk){
			Object * obj = work->getObject(id);

			work->apply(obj, compose->getStateMatrix(), "Transformação composta");

			updateTreeView(treeObjects->Selected, obj);
		}

		compose->Release();
	}
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actCubeExecute(TObject *Sender){
	TformParam * param = new TformParam(this, work, ptNewCube);

	if (param->ShowModal() == mrOk){
		double X = StrToFloat(param->edtX->Text);
		double Y = StrToFloat(param->edtY->Text);
		double Z = StrToFloat(param->edtZ->Text);
		double edge = StrToFloat(param->edtParamX->Text);

		Object * obj = getCube(new Point3D(X,Y,Z), edge, DM_BRESENHAN);

		work->addObject(obj);

		TTreeNode * item = addTreeItem(8, 15);
		updateTreeView(item, obj);
	}

    param->Release();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actPrismExecute(TObject *Sender){
	TformParam * param = new TformParam(this, work, ptNewPolyedron);

	if (param->ShowModal() == mrOk){
		double X = StrToFloat(param->edtX->Text);
		double Y = StrToFloat(param->edtY->Text);
		double Z = StrToFloat(param->edtZ->Text);
		double edge = StrToFloat(param->edtParamX->Text);
		double height = StrToFloat(param->edtParamY->Text);

		Object * obj = getPrism(new Point3D(X,Y,Z), edge, height, DM_BRESENHAN);

		work->addObject(obj);
		TTreeNode * item = addTreeItem(6, 18);
		updateTreeView(item, obj);
	}

    param->Release();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actPyramidExecute(TObject *Sender){
	TformParam * param = new TformParam(this, work, ptNewPolyedron);

	if (param->ShowModal() == mrOk){
		double X = StrToFloat(param->edtX->Text);
		double Y = StrToFloat(param->edtY->Text);
		double Z = StrToFloat(param->edtZ->Text);
		double edge = StrToFloat(param->edtParamX->Text);
		double height = StrToFloat(param->edtParamY->Text);

		Object * obj = getPyramid(new Point3D(X,Y,Z), edge, height, DM_BRESENHAN);

        work->addObject(obj);
		TTreeNode * item = addTreeItem(5, 16);
		updateTreeView(item, obj);
	}

    param->Release();
}
//---------------------------------------------------------------------------

void __fastcall TformMain::actAnimate3DExecute(TObject *Sender){
	int id = treeObjects->Selected->Index;

	if (id >= 0) {
		Timer1->Enabled = !Timer1->Enabled;
	}else{
		ShowMessage("Não há um objeto selecionado!");
    }
}
//---------------------------------------------------------------------------

