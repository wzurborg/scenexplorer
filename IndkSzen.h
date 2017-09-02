//---------------------------------------------------------------------------

#ifndef IndkSzenH
#define IndkSzenH
//---------------------------------------------------------------------------
#include <system.hpp>
#include <dstring.h>
#include <buttons.hpp>
#include <comctrls.hpp>
#include "Anno1602read.h"

class Insel;

class IndkSzen {
public:
    enum Dimensions
    {
        WIDTH = 512,
        HEIGHT = 352
    };
    IndkSzen();
    static String GetInstallDir();
    int saveSzen(const AnsiString& outPath);
    int readSzen(const AnsiString& inPath);
    virtual ~IndkSzen();
    void __fastcall paint(TCanvas* canvas);
    bool __fastcall selectObject(int x, int y, TShiftState shift);
    void __fastcall putSettings(void);
    void __fastcall putAuftrag(int index);
    void __fastcall putPlayer(int index);
    void __fastcall getAuftrag(int index);
    void __fastcall getPlayer(int index);
    void __fastcall setModified(bool mod);
    bool __fastcall isModified() const;
    String __fastcall getPath() const;
    Insel* __fastcall getSelectedIsland() const;
    TSTADTSAVE* __fastcall getSelectedStadt() const;
    TKONTORSAVE* __fastcall getSelectedKontor() const;
    void __fastcall saveSelectedIsland(String path);
    TSHIPSAVE* __fastcall getSelectedShip() const;
    AnsiString __fastcall getInselDescription() const;
    void __fastcall saveKampagne(TFileStream*);
    TColor playerColor(int player);
    void __fastcall mouseHover(int x, int y, TShiftState shift);
    void __fastcall deleteSelectedInsel();
    void __fastcall putStadt(TSTADTSAVE* stadt);
    void __fastcall putSchiff(TSHIPSAVE* ship);
    void __fastcall stadtColorChange();
    void __fastcall shipColorChange();
    int __fastcall getImageIndex(TTreeNode* node);
    void __fastcall kontorLeeren();
    void __fastcall schiffLeeren();
    void __fastcall kontoreLeeren(int player);
    void __fastcall schiffeLeeren(int player);
    void __fastcall karrenLeeren(int player);
    bool __fastcall moveIslandBy(const TPoint& delta);
    int __fastcall getNumChanges() const;
    void __fastcall selectionChanging(TTreeNode* node);
    void __fastcall selectionChanged(TTreeNode* node);
    static int schiff2index(int schiff);

private:
    static TColor PlayerColors[];
    static String* _installDir;
    TAUFTRAGSAVE auftrag[4];
    TPLAYERSAVE player[7];
    TTIMERSAVE timers;
    TSZENESAVE*   szene;
    TSpeedButton* auftragButtons[4];
    TSpeedButton* killButtons[5];
    TSpeedButton* helpButtons[4];
    TLabeledEdit* editStadtWohn[3];
    TLabeledEdit* editStadtBgrp[3];
    TComboBox*    comboStadtBgrp[3];
    TCheckBox*    cbStadt[3];
    TGroupBox*    gbStadt[3];
    TLabel*       lbStadtWohn[3];
    TCheckBox*    cbInfra[32];
    TTreeNode*    inselTree;
    TTreeNode*    shipTree;

    TList*        inseln;
    TList*        schiffe;
    Insel*        currInsel;
    TList*        chunks;
    unsigned      fileLength;
    int kampagne;
    int numChanges;   // counts changes
    String name;
    String path;
    bool dragValid;

    int handleAuftrag(char* buffer, unsigned length);
    int handleTimers(char* buffer, unsigned length);
    int handleSzene(char* buffer, unsigned length);
    int __fastcall handlePlayer(char* buffer, unsigned length);
    int __fastcall handleStadt(char* buffer, unsigned length);
    int __fastcall handleKontor(char* buffer, unsigned length);
    int __fastcall handleShip(char* buffer, unsigned length);
    int __fastcall handleInsel(char* buffer, unsigned length, int type);
    int __fastcall handleInselhaus(char* buffer, unsigned length);
    int __fastcall handleKampagne(char* buffer, unsigned length);
    int __fastcall handleHirsch(char* buffer, unsigned length);
    int __fastcall handleName(char* buffer, unsigned length);
    int __fastcall handleCustom(char* buffer, unsigned length);

    int __fastcall savePlayers(TFileStream* out);
    int __fastcall saveAuftrag(TFileStream* out);
    int __fastcall saveTimers(TFileStream* out);
    int __fastcall saveCustom(TFileStream* out);
    int __fastcall saveSchiffe(TFileStream* out);
    int __fastcall saveInseln(TFileStream* out);
    int __fastcall saveStaedte(TFileStream* out);
    int __fastcall saveKontore(TFileStream* out);


    Insel* __fastcall getInsel(int x, int y, TShiftState shift);
    TSTADTSAVE* __fastcall getStadt(int x, int y, TShiftState shift);
    TSHIPSAVE* __fastcall getSchiff(int x, int y, TShiftState shift);

    void __fastcall saveStadt(TSTADTSAVE* stadt);
    void __fastcall saveSchiff(TSHIPSAVE* schiff);
    void __fastcall drawSchiff(TSHIPSAVE* schiff);

    void __fastcall setChildrenState(TControl* parent, bool state);

};

#endif
