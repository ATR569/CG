//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("frmMain.cpp", formMain);
USEFORM("frmImageMain.cpp", formImageMain);
USEFORM("frmCompose.cpp", formCompose);
USEFORM("frmViewPort3D.cpp", formViewPort3D);
USEFORM("frmProperties.cpp", formProperties);
USEFORM("frmParam.cpp", formParam);
USEFORM("frmCredits.cpp", formCredits);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Sapphire Kamri");
		Application->CreateForm(__classid(TformMain), &formMain);
		Application->CreateForm(__classid(TformImageMain), &formImageMain);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
