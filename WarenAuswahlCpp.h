//---------------------------------------------------------------------------

#ifndef WarenAuswahlCppH
#define WarenAuswahlCppH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TWarenAuswahl : public TForm
{
__published:	// IDE-managed Components
    TImage *imWare00;
    TImage *Image1;
    TImage *Image2;
    TImage *Image3;
    TImage *Image5;
    TImage *Image6;
    TImage *Image7;
    TImage *Image8;
    TImage *Image10;
    TImage *Image11;
    TImage *Image12;
    TImage *Image13;
    TImage *Image15;
    TImage *Image16;
    TImage *Image17;
    TImage *Image18;
    TImage *Image4;
    TImage *Image9;
    TImage *Image14;
    TImage *Image19;
    TImage *Image20;
    TImage *Image21;
    TImage *Image22;
    TImage *Image24;
    TImage *Image25;
    TImage *Image26;
    TImage *Image27;
    TImage *Image28;
    TImage *Image29;
    TImage *Image30;
    TImage *Image31;
    TImage *Image23;
    TImage *Image32;
    TImage *Image33;
    TImage *Image34;
    TImage *Image35;
    TImage *Image36;
    TImage *Image37;
    TImage *Image38;
    TImage *Image39;
    void __fastcall imWareClick(TObject *Sender);
private:	// User declarations
    int lastSelected;

public:		// User declarations
    __fastcall TWarenAuswahl(TComponent* Owner);

    int __fastcall getSelected() const;
};
//---------------------------------------------------------------------------
extern PACKAGE TWarenAuswahl *WarenAuswahl;
//---------------------------------------------------------------------------
#endif
