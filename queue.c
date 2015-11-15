//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Umeå University.
//Usage exept those listed above requires permission by the author.

#include "queue.h"

/*
Kö implementerad med hjälp av riktad lista. Kräver implementation av lista som överenstämmer med gränssninttet för listan som används på kursen för att fungera.
*/

/*
Syfte: Skapa en ny kö
Returvärde: Den nyskapade kö (queue *)
Kommentarer: Då man använt kön färdigt så måste minnet för kön
             avallokeras via funktionen queue_free
*/
queue *queue_empty(void) {
    return list_empty();
}

/*
Syfte: Installera en minneshanterare för kön så att den kan ta över
       ansvaret för att avallokera minnet för värdena då de ej finns kvar
       i kön mer.
Parametrar: q - Kön (queue *)
            f - en funktionspekare till en funktion som tar in ett värde
                av typen data (void pekare) och avallokerar minnet för värdet
                den pekar på (ett av den typ av värden som lagras i kön).
Kommentarer: Bör anropas direkt efter att kön skapats om funktionaliteten
             ska användas. Kön funkar även utan att denna funktion anropas,
             men det är då upp till användaren av datatypen att avallokera allt
             minne för datat som lagras i kön.
*/
void queue_setMemHandler(queue *q, memFreeFunc *f) {
    list_setMemHandler(q,f);
}

/*
Syfte: Ta bort första värdet i kön
Parametrar: q - Kön (queue *)
Kommentarer: odefinierad för en tom kö
*/
void queue_dequeue(queue *q) {
    list_remove(q,list_first(q));
}

/*
Syfte: Hämtar första värdet i kön
Parametrar: q - Kön (queue *)
Returvärde: värdet som fanns längst fram i kön
Kommentarer: ej definierad för tom kö.
*/
data queue_front(queue *q) {
    return list_inspect(q,list_first(q));
}

/*
Syfte: Lägga till ett värde sist i kön
Parametrar: q - Kön (queue *)
            p - värdet som ska läggas till (data)
Kommentarer:
*/
void queue_enqueue(queue *q,data d) {
    list_insert(q,d,list_end(q));
}

/*
Syfte: Konrollera om kön är tom
Parametrar: q - Kön (queue *)
Returvärde: true om kön är tom false annars
Kommentarer:
*/
bool queue_isEmpty(queue *q) {
    return list_isEmpty(q);
}

/*
Syfte: Avallokera minne för kön.
Parametrar: q - Kön (queue *)
Kommentarer: Minne för ev värden i kön avallokeras bara om en funktion
             för detta är satt via queue_setMemFunc. Annars är det användarens
             uppgift att avallokera minnet för alla värden i kön.
*/
void queue_free(queue *q) {
    list_free(q);
}
