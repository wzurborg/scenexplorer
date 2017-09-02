//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SchiffWarenCpp.h"
#include "WarenAuswahlCpp.h"
#include "Main.h"
#include "IndkSzen.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSchiffWaren *SchiffWaren;

static int numWaren[] = {4, 6, 3, 8, 7, 5, 3};

static int waretable[] = {
    -1, 0, 2401, 2405, 1505, 1511, 1507, 1513, 1503, 501,
    521, 517, 529, 527, 1075, 525, 1501, 1509, 519, 507,
    505, 533, 515, 2001, 513,
    9901, 9902, 9903, 9904,
    9905, 9906, 9907, 9908,
    9909, 9910, 9911, 9912,
    9913, 9914, 9915, 9916 };

static int ware2index(int ware)
{
    for(int i=0; i<41; i++)
    {
        if(waretable[i] == ware)
            return i;
    }
    return 1;
}

//---------------------------------------------------------------------------
__fastcall TSchiffWaren::TSchiffWaren(TComponent* Owner)
    : TForm(Owner)
{
    edWare[0] = edWare00;
    edWare[1] = edWare01;
    edWare[2] = edWare02;
    edWare[3] = edWare03;
    edWare[4] = edWare04;
    edWare[5] = edWare05;
    edWare[6] = edWare06;
    edWare[7] = edWare07;
    imWare[0] = imWare00;
    imWare[1] = imWare01;
    imWare[2] = imWare02;
    imWare[3] = imWare03;
    imWare[4] = imWare04;
    imWare[5] = imWare05;
    imWare[6] = imWare06;
    imWare[7] = imWare07;
    gbWare[0] = gbWare00;
    gbWare[1] = gbWare01;
    gbWare[2] = gbWare02;
    gbWare[3] = gbWare03;
    gbWare[4] = gbWare04;
    gbWare[5] = gbWare05;
    gbWare[6] = gbWare06;
    gbWare[7] = gbWare07;
}
//---------------------------------------------------------------------------
void __fastcall TSchiffWaren::btOkClick(TObject *Sender)
{
    saveWaren();
    ModalResult = mrOk;    
}
//---------------------------------------------------------------------------

void __fastcall TSchiffWaren::updateWaren()
{
    TSHIPSAVE* ship = MainForm->getCurrSzen()->getSelectedShip();
    if(ship != 0)
    {
        lbSchiff->Caption = ship->name;
        Graphics::TBitmap* bm = new Graphics::TBitmap;
        MainForm->WappenImages->GetBitmap(
            MainForm->comboSchifffarbe->ItemIndex, bm);
        imSchiff->Picture->Bitmap = bm;
        delete bm;

        for(int i=0; i<8; i++)
            gbWare[i]->Visible = true;

        int type = IndkSzen::schiff2index(ship->figurnr);
        switch(type)
        {
        case 2:
        case 6: gbWare03->Visible = false;
        case 0: gbWare04->Visible = false;
        case 5: gbWare05->Visible = false;
        case 1: gbWare06->Visible = false;
        case 4: gbWare07->Visible = false;
        }

        for(int i=0; i<numWaren[type]; i++)
        {
            edWare[i]->Text = String(ship->waren[i].menge / 32);
            Graphics::TBitmap* bm = new Graphics::TBitmap;
            MainForm->WarenImages->GetBitmap(ware2index(ship->waren[i].hausid), bm);
            imWare[i]->Picture->Bitmap = bm;
            delete bm;
        }

    }
}

void __fastcall TSchiffWaren::saveWaren()
{
    TSHIPSAVE* ship = MainForm->getCurrSzen()->getSelectedShip();
    if(ship != 0)
    {
        int type = IndkSzen::schiff2index(ship->figurnr);
        for(int i=0; i<numWaren[type]; i++)
        {
            ship->waren[i].menge = edWare[i]->Text.ToIntDef(0) * 32;
            ship->waren[i].hausid = waretable[imWare[i]->Tag];
        }
    }
}

void __fastcall TSchiffWaren::imWareClick(TObject *Sender)
{
    TImage* image = (TImage*)Sender;
    if(WarenAuswahl->ShowModal() == mrOk)
    {
        int selWare = WarenAuswahl->getSelected();
        image->Tag = selWare;

        Graphics::TBitmap* bm = new Graphics::TBitmap;
        MainForm->WarenImages->GetBitmap(selWare, bm);
        image->Picture->Bitmap = bm;
        delete bm;
    }
}
//---------------------------------------------------------------------------

void __fastcall TSchiffWaren::FormShow(TObject *Sender)
{
    updateWaren();
}
//---------------------------------------------------------------------------
void __fastcall TSchiffWaren::btLeerenClick(TObject *Sender)
{
    for(int i=0; i<8; i++)
    {
        if(gbWare[i]->Visible)
        {
            Graphics::TBitmap* bm = new Graphics::TBitmap;
            MainForm->WarenImages->GetBitmap(1, bm);    // leer
            imWare[i]->Picture->Bitmap = bm;
            delete bm;
            edWare[i]->Text = "0";
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TSchiffWaren::btCancelClick(TObject *Sender)
{
    ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

