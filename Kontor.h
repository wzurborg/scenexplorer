//---------------------------------------------------------------------------

#ifndef KontorH
#define KontorH

#include "AnnoObject.h"
#include "Insel.h"
#include "Stadt.h"

class Kontor : public AnnoObject
{
public:
    Kontor( void* mem, UINT len );
    virtual ~Kontor();
    virtual AnsiString getName(void) const;
    void setInsel(Insel*);
    void setStadt(Stadt*);
    int inline getInselnr(void) const;
    int inline getStadtnr(void) const;
    virtual void paint(TCanvas* canvas);

private:
    TKONTORSAVE* kontor;
    Insel* myInsel;
    Stadt* myStadt;

};


//---------------------------------------------------------------------------

int inline Kontor::getInselnr(void) const
{
    return kontor->inselnr;
}

int inline Kontor::getStadtnr(void) const
{
    return kontor->stadtnr;
}

#endif
