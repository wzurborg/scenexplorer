//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Main.cpp", MainForm);
USEFORM("Kampagnen.cpp", KampForm);
USEFORM("FreiFormCpp.cpp", FreiForm);
USEFORM("WareFormCpp.cpp", WareForm);
USEFORM("WarenAuswahlCpp.cpp", WarenAuswahl);
USEFORM("SchiffWarenCpp.cpp", SchiffWaren);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->Title = "Sir Henry's 1602 Szenario Explorer";
         Application->CreateForm(__classid(TMainForm), &MainForm);
         Application->CreateForm(__classid(TKampForm), &KampForm);
         Application->CreateForm(__classid(TFreiForm), &FreiForm);
         Application->CreateForm(__classid(TWareForm), &WareForm);
         Application->CreateForm(__classid(TWarenAuswahl), &WarenAuswahl);
         Application->CreateForm(__classid(TSchiffWaren), &SchiffWaren);
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
