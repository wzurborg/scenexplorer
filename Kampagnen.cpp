//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Kampagnen.h"
#include "IndkSzen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TKampForm *KampForm;
//---------------------------------------------------------------------------
__fastcall TKampForm::TKampForm(TComponent* Owner)
    : TForm(Owner), kampLines(0)
{
}
//---------------------------------------------------------------------------


void __fastcall TKampForm::ReadFile(String kampNr)
{
    String fname = IndkSzen::GetInstallDir() + "\\" + "Text.cod";
    if(kampLines != 0) delete kampLines;
    kampLines = 0;
    try {
        TFileStream* fs = new TFileStream(fname, fmOpenRead);
        char* buffer = new char[fs->Size+1];
        fs->Read(buffer, fs->Size);
        kampLines = decode(buffer, fs->Size);
        delete [] buffer;
        delete fs;
    }
    catch(...) {
        String msg("Kann Datei ");
        msg += fname + " nicht entschlüsseln";
        ShowMessage(msg);
        return;
    }

    while(kampLines->Count > 0) {
        if(kampLines->Strings[0] == "[KAMPAGNE]") break;
        kampLines->Delete(0);
    }
    kampLines->Delete(0);
    int i;
    for(i=0; i<kampLines->Count; i++) {
        if(kampLines->Strings[i] == "[END]") break;
    }
    while(i < kampLines->Count) {
        kampLines->Delete(i);
    }
    editKampnr->Text = kampNr;
}

TStrings* __fastcall TKampForm::decode(unsigned char* codlines, int len)
{
    for(int i=0; i<len; i++)
    {
        codlines[i] = 256 - codlines[i];
    }
    TStrings* ret = new TStringList;
    codlines[len] = '\0';
    ret->SetText((char*)codlines);
    return ret;
}

void __fastcall TKampForm::encode(TStrings* lines, unsigned char*& codlines, int& len)
{
    char* buffer = lines->GetText();
    len = strlen(buffer);
    codlines = (unsigned char*)buffer;
    for(int i=0; i<len; i++)
    {
        codlines[i] = 256 - codlines[i];
    }
}

void __fastcall TKampForm::editKampnrChange(TObject *Sender)
{
    String leer;
    editKamp1->Text = leer;
    editKamp2->Text = leer;
    editKamp3->Text = leer;
    editKamp4->Text = leer;
    editKamp5->Text = leer;
    if(kampLines == 0) return;
    int nr;
    try {
        nr = editKampnr->Text.ToInt();
    }
    catch(...) {
        return;
    }
    int first = nr*5;
    if(first+4 < kampLines->Count) {
        editKamp1->Text = kampLines->Strings[first];
        editKamp2->Text = kampLines->Strings[first+1];
        editKamp3->Text = kampLines->Strings[first+2];
        editKamp4->Text = kampLines->Strings[first+3];
        editKamp5->Text = kampLines->Strings[first+4];
    }
    else if(kampLines->Count >= 5) {
        editKampnr->Text = String(kampLines->Count/5 - 1);
    }
    else {
        editKampnr->Text = "";
    }
}
//---------------------------------------------------------------------------

void __fastcall TKampForm::Button1Click(TObject *Sender)
{
    Visible = false;    
}
//---------------------------------------------------------------------------

void __fastcall TKampForm::btnKampSaveClick(TObject *Sender)
{
    int nr = editKampnr->Text.ToInt();
    int first = nr*5;
    kampLines->Strings[first]   = editKamp1->Text;
    kampLines->Strings[first+1] = editKamp2->Text;
    kampLines->Strings[first+2] = editKamp3->Text;
    kampLines->Strings[first+3] = editKamp4->Text;
    kampLines->Strings[first+4] = editKamp5->Text;

    // save kampagnen
    String fname = IndkSzen::GetInstallDir() + "\\" + "Text.cod";
    TStrings* lines;
    try {
        TFileStream* fs = new TFileStream(fname, fmOpenRead);
        char* buffer = new char[fs->Size+1];
        fs->Read(buffer, fs->Size);
        lines = decode(buffer, fs->Size);
        delete [] buffer;
        delete fs;
    }
    catch(...) {
        String msg("Kann Datei ");
        msg += fname + " nicht entschlüsseln";
        ShowMessage(msg);
        return;
    }

    int i = lines->IndexOf("[KAMPAGNE]") + 1;

    while(lines->Strings[i] != "[END]") {
        lines->Delete(i);
    }
    for(int j=0; j<kampLines->Count; j++) {
        lines->Insert(i+j, kampLines->Strings[j]);
    }

    unsigned char* buffer;
    int len;
    encode(lines, buffer, len);
    delete lines;

    try {
        TFileStream* fs = new TFileStream(fname, fmOpenWrite|fmShareExclusive);
        fs->Write(buffer, len);
        StrDispose(buffer);
        delete fs;
    }
    catch(...) {
        String msg("Kann Datei ");
        msg += fname + " nicht schreiben";
        ShowMessage(msg);
        return;
    }
}
//---------------------------------------------------------------------------

