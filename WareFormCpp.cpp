//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WareFormCpp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#include "Anno1602read.h"
#include "Main.h"

TWareForm *WareForm;
//---------------------------------------------------------------------------
__fastcall TWareForm::TWareForm(TComponent* Owner)
    : TForm(Owner)
{
    waren[2] = edWare02;
    waren[3] = edWare03;
    waren[4] = edWare04;
    waren[5] = edWare05;
    waren[6] = edWare06;
    waren[7] = edWare07;
    waren[8] = edWare08;
    waren[9] = edWare09;
    waren[10] = edWare10;
    waren[11] = edWare11;
    waren[12] = edWare12;
    waren[13] = edWare13;
    waren[14] = edWare14;
    waren[15] = edWare15;
    waren[16] = edWare16;
    waren[17] = edWare17;
    waren[18] = edWare18;
    waren[19] = edWare19;
    waren[20] = edWare20;
    waren[21] = edWare21;
    waren[22] = edWare22;
    waren[23] = edWare23;
    waren[24] = edWare24;
}
//---------------------------------------------------------------------------
void __fastcall TWareForm::btOkClick(TObject *Sender)
{
    saveWaren();
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TWareForm::btLeerenClick(TObject *Sender)
{
    // alle Waren auf null
    for(int i=2; i<25; i++)
    {
        waren[i]->Text = "0";
    }
}
//---------------------------------------------------------------------------

void __fastcall TWareForm::updateWaren()
{
    // Waren aktualisieren
    TKONTORSAVE* kontor = MainForm->getCurrSzen()->getSelectedKontor();
    TSTADTSAVE* stadt = MainForm->getCurrSzen()->getSelectedStadt();
    if(stadt != 0)
    {
        lbOwner->Caption = stadt->name;
        Graphics::TBitmap* bm = new Graphics::TBitmap;
        MainForm->WappenImages->GetBitmap(
            MainForm->comboStadtfarbe->ItemIndex, bm);
        picOwner->Picture->Bitmap = bm;
        delete bm;
    }

    if(kontor != 0)
    {
        for(int i=2; i<25; i++)
        {
            waren[i]->Text = kontor->waren[i].lager / 32;
        }
    }
}

void __fastcall TWareForm::saveWaren()
{
    TKONTORSAVE* kontor = MainForm->getCurrSzen()->getSelectedKontor();
    if(kontor != 0)
    {
        for(int i=2; i<25; i++)
        {
            kontor->waren[i].lager = waren[i]->Text.ToIntDef(0) * 32;
        }
    }
}

void __fastcall TWareForm::FormShow(TObject *Sender)
{
    updateWaren();    
}
//---------------------------------------------------------------------------



void __fastcall TWareForm::btCancelClick(TObject *Sender)
{
    ModalResult = mrCancel;    
}
//---------------------------------------------------------------------------

