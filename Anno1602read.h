#ifndef __Anno1602Read_H__
#define __Anno1602Read_H__

typedef unsigned char  BYTE;
typedef unsigned short UWORD;
typedef unsigned int   UINT;
typedef BYTE  TFPOS;
typedef UWORD TIPOS;


/*============================================+
I    Struktur FILECHUNK!                      I
+=============================================*/
typedef struct {
  char   name[16];
  long   lengh;
} TCHUNK;

/*========================================+
I  Structur Erzberg !!                    I
+=========================================*/
typedef struct {
  BYTE    ware;         // Welche Ware liegt hier??
  BYTE    posx;         // Position auf Insel
  BYTE    posy;         // "
  BYTE    playerflags;  // Welche Spieler kennen Geheimnis (ACHTUNG: PLAYER_MAX)
  BYTE    kind;         // Welche Ausführung??
  BYTE    leer1;        // Reserve ist immer gut
  UWORD   lager;        // Wieviel liegt hier ??
} TERZBERG;

/*========================================+
I  Struktur EVENT unter Spielers !!       I
+=========================================*/
typedef struct {
  BYTE      kind;
  BYTE      playernr;
  BYTE      leer1[2];
  UINT      timecnt;
} TRELATION;

/*========================================+
I  Struktur Vertrag   !!                  I
+=========================================*/
typedef struct {
  BYTE    status;     // Welche Vertragsstufe (keine, angeboten, erhalten, abgeschlossen)
  BYTE    leer1[3];   // Reserve ist immer gut!!
  UINT    timecnt;    // Zeitpunkt des Abschlußes
} TVERTRAG;

/*========================================+
I Structur Iso-Objekt-Beschreibung!!      I
+=========================================*/
typedef struct {
  BYTE     kind;
  union    {
  BYTE     inselnr;
  TFPOS    posh;
  };
  union    {
  TIPOS    pos;
  UWORD    nr;
  struct   {
  BYTE     stadtnr;
  BYTE     leer1;
  };
  };
} TISOOBJ;

/*========================================+
I  Struktur AUFTRAGWARE !!                I
+=========================================*/
typedef struct {
  BYTE      ware;
  BYTE      anz;
} TWAREMONO;

/*========================================+
I  Struktur AUFTRAGCITY !!                I
+=========================================*/
typedef struct {
  int       wohnanz;
  int       bgruppnr;
  UINT      bgruppwohn;
} TSTADTMIN;

/*========================================+
I  Struktur AUFTRAGWARE !!                I
+=========================================*/
typedef struct {
  BYTE      ware;
  BYTE      leer1;
  UWORD     lager;
} TWAREMIN;

/*========================================+
I  Struktur AUFTRAG-Save für Spieler !!   I
+=========================================*/
typedef struct {
  int       nr;
  UINT      flags;
  UINT      looseflags;
  UINT      leer1[5];
  TWAREMONO waremono[2];
  BYTE      helpplayernr;
  BYTE      leer2[6];
  BYTE      killanz;
  BYTE      killplayernr[16];
  int       killstadtanz;
  int       stadtanz;
  int       wohnanz;
  int       money;
  int       bilanz;
  int       meldnr;
  int       handelsbilanz;
  int       stadtanzmin;
  short     stadtanzminfrmd;
  short     leer4[1];
  int       leer3[2];
  char      infotxt[2048];
  TWAREMIN  waremin[2];
  TSTADTMIN stadtmin[4];
  TSTADTMIN stadtlowfrmd;
  TSTADTMIN stadtminall;
  TSTADTMIN stadtminfrmd;
} TAUFTRAGSAVE;

/*========================================+
I  Spielerstruktur - SAVE !!              I
+=========================================*/
typedef struct {
  int       money;              // Kapitalstand
  BYTE      kind;               // Menschliche oder Computerspieler, Piraten, Eingeborene,...
  BYTE      playernr;           // Spielerstrukturnummer
  BYTE      humananz;           // Anzahl menschlicher Spieler
  BYTE      colornr;            // Welche Farbe hat sich Spieler ausgesucht??
  BYTE      killer;             // Welcher Spieler hat diesem ausgeschalten??
  BYTE      leer1[1];           // Reserve ist immer gut !!
  UWORD     stirbcnt;           // Wielange ist Spieler schon Schiffe- und Städtelos??
  BYTE      auftragnr;          // Welche Aufgabe ist zu meistern ??
  BYTE      lockflg;            // Spieler darf nicht vom Menschen übernommen werden
  BYTE      schlossbauanz;      // Es wurde bereits ein Schloss gebaut
  BYTE      kathedralbauanz;    // Es wurde bereits ein Schloss gebaut
  UWORD     triumphanz;         // Wieviele Triumphbögen hat Spieler bekommen
  UWORD     triumphbauanz;      // Wieviele Triumphbögen hat Spieler gebaut
  UWORD     killsoldatanz;      // Wieviele Soldaten wurden besiegt
  UWORD     losssoldatanz;      // Wieviele Soldaten sind gefallen
  UWORD     lossshipanz;        // Wieviele Schiffe sind gesunken
  UWORD     killshipanz;        // Wieviele Schiffe wurden versenkt
  UINT      compflags;          // Szenarioinstruktionen für Computergegner??
  UWORD     humanwohnmax;       // Wieviele Leute dürfen max. in menschlicher Siedlung leben
  UWORD     wohnmin;            // Ab wahn wird Computergegner sauer ??
  BYTE      bgruppmin;          // Unter welchen Pegel darf Computer nicht fallen??
  BYTE      bgruppmaxhuman;     // Uber welchen Pegel darf kein Spieler sein??
  BYTE      leer3[2];           // Reserve ist immer Gut !!
  UINT      leer4[3];           // Reserve ist immer Gut !!
  UINT      bauinfraflags;      // Welche Gebäude können bereits gebaut werden??
  UWORD     denkanz;            // Wieviele Denkmäler hat Spieler bekommen
  UWORD     denkbauanz;         // Wieviele Denkmäler hat Spieler gebaut
  UWORD     weltx, welty;       // Wo befand sich Spieler auf der Weltkarte??
  UWORD     waregive[16];       // Wieviel Waren wurden von Spielern geschenkt??
  UWORD     waretrad[16];       // Wieviel Ware, die gebraucht wurde, wurden von Spielern geliefert??
  UINT      hitpoint[16];       // Wieviel Treffer wurden von Spielern ausgeteilt??
  TVERTRAG  frieden[16];        // Mit wem wurden Friedensverträge vereinbart??
  TVERTRAG  handel[16];         // Mit wem wurden Handelsverträge vereinbart??
  TRELATION relation[64];       // Ereignisse unter Spielern !!
  char      name[64];           // Voller Spielername
  char      callname[48];       // Abgekürzter Name
} TPLAYERSAVE;

/*========================================+
I  Zeitcounter für die Rechenroutineen    I
+=========================================*/
typedef struct {
  BYTE      cnt_stadt;
  BYTE      cnt_insel;
  BYTE      cnt_werft;
  BYTE      cnt_militar;
  BYTE      cnt_prod;
  BYTE      cnt_leer4[31];
  BYTE      cnt_leer3[32];
  BYTE      cnt_siedler[32];
  BYTE      cnt_wachs[32];
  UINT      time_stadt;
  UINT      time_insel;
  UINT      time_werft;
  UINT      time_militar;
  UINT      time_prod;
  UINT      time_werkzeugcnt;
  UINT      time_werkzeugmax;
  UINT      time_game;
  BYTE      spez_noerzoutflg;
  BYTE      spez_tutorflg;
  BYTE      spez_complevel;
  BYTE      spez_missnr;
  UINT      spez_szeneflags;
  UINT      spez_gameid;
  UINT      spez_stadtnamenr;
  UINT      time_nextduerr;
  UINT      time_piratsec;
  UINT      spez_misssubnr;
  UINT      spez_shipmax;
  TISOOBJ   spez_vulkanobj;
  TISOOBJ   spez_vulkanlastobj;
  UINT      time_nextvulkan;
  UINT      spez_vulkancnt;
  UINT      time_leer4[17];
  UINT      time_leer3[32];
  UINT      time_siedler[32];
  UINT      time_wachs[32];
} TTIMERSAVE;

/*========================================+
I  Hirschposition und Daten !!            I
+=========================================*/
typedef struct {
  UINT      inselnr:8;
  UINT      posx:8;
  UINT      posy:8;
  UINT      timecnt;
} THIRSCHSAVE;

/*============================================+
I  Struktur SAVE-Kontorware !!                I
+=============================================*/
typedef struct {
  UINT    vkpreis:10;
  UINT    ekpreis:10;
  UINT    vkflg:1;
  UINT    ekflg:1;
  UINT    lagerres:16;
  UINT    ownlager:16;
  UINT    minlager:16;
  UINT    bedarf:16;
  UINT    lager;
  UINT    hausid:16;
} TKONTWARESAVE;
 
/*============================================+
I  Struktur SAVE-Kontor!!                     I
+=============================================*/
#define MAXKONTWARESAVE   50
typedef struct {
  UINT      inselnr:8;
  UINT      posx:8;
  UINT      posy:8;
  UINT      stadtnr:4;
  TKONTWARESAVE waren[50];        //  ACHTUNG falls WARE_MAX > 50
} TKONTORSAVE;

/*============================================+
I  Struktur SAVE-Marktware !!                 I
+=============================================*/
typedef struct {
  UINT      wareneed;       //  Letzter Verbrauch
  UINT      waregive;       //  Deckungssatz der Bedürfnisse
  UINT      leer1;          //  Reserve ist immer gut !!           
  UWORD     hausid;         //  Hausnummer für Warentyp !!      
  BYTE      wareproz;       //  Versorgungsgrad mit dieser Ware
  BYTE      leer2;          //  Reserve ist immer gut !!
} TMARKTWARESAVE;

/*============================================+
I   Struktur SAVE-Marktplatz !!               I
+=============================================*/
typedef struct {
  UINT            inselnr:8;
  UINT            stadtnr:4;  // Auf welcher Insel und Stadt??
  TMARKTWARESAVE  waren[16];  // ACHTUNG: Falls MARKT_WAREMAX > 16
} TMARKTSAVE;

/*========================================+
I  Structur SAVE-Stadt !!                 I
+=========================================*/
typedef struct {
  BYTE        inselnr;                //  Nummer der Insel
  BYTE        stadtnr;                //  Nummer der Stadt auf Insel
  BYTE        playernr;               //  Spieler der Stadt besitzt
  BYTE        speedcnt;               //  Zeitzähler
  BYTE        baustopflg:1;           //  Siedler brauchen nicht weiter ausbauen
  BYTE        lastmeldnr;             //  Welche Größe wurde zuletzt gemeldet??
  UWORD       stimmung;               //  Wieviele Märkte gibt es in Stadt
  UINT        einkauf;                //  Wieviel Geld wurde für Wareneinkauf ausgegeben??
  UINT        verkauf;                //  Wieviel Geld wurde mit den Warenverkauf gemacht??
  UINT        unglueckanz;            //  Wieviele Ungluecke??
  UINT        marktanz;               //  Wieviele Märkte gibt es in Stadt
  UINT        playercredit[16];       //  Guthaben der Spieler in dieser Stadt!!
  UINT        wohnres;                //  Leute, die in Häuser aufgenommen werden wollen
  UINT        bgruppwohn[7];          //  Leute je Bevölkerungsgruppe
  BYTE        bgruppproz[7];          //  Versorgungsquote
  BYTE        bgruppsteuer[7];        //  Steuerquoten
  BYTE        nahrproz;               //  "
  char        name[32];               //  Name der Stadt
} TSTADTSAVE;

/*========================================+
I  Beschreibung zum Abspeichern eines     I
I  Hauses in der Landschaft !!            I
+=========================================*/
typedef struct {
  UWORD   id;
  BYTE    posx;
  BYTE    posy;
  UINT    ausricht:2;
  UINT    animcnt:4;
  UINT    inselnr:8;
  UINT    stadtnr:3;
  UINT    randnr:5;
  UINT    playernr:4;
} TISOSAVE;

/*============================================+
I  Struktur Waren Abspeichen !!               I
+=============================================*/
typedef struct {
  UWORD     hausid;
  UWORD     menge;
  union     {
  int       kind;
  int       preis;
  int       proz;
  };
} TWARESAVE;

/*========================================+
I  Structur Save-Händler-Ware !!          I
+=========================================*/
typedef struct {
//  THANDWARE;  ??? wzb
  UINT      hausid:16;
} THANDWARESAVE;

/*========================================+
I  Structur Save-Händler !!               I
+=========================================*/
typedef struct {
  UINT      kind:8;
  UINT      objnr:16;
  UINT      handnr:8;
  THANDWARESAVE waren[50];        //  ACHTUNG falls WARE_MAX > 50
} THANDLERSAVE;

/*============================================+
I  Struktur SAVE-Ware in Schiffsroute !!      I
+=============================================*/
typedef struct {
  UWORD   hausid;
  UWORD   menge;
  BYTE    vkflg:1;
  BYTE    leer1[3];
} TROUTWARESAVE;

/*============================================+
I  Struktur SAVE-Route für Schiff !!          I
+=============================================*/
typedef struct {
  TISOOBJ       dstobj;
  TROUTWARESAVE waren[4];   // ACHTUNG: MAXROUTEWARE
} TSHIPROUTSAVE;

/*============================================+
I  Struktur Waren am Schiff - Abspeichern!!   I
+=============================================*/
typedef struct {
  UINT      hausid:16;
  UINT      menge:14;
  UINT      preis:10;
} TSHIPWARESAVE;

/*============================================+
I  Struktur Save - Schiffsdaten !!            I
+=============================================*/
typedef struct {
  char      name[24];     // ACHTUNG: MAXNAMECHAR
  UWORD     endposx;
  UWORD     endposy;
  UWORD     strtposx;
  UWORD     strtposy;
  UWORD     homex;
  UWORD     homey;
  UWORD     compjob;
  UWORD     leer1;
  UINT      leer2;
  TISOOBJ   homeobj;
  TISOOBJ   dstobj;
  TISOOBJ   srcobj;
  TISOOBJ   fightobj;
  UWORD     energy;
  UWORD     userw;
  BYTE      routecnt;
  BYTE      radius;
  BYTE      kanonen;
  BYTE      endladeflg:1;
  BYTE      routeflg:1;
  BYTE      vkflg:1;
  BYTE      routeonceflg:1;
  BYTE      repairflg:1;
  UWORD     vkproz;
  UWORD     objnr;
  UWORD     figurnr;
  BYTE      kind;
  BYTE      playernr;
  BYTE      handlernr;
  BYTE      inselnr;
  BYTE      animnr;
  BYTE      routenr;
  BYTE      ausricht;
  BYTE      verfolgcnt;
  TSHIPROUTSAVE route[8];     // ACHTUNG: MAXSHIPROUTE
  TSHIPWARESAVE waren[8];     // ACHTUNG: MAXSHIPWARE
} TSHIPSAVE;

/*============================================+
I  Struktur Route für Schiff !!               I
+=============================================*/
typedef struct {
  TISOOBJ     dstobj;
} TSOLDATROUTE;

/*============================================+
I  Struktur Save - Soldatendaten !!           I
+=============================================*/
typedef struct {
  UWORD     posx;
  UWORD     posy;
  UWORD     energy;
  UWORD     figurnr;
  UWORD     objnr;
  TISOOBJ   homeobj;
  TISOOBJ   fightobj;
  TISOOBJ   dstobj;
  BYTE      kind;
  BYTE      inselnr;
  BYTE      playernr;
  BYTE      animnr;
  BYTE      radius;
  BYTE      ausricht;
  BYTE      routenr;
  BYTE      routeflg:1;
  BYTE      routeonceflg:1;
  TSOLDATROUTE route[4];  // ACHTUNG: MAXSOLDATROUTE !!
  UINT      leer5;
  UINT      leer6;
  UINT      leer7;
  UINT      leer8;
  UINT      leer9;
} TSOLDATSAVE;

/*============================================+
I  Struktur Save - Soldatendaten !!           I
+=============================================*/
typedef struct {
  UWORD     posx;
  UWORD     posy;
  UWORD     energy;
  UWORD     figurnr;
  BYTE      kind;
  BYTE      inselnr;
  BYTE      playernr;
  BYTE      animnr;
  BYTE      ausricht;
  BYTE      leer[3];
  TISOOBJ   homeobj;
} TSOLDATINSEL;

/*============================================+
I  Struktur Save - Soldatendaten !!           I
+=============================================*/
typedef struct {
  UWORD     strtposx;
  UWORD     strtposy;
  UWORD     energy;
  UWORD     figurnr;
  UWORD     objnr;
  TISOOBJ   homeobj;
  TISOOBJ   fightobj;
  TISOOBJ   dstobj;
  BYTE      kind;
  BYTE      inselnr;
  BYTE      playernr;
  BYTE      animnr;
  BYTE      radius;
  BYTE      ausricht;
  UINT      leer5;
  UINT      leer6;
} TTURMSAVE;

/*========================================+
I  Structur SAVE-Landschaftsteil !!       I
+=========================================*/
typedef struct {
  BYTE      inselnr;
  BYTE      felderx;
  BYTE      feldery;
  BYTE      strtduerrflg:1;
  BYTE      nofixflg:1;
  BYTE      vulkanflg:1;
  UWORD     posx;
  UWORD     posy;
  UWORD     hirschreviercnt;
  UWORD     speedcnt;
  BYTE      stadtplayernr[11];
  BYTE      vulkancnt;
  BYTE      schatzflg;
  BYTE      rohstanz;
  BYTE      eisencnt;
  BYTE      playerflags;
  TERZBERG  eisenberg[4];
  TERZBERG  vulkanberg[4];
  UINT      rohstflags;
  UWORD     filenr;
  UWORD     sizenr;
  BYTE      klimanr;
  BYTE      orginalflg;
  BYTE      duerrproz;
  BYTE      rotier;
  UINT      seeplayerflags;
  UINT      duerrcnt;
  UINT      leer3;
} TINSELSAVE;

/*========================================+
I  Structur SAVE-Landschaftsteil MAXFUN!! I
+=========================================*/
typedef struct {
  BYTE      inselnr;
  BYTE      felderx;
  BYTE      feldery;
  BYTE      strtduerrflg:1;
  BYTE      nofixflg:1;
  BYTE      vulkanflg:1;
  UWORD     posx;
  UWORD     posy;
  UWORD     hirschreviercnt;
  UWORD     speedcnt;
  BYTE      stadtplayernr[11];
//  BYTE      vulkancnt;
//  BYTE      schatzflg;
//  BYTE      rohstanz;
  BYTE      eisencnt;
  BYTE      playerflags;
  BYTE      unknown;
  TERZBERG  eisenberg[2];
  TERZBERG  vulkanberg[2];
  UWORD     unknown1;
  UINT      rohstflags;
  UWORD     filenr;
  UWORD     sizenr;
  BYTE      klimanr;
  BYTE      orginalflg;
  BYTE      duerrproz;
  BYTE      rotier;
  UINT      seeplayerflags;
  UINT      duerrcnt;
//  UINT      leer3;
} TINSEL_MAXFUN_SAVE;

/*========================================+
I  Beschreibung einer Inselvariante       I
+=========================================*/
#define MAXSIZEKIND 5
typedef struct {
  BYTE        klimanr;
  BYTE        sizenr;
  BYTE        nativflg:1;
  BYTE        inselnr;
  UWORD       filenr;
  UWORD       leer1;
  int         posx, posy;
} TINSELHEADSAVE;

/*========================================+
I  Speichern Beschreibung einer Mission!  I
+=========================================*/
typedef struct {
  char        name[64];
  int         nativanz[5];
  int         leer1[3];
  int         rohstmax;
  int         inselanz;
  int         goldminsizenr;
  int         goldmaxsizenr;
  int         leer3;
  TWARESAVE   leer2[4];
  TWARESAVE   erze[4];
  TWARESAVE   rohst[12];
  TWARESAVE   goodies[4];
  TWARESAVE   handware[8];
  TINSELHEADSAVE insel[50];
} TSZENESAVE;

/*============================================+
I  Struktur Soldat im Militärgebäude !!       I
+=============================================*/
typedef struct {
  UINT      figurnr:12;     // Welche Figur befindet sich in der Kaserne?? (FIGUR_MAX <= 256!!)
  UINT      trainflg:1;     // Wird gerade eine Einheit ausgebildet
  UINT      waffflg:1;      // Waffe ist für diese Figur bereits vorhanden
  UINT      leer1:18;       // Reserve ist immer gut
  UINT      energy:16;      // Aktueller Energypegel
  UINT      expert:16;      // Erreichter Ausbildungsstand
} TMILOBJSAVE;

/*============================================+
I  Struktur Militär-Gebäude !!                I
+=============================================*/
typedef struct {
  UINT        inselnr:8;          //
  UINT        posx:8;             // Standort des Militärischen Gebäudes
  UINT        posy:8;             //
  UINT        speedcnt:8;         // Wenn (Zeitzähler == Speedzähler) timer++ (MAXROHWACHSCNT)
  UINT        timer:16;           // Zeit bis zur nächsten Produktionsrunde
  UWORD       wafflager[4];       // Aktueller Waffenbestand in der Kaserne
  TMILOBJSAVE objlist[12];        // Objekte in der Kaserne !!
} TMILITARSAVE;

/*============================================+
I  Struktur SAVE-Siedler !!                   I
+=============================================*/
typedef struct {
  UINT      inselnr:8;    //
  UINT      posx:8;       // Standort des Wohnhauses.
  UINT      posy:8;       //
  UINT      speedcnt:8;   // Wenn (Zeitzähler == Speedzähler) timer++ (MAXROHWACHSCNT)
  UINT      stadtcnt:8;   // Merker ob Vermehrung neu gerechnet wurde
  UINT      bgruppnr:8;   // Welche Bevölkerungsgruppe??
  UINT      marktdist:8;  // Entfernung zum Marktplatz (MAXMARKTDIST)
  UINT      anz:16;       // Anzahl hat einen Kommastellenbereich
  UINT      speed:4;      // Welcher Zeitzähler gilt ??
  UINT      leer1:1;      // Wird zur Bevölkerungsgruppenr. hinzugezählt
  UINT      infraflg:1;   // Nötigen Infrastruktureinrichtungen vorhanden?
  UINT      marktflg:1;   // im Umkreis eines Marktes ??
  UINT      kirchflg:1;   // im Umkreis einer Kirche ??
  UINT      wirtflg:1;    // im Umkreis eines Wirtshauses ??
  UINT      badeflg:1;    // im Umkreis eines Badehauses ??
  UINT      theatflg:1;   // im Umkreis eines Theaters ??
  UINT      hqflg:1;      // im Umkreis des Hauptquartiers ??
  UINT      schulflg:1;   // im Umkreis einer Schule ??
  UINT      hschulflg:1;  // Im Umkreis einer Hochschule ??
  UINT      kapellflg:1;  // Im Umkreis einer Kapelle ??
  UINT      klinikflg:1;    // im Umkreis eines Arztes ??
  UINT      leer5:1;      // Reserve ist immer gut
  UINT      leer6:1;      // Reserve ist immer gut
  UINT      leer7:8;      // Reserve ist immer gut
  UINT      leer8:8;      // Reserve ist immer gut
  UINT      leer9:8;      // Reserve ist immer gut
} TSIEDLERSAVE;

/*============================================+
I   Struktur Save-Prod.-Listen-Eintrag!!      I
+=============================================*/
typedef struct {
  BYTE      inselnr;      //  
  BYTE      posx;         //  Wo befindet sich Stätte
  BYTE      posy;         //  
  BYTE      speed;        //  Welcher Speedzähler (MAXWACHSSPEEDKIND)
  UINT      speedcnt:8;   //  Wenn (Zeitzähler == Speedzähler) timer++ (MAXROHWACHSCNT)
  UINT      lager:24;     //  Lagerbestand an Fertigprodukten
  UWORD     timer;        //  Zeitzähler in Sekunden
  UWORD     worklager;    //  Bestand an Betriebsstoffen (vorwiegend Holz)
  UINT      rohlager:24;  //  Lagerbestand an Rohstoffen
  UINT      rohhebe:8;    //  Was wird derzeit produziert??
  UWORD     prodcnt;      //  Wie oft wurde produziert ??
  UWORD     timecnt;      //  Zähler für Produktionsstatistik!!
  BYTE      aktivflg:1;   //  Produktionsstätte derzeit aktiv??
  BYTE      marktflg:1;   //  Eine Verbindung mit dem Hauptquartier besteht!!
  BYTE      animcnt:4;    //  Aktuelle Animationsstufe (ACHTUNG: TISOFELD!!)
  BYTE      nomarktflg:1; //  Marktfahrer dürfen hier keine Waren abholen
  BYTE      leer3:1;      //  Reserve ist immer gut
  BYTE      norohstcnt:4; //  Seit längerer Zeit kein Rohstoff erreichbar
  BYTE      leer1;        //  Reserve ist immer gut
  BYTE      leer2;        //  Reserve ist immer gut
} TPRODLISTSAVE;
 
/*============================================+
I   Struktur Save - Werft !!                  I
+=============================================*/
typedef struct {
  UINT      inselnr:8;    //  
  UINT      posx:8;       //  Wo befindet sich Stätte
  UINT      posy:8;       //  
  UINT      speedcnt:3;   //  Wenn (Zeitzähler == Speedzähler) timer++ (MAXROHWACHSCNT)
  UINT      aktivflg:1;   //  Wird gerade an einem Schiff gebaut??
  UINT      timer:16;     //  Zeitzähler in Sekunden
  UINT      bauship:8;    //  Welcher Schiffstyp wird produziert
  UINT      lager:16;     //  Wieviel Schiffsbauteile sind schon vorhanden 
  UINT      rohlager:16;  //  Lagerbestand an Rohstoffen
  UINT      repshipnr:16; //  Nummer des Schiffes das repariert wird
  UINT      worklager:16; //  Reserve ist immer gut
  UINT      leer3:8;      //  Reserve ist immer gut
  UINT      leer4:8;      //  Reserve ist immer gut
  UINT      leer5;        //  Reserve ist immer gut
} TWERFTSAVE;

/*============================================+
I   Struktur Save - Rohstoff-Wachstum!!       I
+=============================================*/
typedef struct {
  UINT      inselnr:8;    //
  UINT      posx:8;       //  Wo befindet sich Stätte
  UINT      posy:8;       //
  UINT      speed:8;      //  Welcher Speedzähler (MAXWACHSSPEEDKIND)
  UINT      speedcnt:8;   //  Wenn (Zeitzähler != Speedzähler) aktfeld->animcnt++ (MAXROHWACHSCNT)
  UINT      animcnt:8;    //  Aktuelle Wachstumsstufe !!
} TROHWACHSSAVE;


#endif
