//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Ume� University.
//Usage exept those listed above requires permission by the author.

#include "list_2cell.h"

/*
Datatypen K� enligt definitionen p� sidan 155 i Lars-Erik Janlert,
Torbj�rn Wiberg Datatyper och algoritmer 2., [rev.] uppl.,Lund,
Studentlitteratur, 2000, x, 387 s. ISBN 91-44-01364-7

Implementerar k� med hj�lp av en datatypen lista 

Som standard s� �r anv�ndaren av datatypen ansvarig f�r att avallokera
minnet f�r datav�rdena. Genom att anropa queue_setMemHandler och till denna
skicka med en funktion f�r att avallokera ett dataobjekt s� kommer k�n
ta �ver ansvaret f�r minneshanteringen och automatiskt avallokera v�rdena
d� de tas bort fr�n k�n. OBS i detta fall s� m�ste anv�ndaren kopiera
v�rdena om de ska finnas kvar efter att ha tagits bort fr�n k�n.
*/

#ifndef __QUEUE_H
#define __QUEUE_H

typedef list queue;

/*
Syfte: Skapa en ny k�
Returv�rde: Den nyskapade k� (queue *)
Kommentarer: D� man anv�nt k�n f�rdigt s� m�ste minnet f�r k�n
             avallokeras via funktionen queue_free
*/
queue *queue_empty(void);

/*
Syfte: Installera en minneshanterare f�r k�n s� att den kan ta �ver
       ansvaret f�r att avallokera minnet f�r v�rdena d� de ej finns kvar
       i k�n mer.
Parametrar: q - K�n (queue *)
            f - en funktionspekare till en funktion som tar in ett v�rde
                av typen data (void pekare) och avallokerar minnet f�r v�rdet
                den pekar p� (ett av den typ av v�rden som lagras i k�n).
Kommentarer: B�r anropas direkt efter att k�n skapats om funktionaliteten
             ska anv�ndas. K�n funkar �ven utan att denna funktion anropas,
             men det �r d� upp till anv�ndaren av datatypen att avallokera allt
             minne f�r datat som lagras i k�n.
*/
void queue_setMemHandler(queue *q, memFreeFunc *f);

/*
Syfte: Ta bort f�rsta v�rdet i k�n
Parametrar: q - K�n (queue *)
Kommentarer: odefinierad f�r en tom k�
*/
void queue_dequeue(queue *q);

/*
Syfte: H�mtar f�rsta v�rdet i k�n
Parametrar: q - K�n (queue *)
Returv�rde: v�rdet som fanns l�ngst ram i k�n
Kommentarer: ej definierad f�r tom k�.
*/
data queue_front(queue *q);

/*
Syfte: L�gga till ett v�rde sist i k�n
Parametrar: q - K�n (queue *)
            p - v�rdet som ska l�ggas till (data)
Kommentarer:
*/
void queue_enqueue(queue *q,data d);

/*
Syfte: Konrollera om k�n �r tom
Parametrar: q - K�n (queue *)
Returv�rde: true om k�n �r tom false annars
Kommentarer:
*/
bool queue_isEmpty(queue *q);

/*
Syfte: Avallokera minne f�r k�n.
Parametrar: q - K�n (queue *)
Kommentarer: Minne f�r ev v�rden i k�n avallokeras bara om en funktion
             f�r detta �r satt via queue_setMemFunc. Annars �r det anv�ndarens
             uppgift att avallokera minnet f�r alla v�rden i k�n.
*/
void queue_free(queue *q);

#endif
