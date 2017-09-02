//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FreiFormCpp.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFreiForm *FreiForm;
//---------------------------------------------------------------------------
__fastcall TFreiForm::TFreiForm(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFreiForm::CloseButtonClick(TObject *Sender)
{
    Close();    
}
//---------------------------------------------------------------------------
void __fastcall TFreiForm::ControlChanged(TObject *Sender)
{
    MainForm->controlChanged(Sender);    
}
//---------------------------------------------------------------------------

