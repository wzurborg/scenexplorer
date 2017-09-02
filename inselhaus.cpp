#include <vcl\Dialogs.hpp>
#include "Inselhaus.h"
#include "Insel.h"

#include "IndkSzen.h"

Inselhaus::Inselhaus( void* mem, UINT len )
: AnnoObject( mem, len, "INSELHAUS" ), myInsel(0)
{
    felder = (TISOSAVE*)_mem;
}

Inselhaus::~Inselhaus()
{
}

TPoint Inselhaus::fldSize( int id )
{
    switch( id )
    {
    case 303: return TPoint(3,1); // Stadttor
    case 311: return TPoint(2,2); // kl. Burg
    case 313: return TPoint(3,3); // gr. Burg
    case 315: return TPoint(5,5); // Festung
    case 527: return TPoint(3,3); // Kanonengießerei
    case 801: return TPoint(4,6); // Kathedrale
    case 803: return TPoint(1,2); // Kapelle
    case 805: return TPoint(3,4); // Kirche
    case 807: return TPoint(3,2); // Wirtshaus
    case 823:                     // zerstörter Markt
    case 809: return TPoint(3,4); // Markt
    case 811: return TPoint(2,2); // Feuerwehr
    case 813: return TPoint(3,4); // Badehaus
    case 815: return TPoint(3,3); // Theater
    case 817: return TPoint(2,2); // Arzt
    case 819: return TPoint(3,3); // Hochschule
    case 821: return TPoint(2,2); // Schule
    case 2111: return TPoint(3,3); // kl. Werft
    case 2115: return TPoint(4,4); // gr. Werft
    case 2211: return TPoint(4,4); // Pyramide
    case 2221: return TPoint(3,2); // Piratenkontor
  //case ????: // Schloss
  //case ????: // Triumphbogen  

   	case 1110:
		return TPoint(6,6);

   	case 1108:  // Berge
    case 1109:
    case 2101:  // Kontore
    case 2103:
    case 2105:
    case 2107:
	    return TPoint(4,4);

   	case 1103:
    case 1106:
    case 1107:
      	return TPoint(3,3);

    case  904:
    case  905:
   	case 1104:
    case 1105:
      	return TPoint(2,2);
   }

    if(id > 500 && id < 660) // Wohnhäuser, Betriebe
        return TPoint(2,2);

    if(id > 1500 && id < 1520)
        return TPoint(2,2); // Plantagengebäude

    if(id > 2000 && id < 2010)
        return TPoint(2,2); // Holzfäller, Jäger

    if(id > 2200 && id < 2250)
        return TPoint(2,2); // Piraten & Eingeborene

    if(id > 2400 && id < 2408)
        return TPoint(2,1); // Minen

    if(id > 823  && id < 900)
        return TPoint(1,1);

    return TPoint(1,1);
}

TColor Inselhaus::pixelColor( int id, int player )
{
    if( id == 1201 )
        return TColor(0x00FF4444);

    if( id == 1204 || id == 1209 )
        return TColor(0x00FF8888);  // mittelblau

    if( id != 1206 )
    {
        if( id > 1201 && id < 1209 )
            return TColor(0x00FFCCCC);    // hellblau

       if( ( id > 1200 && id < 1214 ) ||
           ( id > 1237 && id < 1300 ) ||
           ( id >  900 && id <  906 ) )
            return TColor(0x00FF4444);  // dunkelblau
    }

/*
   if( ( id > 1103 && id < 1111 ) ||
       ( id > 2300 && id < 2400 ) )
        return clLtGray;

   if( ( id >  106 && id <  161 ) ||
       ( id > 2761 && id < 2801 ) )
        return clYellow;
*/

    return MainForm->getCurrSzen()->playerColor(player);
    //return TColor(0x00406389);
}

void Inselhaus::paint(TCanvas* canvas)
{
    TPoint pos = myInsel->getPos();
    int num = _len / sizeof(TISOSAVE);

    for( int i=0; i<num; i++ )
    {
        // Get field colour
        TColor c = pixelColor( felder[i].id,
            felder[i].playernr );

        TPoint p(pos);
        p.x += felder[i].posx;
        p.y += felder[i].posy;
        TPoint w = fldSize(felder[i].id);
        int wx = w.x;
        int wy = w.y;
        if(felder[i].ausricht % 2 == 0)
        {
            wx = w.y;
            wy = w.x;
        }
        for( int j=0; j<wx; j++ )
        for( int k=0; k<wy; k++ )
            canvas->Pixels[p.x+j][p.y+k] = c;
    }
}

TRect Inselhaus::getStadtBox(UINT stadtnr)
{
    TPoint pos = myInsel->getPos();
    int num = _len / sizeof(TISOSAVE);
    TRect r( 1000, 1000, 0, 0 );

    for( int i=0; i<num; i++ )
    {
        if( felder[i].stadtnr == stadtnr )
        {
            TPoint p(pos);
            p.x += felder[i].posx;
            p.y += felder[i].posy;
            if( p.x < r.Left ) r.Left = p.x;
            if( p.x > r.Right ) r.Right = p.x;
            if( p.y < r.Top ) r.Top = p.y;
            if( p.y > r.Bottom ) r.Bottom = p.y;
        }
    }
    return r;
}

void Inselhaus::saveToFile(TFileStream* tfs, bool leer) const
{
    TCHUNK chunk;
    strcpy( chunk.name, "INSELHAUS" );
    if(leer)
        chunk.lengh = 0;
    else
        chunk.lengh = _len;
    tfs->WriteBuffer( &chunk, sizeof(chunk));

    if(chunk.lengh > 0)
        tfs->WriteBuffer( felder, _len );
}

int Inselhaus::getStadtnr(int x, int y)
{
    TPoint pos = myInsel->getPos();
    int num = _len / sizeof(TISOSAVE);

    for( int i=0; i<num; i++ )
    {
        TPoint p(pos);
        p.x += felder[i].posx;
        p.y += felder[i].posy;
        TPoint sz = fldSize(felder[i].id);
        TRect r(p.x, p.y, p.x + sz.x, p.y + sz.y);
        if(x >= r.Left && x <= r.Right && y >= r.Top && y <= r.Bottom) 
        {
            return felder[i].stadtnr;
        }
    }
    return -1;
}

void __fastcall Inselhaus::stadtPlayerChange(TSTADTSAVE* stadt, int player)
{
    int num = _len / sizeof(TISOSAVE);

    for( int i=0; i<num; i++ )
    {
        if(felder[i].stadtnr == (UINT)stadt->stadtnr)
            felder[i].playernr = player;
    }
}    
