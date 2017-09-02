//---------------------------------------------------------------------------

#ifndef FreiFormCppH
#define FreiFormCppH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFreiForm : public TForm
{
__published:	// IDE-managed Components
    TButton *CloseButton;
    TCheckBox *cbInfra00;
    TCheckBox *cbInfra01;
    TCheckBox *cbInfra02;
    TCheckBox *cbInfra03;
    TCheckBox *cbInfra04;
    TCheckBox *cbInfra05;
    TCheckBox *cbInfra06;
    TCheckBox *cbInfra07;
    TCheckBox *cbInfra08;
    TCheckBox *cbInfra09;
    TCheckBox *cbInfra10;
    TCheckBox *cbInfra11;
    TCheckBox *cbInfra12;
    TCheckBox *cbInfra13;
    TCheckBox *cbInfra14;
    TCheckBox *cbInfra15;
    TCheckBox *cbInfra16;
    TCheckBox *cbInfra17;
    TCheckBox *cbInfra18;
    TCheckBox *cbInfra19;
    TCheckBox *cbInfra20;
    TCheckBox *cbInfra21;
    TCheckBox *cbInfra22;
    TCheckBox *cbInfra23;
    TCheckBox *cbInfra24;
    TCheckBox *cbInfra25;
    TCheckBox *cbInfra26;
    TCheckBox *cbInfra27;
    TCheckBox *cbInfra28;
    TCheckBox *cbInfra29;
    TCheckBox *cbInfra30;
    TCheckBox *cbInfra31;
    TLabel *Label3;
    void __fastcall CloseButtonClick(TObject *Sender);
    void __fastcall ControlChanged(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFreiForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFreiForm *FreiForm;
//---------------------------------------------------------------------------
#endif
