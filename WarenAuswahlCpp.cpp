//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "WarenAuswahlCpp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TWarenAuswahl *WarenAuswahl;
//---------------------------------------------------------------------------
__fastcall TWarenAuswahl::TWarenAuswahl(TComponent* Owner)
    : TForm(Owner), lastSelected(0)
{
}
//---------------------------------------------------------------------------
void __fastcall TWarenAuswahl::imWareClick(TObject *Sender)
{
    lastSelected = ((TComponent*)Sender)->Tag;
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------

int __fastcall TWarenAuswahl::getSelected() const
{
    return lastSelected;
}
