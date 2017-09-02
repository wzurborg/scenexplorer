//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <sysutils.hpp>
#include <windows.hpp>
#include <messages.hpp>
#include <sysutils.hpp>
#include <classes.hpp>
#include <graphics.hpp>
#include <controls.hpp>
#include <forms.hpp>
#include <dialogs.hpp>
#include <stdctrls.hpp>
#include <buttons.hpp>
#include <extctrls.hpp>
#include <menus.hpp>
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>

#include "IndkSzen.h"
#include <StdCtrls.hpp>
#include <ActnList.hpp>
#include <StdActns.hpp>
#include "StShlCtl.hpp"
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Forms.hpp>
#include <ActnCtrls.hpp>
#include <ActnMan.hpp>
#include <ActnMenus.hpp>
#include <ToolWin.hpp>
#include <AppEvnts.hpp>
#include <Graphics.hpp>
#include "SsBase.hpp"
#include "ThemeMgr.hpp"

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
	TStatusBar *StatusLine;
    TMemo *Memo1;
    TPageControl *PageControl1;
    TTabSheet *TabAuftragstext;
    TTabSheet *TabGegner;
    TSplitter *Splitter1;
    TTabSheet *TabStaedte;
    TPanel *Panel1;
    TTabControl *AuftragTabControl;
    TPanel *Panel2;
    TPageControl *MainPageControl;
    TTabSheet *TabAuftraege;
    TTabSheet *TabSettings;
    TSpeedButton *sbRot;
    TSpeedButton *sbBlau;
    TSpeedButton *sbGelb;
    TSpeedButton *sbWeiss;
    TLabel *Label1;
    TTabSheet *TabSpieler;
    TGroupBox *Schiffe;
    TLabeledEdit *editSchiffe;
    TLabeledEdit *editMissNr;
    TLabeledEdit *editMissSubNr;
    TGroupBox *GroupBox2;
    TGroupBox *GroupBox3;
    TLabeledEdit *editTutorflg;
    TLabeledEdit *editCompLevel;
    TLabeledEdit *editGameId;
    TGroupBox *GroupBox4;
    TSpeedButton *sbKillRot;
    TSpeedButton *sbKillBlau;
    TSpeedButton *sbKillGelb;
    TSpeedButton *sbKillWeiss;
    TSpeedButton *sbKillAny;
    TSpeedButton *sbKillPirat;
    TGroupBox *GroupBox5;
    TSpeedButton *sbHelpRot;
    TSpeedButton *sbHelpBlau;
    TSpeedButton *sbHelpGelb;
    TSpeedButton *sbHelpWeiss;
    TSpeedButton *sbHelpAny;
    TLabeledEdit *editHelpWohn;
    TLabeledEdit *editHelpWohnGrp;
    TLabel *lbHelpWohn;
    TComboBox *comboHelpWohnName;
    TGroupBox *gbStadt1;
    TLabel *lbStadt1Wohn;
    TLabeledEdit *editStadt1Wohn;
    TLabeledEdit *editStadt1Bgrp;
    TComboBox *comboStadt1Bgrp;
    TGroupBox *gbStadt2;
    TLabel *lbStadt2Wohn;
    TLabeledEdit *editStadt2Wohn;
    TLabeledEdit *editStadt2Bgrp;
    TComboBox *comboStadt2Bgrp;
    TGroupBox *gbStadt3;
    TLabel *lbStadt3Wohn;
    TLabeledEdit *editStadt3Wohn;
    TLabeledEdit *editStadt3Bgrp;
    TComboBox *comboStadt3Bgrp;
    TCheckBox *cbStadt1;
    TCheckBox *cbStadt2;
    TCheckBox *cbStadt3;
    TGroupBox *GroupBox6;
    TCheckBox *cbSchloss;
    TCheckBox *cbKathedrale;
    TTabSheet *TabHandel;
    TGroupBox *GroupBox7;
    TLabeledEdit *editStore1;
    TStaticText *labelStore1;
    TComboBox *comboStore1;
    TCheckBox *cbStore1;
    TCheckBox *cbStore2;
    TGroupBox *GroupBox8;
    TLabeledEdit *editStore2;
    TStaticText *labelStore2;
    TComboBox *comboStore2;
    TGroupBox *GroupBox9;
    TCheckBox *cbTBalance;
    TEdit *editTBalance;
    TCheckBox *cbBalance;
    TEdit *editBalance;
    TGroupBox *GroupBox10;
    TCheckBox *cbMonopol1;
    TCheckBox *cbMonopol2;
    TComboBox *comboMonopol1;
    TComboBox *comboMonopol2;
    TLabeledEdit *editStadtlowfrmdwohn;
    TLabel *lbStadtlowfrmdwohn;
    TLabeledEdit *editStadtlowfrmdbgwohn;
    TComboBox *comboStadtlowfrmdbgnr;
    TLabeledEdit *editStadtanzminfrmd;
    TLabel *lbStadtanzminfrmd;
    TCheckBox *cbHelpWohn;
    TCheckBox *cbStadtlowfrmd;
    TCheckBox *cbStadtanzminfrmd;
    TSpeedButton *sbHelpEingeb;
    TPanel *Panel3;
    TTabControl *SpielerTabControl;
    TPanel *Panel4;
    TImageList *ImageList1;
    TTabSheet *TabKarte;
    TSpeedButton *btnPiraten;
    TSpeedButton *btnDuerren;
    TSpeedButton *btnVulkan;
    TSpeedButton *btnErz;
    TSpeedButton *btnHaendler;
    TSpeedButton *btnWaffen;
    TGroupBox *grpKampagne;
    TLabeledEdit *editKampagne;
    TCheckBox *cbKampagne;
    TButton *btnKampagne;
    TGroupBox *GroupBox1;
    TLabeledEdit *editGuthaben;
    TGroupBox *GroupBox11;
    TCheckBox *cbWohnanz;
    TLabeledEdit *editWohnanz;
    TLabel *lbWohnanz;
    TCheckBox *cbGuthaben;
    TActionList *ActionList1;
    TAction *SwitchPiraten;
    TAction *SwitchErz;
    TAction *SwitchVulkane;
    TAction *SwitchDuerren;
    TAction *SwitchHaendler;
    TAction *SwitchWaffen;
    TAction *SaveAction;
    TFileSaveAs *SaveAsAction;
    TAction *RevertAction;
    TFileExit *ExitAction;
    TToolBar *ToolBar1;
    TToolButton *ToolButton1;
    TToolButton *ToolButton2;
    TToolButton *ToolButton3;
    TMainMenu *MainMenu1;
    TMenuItem *Datei1;
    TMenuItem *Speichern1;
    TMenuItem *Speichernunter1;
    TMenuItem *Wiederherstellen1;
    TMenuItem *Beenden1;
    TImageList *ImageList2;
    TToolButton *ToolButton4;
    TImageList *ImageList3;
    TFileOpen *OpenAction;
    TMenuItem *Open1;
    TToolButton *ToolButton5;
    TFileSaveAs *SaveInselAction;
    TToolButton *ToolButton6;
    TPopupMenu *InselPopup;
    TMenuItem *SaveAs1;
    TToolButton *ToolButton7;
    TToolButton *ToolButton8;
    TGroupBox *GroupBox13;
    TLabel *Label2;
    TLabeledEdit *editMoney;
    TComboBox *comboKind;
    TStaticText *StaticText1;
    TComboBoxEx *comboPlayerColor;
    TLabeledEdit *editName;
    TGroupBox *GroupBox12;
    TLabeledEdit *editDenkanz;
    TLabeledEdit *editDenkbauanz;
    TGroupBox *GroupBox15;
    TLabeledEdit *editTriumphanz;
    TLabeledEdit *editTriumphbauanz;
    TGroupBox *GroupBox16;
    TLabeledEdit *editKillsoldatanz;
    TLabeledEdit *editLosssoldatanz;
    TGroupBox *GroupBox17;
    TLabeledEdit *editKillshipanz;
    TLabeledEdit *editLossshipanz;
    TGroupBox *GroupBox18;
    TCheckBox *cbSchlossbau;
    TCheckBox *cbKathedralebau;
    TGroupBox *GroupBox19;
    TLabeledEdit *editHumanwohnmax;
    TLabeledEdit *editWohnmin;
    TGroupBox *GroupBox20;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TCheckBox *cbWohnmin;
    TCheckBox *cbHumanwohnmax;
    TTrackBar *tbBgruppmin;
    TTrackBar *tbBgruppmaxhuman;
    TCheckBox *cbBgruppmaxhuman;
    TCheckBox *cbBgruppmin;
    TEdit *editBgruppmin;
    TEdit *editBgruppmaxhuman;
    TGroupBox *GroupBox14;
    TButton *Button1;
    TLabel *Label3;
    TLabel *lbBgruppmin1;
    TLabel *lbBgruppmaxhuman1;
    TLabel *lbBgruppmin2;
    TLabel *lbBgruppmaxhuman2;
    TImage *Image1;
    TImage *Image3;
    TImage *Image2;
    TImage *Image4;
    TImage *Image5;
    TImage *imDaumen1;
    TImageList *DaumenList;
    TImage *imDaumen2;
    TAction *DeleteIslandAction;
    TMenuItem *Insellschen1;
    TToolButton *ToolButton9;
    TGroupBox *GroupBox21;
    TEdit *editSzenName;
    TPanel *Panel5;
    TPanel *Panel6;
    TSpeedButton *btStaedte;
    TSpeedButton *btSchiffe;
    TTreeView *ObjectTree;
    TImageList *TreeImages;
    TPanel *Panel7;
    TStaticText *lbTitle3;
    TStaticText *lbTitle4;
    TStaticText *lbTitle2;
    TStaticText *lbTitle1;
    TImage *imTitle1;
    TPaintBox *PaintBox1;
    TPageControl *pcKarte;
    TTabSheet *tabSchiff;
    TGroupBox *gbSchiff;
    TLabel *Label8;
    TLabel *Label9;
    TLabeledEdit *editSchiffname;
    TComboBoxEx *comboSchifffarbe;
    TLabeledEdit *editSchiffkanonen;
    TComboBox *comboSchifftyp;
    TTabSheet *tabStadt;
    TGroupBox *gbStadt;
    TLabel *Label7;
    TLabeledEdit *editStadtname;
    TComboBoxEx *comboStadtfarbe;
    TCheckBox *cbBaustop;
    TPanel *Panel8;
    TButton *btWarenlager;
    TButton *btCargo;
    TGroupBox *GroupBox22;
    TButton *btKontoreleeren;
    TButton *btSchiffeleeren;
    TButton *btKarrenleeren;
    TTrackBar *tbEnergie;
    TLabel *Label10;
    TUpDown *UpDown1;
    TPanel *Panel9;
    TEditUndo *UndoIslandMove;
    TToolButton *ToolButton10;
    TLabel *Label11;
    TLabel *Label12;
    TImageList *WarenImages;
    TImageList *WappenImages;
    TImage *imSchiff;
    TImageList *ShipImages;
    TStShellTreeView *StShellTreeView1;  // E&xit
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ShowHint(TObject *Sender);
    void __fastcall StShellTreeView1FilterItem(TObject *Sender,
          TStShellItem *ShellItem, bool &Accept);
    void __fastcall StShellTreeView1FolderSelected(TObject *Sender,
          TStShellFolder *Folder);
    void __fastcall AuftragTabControlChange(TObject *Sender);
    void __fastcall sbKillRotClick(TObject *Sender);
    void __fastcall sbKillBlauClick(TObject *Sender);
    void __fastcall sbKillGelbClick(TObject *Sender);
    void __fastcall sbKillWeissClick(TObject *Sender);
    void __fastcall sbKillAnyClick(TObject *Sender);
    void __fastcall cbStadt1Click(TObject *Sender);
    void __fastcall cbStadt2Click(TObject *Sender);
    void __fastcall cbStadt3Click(TObject *Sender);
    void __fastcall cbStore1Click(TObject *Sender);
    void __fastcall cbStore2Click(TObject *Sender);
    void __fastcall cbTBalanceClick(TObject *Sender);
    void __fastcall cbBalanceClick(TObject *Sender);
    void __fastcall cbMonopol1Click(TObject *Sender);
    void __fastcall cbMonopol2Click(TObject *Sender);
    void __fastcall cbHelpWohnClick(TObject *Sender);
    void __fastcall cbStadtlowfrmdClick(TObject *Sender);
    void __fastcall cbStadtanzminfrmdClick(TObject *Sender);
    void __fastcall SpielerTabControlChange(TObject *Sender);
    void __fastcall lbColorClick(TObject *Sender);
    void __fastcall PaintBox1Paint(TObject *Sender);
    void __fastcall SwitchPiratenUpdate(TObject *Sender);
    void __fastcall SwitchErzUpdate(TObject *Sender);
    void __fastcall SwitchVulkaneUpdate(TObject *Sender);
    void __fastcall SwitchDuerrenUpdate(TObject *Sender);
    void __fastcall SwitchHaendlerUpdate(TObject *Sender);
    void __fastcall SwitchWaffenUpdate(TObject *Sender);
    void __fastcall btnKampagneClick(TObject *Sender);
    void __fastcall cbKampagneClick(TObject *Sender);
    void __fastcall MainPageControlChanging(TObject *Sender,
          bool &AllowChange);
    void __fastcall AuftragTabControlChanging(TObject *Sender,
          bool &AllowChange);
    void __fastcall SpielerTabControlChanging(TObject *Sender,
          bool &AllowChange);
    void __fastcall cbGuthabenClick(TObject *Sender);
    void __fastcall cbWohnanzClick(TObject *Sender);
    void __fastcall PaintBox1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall SaveActionExecute(TObject *Sender);
    void __fastcall SaveActionUpdate(TObject *Sender);
    void __fastcall RevertActionExecute(TObject *Sender);
    void __fastcall RevertActionUpdate(TObject *Sender);
    void __fastcall SaveAsActionAccept(TObject *Sender);
    void __fastcall SaveAsActionBeforeExecute(TObject *Sender);
    void __fastcall SaveAsActionUpdate(TObject *Sender);
    void __fastcall SaveInselActionUpdate(TObject *Sender);
    void __fastcall OpenActionAccept(TObject *Sender);
    void __fastcall SaveInselActionBeforeExecute(TObject *Sender);
    void __fastcall PaintBox1ContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
    void __fastcall SaveInselActionAccept(TObject *Sender);
    void __fastcall controlChanged(TObject *Sender);
    void __fastcall tbBgruppminChange(TObject *Sender);
    void __fastcall tbBgruppmaxhumanChange(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall editBgruppminChange(TObject *Sender);
    void __fastcall cbBgruppminClick(TObject *Sender);
    void __fastcall cbBgruppmaxhumanClick(TObject *Sender);
    void __fastcall cbWohnminClick(TObject *Sender);
    void __fastcall cbHumanwohnmaxClick(TObject *Sender);
    void __fastcall editBgruppmaxhumanChange(TObject *Sender);
    void __fastcall numericKeyPress(TObject *Sender, char &Key);
    void __fastcall btStaedteClick(TObject *Sender);
    void __fastcall PaintBox1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall DeleteIslandActionUpdate(TObject *Sender);
    void __fastcall DeleteIslandActionExecute(TObject *Sender);
    void __fastcall mapcolorChange(TObject *Sender);
    void __fastcall comboStadtfarbeChange(TObject *Sender);
    void __fastcall ObjectTreeChange(TObject *Sender, TTreeNode *Node);
    void __fastcall ObjectTreeCompare(TObject *Sender, TTreeNode *Node1,
          TTreeNode *Node2, int Data, int &Compare);
    void __fastcall ObjectTreeGetImageIndex(TObject *Sender,
          TTreeNode *Node);
    void __fastcall ActionExecute(TObject *Sender);
    void __fastcall comboSchifffarbeChange(TObject *Sender);
    void __fastcall btKontoreleerenClick(TObject *Sender);
    void __fastcall btSchiffeleerenClick(TObject *Sender);
    void __fastcall btKarrenleerenClick(TObject *Sender);
    void __fastcall editSchiffnameChange(TObject *Sender);
    void __fastcall ObjectTreeContextPopup(TObject *Sender,
          TPoint &MousePos, bool &Handled);
    void __fastcall PaintBox1DragOver(TObject *Sender, TObject *Source,
          int X, int Y, TDragState State, bool &Accept);
    void __fastcall PaintBox1DragDrop(TObject *Sender, TObject *Source,
          int X, int Y);
    void __fastcall Panel9CanResize(TObject *Sender, int &NewWidth,
          int &NewHeight, bool &Resize);
    void __fastcall UndoIslandMoveUpdate(TObject *Sender);
    void __fastcall UndoIslandMoveExecute(TObject *Sender);
    void __fastcall btWarenlagerClick(TObject *Sender);
    void __fastcall ObjectTreeChanging(TObject *Sender, TTreeNode *Node,
          bool &AllowChange);
    void __fastcall comboSchifftypChange(TObject *Sender);
    void __fastcall btCargoClick(TObject *Sender);
    void __fastcall WndProc(Messages::TMessage &Message);
    void __fastcall StShellTreeView1Changing(TObject *Sender,
          TTreeNode *Node, bool &AllowChange);
    void __fastcall FormPaint(TObject *Sender);

private:
    Graphics::TBitmap* background;
    IndkSzen* currSzen;
    bool __fastcall isSupportedFile(String) const;        // private user declarations
    bool __fastcall loadSzenario(String path);
    TWinControl* lastActiveCtrl;
    bool __fastcall canClose();
    String currentFolder;
    TTreeNode* inselTree;
    TTreeNode* shipTree;
    TPoint dragStart;
    TPoint dragPos;
    Graphics::TBitmap* offscreen;
    bool canUndoDrag;
    void __fastcall openInsel( String path );
    AnsiString getRegistryValue(void* root, AnsiString key, AnsiString name);
    void __fastcall SetDaumen(TCheckBox* cb, TTrackBar* tb, TImage* im, bool inverse=false);
    static LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);
//    bool __fastcall (__closure *TWindowHook) HookFunction(Messages::TMessage& Message);
    int __fastcall keystroke(int key);

    int count;

public:         // public user declarations
	virtual __fastcall TMainForm(TComponent* Owner);
    virtual __fastcall ~TMainForm();
    void __fastcall SetTitleFile(AnsiString fname);
    String __fastcall GetBgrupp(int value);
    inline IndkSzen* getCurrSzen() const;
};
//---------------------------------------------------------------------------
inline IndkSzen* TMainForm::getCurrSzen() const
{
    return currSzen;
}
//---------------------------------------------------------------------------
extern TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
