//---------------------------------------------------------------------------

#ifndef frmMainH
#define frmMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ActnMenus.hpp>
//---------------------------------------------------------------------------

#include "cglib.h"
#include <Vcl.ColorGrd.hpp>
#include <Vcl.Buttons.hpp>
#include "frmParam.h"
#include <Vcl.Menus.hpp>
#include "frmProperties.h"

const int DEFAULT_SCR_SIZE = 300;

class TformMain : public TForm {
__published:	// IDE-managed Components
	TImageList *imagelist48;
	TActionManager *action_manager;
	TAction *actCircle;
	TAction *actLine;
	TAction *actPolygon;
	TAction *actRotate;
	TAction *actMove;
	TAction *actScale;
	TAction *actShear;
	TAction *actReflect;
	TAction *actComposed;
	TToolBar *barTools;
	TToolButton *btnLine;
	TToolButton *btnCircle;
	TToolButton *ToolButton3;
	TStatusBar *statusbar;
	TCoolBar *coolTools2D;
	TPanel *pnlLayout;
	TActionMainMenuBar *mainMenu;
	TImageList *imagelist16;
	TImageList *imagelist16ds;
	TCoolBar *barObjects;
	TPanel *desktop;
	TImageList *Imagelist48ds;
	TTimer *timer;
	TPanel *pnlCoord;
	TLabel *lblUserX;
	TLabel *lblUserY;
	TLabel *lblScrX;
	TLabel *lblScrY;
	TLabel *Label1;
	TLabel *Label2;
	TToolBar *barTransformations;
	TToolButton *btnTranslate;
	TToolButton *btnScale;
	TToolButton *btnRotate;
	TToolButton *btnShear;
	TToolButton *btnReflect;
	TToolButton *btnCompose;
	TAction *actProperties;
	TCheckBox *chkShowGrid;
	TCheckBox *chkShowPoints;
	TCheckBox *chkShowAxis;
	TCoolBar *coolOptions;
	TPanel *pnlOptions;
	TActionToolBar *barProperties;
	TPanel *Panel1;
	TTreeView *treeObjects;
	TPanel *Panel2;
	TPanel *Panel3;
	TAction *actRemove;
	TAction *actClearScreen;
	TImageList *imagelist24;
	TImageList *imagelist24ds;
	TAction *actCentralize;
	TAction *actObjectCancel;
	TSpeedButton *btnObjectCancel;
	TBevel *Bevel1;
	TButton *Button1;
	TAction *actMode2D;
	TAction *actMode3D;
	TAction *actModeImage;
	TAction *actPolyedron;
	TAction *actCube;
	TAction *actPrism;
	TAction *actPyramid;
	TAction *actExit;
	void __fastcall actPolygonExecute(TObject *Sender);
	void __fastcall actMoveExecute(TObject *Sender);
	void __fastcall actScaleExecute(TObject *Sender);
	void __fastcall timerTimer(TObject *Sender);
	void __fastcall desktopResize(TObject *Sender);
	void __fastcall treeObjectsClick(TObject *Sender);
	void __fastcall desktopMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall actLineExecute(TObject *Sender);
	void __fastcall FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize);
	void __fastcall actCircleExecute(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall desktopDblClick(TObject *Sender);
	void __fastcall desktopMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall actRotateExecute(TObject *Sender);
	void __fastcall chkShowAxisClick(TObject *Sender);
	void __fastcall actPropertiesExecute(TObject *Sender);
	void __fastcall actShearExecute(TObject *Sender);
	void __fastcall actReflectExecute(TObject *Sender);
	void __fastcall actRemoveExecute(TObject *Sender);
	void __fastcall actCentralizeExecute(TObject *Sender);
	void __fastcall actObjectCancelExecute(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall actMode2DExecute(TObject *Sender);
	void __fastcall actMode3DExecute(TObject *Sender);
	void __fastcall actModeImageExecute(TObject *Sender);
	void __fastcall actExitExecute(TObject *Sender);

private:	// User declarations
	StateMachine * machine;
public:		// User declarations
	std::vector<Point2D*> pointBuffer;
	WorkSpace * work;
	__fastcall TformMain(TComponent* Owner);

	void updateTreeView(TTreeNode * node, Object * obj);
	TTreeNode * addTreeItem(int numChilds, int imageIndex);

	TformParam * getParamWindow(ParamType paramType);
};
//---------------------------------------------------------------------------
extern PACKAGE TformMain *formMain;
//---------------------------------------------------------------------------
#endif
