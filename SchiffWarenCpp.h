//---------------------------------------------------------------------------

#ifndef SchiffWarenCppH
#define SchiffWarenCppH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TSchiffWaren : public TForm
{
__published:	// IDE-managed Components
    TButton *btOk;
    TButton *btLeeren;
    TGroupBox *gbWare00;
    TImage *imWare00;
    TEdit *edWare00;
    TUpDown *UpDown1;
    TGroupBox *gbWare01;
    TImage *imWare01;
    TEdit *edWare01;
    TUpDown *UpDown2;
    TGroupBox *gbWare02;
    TImage *imWare02;
    TEdit *edWare02;
    TUpDown *UpDown3;
    TGroupBox *gbWare03;
    TImage *imWare03;
    TEdit *edWare03;
    TUpDown *UpDown4;
    TGroupBox *gbWare04;
    TImage *imWare04;
    TEdit *edWare04;
    TUpDown *UpDown5;
    TGroupBox *gbWare05;
    TImage *imWare05;
    TEdit *edWare05;
    TUpDown *UpDown6;
    TGroupBox *gbWare06;
    TImage *imWare06;
    TEdit *edWare06;
    TUpDown *UpDown7;
    TGroupBox *gbWare07;
    TImage *imWare07;
    TEdit *edWare07;
    TUpDown *UpDown8;
    TImage *imSchiff;
    TLabel *lbSchiff;
    TButton *btCancel;
    void __fastcall btOkClick(TObject *Sender);
    void __fastcall imWareClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btLeerenClick(TObject *Sender);
    void __fastcall btCancelClick(TObject *Sender);
private:	// User declarations
    TEdit* edWare[8];
    TImage* imWare[8];
    TGroupBox* gbWare[8];

public:		// User declarations
    __fastcall TSchiffWaren(TComponent* Owner);
    void __fastcall updateWaren();
    void __fastcall saveWaren();
    
};
//---------------------------------------------------------------------------
extern PACKAGE TSchiffWaren *SchiffWaren;
//---------------------------------------------------------------------------
#endif
