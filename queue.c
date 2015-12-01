//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Ume� University.
//Usage exept those listed above requires permission by the author.

#include "queue.h"

/*
K� implementerad med hj�lp av riktad lista. Kr�ver implementation av lista som �verenst�mmer med gr�nssninttet f�r listan som anv�nds p� kursen f�r att fungera.
*/

/*
Syfte: Skapa en ny k�
Returv�rde: Den nyskapade k� (queue *)
Kommentarer: D� man anv�nt k�n f�rdigt s� m�ste minnet f�r k�n
             avallokeras via funktionen queue_free
*/
queue *queue_empty(void) {
    return list_empty();
}

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
void queue_setMemHandler(queue *q, memFreeFunc *f) {
    list_setMemHandler(q,f);
}

/*
Syfte: Ta bort f�rsta v�rdet i k�n
Parametrar: q - K�n (queue *)
Kommentarer: odefinierad f�r en tom k�
*/
void queue_dequeue(queue *q) {
    list_remove(q,list_first(q));
}

/*
Syfte: H�mtar f�rsta v�rdet i k�n
Parametrar: q - K�n (queue *)
Returv�rde: v�rdet som fanns l�ngst fram i k�n
Kommentarer: ej definierad f�r tom k�.
*/
data queue_front(queue *q) {
    return list_inspect(q,list_first(q));
}

/*
Syfte: L�gga till ett v�rde sist i k�n
Parametrar: q - K�n (queue *)
            p - v�rdet som ska l�ggas till (data)
Kommentarer:
*/
void queue_enqueue(queue *q,data d) {
    if(queue_isEmpty(q)) {
        list_insert(q, d, list_end(q));
    }
}

/*
Syfte: Konrollera om k�n �r tom
Parametrar: q - K�n (queue *)
Returv�rde: true om k�n �r tom false annars
Kommentarer:
*/
bool queue_isEmpty(queue *q) {
    return list_isEmpty(q);
}

/*
Syfte: Avallokera minne f�r k�n.
Parametrar: q - K�n (queue *)
Kommentarer: Minne f�r ev v�rden i k�n avallokeras bara om en funktion
             f�r detta �r satt via queue_setMemFunc. Annars �r det anv�ndarens
             uppgift att avallokera minnet f�r alla v�rden i k�n.
*/
void queue_free(queue *q) {
    //list_free(q);
}
