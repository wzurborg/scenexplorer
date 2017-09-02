//---------------------------------------------------------------------------

#ifndef StadtH
#define StadtH

#include "AnnoObject.h"
#include "Insel.h"

class Stadt : public AnnoObject
{
public:
    Stadt( void* mem, UINT len );
    virtual ~Stadt();
    virtual AnsiString getName(void) const;
    virtual TRect boundingBox(void) const;
    void setInsel(Insel*);
    int inline getInselnr(void) const;
    int inline getStadtnr(void) const;
    int inline getPlayernr(void) const;
    virtual TImageIndex getImageIndex() const;
    virtual bool renameAllowed() const;
    virtual void rename(const AnsiString& newName);

private:
    TSTADTSAVE* stadt;
    Insel* myInsel;

};


//---------------------------------------------------------------------------

int inline Stadt::getInselnr(void) const
{
    return stadt->inselnr;
}

int inline Stadt::getStadtnr(void) const
{
    return stadt->stadtnr;
}

int inline Stadt::getPlayernr(void) const
{
    return stadt->playernr;
}

#endif

