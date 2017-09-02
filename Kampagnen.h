//---------------------------------------------------------------------------

#ifndef KampagnenH
#define KampagnenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TKampForm : public TForm
{
__published:	// IDE-managed Components
    TLabeledEdit *editKamp1;
    TLabeledEdit *editKamp2;
    TLabeledEdit *editKamp3;
    TLabeledEdit *editKamp4;
    TLabeledEdit *editKamp5;
    TLabeledEdit *editKampnr;
    TUpDown *UpDown1;
    TButton *Button1;
    TButton *btnKampSave;
    void __fastcall editKampnrChange(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall btnKampSaveClick(TObject *Sender);
private:
    TStrings* kampLines;
    TStrings* __fastcall decode(unsigned char* codlines, int len);
    void __fastcall encode(TStrings* lines, unsigned char*& codlines, int& len);
public:		// User declarations
    __fastcall TKampForm(TComponent* Owner);
    void __fastcall ReadFile(String kampNr);
};
//---------------------------------------------------------------------------
extern PACKAGE TKampForm *KampForm;
//---------------------------------------------------------------------------
#endif
