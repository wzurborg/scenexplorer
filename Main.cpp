//---------------------------------------------------------------------------
#include <vcl.h>
#include <process.h>
#pragma hdrstop

#include "Main.h"
#include "Kampagnen.h"
#include "FreiFormCpp.h"
#include "WareFormCpp.h"
#include "SchiffWarenCpp.h"
#include "Insel.h"
#include "SzenExplorer.rh"

//---------------------------------------------------------------------------
#pragma link "StShlCtl"
#pragma link "SsBase"
#pragma link "ThemeMgr"
#pragma resource "*.dfm"
TMainForm *MainForm;

static char* C_SuppExt_s = ".gam\n.szs\n.szm\n.mfs\n.mfm";
static TStringList* C_SuppExt = new TStringList();

LRESULT CALLBACK TMainForm::KeyboardProc(
    int code,	// hook code
    WPARAM wParam,	// virtual-key code
    LPARAM lParam 	// keystroke-message information
    )
{
    return MainForm->keystroke(wParam);
}

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner), currSzen(0), canUndoDrag(false), count(0)
{
    background = new Graphics::TBitmap;
    background->LoadFromResourceID((int)HInstance, BACKGROUND);

    offscreen = new Graphics::TBitmap;
    offscreen->Height = IndkSzen::HEIGHT;
    offscreen->Width = IndkSzen::WIDTH;

    SaveAsAction->OnUpdate = SaveAsActionUpdate;
    SaveInselAction->OnUpdate = SaveInselActionUpdate;

    C_SuppExt->Text = C_SuppExt_s;

    StShellTreeView1->SelectFolder(IndkSzen::GetInstallDir());

    // avoids flickering during repaints
    PaintBox1->ControlStyle << csOpaque;
    DoubleBuffered = true;

    inselTree = ObjectTree->Items->Item[0];
    shipTree = ObjectTree->Items->Item[1];

    SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, HInstance, GetCurrentThreadId());
//    Application->HookMainWindow(HookFunction);    
}

//----------------------------------------------------------------------------

__fastcall TMainForm::~TMainForm()
{
    UnhookWindowsHookEx(KeyboardProc);
    delete currSzen;
    currSzen = 0;
    delete C_SuppExt;
    delete offscreen;
}


void __fastcall TMainForm::WndProc(Messages::TMessage &Message)
{
/*
    if(Message.Msg == WM_ERASEBKGND)
    {
        ShowMessage("ERASEBKGND");
    }
    else
    {
*/
        TWinControl::WndProc(Message);
//    }
}


void __fastcall TMainForm::SetTitleFile(AnsiString fname) {
    String title = "Sir Henry's 1602 Szenario Explorer ";
    if(currSzen != 0 && currSzen->isModified()) {
        fname += "*";
    }
    title += "[" + fname + "]";
    this->Caption = title;
}

//----------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
//	Application->OnHint = ShowHint;
}
//----------------------------------------------------------------------------
void __fastcall TMainForm::ShowHint(TObject *Sender)
{
//	StatusLine->SimpleText = Application->Hint;
}
//----------------------------------------------------------------------------

void __fastcall TMainForm::StShellTreeView1FilterItem(TObject *Sender,
      TStShellItem *ShellItem, bool &Accept)
{
    if(ShellItem->IsFile)
        Accept = isSupportedFile(ShellItem->Path);
    else
    if(ShellItem->IsFolder)
        Accept = ExtractFileExt(ShellItem->Path) != ".zip";
    else
        Accept = false;
}
//--------------------------------------------------------------------
void __fastcall TMainForm::StShellTreeView1FolderSelected(TObject *Sender,
      TStShellFolder *Folder)
{
    if(isSupportedFile(Folder->Path)) {
        currentFolder = ExtractFileDir(Folder->Path);
        loadSzenario(Folder->Path);
    }
}
//--------------------------------------------------------------------

bool __fastcall TMainForm::isSupportedFile(String name) const
{
    return C_SuppExt->IndexOf(ExtractFileExt(name)) >= 0;
}

//--------------------------------------------------------------------


void __fastcall TMainForm::AuftragTabControlChanging(TObject *Sender,
      bool &AllowChange)
{
    if(currSzen != 0) {
        currSzen->getAuftrag(AuftragTabControl->TabIndex);  // sichere alten Auftrag
    }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::AuftragTabControlChange(TObject *Sender)
{
    if(currSzen != 0) {
        currSzen->putAuftrag(AuftragTabControl->TabIndex);  // fülle neuen Auftrag
    }
}
//---------------------------------------------------------------------------


bool __fastcall TMainForm::loadSzenario(String path)
{
    ObjectTree->Items->BeginUpdate();

    if(!canClose())
    {
        ObjectTree->Items->EndUpdate();
        return false;
    }

    currSzen = new IndkSzen();
    if(currSzen->readSzen(path) == 0) {
        lbTitle1->Visible = false;
        lbTitle2->Visible = false;
        lbTitle3->Visible = false;
        lbTitle4->Visible = false;
        imTitle1->Visible = false;
        Panel5->Visible = true;
        Panel8->Visible = true;
//        Splitter2->Visible = true;
//        Splitter3->Visible = true;

        AuftragTabControl->Enabled = true;
        AuftragTabControl->TabIndex = 0;
        SpielerTabControl->Enabled = true;
        SpielerTabControl->TabIndex = 0;
        Memo1->Clear();
        currSzen->putAuftrag(0);
        currSzen->putPlayer(0);
        currSzen->putSettings();
        StatusLine->Panels->Items[0]->Text =
            MinimizeName(path, StatusLine->Canvas,
            StatusLine->Panels->Items[0]->Width);
        StatusLine->Panels->Items[1]->Text = "";
        PaintBox1->Invalidate();
        canUndoDrag = false;
    }
    else {
        delete currSzen;
        currSzen = 0;
        ShowMessage("Read scenario failed!");
    }

    if(currSzen != 0) {
        currSzen->setModified(false);
        MainPageControl->Enabled = true;
    }

    inselTree->Expanded = true;
    shipTree->Expanded = true;
    ObjectTree->AlphaSort(true);
    ObjectTree->Items->EndUpdate();
    return true;
}

void __fastcall TMainForm::sbKillRotClick(TObject *Sender)
{
    if(sbKillRot->Down)
        sbKillAny->Down = false;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::sbKillBlauClick(TObject *Sender)
{
    if(sbKillBlau->Down)
        sbKillAny->Down = false;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::sbKillGelbClick(TObject *Sender)
{
    if(sbKillGelb->Down)
        sbKillAny->Down = false;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::sbKillWeissClick(TObject *Sender)
{
    if(sbKillWeiss->Down)
        sbKillAny->Down = false;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::sbKillAnyClick(TObject *Sender)
{
    if(sbKillAny->Down) {
        sbKillRot->Down = false;
        sbKillBlau->Down = false;
        sbKillGelb->Down = false;
        sbKillWeiss->Down = false;
    }
    controlChanged(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::cbStadt1Click(TObject *Sender)
{
    bool state = cbStadt1->Checked;
    gbStadt1->Enabled = state;
    editStadt1Wohn->Enabled = state;
    editStadt1Bgrp->Enabled = state;
    comboStadt1Bgrp->Enabled = state;
    lbStadt1Wohn->Enabled = state;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbStadt2Click(TObject *Sender)
{
    bool state = cbStadt2->Checked;
    gbStadt2->Enabled = state;
    editStadt2Wohn->Enabled = state;
    editStadt2Bgrp->Enabled = state;
    comboStadt2Bgrp->Enabled = state;
    lbStadt2Wohn->Enabled = state;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbStadt3Click(TObject *Sender)
{
    bool state = cbStadt3->Checked;
    gbStadt3->Enabled = state;
    editStadt3Wohn->Enabled = state;
    editStadt3Bgrp->Enabled = state;
    comboStadt3Bgrp->Enabled = state;
    lbStadt3Wohn->Enabled = state;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::cbStore1Click(TObject *Sender)
{
    bool state = cbStore1->Checked;
    editStore1->Enabled = state;
    labelStore1->Enabled = state;
    comboStore1->Enabled = state;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbStore2Click(TObject *Sender)
{
    bool state = cbStore2->Checked;
    editStore2->Enabled = state;
    labelStore2->Enabled = state;
    comboStore2->Enabled = state;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbTBalanceClick(TObject *Sender)
{
    editTBalance->Enabled = cbTBalance->Checked;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbBalanceClick(TObject *Sender)
{
    editBalance->Enabled = cbBalance->Checked;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbMonopol1Click(TObject *Sender)
{
    comboMonopol1->Enabled = cbMonopol1->Checked;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbMonopol2Click(TObject *Sender)
{
    comboMonopol2->Enabled = cbMonopol2->Checked;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbHelpWohnClick(TObject *Sender)
{
    bool state = cbHelpWohn->Checked;
    editHelpWohn->Enabled = state;
    lbHelpWohn->Enabled = state;
    editHelpWohnGrp->Enabled = state;
    comboHelpWohnName->Enabled = state;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbStadtlowfrmdClick(TObject *Sender)
{
    bool state = cbStadtlowfrmd->Checked;
    editStadtlowfrmdwohn->Enabled = state;
    editStadtlowfrmdbgwohn->Enabled = state;
    comboStadtlowfrmdbgnr->Enabled = state;
    lbStadtlowfrmdwohn->Enabled = state;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbStadtanzminfrmdClick(TObject *Sender)
{
    bool state = cbStadtanzminfrmd->Checked;
    editStadtanzminfrmd->Enabled = state;
    lbStadtanzminfrmd->Enabled = state;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::SpielerTabControlChanging(TObject *Sender,
      bool &AllowChange)
{
    if(currSzen != 0)
        currSzen->getPlayer(SpielerTabControl->TabIndex); // sichere alten Spieler
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::SpielerTabControlChange(TObject *Sender)
{
    if(currSzen != 0)
        currSzen->putPlayer(SpielerTabControl->TabIndex);  // fülle neuen Spieler
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::lbColorClick(TObject *Sender)
{
    //    
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::PaintBox1Paint(TObject *Sender)
{
    if(currSzen != 0) {
        currSzen->paint(offscreen->Canvas);
        TRect r(0, 0, PaintBox1->Width, PaintBox1->Height);
//        PaintBox1->Canvas->Draw(0, 0, bitmap);
        PaintBox1->Canvas->StretchDraw(r, offscreen);
    }

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::SwitchPiratenUpdate(TObject *Sender)
{
    SwitchPiraten->Hint = btnPiraten->Down ?
        "Piraten erscheinen nicht wieder" : "Piraten erscheinen wieder";
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::SwitchErzUpdate(TObject *Sender)
{
    SwitchErz->Hint = btnErz->Down ?
        "Große Erzvorkommen sind unerschöpflich" : "Große Erzvorkommen sind erschöpflich";
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::SwitchVulkaneUpdate(TObject *Sender)
{
    SwitchVulkane->Hint = btnVulkan->Down ?
        "Vulkane brechen nicht aus" : "Vulkane brechen aus";
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::SwitchDuerrenUpdate(TObject *Sender)
{
    SwitchDuerren->Hint = btnDuerren->Down ?
        "Dürren sind nicht möglich" : "Dürren sind möglich";
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::SwitchHaendlerUpdate(TObject *Sender)
{
    SwitchHaendler->Hint = btnHaendler->Down ?
        "Fliegender Händler erscheint nicht" : "Fliegender Händler erscheint";
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::SwitchWaffenUpdate(TObject *Sender)
{
    SwitchWaffen->Hint = btnWaffen->Down ?
        "Militäroptionen aus" : "Militäroptionen ein";
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::btnKampagneClick(TObject *Sender)
{
    KampForm->Visible = true;
    KampForm->SetFocus();
    KampForm->ReadFile(editKampagne->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbKampagneClick(TObject *Sender)
{
    if(cbKampagne->Checked) {
        editKampagne->Enabled = true;
        btnKampagne->Enabled = true;
    } else {
        editKampagne->Enabled = false;
        btnKampagne->Enabled = false;
    }
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::MainPageControlChanging(TObject *Sender,
      bool &AllowChange)
{
    // sichern des Auftrags falls Auftragsseite verlassen wird
    if(currSzen != 0) {
        if( MainPageControl->ActivePage == TabAuftraege )
            currSzen->getAuftrag(AuftragTabControl->TabIndex);  // sichere Auftrag
    }

    //  sichern des Spielers falls Spielerseite verlassen wird
    if(currSzen != 0) {
        if( MainPageControl->ActivePage == TabSpieler )
            currSzen->getPlayer(SpielerTabControl->TabIndex);  // sichere Spieler
    }
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::cbGuthabenClick(TObject *Sender)
{
    bool state = cbGuthaben->Checked;
    editGuthaben->Enabled = state;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbWohnanzClick(TObject *Sender)
{
    bool state = cbWohnanz->Checked;
    editWohnanz->Enabled = state;
    lbWohnanz->Enabled = state;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PaintBox1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(currSzen != 0)
    {
        // convert X/Y to streched PaintBox
        X = X * IndkSzen::WIDTH / MainForm->PaintBox1->Width;
        Y = Y * IndkSzen::HEIGHT / MainForm->PaintBox1->Height;
        if(currSzen->selectObject(X, Y, Shift))
        {
            if(ObjectTree->Selected != 0 &&
               ObjectTree->Selected->Parent == inselTree &&
               Button == mbLeft)
            {
                PaintBox1->BeginDrag(false);
                dragPos = TPoint(X,Y);
                dragStart = dragPos;
                canUndoDrag = false;
            }
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = canClose();
}
//---------------------------------------------------------------------------


bool __fastcall TMainForm::canClose()
{
    if(currSzen != 0) {
        if(currSzen->isModified()) {
            int r = MessageDlg("Sollen die Änderungen gespeichert werden?",
                mtConfirmation, mbYesNoCancel, -1);
            if(r == mrCancel) {
                return false;
            }
            else
            if(r == mrYes) {
                if(currSzen->saveSzen(currSzen->getPath()) != 0) {
                    MessageDlg("Datei konnte nicht gesichert werden!", mtError,
                    TMsgDlgButtons() << mbOK, 0);
                    return false;
                }
            }
        }
        delete currSzen;
        currSzen = 0;
        ObjectTree->Items->Item[0]->DeleteChildren();
        ObjectTree->Items->Item[1]->DeleteChildren();
    }
    return true;
}


void __fastcall TMainForm::SaveActionExecute(TObject *Sender)
{
    if(currSzen != 0) {
        if(currSzen->saveSzen(currSzen->getPath()) != 0) {
            MessageDlg("Datei konnte nicht gesichert werden!", mtError,
            TMsgDlgButtons() << mbOK, 0);
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::SaveActionUpdate(TObject *Sender)
{
    SaveAction->Enabled = currSzen != 0 && currSzen->isModified();    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RevertActionExecute(TObject *Sender)
{
    if(currSzen != 0) {
        if(currSzen->isModified()) {
            int r = MessageDlg("Achtung: Änderungen gehen verloren!",
                mtWarning, mbOKCancel, -1);
            if(r == mrOk) {
                currSzen->setModified(false);   // suppress query !
            }
            else {
                return;
            }
        }
        loadSzenario(currSzen->getPath());
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::RevertActionUpdate(TObject *Sender)
{
    RevertAction->Enabled = currSzen != 0 && currSzen->isModified();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::SaveAsActionAccept(TObject *Sender)
{
    static char* C_Ext[] = {".szs", ".szm", ".gam"};
    int error = 1;

    String fname = SaveAsAction->Dialog->FileName;
    String ext = C_Ext[SaveAsAction->Dialog->FilterIndex - 1];

    fname = ChangeFileExt(fname, ext);

    try {
        error = currSzen->saveSzen(fname);
    }
    catch(...) {}

    if( error != 0 ) {
        MessageDlg("Datei konnte nicht gesichert werden!", mtError,
            TMsgDlgButtons() << mbOK, 0);
    }
    else {
        StShellTreeView1->Refresh(0);
        StShellTreeView1->SelectFolder(fname);
        StShellTreeView1->SetFocus();
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveAsActionBeforeExecute(TObject *Sender)
{
    if( SaveAsAction->Dialog->InitialDir.IsEmpty() )
        SaveAsAction->Dialog->InitialDir = currentFolder;
    String fname = ExtractFileName(currSzen->getPath());

    SaveAsAction->Dialog->FileName = ChangeFileExt(fname, ".szs");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveAsActionUpdate(TObject *Sender)
{
    SaveAsAction->Enabled = currSzen != 0;
}

void __fastcall TMainForm::SaveInselActionUpdate(TObject *Sender)
{
    SaveInselAction->Enabled = currSzen != 0 && currSzen->getSelectedIsland() != 0;
}


void __fastcall TMainForm::OpenActionAccept(TObject *Sender)
{
    String fname = OpenAction->Dialog->FileName;
    loadSzenario(fname);

    // update tree
    StShellTreeView1->Refresh(0);

    // select file in tree
    StShellTreeView1->SelectFolder(fname);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveInselActionBeforeExecute(TObject *Sender)
{
    // ...
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PaintBox1ContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
    Handled = currSzen == 0 || currSzen->getSelectedIsland() == 0;    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SaveInselActionAccept(TObject *Sender)
{
    if(currSzen != 0)
    {
        String path = SaveInselAction->Dialog->FileName;
        if(ExtractFileExt(path) != ".scp")
            path += ".scp";
        currSzen->saveSelectedIsland(path);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::openInsel( String path ) {
    static AnsiString cmd;
    if( cmd.Length() == 0 )
    {
        AnsiString key = "SOFTWARE\\Sir Henry\\AnnoEdit";
        cmd = getRegistryValue( HKEY_LOCAL_MACHINE, key, "BitmapDir" );
        cmd = ExtractFileDir(cmd) + "\\AnnoEdit.exe";
    }

    if( !FileExists(cmd) )
        return;

    spawnl( P_NOWAITO, cmd.c_str(), cmd.c_str(), "-", path.c_str(), 0 );
}

AnsiString TMainForm::getRegistryValue(void* root, AnsiString key, AnsiString name)
{
  AnsiString S;
  TRegistry *Registry = new TRegistry;

  try
  {
    Registry->RootKey = root;
    // False because we do not want to create it if it doesn't exist
    if( Registry->OpenKey(key,false) && Registry->ValueExists(name))
        S = Registry->ReadString(name);
  }
  __finally
  {
    delete Registry;
  }
  return S;
}

void __fastcall TMainForm::controlChanged(TObject *Sender)
{
    if(currSzen != 0)
        currSzen->setModified(true);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tbBgruppminChange(TObject *Sender)
{
    tbBgruppmin->SelStart = tbBgruppmin->Min;
    tbBgruppmin->SelEnd = tbBgruppmin->Position;
    editBgruppmin->Text = Format("%.2f", ARRAYOFCONST(((double)tbBgruppmin->Position/100.0)));
    lbBgruppmin2->Caption = GetBgrupp(tbBgruppmin->Position);
    SetDaumen(cbBgruppmin, tbBgruppmin, imDaumen1);
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::tbBgruppmaxhumanChange(TObject *Sender)
{
    tbBgruppmaxhuman->SelStart = tbBgruppmaxhuman->Position;
    tbBgruppmaxhuman->SelEnd = tbBgruppmaxhuman->Max;
    editBgruppmaxhuman->Text = Format("%.2f", ARRAYOFCONST(((double)tbBgruppmaxhuman->Position/100.0)));
    lbBgruppmaxhuman2->Caption = GetBgrupp(tbBgruppmaxhuman->Position);
    SetDaumen(cbBgruppmaxhuman, tbBgruppmaxhuman, imDaumen2, true);
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
    FreiForm->Visible = true;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::editBgruppminChange(TObject *Sender)
{
    try
    {
        tbBgruppmin->Position = editBgruppmin->Text.ToDouble() * 100;
        SetDaumen(cbBgruppmin, tbBgruppmin, imDaumen1);
        controlChanged(Sender);
    }
    catch(...) {}
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::editBgruppmaxhumanChange(TObject *Sender)
{
    try
    {
        tbBgruppmaxhuman->Position = editBgruppmaxhuman->Text.ToDouble() * 100;
        SetDaumen(cbBgruppmaxhuman, tbBgruppmaxhuman, imDaumen2, true);
        controlChanged(Sender);
    }
    catch(...) {}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbBgruppminClick(TObject *Sender)
{
    tbBgruppmin->Enabled = cbBgruppmin->Checked;
    editBgruppmin->Enabled = cbBgruppmin->Checked;
    tbBgruppmin->SelEnd = cbBgruppmin->Checked ? tbBgruppmin->Position : tbBgruppmin->Min;
    lbBgruppmin1->Enabled = cbBgruppmin->Checked;
    lbBgruppmin2->Enabled = cbBgruppmin->Checked;
//    lbBgruppmin3->Enabled = cbBgruppmin->Checked;
    SetDaumen(cbBgruppmin, tbBgruppmin, imDaumen1);
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbBgruppmaxhumanClick(TObject *Sender)
{
    tbBgruppmaxhuman->Enabled = cbBgruppmaxhuman->Checked;
    editBgruppmaxhuman->Enabled = cbBgruppmaxhuman->Checked;
    tbBgruppmaxhuman->SelStart = cbBgruppmaxhuman->Checked ?
        tbBgruppmaxhuman->Position : tbBgruppmaxhuman->Max;
    lbBgruppmaxhuman1->Enabled = cbBgruppmaxhuman->Checked;
    lbBgruppmaxhuman2->Enabled = cbBgruppmaxhuman->Checked;
//    lbBgruppmaxhuman3->Enabled = cbBgruppmaxhuman->Checked;
    SetDaumen(cbBgruppmaxhuman, tbBgruppmaxhuman, imDaumen2, true);
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbWohnminClick(TObject *Sender)
{
    editWohnmin->Enabled = cbWohnmin->Checked;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cbHumanwohnmaxClick(TObject *Sender)
{
    editHumanwohnmax->Enabled = cbHumanwohnmax->Checked;
    controlChanged(Sender);
}
//---------------------------------------------------------------------------


String __fastcall TMainForm::GetBgrupp(int value)
{
    return "XXXXX";
}

void __fastcall TMainForm::SetDaumen(TCheckBox* cb, TTrackBar* tb, TImage* im, bool inverse)
{
    if(cb->Checked)
    {
        int div = (tb->Max - tb->Min) / 7;
        int index = (tb->Position - tb->Min) / div;
        if(index > 6) index = 6;
        if(inverse) index = 6 - index;
        Graphics::TBitmap* bm = new Graphics::TBitmap;
        DaumenList->GetBitmap(index, bm);
        im->Picture->Bitmap = bm;
//        im->SendToBack();
        delete bm;
    }
    else
    {
        im->Picture->Bitmap = 0;
    }
}

void __fastcall TMainForm::numericKeyPress(TObject *Sender, char &Key)
{
    if((Key < '0' || Key > '9') && Key != 8)
        Key = 0;
}


void __fastcall TMainForm::btStaedteClick(TObject *Sender)
{
    PaintBox1->Invalidate();    
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PaintBox1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    // convert X/Y to streched PaintBox
    X = X * IndkSzen::WIDTH / MainForm->PaintBox1->Width;
    Y = Y * IndkSzen::HEIGHT / MainForm->PaintBox1->Height;

    StatusLine->Panels->Items[1]->Text = String(X) + " / " + Y;
    if(currSzen != 0)
    {
        currSzen->mouseHover(X, Y, Shift);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DeleteIslandActionUpdate(TObject *Sender)
{
    bool enabled = false;
    if(currSzen != 0)
    {
        Insel* insel = currSzen->getSelectedIsland();
        enabled = insel != 0 && insel->isEmpty();
    }

    DeleteIslandAction->Enabled = enabled;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DeleteIslandActionExecute(TObject *Sender)
{
    if(currSzen != 0)
    {
        currSzen->deleteSelectedInsel();
        PaintBox1->Invalidate();
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::mapcolorChange(TObject *Sender)
{
    PaintBox1->Invalidate();
    ObjectTree->Invalidate();
    controlChanged(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::comboStadtfarbeChange(TObject *Sender)
{
    if(currSzen != 0)
    {
        currSzen->stadtColorChange();
        WareForm->updateWaren();
        mapcolorChange(Sender);
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::ObjectTreeChange(TObject *Sender,
      TTreeNode *Node)
{
    if(currSzen != 0)
    {
        currSzen->selectionChanged(Node);
        PaintBox1->Invalidate();
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ObjectTreeCompare(TObject *Sender,
      TTreeNode *Node1, TTreeNode *Node2, int Data, int &Compare)
{
    if(Node1->Parent == Node2->Parent &&
       Node1->Parent == ObjectTree->Items->Item[0])
    {
        // Schiffe
        Compare = ((Insel*)Node1->Data)->getInselnr()
                - ((Insel*)Node2->Data)->getInselnr();
    }
    else
    {
        Compare = CompareStr(Node1->Text, Node2->Text);
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ObjectTreeGetImageIndex(TObject *Sender,
      TTreeNode *Node)
{
    if(currSzen != 0)
    {
        int index = currSzen->getImageIndex(Node);
        Node->ImageIndex = index;
        Node->SelectedIndex = index;
    }
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::ActionExecute(TObject *Sender)
{
    if(currSzen != 0)
    {
        currSzen->kontorLeeren();
        controlChanged(Sender);
    }
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::comboSchifffarbeChange(TObject *Sender)
{
    if(currSzen != 0)
    {
        currSzen->shipColorChange();
        mapcolorChange(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btKontoreleerenClick(TObject *Sender)
{
    if(currSzen != 0)
    {
        currSzen->kontoreLeeren(SpielerTabControl->TabIndex);
        controlChanged(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btSchiffeleerenClick(TObject *Sender)
{
    if(currSzen != 0)
    {
        currSzen->schiffeLeeren(SpielerTabControl->TabIndex);
        controlChanged(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btKarrenleerenClick(TObject *Sender)
{
    if(currSzen != 0)
    {
        currSzen->karrenLeeren(SpielerTabControl->TabIndex);
        controlChanged(Sender);
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::editSchiffnameChange(TObject *Sender)
{
    if(ObjectTree->Selected != 0)
    {
        ObjectTree->Selected->Text = editSchiffname->Text;
        controlChanged(Sender);
    }
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::ObjectTreeContextPopup(TObject *Sender,
      TPoint &MousePos, bool &Handled)
{
    TTreeNode* node = ObjectTree->GetNodeAt(MousePos.x, MousePos.y);
    if(node != 0)
    {
        ObjectTree->Selected = node;
    }
    node = ObjectTree->Selected;
    Handled = node == 0 || node->Parent != inselTree;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::PaintBox1DragOver(TObject *Sender,
      TObject *Source, int X, int Y, TDragState State, bool &Accept)
{
    // convert X/Y to streched PaintBox
    X = X * IndkSzen::WIDTH / MainForm->PaintBox1->Width;
    Y = Y * IndkSzen::HEIGHT / MainForm->PaintBox1->Height;

    StatusLine->Panels->Items[1]->Text = String(X) + " / " + Y;
    if(ObjectTree->Selected == 0 || ObjectTree->Selected->Parent != inselTree)
    {
        Accept = false;
        return;
    }

    switch(State)
    {
    case dsDragMove:
        TPoint delta = TPoint(X - dragPos.x, Y - dragPos.y);
        dragPos = Point(X,Y);
        Accept = currSzen->moveIslandBy(delta);
        PaintBox1->Invalidate();
        break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PaintBox1DragDrop(TObject *Sender,
      TObject *Source, int X, int Y)
{
    // convert X/Y to streched PaintBox
    X = X * IndkSzen::WIDTH / MainForm->PaintBox1->Width;
    Y = Y * IndkSzen::HEIGHT / MainForm->PaintBox1->Height;

    TPoint delta = TPoint(X - dragPos.x, Y - dragPos.y);
    if(currSzen->moveIslandBy(delta))
    {
        controlChanged(Sender);
        PaintBox1->EndDrag(true);
        dragPos = Point(X,Y);
        canUndoDrag = true;
    }
    else
    {
        delta.x = dragStart.x - X;
        delta.y = dragStart.y - Y;
        currSzen->moveIslandBy(delta);
        PaintBox1->EndDrag(false);
    }
    PaintBox1->Invalidate();
}
//---------------------------------------------------------------------------

int __fastcall TMainForm::keystroke(int key)
{
    switch(key)
    {
    case VK_RIGHT:
    case VK_LEFT:
    case VK_UP:
    case VK_DOWN:
        if(MainPageControl->ActivePage == TabKarte)
        {
            if(ObjectTree->Selected != 0 && ObjectTree->Selected->Parent == inselTree)
            {
                TPoint delta(0,0);
                delta.x = key == VK_LEFT ? -1 : (key == VK_RIGHT ? 1 : 0);
                delta.y = key == VK_UP   ? -1 : (key == VK_DOWN  ? 1 : 0);
                if(currSzen->moveIslandBy(delta))
                {
                    PaintBox1->Invalidate();
                    controlChanged(PaintBox1);
                }
                else
                {
                    // undo
                    delta.x = -delta.x;
                    delta.y = -delta.y;
                    currSzen->moveIslandBy(delta);
                }
                return 1;
            }
        }
        break;
    }
    return 0;
}


void __fastcall TMainForm::Panel9CanResize(TObject *Sender, int &NewWidth,
      int &NewHeight, bool &Resize)
{
    float widthRatio = ((float)NewWidth) / (float)IndkSzen::WIDTH;
    float heightRatio = ((float)NewHeight) / (float)IndkSzen::HEIGHT;
    if(widthRatio < heightRatio)
    {
        NewHeight = ((float)IndkSzen::HEIGHT) * widthRatio;
    }
    else
    if(heightRatio < widthRatio)
    {
        NewWidth = ((float)IndkSzen::WIDTH) * heightRatio;
    }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::UndoIslandMoveUpdate(TObject *Sender)
{
    UndoIslandMove->Enabled = canUndoDrag;
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::UndoIslandMoveExecute(TObject *Sender)
{
    TPoint delta;
    delta.x = dragStart.x - dragPos.x;
    delta.y = dragStart.y - dragPos.y;
    currSzen->moveIslandBy(delta);
    PaintBox1->Invalidate();
    canUndoDrag = false;

    if(currSzen->getNumChanges() == 1)
        currSzen->setModified(false);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::btWarenlagerClick(TObject *Sender)
{
    if(WareForm->ShowModal() == mrOk)
    {
        controlChanged(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ObjectTreeChanging(TObject *Sender,
      TTreeNode *Node, bool &AllowChange)
{
    if(currSzen != 0)
    {
        currSzen->selectionChanging(Node);
    }
    AllowChange = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::comboSchifftypChange(TObject *Sender)
{
    if(currSzen != 0)
    {
        currSzen->shipColorChange();
        imSchiff->Invalidate();
        controlChanged(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btCargoClick(TObject *Sender)
{
    if(SchiffWaren->ShowModal() == mrOk)
    {
        controlChanged(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StShellTreeView1Changing(TObject *Sender,
      TTreeNode *Node, bool &AllowChange)
{
    AllowChange = canClose();            
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormPaint(TObject *Sender)
{
    int w = background->Width;
    int h = background->Height;

    int x = 0;
    while( x < this->Width )
    {
        int y = 0;
        while( y < this->Height )
        {
            Canvas->Draw(x, y, background);
            y += h;
        }
        x += w;
    }
}
//---------------------------------------------------------------------------


