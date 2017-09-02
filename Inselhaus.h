#ifndef __inselhaus_h__
#define __inselhaus_h__

#include "AnnoObject.h"

#include "Main.h"

class Insel;

class Inselhaus: public AnnoObject
{
public:
    Inselhaus(void* mem, UINT len);
    virtual ~Inselhaus();
    virtual void paint(TCanvas* canvas);
    void inline setInsel(Insel* insel);
    TRect getStadtBox(UINT stadtnr);
    void saveToFile(TFileStream* tfs, bool leer) const;
    int getStadtnr(int x, int y);
    void __fastcall stadtPlayerChange(TSTADTSAVE* stadt, int player);

private:
    static TPoint fldSize( int id );
    static TColor pixelColor( int id, int player );

    TISOSAVE* felder;
    Insel* myInsel;
};

#endif


void inline Inselhaus::setInsel(Insel* insel)
{
    myInsel = insel;
}