//---------------------------------------------------------------------------


#pragma hdrstop

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Classes.hpp>
#include <Dialogs.hpp>
#include "IndkSzen.h"
#include "Main.h"
#include "insel.h"
#include "inselhaus.h"
#include "stadt.h"
#include "FreiFormCpp.h"
#include "WareFormCpp.h"
#include "SchiffWarenCpp.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

TColor IndkSzen::PlayerColors[] =
{ clRed, clBlue, clYellow, clWhite, clBlack, clGreen, clPurple, TColor(0x00406389) };

static const String leer;
static const int C_ShipRadius = 6;

String* IndkSzen::_installDir = 0;

    enum MonopolyGood
    {
       erz = 0x02,
       gold = 0x03,
       kakao = 0x33,
       baumwolle = 0x31,
       gewuerze = 0x2f,
       tabak = 0x2e,
       wein = 0x32,
       zuckerrohr = 0x30
    };

    enum PlayerKind
    {
        missing = 10,
        mensch = 0,
        computer = 12,
        haendler = 13,
        eingeborene = 11,
        pirat = 14
    };

static const int schiffTyp[]  = {21, 23, 25, 27, 29, 31, 37};
static const int schiffKind[] = { 1,  1,  1,  1,  2,  3,  5};
static const int schiffEnergie[] = { 1600, 2560, 2080, 3840, 3040, 3040, 448 };

static int waremap[] = { erz, gold, kakao, baumwolle, gewuerze, tabak, wein, zuckerrohr };
static int ware2index( int ware ) {
    for(int i=0; i<8; i++)
        if(waremap[i] == ware)
            return i;
    return -1;
}

static int index2ware( int index ) {
    return waremap[index];
}

static int kindmap[] = {missing, mensch, computer, haendler, eingeborene, pirat};
static int kind2index(int kind) {
    for(int i=0; i<6; i++) {
        if(kindmap[i] == kind)
            return i;
    }
    return -1;
}

static int index2kind( int index ) {
    return kindmap[index];
}

int IndkSzen::schiff2index(int schiff)
{
    for(int i=0; i<7; i++)
    {
        if(schiffTyp[i] == schiff)
            return i;
    }
    return -1;
}

static int getEnergie(int index, int pos)
{
    return schiffEnergie[index] * pos / 100;
}

static int getPos(int index, int energie)
{
    return energie * 100 / schiffEnergie[index];
}

TColor IndkSzen::playerColor(int p)
{
    if(p > 6) return PlayerColors[7];
    return PlayerColors[player[p].colornr];
}

String IndkSzen::GetInstallDir(void)
{
    if(_installDir == 0) {
        // Get Savegame directory from registry
        TRegistry* Registry = new TRegistry;
        Registry->RootKey = HKEY_LOCAL_MACHINE;
        _installDir = new String();
        try
        {
            Registry->OpenKeyReadOnly( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\1602.EXE" );
            *_installDir = Registry->ReadString( "Path" );
        }
        __finally
        {
            delete Registry;
        }

        if( !DirectoryExists( *_installDir ) )
            *_installDir = String();
    }

    return *_installDir;
}


IndkSzen::IndkSzen()
 : kampagne(-1),numChanges(0),dragValid(true)
{
    inselTree = MainForm->ObjectTree->Items->Item[0];
    shipTree = MainForm->ObjectTree->Items->Item[1];

    for(int i=0; i<4; i++) auftrag[i].nr = -1;

    inseln = new TList();
    schiffe = new TList();

    auftragButtons[0] = MainForm->sbRot;
    auftragButtons[1] = MainForm->sbBlau;
    auftragButtons[2] = MainForm->sbGelb;
    auftragButtons[3] = MainForm->sbWeiss;

    killButtons[0] = MainForm->sbKillRot;
    killButtons[1] = MainForm->sbKillBlau;
    killButtons[2] = MainForm->sbKillGelb;
    killButtons[3] = MainForm->sbKillWeiss;
    killButtons[4] = MainForm->sbKillPirat;

    helpButtons[0] = MainForm->sbHelpRot;
    helpButtons[1] = MainForm->sbHelpBlau;
    helpButtons[2] = MainForm->sbHelpGelb;
    helpButtons[3] = MainForm->sbHelpWeiss;

    gbStadt[0] = MainForm->gbStadt1;
    gbStadt[1] = MainForm->gbStadt2;
    gbStadt[2] = MainForm->gbStadt3;

    cbStadt[0] = MainForm->cbStadt1;
    cbStadt[1] = MainForm->cbStadt2;
    cbStadt[2] = MainForm->cbStadt3;

    lbStadtWohn[0] = MainForm->lbStadt1Wohn;
    lbStadtWohn[1] = MainForm->lbStadt2Wohn;
    lbStadtWohn[2] = MainForm->lbStadt3Wohn;

    editStadtWohn[0] = MainForm->editStadt1Wohn;
    editStadtWohn[1] = MainForm->editStadt2Wohn;
    editStadtWohn[2] = MainForm->editStadt3Wohn;

    editStadtBgrp[0] = MainForm->editStadt1Bgrp;
    editStadtBgrp[1] = MainForm->editStadt2Bgrp;
    editStadtBgrp[2] = MainForm->editStadt3Bgrp;

    comboStadtBgrp[0] = MainForm->comboStadt1Bgrp;
    comboStadtBgrp[1] = MainForm->comboStadt2Bgrp;
    comboStadtBgrp[2] = MainForm->comboStadt3Bgrp;

    cbInfra[ 0] = FreiForm->cbInfra00;
    cbInfra[ 1] = FreiForm->cbInfra01;
    cbInfra[ 2] = FreiForm->cbInfra02;
    cbInfra[ 3] = FreiForm->cbInfra03;
    cbInfra[ 4] = FreiForm->cbInfra04;
    cbInfra[ 5] = FreiForm->cbInfra05;
    cbInfra[ 6] = FreiForm->cbInfra06;
    cbInfra[ 7] = FreiForm->cbInfra07;
    cbInfra[ 8] = FreiForm->cbInfra08;
    cbInfra[ 9] = FreiForm->cbInfra09;
    cbInfra[10] = FreiForm->cbInfra10;
    cbInfra[11] = FreiForm->cbInfra11;
    cbInfra[12] = FreiForm->cbInfra12;
    cbInfra[13] = FreiForm->cbInfra13;
    cbInfra[14] = FreiForm->cbInfra14;
    cbInfra[15] = FreiForm->cbInfra15;
    cbInfra[16] = FreiForm->cbInfra16;
    cbInfra[17] = FreiForm->cbInfra17;
    cbInfra[18] = FreiForm->cbInfra18;
    cbInfra[19] = FreiForm->cbInfra19;
    cbInfra[20] = FreiForm->cbInfra20;
    cbInfra[21] = FreiForm->cbInfra21;
    cbInfra[22] = FreiForm->cbInfra22;
    cbInfra[23] = FreiForm->cbInfra23;
    cbInfra[24] = FreiForm->cbInfra24;
    cbInfra[25] = FreiForm->cbInfra25;
    cbInfra[26] = FreiForm->cbInfra26;
    cbInfra[27] = FreiForm->cbInfra27;
    cbInfra[28] = FreiForm->cbInfra28;
    cbInfra[29] = FreiForm->cbInfra29;
    cbInfra[30] = FreiForm->cbInfra30;
    cbInfra[31] = FreiForm->cbInfra31;

    MainForm->editSzenName->Text = leer;
}

IndkSzen::~IndkSzen()
{
    for(int i=0; i<inseln->Count; i++)
    {
        delete (Insel*)inseln->Items[i];
    }
    delete inseln;

    for(int i=0; i<chunks->Count; i++)
        delete [] chunks->Items[i];
    delete chunks;
}

int IndkSzen::readSzen(const AnsiString& inPath)
{
    chunks = new TList();
    TFileStream* szenFile = new TFileStream(inPath, fmOpenRead);
//    String namefile = ChangeFileExt(inPath, ".chk");
//    TFileStream* nfs = new TFileStream(namefile, fmCreate);

    TCHUNK chunk;
    const unsigned chunklen = sizeof(TCHUNK);
    while(szenFile->Read(&chunk, chunklen) == chunklen)
    {
//        char chbuf[500];
//        sprintf(chbuf, "%s - %d\n", chunk.name, chunk.lengh);
//        nfs->Write(chbuf, strlen(chbuf));

        if(strlen(chunk.name) > 15 || chunk.lengh > 1000000 || chunk.lengh < 0)
        {
            String msg("Strange chunk: ");
            msg += chunk.name;
            msg += " / ";
            msg += chunk.lengh;
//            ShowMessage(msg.c_str());
            break;
        }

        char* buffer = new char[chunklen + chunk.lengh];
        memcpy(buffer, &chunk, chunklen);
        if(chunk.lengh > 0)
            szenFile->Read(&buffer[chunklen], chunk.lengh);
        chunks->Add(buffer);
    }
    delete szenFile;
//    delete nfs;

    bool success = false;
    bool done = false;
    for(int i=0; i<chunks->Count; i++)
    {
        TCHUNK* chunk = (TCHUNK*)chunks->Items[i];
        char* buffer = ((char*)chunk) + chunklen;
        if(chunk->lengh > 0) {
            AnsiString name(chunk->name);
            int result = 0;
            if(name == "INSEL5") {
                result = handleInsel(buffer, chunk->lengh, 0);
            }
            else if(name == "HIRSCH2") {
                result = handleHirsch(buffer, chunk->lengh);
            }
            else if(name == "SZENE_KAMPAGNE") {
                result = handleKampagne(buffer, chunk->lengh);
            }
            else if(name == "INSEL_MAXFUN") {
                result = handleInsel(buffer, chunk->lengh, 1);
            }
            else if(name == "INSELHAUS") {
                result = handleInselhaus(buffer, chunk->lengh);
            }
            else if(name == "AUFTRAG4") {
                result = handleAuftrag(buffer, chunk->lengh);
            }
            else if(name == "TIMERS") {
                result = handleTimers(buffer, chunk->lengh);
                if(result == 0)
                    success = true;
                done = true;    // last chunk
            }
            else if(name == "SZENE") {
                result = handleSzene(buffer, chunk->lengh);
            }
            else if(name == "PLAYER4") {
                result = handlePlayer(buffer, chunk->lengh);
            }
            else if(name == "STADT4") {
                result = handleStadt(buffer, chunk->lengh);
            }
            else if(name == "KONTOR2") {
                result = handleKontor(buffer, chunk->lengh);
            }
            else if(name == "SHIP4") {
                result = handleShip(buffer, chunk->lengh);
            }
            else if(name == "NAME") {
                result = handleName(buffer, chunk->lengh);
            }
            else if(name == "CUSTOM") {
                result = handleCustom(buffer, chunk->lengh);
            }

            if(result != 0 || done)
                break;
        }
    }  // end while

    putSchiff(0);
    putStadt(0);
    
    if(success) {
        path = inPath;
        name = ExtractFileName(inPath);
        return 0;
    }
    return 1;
}

int IndkSzen::saveSzen(const AnsiString& outPath) {
    TFileStream* outSzen;
    AnsiString tempname = ExtractFileDir(outPath) + "\\temp.file";
    try {
        outSzen = new TFileStream(tempname, fmCreate);
    }
    catch(...) {
        return 1;   // can't open
    }

    TCHUNK* chunk;
    bool success = true;
    bool inselnDone = false;

    saveStadt(getSelectedStadt());   // nur in memory
    saveSchiff(getSelectedShip());   // nur in memory

//    saveCustom(outSzen); VERSUCH!
    saveKampagne(outSzen);

    for(int i=0; i<chunks->Count; i++)
    {
        chunk = (TCHUNK*)chunks->Items[i];
        AnsiString name(chunk->name);

        if(name == "INSEL_MAXFUN" || name == "INSEL5")
        {
            // save inseln
            if(!inselnDone)
            {
                saveInseln(outSzen);
//                saveStaedte(outSzen);
//                saveKontore(outSzen);
            }
            inselnDone = true;
        }
        else
        if(name == "INSELHAUS" || name == "HIRSCH2" ||
           name == "STADT4"    || name == "KONTOR2")
        {
            // already saved with island
        }
        else
        if(name == "PLAYER4") {
            savePlayers(outSzen);
        }
//        else
//        if(name == "SZENE") {
//            saveSzene(outSzen);
//        }
        else
        if(name == "SZENE_KAMPAGNE") {
            // do nothing
        }
        else
        if(name == "AUFTRAG4") {
            saveAuftrag(outSzen);
        }
        else if(name == "TIMERS") {
            // save TIMERS chunk last
            saveTimers(outSzen);
        }
        else if(name == "SHIP4") {
            saveSchiffe(outSzen);
        }
        else
        {
            outSzen->Write(chunk, sizeof(TCHUNK) + chunk->lengh);
        }
    } // end while

    delete outSzen;

    if( FileExists(outPath) ) {
        DeleteFile(outPath);
    }

    if( !RenameFile(tempname, outPath) ) {
        success = false;
        DeleteFile(tempname);
    }

    if(success) {
        name = ExtractFileName(outPath);
        path = outPath;
        setModified(false);
        return 0;
    }
    return 1;
}

int IndkSzen::handleAuftrag(char* buffer, unsigned length) {
    // multiple AUFTRAG in one chunk!!
    memset(&auftrag[0], 0, 4*sizeof(TAUFTRAGSAVE));
    memcpy(&auftrag[0], buffer, length);
    return 0;
}

int IndkSzen::handleTimers(char* buffer, unsigned length) {
    memcpy(&timers, buffer, length);
    return 0;
}

int IndkSzen::handleSzene(char* buffer, unsigned length) {
//    memcpy(&szene, buffer, length);
    szene = (TSZENESAVE*)buffer;
    for(int i=0; i<szene->inselanz; i++) {
        currInsel = new Insel(szene->insel[i]);
        int inselnr = currInsel->getInselnr();
        if(inselnr >= inseln->Count)
            inseln->Count = inselnr+1;
        inseln->Items[inselnr] = currInsel;
        TTreeNode* node = MainForm->ObjectTree->Items->AddChildObject(
                inselTree, currInsel->getDescr(), currInsel);
        currInsel->setNode(node);
    }

    return 0;
}

int __fastcall IndkSzen::handlePlayer(char* buffer, unsigned length)
{
    // Multiple PLAYER in one chunk!
    memset(&player[0], 0, 7*sizeof(TPLAYERSAVE));
    memcpy(&player[0], buffer, length);
    return 0;
}

int __fastcall IndkSzen::handleHirsch(char* buffer, unsigned length)
{
    THIRSCHSAVE* hirsch = (THIRSCHSAVE*)buffer;
    for(unsigned i=0; i<length/sizeof(THIRSCHSAVE); i++)
    {
        ((Insel*)inseln->Items[hirsch->inselnr])->addHirsch(&hirsch[i]);
    }
    return 0;
}

int __fastcall IndkSzen::handleStadt(char* buffer, unsigned length)
{
    TSTADTSAVE* stadt = (TSTADTSAVE*)buffer;
    for(unsigned i=0; i<length/sizeof(TSTADTSAVE); i++)
    {
        Insel* insel = (Insel*)inseln->Items[stadt[i].inselnr];
        insel->addStadt(&stadt[i]);
        TTreeNode* node = (TTreeNode*)insel->getNode();
        MainForm->ObjectTree->Items->AddChildObject(
                node, stadt[i].name, &stadt[i]);
    }
    return 0;
}

int __fastcall IndkSzen::handleShip(char* buffer, unsigned length)
{
    TSHIPSAVE* ship = (TSHIPSAVE*)buffer;
    unsigned num = length/sizeof(TSHIPSAVE);
    schiffe->Count = num;
    for(unsigned i=0; i<num; i++)
    {
        schiffe->Items[i] = &ship[i];
        TTreeNode* node =
            MainForm->ObjectTree->Items->AddChild(shipTree, ship[i].name);
        node->Data = &ship[i];
    }
    return 0;
}

int __fastcall IndkSzen::handleKontor(char* buffer, unsigned length)
{
    TKONTORSAVE* kontor = (TKONTORSAVE*)buffer;
    for(unsigned i=0; i<length/sizeof(TKONTORSAVE); i++)
    {
        ((Insel*)inseln->Items[kontor[i].inselnr])->addKontor(&kontor[i]);
    }
    return 0;
}

int __fastcall IndkSzen::saveAuftrag(TFileStream* out)
{
    getAuftrag(MainForm->AuftragTabControl->TabIndex);

    int num;
    for(num=0; num<4; num++) {
        if(String(auftrag[num].infotxt).Trim().IsEmpty()) {
            break;
        }
    }

    TCHUNK chunk;
    sprintf(chunk.name, "AUFTRAG4");
    chunk.lengh = num * sizeof(TAUFTRAGSAVE);
    out->Write(&chunk, sizeof(TCHUNK));
    out->Write(&auftrag[0], chunk.lengh);
    return 0;
}

void __fastcall IndkSzen::getAuftrag(int index)
{
    TAUFTRAGSAVE& a = auftrag[index];
    a.nr = index;
    strncpy(a.infotxt, MainForm->Memo1->Lines->Text.c_str(), sizeof(a.infotxt)-1);
    a.infotxt[sizeof(a.infotxt)-1] = '\0';

    for(int i=0; i<3; i++) {
        if(cbStadt[i]->Checked) {
            a.flags |= (1 << i);    // set flag
            a.stadtmin[i].wohnanz = editStadtWohn[i]->Text.ToIntDef(0);
            a.stadtmin[i].bgruppwohn = editStadtBgrp[i]->Text.ToIntDef(0);
            a.stadtmin[i].bgruppnr = comboStadtBgrp[i]->ItemIndex;
        }
        else {
            a.flags &= ~(1 << i);   // clear flag
        }
    }


    a.flags &= ~0x8;
    if(MainForm->cbGuthaben->Checked) {
        a.flags |= 0x90868;
        a.money = MainForm->editGuthaben->Text.ToIntDef(0);
    }

    a.flags &= ~0x80;
    if(MainForm->cbWohnanz->Checked) {
        a.flags |= 0x80;
        a.wohnanz = MainForm->editWohnanz->Text.ToIntDef(0);
    }

    a.flags &= ~0x60000;    // clear flags
    if(MainForm->cbSchloss->Checked) {
        a.flags |= 0x20000;     // set flag
    }
    if(MainForm->cbKathedrale->Checked) {
        a.flags |= 0x40000;     // set flag
    }

    // Gegner
    bool killplayer = false;
    for(int i=0; i<6; i++) {
        if(i==4) continue;
        int color = player[i].colornr;
        if(killButtons[color]->Down) {
            a.killplayernr[i] = 1;
            killplayer = true;
        } else {
            a.killplayernr[i] = 0;
        }
    }

    a.flags &= ~0x600;  // clear flags
    if(killplayer) {
        a.flags |= 0x400;   // set flag
    }

    if(MainForm->sbKillAny->Down) {
        a.flags |= 0x200;   // set flag
    }

    // Unterstützung
    bool helpplayer = false;
    a.flags &= ~0x10;   // clear flag
    if(MainForm->cbHelpWohn->Checked) {
        a.flags |= 0x10;    // set flag
        helpplayer = true;
        a.stadtminfrmd.wohnanz = MainForm->editHelpWohn->Text.ToIntDef(0);
        a.stadtminfrmd.bgruppwohn = MainForm->editHelpWohnGrp->Text.ToIntDef(0);
        a.stadtminfrmd.bgruppnr = MainForm->comboHelpWohnName->ItemIndex;
    }
    a.looseflags &= ~0x03;  // clear flags
    if(MainForm->cbStadtlowfrmd->Checked) {   // Einwohnerzahl halten
        a.looseflags |= 0x01;
        helpplayer = true;
        a.stadtlowfrmd.wohnanz = MainForm->editStadtlowfrmdwohn->Text.ToIntDef(0);
        a.stadtlowfrmd.bgruppwohn = MainForm->editStadtlowfrmdbgwohn->Text.ToIntDef(0);
        a.stadtlowfrmd.bgruppnr = MainForm->comboStadtlowfrmdbgnr->ItemIndex;
    }
    if(MainForm->cbStadtanzminfrmd->Checked) {
        a.looseflags |= 0x02;  // Anzahl Siedlungen halten
        helpplayer = true;
        a.stadtanzminfrmd = MainForm->editStadtanzminfrmd->Text.ToIntDef(0);
    }

    if(helpplayer) {
        if(MainForm->sbHelpAny->Down) {
            a.helpplayernr = 7;
        }
        else
        if(MainForm->sbHelpEingeb->Down) {
            a.helpplayernr = 6; // Eingeborene
        }
        else {
            // find player where button is down
            for(int i=0; i<4; i++) {
                int index = player[i].colornr;
                if(index < 4 && helpButtons[index]->Down) {
                    a.helpplayernr = i;
                    break;
                }
            }
        }
    }

    // STORE

    a.flags &= ~0x1000;
    if(MainForm->cbStore1->Checked) {
        a.flags |= 0x1000;
        a.waremin[0].lager = MainForm->editStore1->Text.ToIntDef(0) << 5;
        a.waremin[0].ware = MainForm->comboStore1->ItemIndex + 2;
    }

    a.flags &= ~0x2000;
    if(MainForm->cbStore2->Checked) {
        a.flags |= 0x2000;
        a.waremin[1].lager = MainForm->editStore2->Text.ToIntDef(0) << 5;
        a.waremin[1].ware = MainForm->comboStore2->ItemIndex + 2;
    }

    a.flags &= ~0x100;
    if(MainForm->cbBalance->Checked) {
        a.flags |= 0x100;
        a.bilanz = MainForm->editBalance->Text.ToIntDef(0);
    }

    a.flags &= ~0x200;
    if(MainForm->cbTBalance->Checked) {
        a.flags |= 0x200;
        a.handelsbilanz = MainForm->editTBalance->Text.ToIntDef(0);
    }

    a.flags &= ~0x4000;
    if(MainForm->cbMonopol1->Checked) {
        a.flags |= 0x4000;
        a.waremono[0].ware = waremap[MainForm->comboMonopol1->ItemIndex];
    }

    a.flags &= ~0x8000;
    if(MainForm->cbMonopol2->Checked) {
        a.flags |= 0x8000;
        a.waremono[1].ware = waremap[MainForm->comboMonopol2->ItemIndex];
    }

    // zugeordnete Spieler
    for(int i=0; i<4; i++) {
        if(auftragButtons[i]->Down) {
            player[i].auftragnr = index;
        }
    }
}

void __fastcall IndkSzen::putAuftrag(int index)
{

    bool saveModified = isModified();   // save state

    TStringList* strl = new TStringList();
    TAUFTRAGSAVE& a = auftrag[index];

    for(int i=0; i<4; i++)
        auftragButtons[i]->Down = false;
    for(int i=0; i<5; i++)
        killButtons[i]->Down = false;
    MainForm->sbKillAny->Down = false;
    for(int i=0; i<4; i++)
        helpButtons[i]->Down = false;
    MainForm->sbHelpEingeb->Down = false;
    MainForm->sbHelpAny->Down = false;
    MainForm->cbHelpWohn->Checked = false;
    MainForm->editHelpWohn->Text = leer;
    MainForm->editHelpWohnGrp->Text = leer;
    MainForm->comboHelpWohnName->ItemIndex = -1;
    MainForm->cbStadtlowfrmd->Checked = false;
    MainForm->editStadtlowfrmdwohn->Text = leer;
    MainForm->editStadtlowfrmdbgwohn->Text = leer;
    MainForm->comboStadtlowfrmdbgnr->ItemIndex = -1;
    MainForm->cbStadtanzminfrmd->Checked = false;
    MainForm->editStadtanzminfrmd->Text = leer;

    for(int i=0; i<3; i++) {
        cbStadt[i]->Checked = false;
        gbStadt[i]->Enabled = false;
        editStadtWohn[i]->Text = leer;
        editStadtWohn[i]->Enabled = false;
        lbStadtWohn[i]->Enabled = false;
        editStadtBgrp[i]->Text = leer;
        editStadtBgrp[i]->Enabled = false;
        comboStadtBgrp[i]->ItemIndex = -1;
        comboStadtBgrp[i]->Enabled = false;
    }
    MainForm->cbWohnanz->Checked = false;
    MainForm->editWohnanz->Text = leer; 
    MainForm->editWohnanz->Enabled = false;

    MainForm->cbGuthaben->Checked = false;
    MainForm->editGuthaben->Text = leer;
    MainForm->editGuthaben->Enabled = false;
    MainForm->cbStore1->Checked = false;
    MainForm->editStore1->Text = leer;
    MainForm->comboStore1->ItemIndex = -1;
    MainForm->cbStore2->Checked = false;
    MainForm->editStore2->Text = leer;
    MainForm->comboStore2->ItemIndex = -1;
    MainForm->cbTBalance->Checked = false;
    MainForm->editTBalance->Text = leer;
    MainForm->cbBalance->Checked = false;
    MainForm->editBalance->Text = leer;
    MainForm->cbMonopol1->Checked = false;
    MainForm->comboMonopol1->ItemIndex = -1;
    MainForm->cbMonopol2->Checked = false;
    MainForm->comboMonopol2->ItemIndex = -1;

    if(a.nr >= 0) {
        strl->Text = a.infotxt;

        for(int i=0; i<3; i++) {
            if(a.flags & (1 << i)) {
                cbStadt[i]->Checked = true;
                gbStadt[i]->Enabled = true;
                editStadtWohn[i]->Enabled = true;
                editStadtWohn[i]->Text = String(a.stadtmin[i].wohnanz);
                lbStadtWohn[i]->Enabled = true;
                editStadtBgrp[i]->Enabled = true;
                editStadtBgrp[i]->Text = String(a.stadtmin[i].bgruppwohn);
                comboStadtBgrp[i]->Enabled = true;
                comboStadtBgrp[i]->ItemIndex = a.stadtmin[i].bgruppnr;
            }
        }
        MainForm->cbSchloss->Checked = (a.flags & 0x20000) != 0;
        MainForm->cbKathedrale->Checked = (a.flags & 0x40000) != 0;

        // TEST !!

        if(a.flags & 0x8) {
            MainForm->cbGuthaben->Checked = true;
            MainForm->editGuthaben->Enabled = true;
            MainForm->editGuthaben->Text = String(a.money);
        }

        if(a.flags&0x400) {
            for(int i=0; i<6; i++) {
                if(i==4) continue;
                if(a.killplayernr[i]) {
                    killButtons[player[i].colornr]->Down = true;
                }
            }
        }

        MainForm->sbKillAny->Down = (a.flags&0x200);

        if( a.flags&0x10 || a.looseflags != 0 ) {    // help player
            if(a.helpplayernr == 7) {
                MainForm->sbHelpAny->Down = true;   // beliebigen
            }
            else if(a.helpplayernr == 6) {
                MainForm->sbHelpEingeb->Down = true;   // Eingeborene
            }
            else {
                int color = player[a.helpplayernr].colornr;
                if(color < 4)
                    helpButtons[color]->Down = true;
            }
        }

        if(a.flags&0x80) {
            MainForm->cbWohnanz->Checked = true;
            MainForm->editWohnanz->Enabled = true;
            MainForm->editWohnanz->Text = String(a.wohnanz);
        }

        if(a.flags&0x10) {
            MainForm->cbHelpWohn->Checked = true;
            MainForm->editHelpWohn->Text = String(a.stadtminfrmd.wohnanz);
            MainForm->editHelpWohnGrp->Text = String(a.stadtminfrmd.bgruppwohn);
            MainForm->comboHelpWohnName->ItemIndex = a.stadtminfrmd.bgruppnr;
        }

        if(a.looseflags & 0x01) {  // Einwohnerzahl halten
            MainForm->cbStadtlowfrmd->Checked = true;
            MainForm->editStadtlowfrmdwohn->Text = String(a.stadtlowfrmd.wohnanz);
            MainForm->editStadtlowfrmdbgwohn->Text = String(a.stadtlowfrmd.bgruppwohn);
            MainForm->comboStadtlowfrmdbgnr->ItemIndex = a.stadtlowfrmd.bgruppnr;
        }

        if(a.looseflags & 0x02) {  // Anzahl Siedlungen halten
            MainForm->cbStadtanzminfrmd->Checked = true;
            MainForm->editStadtanzminfrmd->Text = String(a.stadtanzminfrmd);
        }


        if(a.flags&0x1000) {
            MainForm->cbStore1->Checked = true;
            MainForm->editStore1->Text = String(a.waremin[0].lager >> 5);
            MainForm->comboStore1->ItemIndex = a.waremin[0].ware - 2;
        }
        if(a.flags&0x2000) {
            MainForm->cbStore2->Checked = true;
            MainForm->editStore2->Text = String(a.waremin[1].lager >> 5);
            MainForm->comboStore2->ItemIndex = a.waremin[1].ware - 2;
        }

        if(a.flags&0x100) {
            MainForm->cbBalance->Checked = true;
            MainForm->editBalance->Text = String(a.bilanz);
        }

        if(a.flags&0x10000) {
            MainForm->cbTBalance->Checked = true;
            MainForm->editTBalance->Text = String(a.handelsbilanz);
        }

        if(a.flags&0x4000) {
            MainForm->cbMonopol1->Checked = true;
            MainForm->comboMonopol1->ItemIndex = ware2index(a.waremono[0].ware);
        }
        if(a.flags&0x8000) {
            MainForm->cbMonopol2->Checked = true;
            MainForm->comboMonopol2->ItemIndex = ware2index(a.waremono[1].ware);
        }


        // zugeordnete Spieler
        for(int i=0; i<4; i++) {
            if(player[i].auftragnr == index) {
                auftragButtons[i]->Down = true;
            }
        }
    }

    MainForm->Memo1->Lines = strl;
    delete strl;

    setModified(saveModified);    // restore
}

void __fastcall IndkSzen::putSettings(void)
{
    MainForm->editSchiffe->Text = String(timers.spez_shipmax);
    MainForm->editMissNr->Text = String(timers.spez_missnr);
    MainForm->editMissSubNr->Text = String(timers.spez_misssubnr);
    MainForm->editTutorflg->Text = String(timers.spez_tutorflg);
    MainForm->editCompLevel->Text = String(timers.spez_complevel);
    MainForm->editGameId->Text = String(timers.spez_gameid);
    if(kampagne >= 0) {
        MainForm->cbKampagne->Checked = true;
        MainForm->editKampagne->Enabled = true;
        MainForm->btnKampagne->Enabled = true;
        MainForm->editKampagne->Text = String(kampagne);
    } else {
        MainForm->editKampagne->Text = leer;
        MainForm->cbKampagne->Checked = false;
        MainForm->editKampagne->Enabled = false;
        MainForm->btnKampagne->Enabled = false;
    }

    MainForm->btnPiraten->Down =  (timers.spez_szeneflags & 0x01)  ? true : false;
    MainForm->btnDuerren->Down =  (timers.spez_szeneflags & 0x04)  ? true : false;
    MainForm->btnErz->Down =      (timers.spez_szeneflags & 0x08)  ? true : false;
    MainForm->btnHaendler->Down = (timers.spez_szeneflags & 0x40)  ? true : false;
    MainForm->btnVulkan->Down =   (timers.spez_szeneflags & 0x100) ? true : false;
    MainForm->btnWaffen->Down =   (timers.spez_szeneflags & 0x200) ? true : false;
}

int __fastcall IndkSzen::saveTimers(TFileStream* out)
{
    timers.spez_shipmax = MainForm->editSchiffe->Text.ToIntDef(33);
    timers.spez_missnr = MainForm->editMissNr->Text.ToIntDef(0);
    timers.spez_misssubnr = MainForm->editMissSubNr->Text.ToIntDef(0);
    timers.spez_tutorflg = MainForm->editTutorflg->Text.ToIntDef(0);
    timers.spez_complevel = MainForm->editCompLevel->Text.ToIntDef(0);
    timers.spez_gameid = MainForm->editGameId->Text.ToIntDef(0);

    if(MainForm->btnPiraten->Down)
        timers.spez_szeneflags |= 0x01;
    else
        timers.spez_szeneflags &= (~0x01);
    if(MainForm->btnDuerren->Down)
        timers.spez_szeneflags |= 0x04;
    else
        timers.spez_szeneflags &= (~0x04);
    if(MainForm->btnErz->Down)
        timers.spez_szeneflags |= 0x08;
    else
        timers.spez_szeneflags &= (~0x08);
    if(MainForm->btnHaendler->Down)
        timers.spez_szeneflags |= 0x40;
    else
        timers.spez_szeneflags &= (~0x40);
    if(MainForm->btnVulkan->Down)
        timers.spez_szeneflags |= 0x100;
    else
        timers.spez_szeneflags &= (~0x100);
    if(MainForm->btnWaffen->Down)
        timers.spez_szeneflags |= 0x200;
    else
        timers.spez_szeneflags &= (~0x200);

    TCHUNK chunk;
    sprintf(chunk.name, "TIMERS");
    chunk.lengh = sizeof(TTIMERSAVE);
    out->Write(&chunk, sizeof(TCHUNK));
    out->Write(&timers, chunk.lengh);
    return 0;
}

int __fastcall IndkSzen::saveInseln(TFileStream* out)
{
    for(int i=0; i<inseln->Count; i++)
    {
        Insel* insel = (Insel*)inseln->Items[i];
        if(insel != 0)
        {
            insel->saveToFile(out, false);
        }
    }
    return 0;
}

int __fastcall IndkSzen::saveStaedte(TFileStream* out)
{
    int pos = out->Position;
    TCHUNK chunk;
    strcpy(chunk.name, "STADT4");
    chunk.lengh = 0;    // dummy
    out->Write(&chunk, sizeof(TCHUNK));

    for(int i=0; i<inseln->Count; i++)
    {
        Insel* insel = (Insel*)inseln->Items[i];
        if(insel != 0)
        {
            insel->saveStaedte(out, false); // no header
        }
    }

    // rewrite chunk
    chunk.lengh = out->Position - pos - sizeof(TCHUNK);
    out->Position = pos;
    out->Write(&chunk, sizeof(TCHUNK));
    out->Seek(0, soFromEnd);
    return 0;
}

int __fastcall IndkSzen::saveKontore(TFileStream* out)
{
    int pos = out->Position;
    TCHUNK chunk;
    strcpy(chunk.name, "KONTOR2");
    chunk.lengh = 0; // dummy
    out->Write(&chunk, sizeof(TCHUNK));

    for(int i=0; i<inseln->Count; i++)
    {
        Insel* insel = (Insel*)inseln->Items[i];
        if(insel != 0)
        {
            insel->saveKontore(out, false); // no header
        }
    }
    // rewrite chunk
    chunk.lengh = out->Position - pos - sizeof(TCHUNK);
    out->Position = pos;
    out->Write(&chunk, sizeof(TCHUNK));
    out->Seek(0, soFromEnd);
    return 0;
}

int __fastcall IndkSzen::saveCustom(TFileStream* out)
{
    TCHUNK chunk;
    sprintf(chunk.name, "CUSTOM");
    char* sig = "Signatur";
    chunk.lengh = strlen(sig);
    out->Write(&chunk, sizeof(TCHUNK));
    out->Write(sig, chunk.lengh);
    return 0;
}

void __fastcall IndkSzen::getPlayer(int index)
{
    TPLAYERSAVE& p = player[index];
    p.money = MainForm->editMoney->Text.ToIntDef(0);
    p.kind = index2kind(MainForm->comboKind->ItemIndex);
    p.colornr = MainForm->comboPlayerColor->ItemIndex;
    strncpy(p.name, MainForm->editName->Text.c_str(), sizeof(p.name)-1);
    p.name[sizeof(p.name)-1] = '\0';

    p.denkanz = MainForm->editDenkanz->Text.ToIntDef(0);
    p.denkbauanz = MainForm->editDenkbauanz->Text.ToIntDef(0);
    p.triumphanz = MainForm->editTriumphanz->Text.ToIntDef(0);
    p.triumphbauanz = MainForm->editTriumphbauanz->Text.ToIntDef(0);

    p.killsoldatanz = MainForm->editKillsoldatanz->Text.ToIntDef(0);
    p.losssoldatanz = MainForm->editLosssoldatanz->Text.ToIntDef(0);
    p.killshipanz = MainForm->editKillshipanz->Text.ToIntDef(0);
    p.lossshipanz = MainForm->editLossshipanz->Text.ToIntDef(0);

//    p.lockflg = MainForm->cbLockflag->Checked ? 0 : 1;
    p.schlossbauanz = MainForm->cbSchlossbau->Checked ? 1 : 0;
    p.kathedralbauanz = MainForm->cbKathedralebau->Checked ? 1 : 0;

    p.humanwohnmax = MainForm->editHumanwohnmax->Text.ToIntDef(0);
    p.wohnmin = MainForm->editWohnmin->Text.ToIntDef(0);
    p.bgruppmin = ((double)MainForm->tbBgruppmin->Position/100 - 1.0) * 32;
    p.bgruppmaxhuman = ((double)MainForm->tbBgruppmaxhuman->Position/100 - 1.0) * 32;

    p.compflags &= ~0x330;
    if(MainForm->cbBgruppmin->Checked) p.compflags |= 0x100;
    if(MainForm->cbBgruppmaxhuman->Checked) p.compflags |= 0x200;
    if(MainForm->cbHumanwohnmax->Checked) p.compflags |= 0x10;
    if(MainForm->cbWohnmin->Checked) p.compflags |= 0x20;

/*
    String compflags = MainForm->editCompflags->Text.LowerCase();
    UINT val;
    sscanf(compflags.c_str(), "%8x", &val);
    p.compflags = val;
*/
    p.bauinfraflags = 0;
    for(int i=0; i<32; i++) {
        if(cbInfra[i]->Checked)
            p.bauinfraflags |= (1<<i);
    }
}

void __fastcall IndkSzen::putPlayer(int index)
{
    bool saveModified = isModified();   // save modify state

    const TPLAYERSAVE& p = player[index];
    MainForm->editMoney->Text = String(p.money);
    MainForm->comboKind->ItemIndex = kind2index(p.kind);
    MainForm->comboPlayerColor->ItemIndex = p.colornr;
    MainForm->editName->Text = String(p.name);

    MainForm->editDenkanz->Text = String(p.denkanz);
    MainForm->editDenkbauanz->Text = String(p.denkbauanz);
    MainForm->editTriumphanz->Text = String(p.triumphanz);
    MainForm->editTriumphbauanz->Text = String(p.triumphbauanz);

    MainForm->editKillsoldatanz->Text = String(p.killsoldatanz);
    MainForm->editLosssoldatanz->Text = String(p.losssoldatanz);
    MainForm->editKillshipanz->Text = String(p.killshipanz);
    MainForm->editLossshipanz->Text = String(p.lossshipanz);

//    MainForm->cbLockflag->Checked = p.lockflg == 0;
    MainForm->cbSchlossbau->Checked = p.schlossbauanz > 0;
    MainForm->cbKathedralebau->Checked = p.kathedralbauanz > 0;

    MainForm->editWohnmin->Text = String(p.wohnmin);
    MainForm->cbWohnmin->Checked = (p.compflags & 0x20) != 0;
    MainForm->editHumanwohnmax->Text = String(p.humanwohnmax);
    MainForm->cbHumanwohnmax->Checked = (p.compflags & 0x10) != 0;

    MainForm->tbBgruppmin->Position = ((double)p.bgruppmin/32 + 1.0) * 100.0;
    MainForm->editBgruppmin->Text = Format("%.2f", ARRAYOFCONST(((double)p.bgruppmin/32 + 1.0)));
    MainForm->cbBgruppmin->Checked = (p.compflags & 0x100) != 0;
    MainForm->lbBgruppmin1->Enabled = (p.compflags & 0x100) != 0;
    MainForm->lbBgruppmin2->Enabled = (p.compflags & 0x100) != 0;
    MainForm->lbBgruppmin2->Caption =
        MainForm->GetBgrupp(MainForm->tbBgruppmin->Position);
//    MainForm->lbBgruppmin3->Enabled = (p.compflags & 0x100) != 0;
    MainForm->tbBgruppmin->SelEnd = MainForm->cbBgruppmin->Checked ?
        MainForm->tbBgruppmin->Position : MainForm->tbBgruppmin->Min;

    MainForm->tbBgruppmaxhuman->Position = ((double)p.bgruppmaxhuman/32 + 1.0) * 100.0;
    MainForm->editBgruppmaxhuman->Text = Format("%.2f", ARRAYOFCONST(((double)p.bgruppmaxhuman/32 + 1.0)));
    MainForm->cbBgruppmaxhuman->Checked = (p.compflags & 0x200) != 0;
    MainForm->lbBgruppmaxhuman1->Enabled = (p.compflags & 0x200) != 0;
    MainForm->lbBgruppmaxhuman2->Enabled = (p.compflags & 0x200) != 0;
    MainForm->lbBgruppmaxhuman2->Caption =
        MainForm->GetBgrupp(MainForm->tbBgruppmaxhuman->Position);
//    MainForm->lbBgruppmaxhuman3->Enabled = (p.compflags & 0x200) != 0;
    MainForm->tbBgruppmaxhuman->SelStart = MainForm->cbBgruppmaxhuman->Checked ?
        MainForm->tbBgruppmaxhuman->Position : MainForm->tbBgruppmaxhuman->Max;

//    MainForm->editCompflags->Text = String::IntToHex(p.compflags, 8);

    for(int i=0; i<32; i++) {
        cbInfra[i]->Checked = (p.bauinfraflags & (1<<i)) != 0;
    }

    setModified(saveModified);    // restore
}

int __fastcall IndkSzen::handleInsel(char* buffer, unsigned length, int type)
{
    currInsel = new Insel( buffer, length, type );
    int inselnr = currInsel->getInselnr();
    if(inselnr >= inseln->Count)
        inseln->Count = inselnr+1;
    inseln->Items[inselnr] = currInsel;
    TTreeNode* node = MainForm->ObjectTree->Items->AddChildObject(
            inselTree, currInsel->getDescr(), currInsel);
    currInsel->setNode(node);
    return 0;
}

void __fastcall IndkSzen::paint(TCanvas* canvas)
{
/*
    Graphics::TBitmap* bm = new Graphics::TBitmap();
    bm->Width = MainForm->PaintBox1->Width;
    bm->Height = MainForm->PaintBox1->Height;
    TRect r(0, 0, bm->Width, bm->Height);
//    bm->Canvas->Brush->Assign( canvas->Brush );
//    bm->Canvas->Brush->Color = TColor(0x85C2CC);
*/
    canvas->Brush->Color = TColor(0x00FF4444);
    canvas->FillRect( canvas->ClipRect );
    canvas->Brush->Style = bsClear;
    canvas->Pen->Color = TColor(0x00406389);

    for( int i=0; i<inseln->Count; i++ )
    {
        Insel* insel = (Insel*)inseln->Items[i];
        if(insel != 0)
        {
            insel->paint(canvas);
        }
    }

    TSTADTSAVE* selectedStadt = getSelectedStadt();
    Insel* selectedIsland = getSelectedIsland();
    TSHIPSAVE* selectedShip = getSelectedShip();

    if(selectedStadt != 0)
    {
        Insel* insel = (Insel*)inseln->Items[selectedStadt->inselnr];
        canvas->Brush->Color = clWhite;
        canvas->FrameRect(insel->getStadtBox(selectedStadt->stadtnr));
    }
    else
    if(selectedIsland != 0)
    {
        canvas->Brush->Color = dragValid ? clWhite : clRed;
        canvas->FrameRect(selectedIsland->boundingBox());
    }

    // draw Schiffe
    if(MainForm->btSchiffe->Down)
    {
        for(int i=0; i<schiffe->Count; i++)
        {
            TSHIPSAVE* ship = (TSHIPSAVE*)schiffe->Items[i];
            TColor c = playerColor(ship->playernr);
            canvas->Brush->Color = c;
            canvas->Pen->Color = (~c) & 0xFFFFFF;
            canvas->Pen->Width =
                ship == selectedShip ? 2 : 1;
            canvas->Ellipse(ship->strtposx-C_ShipRadius,
                ship->strtposy-C_ShipRadius,
                ship->strtposx+C_ShipRadius,
                ship->strtposy+C_ShipRadius);
        }
    }
/*
    canvas->Draw(0, 0, bm);
    delete bm;
*/
}

int __fastcall IndkSzen::handleInselhaus(char* buffer, unsigned length)
{
    Inselhaus* inselhaus = new Inselhaus( buffer, length );
    currInsel->addInselhaus( inselhaus );
    return 0;
}

int __fastcall IndkSzen::handleKampagne(char* buffer, unsigned length)
{
    memcpy(&kampagne, buffer, sizeof(int));
    return 0;
}

int __fastcall IndkSzen::handleName(char* buffer, unsigned length)
{
    char* namebuf = new char[length+1];
    memcpy(namebuf, buffer, length);
    namebuf[length] = '\0';
    MainForm->editSzenName->Text = namebuf;
    delete [] namebuf;
    return 0;
}

int __fastcall IndkSzen::handleCustom(char* buffer, unsigned length)
{
    return 0;
}

void __fastcall IndkSzen::selectionChanging(TTreeNode* Node)
{
    // sichere selected stadt
    if(Node != 0 && Node->Parent != 0 && Node->Parent->Parent == inselTree)
        saveStadt(getSelectedStadt());

    // sichere selected ship
    if(Node != 0 && Node->Parent == shipTree)
        saveSchiff(getSelectedShip());
}

void __fastcall IndkSzen::selectionChanged(TTreeNode* Node)
{
    if(Node != 0 && Node->Parent == shipTree)
    {
        putSchiff((TSHIPSAVE*)Node->Data);
    }
    else
    if(Node != 0 && Node->Parent != 0 && Node->Parent->Parent == inselTree)
    {
        putStadt((TSTADTSAVE*)Node->Data);
    }
    else
    {
        putSchiff(0);
        putStadt(0);
    }
}

bool __fastcall IndkSzen::selectObject(int x, int y, TShiftState shift)
{
    TTreeNode* node = 0;
    for(int i=0; i<inseln->Count; i++) {
        Insel* insel = (Insel*)inseln->Items[i];
        if(insel != 0)
        {
            if(insel->containsPoint(Point(x,y)))
            {
                node = (TTreeNode*)insel->getNode();
                break;
            }
        }
    }

    if(MainForm->btStaedte->Down)
    {
        TSTADTSAVE* selectedStadt = getStadt(x, y, shift);
        if(selectedStadt != 0)
        {
            for(int i=0; i<MainForm->ObjectTree->Items->Count; i++)
            {
                if((TSTADTSAVE*)MainForm->ObjectTree->Items->Item[i]->Data == selectedStadt)
                {
                    node = MainForm->ObjectTree->Items->Item[i];
                    break;
                }
            }
        }
    }

    if(MainForm->btSchiffe->Down)
    {
        TSHIPSAVE* selectedShip = getSchiff(x, y, shift);
        if(selectedShip != 0)
        {
            for(int i=0; i<MainForm->ObjectTree->Items->Count; i++)
            {
                if((TSHIPSAVE*)MainForm->ObjectTree->Items->Item[i]->Data == selectedShip)
                {
                    node = MainForm->ObjectTree->Items->Item[i];
                    break;
                }
            }
        }
    }

    MainForm->ObjectTree->Selected = node;
    return true;
}

int __fastcall IndkSzen::savePlayers(TFileStream* out)
{
    getPlayer(MainForm->SpielerTabControl->TabIndex);

    TCHUNK chunk;
    sprintf(chunk.name, "PLAYER4");
    chunk.lengh = 7 * sizeof(TPLAYERSAVE);
    out->Write(&chunk, sizeof(TCHUNK));
    out->Write(&player[0], chunk.lengh);
    return 0;
}



void __fastcall IndkSzen::setModified(bool mod)
{
    if(mod)
        numChanges++;
    else
        numChanges = 0;

    MainForm->SetTitleFile(name);
}

bool __fastcall IndkSzen::isModified() const
{
    return numChanges > 0;
}

String __fastcall IndkSzen::getPath() const
{
    return path;
}

Insel* __fastcall IndkSzen::getSelectedIsland() const
{
    TTreeNode* node = MainForm->ObjectTree->Selected;
    if(node != 0 && node->Parent == inselTree)
        return (Insel*)node->Data;
    else
        return 0;
}

TSHIPSAVE* __fastcall IndkSzen::getSelectedShip() const
{
    TTreeNode* node = MainForm->ObjectTree->Selected;
    if(node != 0 && node->Parent == shipTree)
        return (TSHIPSAVE*)node->Data;
    else
        return 0;
}

inline TSTADTSAVE* __fastcall IndkSzen::getSelectedStadt() const
{
    TTreeNode* node = MainForm->ObjectTree->Selected;
    if(node != 0 && node->Parent != 0 && node->Parent->Parent == inselTree)
        return (TSTADTSAVE*)node->Data;
    else
        return 0;
}

void __fastcall IndkSzen::saveSelectedIsland(String path)
{
    Insel* selectedIsland = getSelectedIsland();
    if(selectedIsland != 0)
    {
        TFileStream* tfs = new TFileStream(path, fmCreate|fmShareExclusive);
        selectedIsland->saveToFile(tfs, true);
        delete tfs;
    }
}

AnsiString __fastcall IndkSzen::getInselDescription() const
{
    String descr;
    Insel* selectedIsland = getSelectedIsland();
    if(selectedIsland != 0)
    {
        descr = selectedIsland->getDescr();
    }
    return descr;
}

void __fastcall IndkSzen::saveKampagne(TFileStream* out)
{
    kampagne = -1;
    if(MainForm->cbKampagne->Checked) {
        kampagne = MainForm->editKampagne->Text.ToIntDef(0);

        TCHUNK chunk;
        sprintf(chunk.name, "SZENE_KAMPAGNE");
        chunk.lengh = sizeof(kampagne);
        out->Write(&chunk, sizeof(TCHUNK));
        out->Write(&kampagne, sizeof(kampagne));
    }
}

static double distance(int x1, int y1, int x2, int y2)
{
    double dx = abs(x2-x1);
    double dy = abs(y2-y1);
    return sqrt(dx*dx + dy*dy);
}

Insel* __fastcall IndkSzen::getInsel(int x, int y, TShiftState shift)
{
    Insel* ret = 0;
    TPoint p(x,y);
    for(int i=0; i<inseln->Count; i++)
    {
        Insel* insel = (Insel*)inseln->Items[i];
        if(insel != 0)
        {
            if(insel->containsPoint(p))
            {
                ret = insel;
                break;
            }
        }
    }
    
    return ret;
}

TSTADTSAVE* __fastcall IndkSzen::getStadt(int x, int y, TShiftState shift)
{
    TSTADTSAVE* stadt = 0;
    for(int i=0; i<inseln->Count; i++)
    {
        if(inseln->Items[i] != 0)
        {
            stadt = ((Insel*)inseln->Items[i])->getStadt(x, y);
            if(stadt != 0)
                break;
        }
    }

    return stadt;
}

TSHIPSAVE* __fastcall IndkSzen::getSchiff(int x, int y, TShiftState shift)
{
    double minDist = 1000;
    TSHIPSAVE* ret = 0;
    for(int i=0; i<schiffe->Count; i++)
    {
        TSHIPSAVE* ship = (TSHIPSAVE*)schiffe->Items[i];
        double d = distance(x, y, ship->strtposx, ship->strtposy);
        if( d < minDist )
        {
            ret = ship;
            minDist = d;
        }
    }

    if(minDist >= C_ShipRadius)
        ret = 0;    // too far

    return ret;
}

void __fastcall IndkSzen::mouseHover(int x, int y, TShiftState shift)
{
    // find closest object
    String hint;

    if(MainForm->btStaedte->Down)
    {
        TSTADTSAVE* stadt = getStadt(x, y, shift);
        if(stadt != 0)
            hint = stadt->name;
    }

    if(MainForm->btSchiffe->Down && hint.IsEmpty())
    {
        TSHIPSAVE* ship = getSchiff(x, y, shift);
        if(ship != 0)
            hint = ship->name;
    }

    if(hint.IsEmpty())
    {
        Insel* insel = getInsel(x, y, shift);
        if(insel != 0)
            hint = insel->getDescr();
    }

    if(!hint.IsEmpty())
    {
        MainForm->PaintBox1->Cursor = crHandPoint;
        MainForm->PaintBox1->Hint = hint;
        MainForm->PaintBox1->ShowHint = true;
    }
    else
    {
        MainForm->PaintBox1->Cursor = crDefault;
        MainForm->PaintBox1->Hint = "";
        MainForm->PaintBox1->ShowHint = false;
    }
}

void __fastcall IndkSzen::deleteSelectedInsel()
{
    Insel* selectedIsland = getSelectedIsland();
    if(selectedIsland != 0)
    {
        for(int i=0; i<inseln->Count; i++)
        {
            Insel* insel = (Insel*)inseln->Items[i];
            if(insel == selectedIsland)
            {
                inseln->Items[i] = 0;
                delete insel;
                MainForm->ObjectTree->Items->Delete(MainForm->ObjectTree->Selected);                
                setModified(true);
                break;
            }
        }
    }
}

void __fastcall IndkSzen::putStadt(TSTADTSAVE* stadt)
{
    bool saveModified = isModified();   // save modify state
    if(stadt != 0)
    {
        setChildrenState(MainForm->gbStadt, true);
        MainForm->editStadtname->Text = stadt->name;
        MainForm->comboStadtfarbe->ItemIndex =
            player[stadt->playernr].colornr;
        MainForm->cbBaustop->Checked = stadt->baustopflg != 0;
        MainForm->pcKarte->ActivePage = MainForm->tabStadt;
    }
    else
    {
        MainForm->editStadtname->Text = leer;
        MainForm->comboStadtfarbe->ItemIndex = -1;
        MainForm->cbBaustop->Checked = false;
        setChildrenState(MainForm->gbStadt, false);
    }
    setModified(saveModified);
}

void __fastcall IndkSzen::saveStadt(TSTADTSAVE* stadt)
{
    if(stadt != 0 && !MainForm->editStadtname->Text.IsEmpty())
    {
        strncpy(stadt->name, MainForm->editStadtname->Text.c_str(), 31);
        stadt->name[31] = '\0';
        int colornr = MainForm->comboStadtfarbe->ItemIndex;
        for(int i=0; i<7; i++)
        {
            if(i == 4) continue;    // kein Händler
            if(colornr == player[i].colornr)
            {
                stadt->playernr = i;
                break;
            }
        }
        stadt->baustopflg = MainForm->cbBaustop->Checked ? 1 : 0;
    }
}

void __fastcall IndkSzen::putSchiff(TSHIPSAVE* ship)
{
    bool saveModified = isModified();   // save modify state
    if(ship != 0)
    {
        setChildrenState(MainForm->gbSchiff, true);
        MainForm->editSchiffname->Text = ship->name;
        MainForm->comboSchifftyp->ItemIndex = schiff2index(ship->figurnr);
        int index = player[ship->playernr].colornr;
        if(index == 6) index = 5;   // Händler
        MainForm->comboSchifffarbe->ItemIndex = index;
        MainForm->tbEnergie->Position = getPos(
            MainForm->comboSchifftyp->ItemIndex, ship->energy);
        MainForm->editSchiffkanonen->Text = String(ship->kanonen);
        MainForm->pcKarte->ActivePage = MainForm->tabSchiff;
    }
    else
    {
        TNotifyEvent event = MainForm->editSchiffname->OnChange;
        MainForm->editSchiffname->OnChange = 0;
        MainForm->editSchiffname->Text = leer;
        MainForm->editSchiffname->OnChange = event;
        MainForm->comboSchifftyp->ItemIndex = -1;
        MainForm->comboSchifffarbe->ItemIndex = -1;
        MainForm->tbEnergie->Position = 0;
        MainForm->editSchiffkanonen->Text = leer;
        setChildrenState(MainForm->gbSchiff, false);
    }

    drawSchiff(ship);
    setModified(saveModified);
}

void __fastcall IndkSzen::drawSchiff(TSHIPSAVE* ship)
{
    if(ship != 0)
    {
        Graphics::TBitmap* bm = new Graphics::TBitmap;
        MainForm->ShipImages->GetBitmap(MainForm->comboSchifftyp->ItemIndex, bm);
        MainForm->imSchiff->Picture->Bitmap = bm;
        MainForm->imSchiff->Visible = true;
        delete bm;
    }
    else
    {
        MainForm->imSchiff->Visible = false;
    }
}

void __fastcall IndkSzen::saveSchiff(TSHIPSAVE* ship)
{
    if(ship != 0 && !MainForm->editSchiffname->Text.IsEmpty())
    {
        strncpy(ship->name, MainForm->editSchiffname->Text.c_str(), 23);
        ship->name[23] = '\0';
        if(MainForm->comboSchifftyp->ItemIndex >= 0)
        {
            ship->figurnr = schiffTyp[MainForm->comboSchifftyp->ItemIndex];
            ship->kind = schiffKind[MainForm->comboSchifftyp->ItemIndex];
            ship->energy = getEnergie(
                MainForm->comboSchifftyp->ItemIndex,
                MainForm->tbEnergie->Position);
        }
        int colornr = MainForm->comboSchifffarbe->ItemIndex;
        if(colornr == 5) colornr = 6;   // Händler
        for(int i=0; i<7; i++)
        {
            if(colornr == player[i].colornr)
            {
                ship->playernr = i;
                break;
            }
        }
        ship->kanonen = MainForm->editSchiffkanonen->Text.ToIntDef(0);

        if(MainForm->ObjectTree->Selected != 0)
        {
            MainForm->ObjectTree->Selected->Text = ship->name;
        }
    }
}

int __fastcall IndkSzen::saveSchiffe(TFileStream* out)
{
    saveSchiff(getSelectedShip());
    TCHUNK chunk;
    sprintf(chunk.name, "SHIP4");
    chunk.lengh = schiffe->Count * sizeof(TSHIPSAVE);
    out->Write(&chunk, sizeof(TCHUNK));
    for(int i=0; i<schiffe->Count; i++)
    {
        TSHIPSAVE* ship = (TSHIPSAVE*)schiffe->Items[i];
        out->Write(ship, sizeof(TSHIPSAVE));
    }
    return 0;
}

void __fastcall IndkSzen::stadtColorChange()
{
    TSTADTSAVE* selectedStadt = getSelectedStadt();
    if(selectedStadt != 0)
    {
        int colornr = MainForm->comboStadtfarbe->ItemIndex;
        int i;
        for(i=0; i<7; i++)
        {
            if(i == 4) continue;    // kein Händler
            if(colornr == player[i].colornr)
                break;
        }
        if(i < 7)
        {
            Insel* insel = (Insel*)inseln->Items[selectedStadt->inselnr];
            if(insel != 0)
            {
                insel->stadtPlayerChange(selectedStadt, i);
            }
        }
    }
}

void __fastcall IndkSzen::shipColorChange()
{
    TSHIPSAVE* selectedShip = getSelectedShip();
    if(selectedShip != 0)
    {
        int colornr = MainForm->comboSchifffarbe->ItemIndex;
        if(colornr == 5) colornr = 6;   // Händler
        int i;
        for(i=0; i<7; i++)
        {
            if(colornr == player[i].colornr)
                break;
        }
        if(i < 7)
        {
            selectedShip->playernr = i;
            MainForm->ObjectTree->Invalidate();
        }
        selectedShip->figurnr = schiffTyp[MainForm->comboSchifftyp->ItemIndex];
        selectedShip->kind = schiffKind[MainForm->comboSchifftyp->ItemIndex];
        drawSchiff(selectedShip);
    }
}

int __fastcall IndkSzen::getImageIndex(TTreeNode* Node)
{
    if(Node->Parent == inselTree)
    {
        return 8;
    }
    else
    if(Node->Parent == shipTree)
    {
        return player[((TSHIPSAVE*)Node->Data)->playernr].colornr+1;
    }
    else
    if(Node->Parent != 0 && Node->Parent->Parent == inselTree)
    {
        return player[((TSTADTSAVE*)Node->Data)->playernr].colornr+1;
    }
    else
    {
        return 9;
    }
}

TKONTORSAVE* __fastcall IndkSzen::getSelectedKontor() const
{
    TKONTORSAVE* kontor = 0;
    TSTADTSAVE* stadt = getSelectedStadt();
    if(stadt != 0)
    {
        TTreeNode* inselNode = inselTree->getFirstChild();
        while(inselNode != 0)
        {
            Insel* insel = (Insel*)inselNode->Data;
            if(stadt->inselnr == insel->getInselnr())
            {
                kontor = insel->getKontor(stadt->stadtnr);
                if(kontor != 0)
                    break;
            }
            inselNode = inselTree->GetNextChild(inselNode);
        }
    }
    return kontor;
}

void __fastcall IndkSzen::kontorLeeren()
{
    TKONTORSAVE* kontor = getSelectedKontor();
    if(kontor != 0)
    {
        for(int i=0; i<50; i++)
        {
            kontor->waren[i].lager = 0;
            kontor->waren[i].ownlager = 0;
            kontor->waren[i].minlager = 0;
        }
        ShowMessage("Kontor wurde geleert!");
    }
}

void __fastcall IndkSzen::schiffLeeren()
{
    TSHIPSAVE* schiff = getSelectedShip();
    if(schiff != 0)
    {
        for(int i=0; i<8; i++)
        {
            schiff->waren[i].hausid = 0;
            schiff->waren[i].menge = 0;
        }
        String typ = schiff->kind == 5 ? "Karren" : "Schiff";
        ShowMessage(typ + " wurde geleert!");
    }
}

void __fastcall IndkSzen::kontoreLeeren(int player)
{
    for(int i=0; i<inseln->Count; i++)
    {
        Insel* insel = (Insel*)inseln->Items[i];
        if(insel != 0)
        {
            insel->kontoreLeeren(player);
        }
    }
    ShowMessage("Alle Kontore des Spielers wurden geleert");
}

void __fastcall IndkSzen::schiffeLeeren(int player)
{
    for(int i=0; i<schiffe->Count; i++)
    {
        TSHIPSAVE* ship = (TSHIPSAVE*)schiffe->Items[i];
        if(ship->playernr == player && ship->kind != 5)
        {
            for(int i=0; i<8; i++)
            {
                ship->waren[i].hausid = 0;
                ship->waren[i].menge = 0;
            }
        }
    }
    ShowMessage("Alle Schiffe des Spielers wurden geleert");
}

void __fastcall IndkSzen::karrenLeeren(int player)
{
    for(int i=0; i<schiffe->Count; i++)
    {
        TSHIPSAVE* ship = (TSHIPSAVE*)schiffe->Items[i];
        if(ship->playernr == player && ship->kind == 5)
        {
            for(int i=0; i<8; i++)
            {
                ship->waren[i].menge = 0;
            }
        }
    }
    ShowMessage("Alle Karren des Spielers wurden geleert");
}

void __fastcall IndkSzen::setChildrenState(TControl* parent, bool state)
{
    for(int i=0; i<MainForm->ComponentCount; i++)
    {
        TControl* ctrl =
            dynamic_cast<TControl*>(MainForm->Components[i]);
        if(ctrl != 0 && ctrl->Parent == parent)
            ctrl->Enabled = state;
    }
}

bool __fastcall IndkSzen::moveIslandBy(const TPoint& delta)
{
    dragValid = false;
    Insel* insel = getSelectedIsland();
    if(insel != 0)
    {
        insel->moveBy(delta);
        TRect bbox = insel->boundingBox();
        TRect pbrect = Bounds(0, 0, WIDTH, HEIGHT);
        TRect dummy;
        IntersectRect(dummy, bbox, pbrect);
        if(dummy == bbox)
        {
            // bbox liegt komplett in PaintBox
            dragValid = true;
            for(int i=0; i<inseln->Count; i++)
            {
                Insel* other = (Insel*)inseln->Items[i];
                if(other != 0 && other != insel)
                {
                    if(IntersectRect(dummy, bbox, other->boundingBox()))
                    {
                        dragValid = false;
                        break;
                    }
                }
            }
        }
    }
    return dragValid;
}

int __fastcall IndkSzen::getNumChanges() const
{
    return numChanges;
}
