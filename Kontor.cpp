//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Kontor.h"

Kontor::Kontor( void* mem, UINT len )
: AnnoObject( mem, len, "KONTOR" ), myInsel(0)
{
    kontor = (TKONTORSAVE*)_mem;
    myCategory = "Kontore";
}

Kontor::~Kontor()
{
}

AnsiString Kontor::getName(void) const
{
    String res;
    if(myStadt != 0)
        res = myStadt->getName();
    return res;
}

void Kontor::setInsel(Insel* insel)
{
    myInsel = insel;
}

void Kontor::setStadt(Stadt* stadt)
{
    myStadt = stadt;
}

void Kontor::paint(TCanvas* canvas)
{
    if(myStadt != 0 && myInsel != 0)
    {
        TPoint ip = myInsel->getPos();
        ip.x += kontor->posx;
        ip.y += kontor->posy;
        
    }
}
