#include <vcl\Dialogs.hpp>
#include "Insel.h"
#include "Inselhaus.h"
#include "Anno1602Read.h"
#include "IndkSzen.h"
#include "main.h"

__fastcall Insel::Insel(const TINSELHEADSAVE& inselhead)
 : AnnoObject(0, 0, "INSEL"),insel5(0),saveflag(false)
{
    filenr = inselhead.filenr;
    sizenr = inselhead.sizenr;
    klimanr = inselhead.klimanr;
    nativflg = inselhead.nativflg != 0;
    inselhausList = new TList();
    staedte = new TList();
    kontore = new TList();
    hirsche = new TList();
    posx = inselhead.posx;
    posy = inselhead.posy;
    readInselFile();
    insel5->inselnr = inselhead.inselnr;
    insel5->klimanr = inselhead.klimanr;
}

__fastcall Insel::Insel( void* mem, UINT len, int type )
: AnnoObject( mem, len, "INSEL" ),insel5(0),saveflag(true)
{
    nativflg = false;
    if(type == 1)
    {
        // Insel needs conversion
        TINSEL_MAXFUN_SAVE* inselmf = (TINSEL_MAXFUN_SAVE*)_mem;
        TINSELSAVE* ti = new TINSELSAVE;
        convertInsel(*inselmf, *ti);
        delete [] _mem;
        _mem = ti;
    }

    insel5 = (TINSELSAVE*)_mem;
    filenr = insel5->filenr;
    sizenr = insel5->sizenr;
    klimanr = insel5->klimanr;
    posx = insel5->posx;
    posy = insel5->posy;

    inselhausList = new TList();
    staedte = new TList();
    kontore = new TList();
    hirsche = new TList();
    if(!insel5->orginalflg) {
        readInselFile();
//        insel5->orginalflg = 1;
    }
}

Insel::~Insel()
{
    for( int i=0; i<inselhausList->Count; i++ )
    {
        delete (Inselhaus*)inselhausList->Items[i];
    }
    delete inselhausList;

    delete staedte;

    delete kontore;
}

void Insel::addInselhaus( Inselhaus* inselhaus )
{
    inselhausList->Add( inselhaus );
    inselhaus->setInsel( this );
}

void Insel::addStadt(TSTADTSAVE* stadt)
{
    int stadtnr = stadt->stadtnr;
    if(stadtnr >= staedte->Count)
        staedte->Count = stadtnr + 1;
    staedte->Items[stadtnr] = stadt;
}

void Insel::addHirsch(THIRSCHSAVE* hirsch)
{
    if(hirsch->inselnr == (unsigned)insel5->inselnr)
    {
        hirsche->Add(hirsch);
    }
    else
        ShowMessage("Invalid inselnr!!");
}

void Insel::addKontor( TKONTORSAVE* kontor)
{
    kontore->Add(kontor);
}

AnsiString Insel::getName(void) const
{
    int nr = insel5->inselnr;
    return AnsiString("Insel ") + nr;
}

void Insel::paint(TCanvas* canvas)
{
    for( int i=0; i<inselhausList->Count; i++ )
    {
        ((Inselhaus*)inselhausList->Items[i])->paint( canvas );
        if(!MainForm->btStaedte->Down)
            break; // only 1st layer
    }
}

TRect Insel::boundingBox(void) const
{
    return Bounds( posx, posy, insel5->felderx,insel5->feldery );
}

TRect Insel::getStadtBox(int stadtnr)
{
    if( inselhausList->Count > 1 )
    {
        return
        ((Inselhaus*)inselhausList->Items[1])->getStadtBox( stadtnr );
    }
    return TRect();
}

void Insel::saveToFile(TFileStream* tfs, bool inselOnly) const
{
    if(!saveflag && !inselOnly)
    {
        // Insel wird nicht gesichert, weil sie aus einem SZENE-Block
        // erzeugt wurde und nicht alleine geschrieben wird
        return;
    }

    // Bei inselOnly wird die Anzahl der Städte auf null gesetzt
    unsigned char saveplayernr[11];
    if(inselOnly)
    {
        memcpy(&saveplayernr[0], &insel5->stadtplayernr[0], 11);
        for(int i=0; i<8; i++)
            insel5->stadtplayernr[i] = 7;   // alle Städte löschen
    }

    TCHUNK chunk;
    strcpy( chunk.name, "INSEL5" );
    chunk.lengh = sizeof(TINSELSAVE);
    tfs->WriteBuffer( &chunk, sizeof(chunk));
    tfs->WriteBuffer( insel5, sizeof(TINSELSAVE) );

    if(inselOnly)
    {
        // zurücksichern zum Weiterarbeiten...
        memcpy(&insel5->stadtplayernr[0], &saveplayernr[0], 11);
    }

    // Bei orginalflg == 0 kommt die Basis der Insel aus dem Inselfile
    // daher wird nur ein leeres Inselhaus geschrieben.
    //
    // Bei inselOnly wird das erste Inselhaus in jedem Fall
    // geschrieben, dann nichts weiter.
    for(int i=0; i<inselhausList->Count; i++)
    {
        bool leer = false;
        if(i == 0 && insel5->orginalflg == 0 && !inselOnly) leer = true;
        ((Inselhaus*)inselhausList->Items[i])->saveToFile(tfs, leer);
        if(inselOnly) break;
    }

    if(!inselOnly)
    {
        saveHirsche(tfs);
        saveStaedte(tfs, true); // with header
        saveKontore(tfs, true); // with header
    }
}

void __fastcall Insel::readInselFile()
{
    static char* s_klima[] = {"nord", "sued", "noklima"};
//    char* s_size[] = {"lar", "big", "med", "mit", "lit"};
    static char* s_size[] = {"lit", "mit", "med", "big", "lar"};

    if(klimanr > 2) {
        String msg = "klimanr: ";
        ShowMessage(msg + klimanr);
        return;
    }
    if(sizenr > 4) {
        String msg = "sizenr: ";
        ShowMessage(msg + sizenr);
        return;
    }

    String path = IndkSzen::GetInstallDir() + "\\";
    TVarRec args[] = {filenr};
    path = path + s_klima[klimanr];
    if(nativflg) path += "nat";
    if(nativflg) ShowMessage("nativflg!");
    path = path + "\\" + s_size[sizenr];
    if(filenr < 0xFFFF) path += Format("%2.2d", args, 0);
    path += ".scp";

    TFileStream* inselfile = new TFileStream(path, fmOpenRead);

    TCHUNK chunk;
    char* buffer = 0;

    bool done = false;
    while(!done) {
        if( inselfile->Read(&chunk, sizeof(TCHUNK)) != sizeof(TCHUNK)) {
            break;
        }

        if(chunk.lengh > 0) {
            buffer = new char[chunk.lengh];
            if(inselfile->Read(buffer, chunk.lengh) != chunk.lengh)
                break;

            AnsiString name(chunk.name);
            if(name == "INSEL5" || name == "INSEL4" || name == "INSEL3") {
                if(_mem == 0) {
                    _mem = new BYTE[chunk.lengh];
                    _len = chunk.lengh;
                    memcpy(_mem, buffer, chunk.lengh);
                    insel5 = (TINSELSAVE*)_mem;
                    insel5->posx = posx;
                    insel5->posy = posy;
                }
            }
            else if(name == "INSELHAUS") {
                Inselhaus* inselhaus = new Inselhaus( buffer, chunk.lengh);
                addInselhaus( inselhaus );
            }
            delete [] buffer;
            buffer = 0;
        }
    }
    delete [] buffer;
    delete inselfile;
}

void __fastcall Insel::convertInsel(const TINSEL_MAXFUN_SAVE& mf, TINSELSAVE& ke) const
{
    // fill ke with data from mf
  memset(&ke, 0, sizeof(ke));
  ke.inselnr = mf.inselnr;
  ke.felderx = mf.felderx;
  ke.feldery = mf.feldery;
  ke.strtduerrflg = mf.strtduerrflg;
  ke.nofixflg = mf.nofixflg;
  ke.vulkanflg = mf.vulkanflg;
  ke.posx = mf.posx;
  ke.posy = mf.posy;
  ke.hirschreviercnt = mf.hirschreviercnt;
  ke.speedcnt = mf.speedcnt;
  memcpy(&ke.stadtplayernr[0], &mf.stadtplayernr[0], 11);
  ke.schatzflg = 0;
  ke.rohstanz = 0;
  ke.eisencnt = mf.eisencnt;
  ke.playerflags = mf.playerflags;
  ke.vulkancnt = 0;
  for(int i=0; i<2; i++) {
    memcpy(&ke.eisenberg[i], &mf.eisenberg[i], sizeof(TERZBERG));
    memcpy(&ke.vulkanberg[i], &mf.vulkanberg[i], sizeof(TERZBERG));
    if(mf.vulkanberg[i].lager != 0) ke.vulkancnt++;
  }
  ke.rohstflags = mf.rohstflags;
  ke.filenr = mf.filenr;
  ke.sizenr = mf.sizenr;
  ke.klimanr = mf.klimanr;
  ke.orginalflg = mf.orginalflg;
  ke.duerrproz = mf.duerrproz;
  ke.rotier = mf.rotier;
  ke.seeplayerflags = mf.seeplayerflags;
  ke.duerrcnt = mf.duerrcnt;
}



AnsiString __fastcall Insel::getDescr() const
{
    int w, h, k;
    w = insel5->felderx;
    h = insel5->feldery;
    k = insel5->klimanr;
    String d("Insel " );
    d += String(insel5->inselnr) + ": ";
    d = d + w + "x" + h + " " + (k == 0 ? "N" : "S");
    return d;
}

TSTADTSAVE* Insel::getStadt(int x, int y)
{
    TRect box = boundingBox();
    if(x < box.Left || x > box.Right || y < box.Top || y > box.Bottom)
        return 0;

    for(int i=1; i<inselhausList->Count; i++)
    {
        int s = ((Inselhaus*)inselhausList->Items[i])->getStadtnr(x, y);
        if(s != -1 && s < 7)
            return (TSTADTSAVE*)staedte->Items[s];
    }
    return 0;
}

bool Insel::isEmpty() const
{
    for(int i=0; i<7; i++)
    {
        if(insel5->stadtplayernr[i] < 7)
            return false;
    }
    return true;
}

int __fastcall Insel::saveStaedte(TFileStream* out, bool writeHeader) const
{
    int pos = out->Position;
    TCHUNK chunk;
    if(writeHeader)
    {
        strcpy(chunk.name, "STADT4");
        chunk.lengh = 0;    // dummy
        out->Write(&chunk, sizeof(TCHUNK));
    }

    for(int i=0; i<staedte->Count; i++)
    {
        TSTADTSAVE* stadt = (TSTADTSAVE*)staedte->Items[i];
        if(stadt != 0)
        {
            out->Write(stadt, sizeof(TSTADTSAVE));
        }
    }

    if(writeHeader)
    {
        // rewrite chunk
        chunk.lengh = out->Position - pos - sizeof(TCHUNK);
        out->Position = pos;
        out->Write(&chunk, sizeof(TCHUNK));
        out->Seek(0, soFromEnd);
    }

    return 0;
}

int __fastcall Insel::saveKontore(TFileStream* out, bool writeHeader) const
{
    int pos = out->Position;
    TCHUNK chunk;
    if(writeHeader)
    {
        strcpy(chunk.name, "KONTOR2");
        chunk.lengh = 0; // dummy
        out->Write(&chunk, sizeof(TCHUNK));
    }

    for(int i=0; i<kontore->Count; i++)
    {
        TKONTORSAVE* kontor = (TKONTORSAVE*)kontore->Items[i];
        out->Write(kontor, sizeof(TKONTORSAVE));
    }

    if(writeHeader)
    {
        // rewrite chunk
        chunk.lengh = out->Position - pos - sizeof(TCHUNK);
        out->Position = pos;
        out->Write(&chunk, sizeof(TCHUNK));
        out->Seek(0, soFromEnd);
    }

    return 0;
}

int __fastcall Insel::saveHirsche(TFileStream* out) const
{
    int pos = out->Position;
    TCHUNK chunk;
    strcpy(chunk.name, "HIRSCH2");
    chunk.lengh = 0;    // dummy
    out->Write(&chunk, sizeof(TCHUNK));

    int count = 0;
    for(int i=0; i<hirsche->Count; i++)
    {
        THIRSCHSAVE* hirsch = (THIRSCHSAVE*)hirsche->Items[i];
        out->Write(hirsch, sizeof(THIRSCHSAVE));
        count++;
    }

    // rewrite chunk
    chunk.lengh = count * sizeof(THIRSCHSAVE);
    out->Position = pos;
    out->Write(&chunk, sizeof(TCHUNK));
    out->Seek(0, soFromEnd);

    return 0;
}

void __fastcall Insel::stadtPlayerChange(TSTADTSAVE* stadt, int player)
{
    if(stadt->inselnr == insel5->inselnr)
    {
        insel5->stadtplayernr[stadt->stadtnr] = player;
        stadt->playernr = player;
        for(int i=0; i<inselhausList->Count; i++)
        {
            ((Inselhaus*)inselhausList->Items[i])->stadtPlayerChange(stadt, player);
        }
    }

}



TKONTORSAVE* __fastcall Insel::getKontor(unsigned stadtnr)
{
    for(int i=0; i<kontore->Count; i++)
    {
        TKONTORSAVE* kontor = (TKONTORSAVE*)kontore->Items[i];
        if(kontor->stadtnr == stadtnr)
            return kontor;
    }
    return 0;
}

void __fastcall Insel::kontoreLeeren(int player)
{
    for(int i=0; i<kontore->Count; i++)
    {
        TKONTORSAVE* kontor = (TKONTORSAVE*)kontore->Items[i];
        TSTADTSAVE* stadt = (TSTADTSAVE*)staedte->Items[kontor->stadtnr];
        if(stadt->playernr == player)
        {
            for(int i=0; i<50; i++)
            {
                kontor->waren[i].lager = 0;
                kontor->waren[i].ownlager = 0;
                kontor->waren[i].minlager = 0;
            }
        }
    }
}

void __fastcall Insel::moveBy(const TPoint& delta)
{
    posx += delta.x;
    posy += delta.y;
    insel5->posx = posx;
    insel5->posy = posy;
}

