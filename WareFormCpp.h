//---------------------------------------------------------------------------

#ifndef WareFormCppH
#define WareFormCppH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TWareForm : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *gbWare02;
    TImage *imWare02;
    TEdit *edWare02;
    TUpDown *udWare02;
    TGroupBox *GroupBox1;
    TImage *Image1;
    TEdit *edWare05;
    TUpDown *UpDown1;
    TGroupBox *GroupBox2;
    TImage *Image2;
    TEdit *edWare03;
    TUpDown *UpDown2;
    TGroupBox *GroupBox3;
    TImage *Image3;
    TEdit *edWare04;
    TUpDown *UpDown3;
    TGroupBox *GroupBox4;
    TImage *Image4;
    TEdit *edWare06;
    TUpDown *UpDown4;
    TGroupBox *GroupBox5;
    TImage *Image5;
    TEdit *edWare09;
    TUpDown *UpDown5;
    TGroupBox *GroupBox6;
    TImage *Image6;
    TEdit *edWare07;
    TUpDown *UpDown6;
    TGroupBox *GroupBox7;
    TImage *Image7;
    TEdit *edWare08;
    TUpDown *UpDown7;
    TGroupBox *GroupBox8;
    TImage *Image8;
    TEdit *edWare10;
    TUpDown *UpDown8;
    TGroupBox *GroupBox9;
    TImage *Image9;
    TEdit *edWare13;
    TUpDown *UpDown9;
    TGroupBox *GroupBox10;
    TImage *Image10;
    TEdit *edWare11;
    TUpDown *UpDown10;
    TGroupBox *GroupBox11;
    TImage *Image11;
    TEdit *edWare12;
    TUpDown *UpDown11;
    TGroupBox *GroupBox12;
    TImage *Image12;
    TEdit *edWare14;
    TUpDown *UpDown12;
    TGroupBox *GroupBox13;
    TImage *Image13;
    TEdit *edWare17;
    TUpDown *UpDown13;
    TGroupBox *GroupBox14;
    TImage *Image14;
    TEdit *edWare15;
    TUpDown *UpDown14;
    TGroupBox *GroupBox15;
    TImage *Image15;
    TEdit *edWare16;
    TUpDown *UpDown15;
    TGroupBox *GroupBox16;
    TImage *Image16;
    TEdit *edWare18;
    TUpDown *UpDown16;
    TGroupBox *GroupBox17;
    TImage *Image17;
    TEdit *edWare21;
    TUpDown *UpDown17;
    TGroupBox *GroupBox18;
    TImage *Image18;
    TEdit *edWare19;
    TUpDown *UpDown18;
    TGroupBox *GroupBox19;
    TImage *Image19;
    TEdit *edWare20;
    TUpDown *UpDown19;
    TGroupBox *GroupBox20;
    TImage *Image20;
    TEdit *edWare22;
    TUpDown *UpDown20;
    TGroupBox *GroupBox22;
    TImage *Image22;
    TEdit *edWare23;
    TUpDown *UpDown22;
    TGroupBox *GroupBox23;
    TImage *Image23;
    TEdit *edWare24;
    TUpDown *UpDown23;
    TButton *btOk;
    TButton *btLeeren;
    TImage *picOwner;
    TLabel *lbOwner;
    TButton *btCancel;
    void __fastcall btOkClick(TObject *Sender);
    void __fastcall btLeerenClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btCancelClick(TObject *Sender);
private:	// User declarations
    TEdit* waren[25];


public:		// User declarations
    __fastcall TWareForm(TComponent* Owner);

    void __fastcall updateWaren();
    void __fastcall saveWaren();
};
//---------------------------------------------------------------------------
extern PACKAGE TWareForm *WareForm;
//---------------------------------------------------------------------------
#endif
