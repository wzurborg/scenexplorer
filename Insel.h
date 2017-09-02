#ifndef __insel_h__
#define __insel_h__

#include "AnnoObject.h"

class Inselhaus;

class Insel: public AnnoObject
{
public:
    __fastcall Insel( void* mem, UINT len, int type );
    __fastcall Insel(const TINSELHEADSAVE&);
    virtual ~Insel();

    void addInselhaus( Inselhaus* inselhaus );
    void addStadt(TSTADTSAVE* stadt);
    void addKontor(TKONTORSAVE* kontor);
    void addHirsch(THIRSCHSAVE* hirsch);
    virtual void paint(TCanvas* canvas);
    TPoint inline getPos(void) const;
    virtual TRect boundingBox(void) const;
    int inline getInselnr(void) const;
    TRect getStadtBox(int stadtnr);
    virtual void saveToFile(TFileStream* tfs, bool inselOnly) const;
    AnsiString __fastcall getDescr() const;
    TSTADTSAVE* getStadt(int x, int y);
    bool isEmpty() const;
    int __fastcall saveStaedte(TFileStream* out, bool writeHeader) const;
    int __fastcall saveKontore(TFileStream* out, bool writeHeader) const;
    int __fastcall saveHirsche(TFileStream* out) const;
    void __fastcall stadtPlayerChange(TSTADTSAVE* stadt, int player);
    const void* getNode() const {return myNode;}
    void setNode(void* node) {myNode = node;}
    TKONTORSAVE* __fastcall getKontor(unsigned stadtnr);
    void __fastcall kontoreLeeren(int player);
    void __fastcall moveBy(const TPoint& delta);

private:
    TINSELSAVE* insel5;
    int filenr;
    int sizenr;
    int klimanr;
    int posx;
    int posy;
    bool nativflg;
    TList* inselhausList;
    TList* staedte;
    TList* kontore;
    TList* hirsche;
    void* myNode;
    bool saveflag;  // 1 = Insel wird gesichert
    virtual AnsiString getName(void) const;
    void __fastcall readInselFile();
    void __fastcall convertInsel(const TINSEL_MAXFUN_SAVE& mf, TINSELSAVE& ke) const;
};


TPoint inline Insel::getPos(void) const
{
    return TPoint( posx, posy );
}

int inline Insel::getInselnr(void) const
{
    return insel5->inselnr;
}



#endif

