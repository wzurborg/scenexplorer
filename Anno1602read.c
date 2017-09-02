#include <string.h>
#include "Anno1602Read.h"


int saveanz;
int inselanz;
int i,j;
void* prodlistsave;
void* rohwachssave;
void* militarsave;
void* siedlersave;
void* kontorsave;

/*========================================*
I  Produktionsstrukturen einlesen !!      I
+=========================================*/
void ReadIsoProdList(char *name, void *mem, long lengh)
{
/*---Neueste Spielstandsvariante---*/
  if (strcmp(name, "PRODLIST2") == 0)
  {
    prodlistsave = mem;
    saveanz = lengh/sizeof(TPRODLISTSAVE);
    for (i = 0; i < saveanz; i++)
    {
    }
  }
}


/*========================================*
I  Rohstoffwachstumsstrukturen einlesen!  I
+=========================================*/
void ReadIsoRohWachs(char *name, void *mem, long lengh)
{
/*---Neues Spielstandformat---*/
  if (strcmp(name, "ROHWACHS2") == 0)
  {
    rohwachssave = mem;
    saveanz = lengh/sizeof(TROHWACHSSAVE);
    for (i = 0; i < saveanz; i++)
    {
    }
  }
}


/*========================================*
I  Werftstrukturen einlesen !!            I
+=========================================*/
void ReadIsoWerft(char *name, void *mem, long lengh)
{
//  TISOINSEL   *aktinsel;
//  TISOFELD    *aktfeld;
//  TISOHAUS    *akthaus;
//  TISOSTADT   *aktstadt;
//  TWERFT      *aktwerft;
//  TWERFTSAVE  *werftsave;

  if (strcmp(name, "WERFT") == 0)
  {
//    werftsave = mem;
//    saveanz = lengh/sizeof(TWERFTSAVE);
//    for (i = 0; i < saveanz; i++)
//    {
//    }
  }
}


/*========================================*
I  Militarstrukturen einlesen !!            I
+=========================================*/
void ReadIsoMilitar(char *name, void *mem, long lengh)
{
  if (strcmp(name, "MILITAR") == 0)
  {
    militarsave = mem;
    saveanz = lengh/sizeof(TMILITARSAVE);
    for (i = 0; i < saveanz; i++)
    {
      //
      //  Diverse Einleseverarbeitung
      //
      //  .
      //  .

      /*---Waffenvorräte in Kaserne---*/
//        for (j = 0; j < 3; j++) aktmilitar->wafflager[j] = militarsave[i].wafflager[j];

      /*---Ausgebildete Einheiten---*/
/*
        for (j = 0; j < MAXMILOBJ; j++)
        {
          if ((figurnr = militarsave[i].objlist[j].figurnr) != FIG_UNUSED)
          {
            aktmilitar->objlist[j].trainflg = militarsave[i].objlist[j].trainflg;
            aktmilitar->objlist[j].waffflg  = militarsave[i].objlist[j].waffflg;
            aktmilitar->objlist[j].energy   = militarsave[i].objlist[j].energy;
            aktmilitar->objlist[j].expert   = militarsave[i].objlist[j].expert;
            aktplayer->soldatanz[einh_figur[figurnr].kind]++;
          }
          aktmilitar->objlist[j].figurnr  = figurnr;
        }
      }
*/      
    }
  }
}


/*========================================*
I  Siedlerstrukturen einlesen !!          I
+=========================================*/
void ReadIsoSiedler(char *name, void *mem, long lengh)
{
  if (strcmp(name, "SIEDLER") == 0)
  {
    siedlersave = mem;
    saveanz = lengh/sizeof(TSIEDLERSAVE);
    for (i = 0; i < saveanz; i++)
    {
    }
  }
}


/*========================================*
I  Kontor-Strukturen einlesen !!          I
+=========================================*/
void ReadIsoKontor(char *name, void *mem, long lengh)
{
  if (strcmp(name, "KONTOR2") == 0)
  {
    kontorsave = mem;
    saveanz = lengh/sizeof(TKONTORSAVE);
    for (i = 0; i < saveanz; i++)
    {
//      ReadIsoKontorHeader( .. )

    /*---Waren einlesen und ans Netzwerk senden---*/
/*
      for (j = 0; j < MAXKONTWARESAVE; j++)
      {
        if ((akthaus = GetIsoHaus(20000+kontorsave[i].waren[j].hausid)) != NULL)
        {
          aktkontware = &aktkontor->waren[akthaus->prodtyp.ware];
          aktkontware->lager    = kontorsave[i].waren[j].lager;
          aktkontware->bedarf   = kontorsave[i].waren[j].bedarf;
          aktkontware->minlager = kontorsave[i].waren[j].minlager;
          aktkontware->vkpreis  = kontorsave[i].waren[j].vkpreis;
          aktkontware->ekpreis  = kontorsave[i].waren[j].ekpreis;
          aktkontware->vkflg    = kontorsave[i].waren[j].vkflg;
          aktkontware->ekflg    = kontorsave[i].waren[j].ekflg;
        }
      }
*/      
    }
  }
}

/*========================================+
I  Status der Zeitzähler für Rechen-      I
I  routinen einlesen !!                   I
+=========================================*/
void ReadIsoTimers(char *name, void *mem, long lengh)
{
}

/*========================================*
I  Markt-Strukturen einlesen !!          I
+=========================================*/
void ReadIsoMarkt(char *name, void *mem, long lengh)
{
  int         i, j;
  int         saveanz;
  UINT        mware;
//  TISOHAUS    *akthaus;
//  TISOSTADT   *aktstadt;
//  TMARKT      *aktmarkt;
  TMARKTSAVE  *marktsave;

  if (strcmp(name, "MARKT2") == 0)
  {
    saveanz = lengh/sizeof(TMARKTSAVE);
    for (i = 0; i < saveanz; i++)
    {
      //
      //  Diverse Einleseverarbeitung
      //
      //  .
      //  .

      // Marktwarenbestand einlesen
/*
      for (j = 0; j < 16; j++)
      {
        if (((akthaus = GetIsoHaus(20000+marktsave[i].waren[j].hausid)) != NULL)
        &&  (CheckIfMarktWare(akthaus->prodtyp.ware)))
        {
          mware = WareToMarktWare(akthaus->prodtyp.ware);
          aktmarkt->waren[mware].wareneed = marktsave[i].waren[j].wareneed;
          aktmarkt->waren[mware].waregive = marktsave[i].waren[j].waregive;
          aktmarkt->waren[mware].wareproz[0] = marktsave[i].waren[j].wareproz;
        }
      }
*/      
    }
  }
}


/*========================================*
I  Stadt-Strukturen einlesen !!          I
+=========================================*/
void ReadIsoStadt(char *name, void *mem, long lengh)
{

/*---Ältere Stadt-Savestruktur---*/
  if (strcmp(name, "STADT3") == 0)
  {
    //
    //  Nicht mehr nötig
    //
  }
/*---Aktuelle Stadt-Savestruktur---*/
  else if (strcmp(name, "STADT4") == 0)
  {
    saveanz = lengh/sizeof(TSTADTSAVE);
    for( i = 0; i < saveanz; i++ )
    {
//      ReadIsoStadtHeader( .. );
    }
  }
}


/*========================================+
I  Insel-Daten einlesen und konvertieren  I
+=========================================*/
void ReadIsoInselHaus(char *name, void *mem, long lengh)
{
}


/*========================================+
I  Insel-Daten einlesen und konvertieren  I
+=========================================*/
void ReadIsoInsel(char *name, void *mem, long lengh)
{
/*---Älteres Insel-Format---*/
  if (strcmp(name, "INSEL3") == 0)
  {
    //
    //  Nicht mehr nötig
    //
  }
  else if (strcmp(name, "INSEL4") == 0)
  {
    //
    //  Nicht mehr nötig
    //
  }
/*---Aktuelles Insel-Format---*/
  else if (strcmp(name, "INSEL5") == 0)
  {
    inselanz = lengh/sizeof(TINSELSAVE);
    for (i = 0; i < inselanz; i++)
    {
//      ReadIsoInselHeader( ... )
//      ReadIsoGameData(fp, "INSELHAUS", FALSE);
    }
  }
  else if (strcmp(name, "INSEL_MAXFUN") == 0)
  {
    inselanz = lengh/sizeof(TINSEL_MAXFUN_SAVE);
    for (i = 0; i < inselanz; i++)
    {
//      ReadIsoInselHeader( ... )
//      ReadIsoGameData(fp, "INSELHAUS", FALSE);
    }
  }
}


/*========================================*
I    Hirsch-Strukturen einlesen !!        I
+=========================================*/
void ReadIsoHirsch(char *name, void *mem, long lengh)
{
}

/*========================================*
I   Spieler-Strukturen einlesen !!        I
+=========================================*/
void ReadIsoPlayer(char *name, void *mem, long lengh)
{
}

/*========================================+
I   Informationen über zufällig ver-      I
I   teilte Inselwelt einlesen !!          I
+=========================================*/
void ReadIsoShip(char *name, void *mem, long lengh)
{
}

void ReadIsoHandler(char *name, void *mem, long lengh)
{
}

void ReadIsoSoldat(char *name, void *mem, long lengh)
{
}

void ReadIsoSoldatInsel(char *name, void *mem, long lengh)
{
}

void ReadIsoTurm(char *name, void *mem, long lengh)
{
}

void ReadIsoAuftrag(char *name, void *mem, long lengh)
{
}



/*========================================+
I   Pointer auf aktuelle Laderoutinen     I
I   holen !!                              I
+=========================================*/
void (*GetIsoChunkReader(char *name))(char *name, void *pMem, long lengh)
{
  if (strcmp(name, "INSELHAUS") == 0) return &ReadIsoInselHaus;
 #if (!defined MAXFUN)||(defined MISSIONEDIT)
  else if (strcmp(name, "INSEL3") == 0) return &ReadIsoInsel;
  else if (strcmp(name, "INSEL4") == 0) return &ReadIsoInsel;
  else if (strcmp(name, "INSEL5") == 0) return &ReadIsoInsel;
 #endif
// #ifdef MAXFUN
  else if (strcmp(name, "INSEL_MAXFUN") == 0) return &ReadIsoInsel;
// #endif
  else if (strcmp(name, "PRODLIST2") == 0) return &ReadIsoProdList;
  else if (strcmp(name, "ROHWACHS2") == 0) return &ReadIsoRohWachs;
  else if (strcmp(name, "SIEDLER") == 0) return &ReadIsoSiedler;
  else if (strcmp(name, "WERFT") == 0) return &ReadIsoWerft;
  else if (strcmp(name, "MILITAR") == 0) return &ReadIsoMilitar;
  else if (strcmp(name, "KONTOR2") == 0) return &ReadIsoKontor;
  else if (strcmp(name, "MARKT2") == 0) return &ReadIsoMarkt;
  else if (strcmp(name, "STADT3") == 0) return &ReadIsoStadt;
  else if (strcmp(name, "STADT4") == 0) return &ReadIsoStadt;
  else if (strcmp(name, "HIRSCH2") == 0) return &ReadIsoHirsch;
  else if (strcmp(name, "SHIP4") == 0) return &ReadIsoShip;
  else if (strcmp(name, "HANDLER") == 0) return &ReadIsoHandler;
  else if (strcmp(name, "SOLDAT2") == 0) return &ReadIsoSoldat;
  else if (strcmp(name, "SOLDAT3") == 0) return &ReadIsoSoldat;
  else if (strcmp(name, "SOLDATINSEL") == 0) return &ReadIsoSoldatInsel;
  else if (strcmp(name, "TURM") == 0) return &ReadIsoTurm;
  else if (strcmp(name, "TIMERS") == 0) return &ReadIsoTimers;
  else if (strcmp(name, "PLAYER2") == 0) return &ReadIsoPlayer;
  else if (strcmp(name, "PLAYER3") == 0) return &ReadIsoPlayer;
  else if (strcmp(name, "PLAYER4") == 0) return &ReadIsoPlayer;
  else if (strcmp(name, "AUFTRAG") == 0) return &ReadIsoAuftrag;
  else if (strcmp(name, "AUFTRAG2") == 0) return &ReadIsoAuftrag;
  else if (strcmp(name, "AUFTRAG4") == 0) return &ReadIsoAuftrag;
 #if (defined CUSTOMSZENES)||(defined MISSIONEDIT)
  else if (strcmp(name, "SZENE") == 0) return &ReadIsoSzeneData;
  else if (strcmp(name, "RANDTAB") == 0) return &ReadIsoSzeneRandTab;
  else if (strcmp(name, "NAME") == 0) return &ReadIsoSzeneName;
  else if (strcmp(name, "CUSTOM") == 0) return &ReadIsoSzeneName;
 #endif
  return NULL;
}


