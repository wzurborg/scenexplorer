//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Stadt.h"

Stadt::Stadt( void* mem, UINT len )
: AnnoObject( mem, len, "STADT" ), myInsel(0)
{
    stadt = (TSTADTSAVE*)_mem;
    myCategory = "Städte";
}

Stadt::~Stadt()
{
}

AnsiString Stadt::getName(void) const
{
    return stadt->name;
}

TRect Stadt::boundingBox(void) const
{
   return
    myInsel->getStadtBox( stadt->stadtnr );    
}

void Stadt::setInsel(Insel* insel)
{
    myInsel = insel;
}


TImageIndex Stadt::getImageIndex() const
{
    return 1 + stadt->playernr;
}

bool Stadt::renameAllowed() const
{
    return true;
}

void Stadt::rename(const AnsiString& newName)
{
    strncpy( stadt->name, newName.c_str(), 31 );
    stadt->name[31] = '\0';
}


