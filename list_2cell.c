//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Umeå University.
//Usage exept those listed above requires permission by the author.

#include <stdlib.h>
#include <stdio.h>
#include "list_2cell.h"

/*

Datatypen Lista enligt definitionen på sidan 44 i Lars-Erik Janlert,
Torbjörn Wiberg Datatyper och algoritmer 2., [rev.] uppl.,Lund,
Studentlitteratur, 2000, x, 387 s. ISBN 91-44-01364-7

Denna implementation använder sig av en 2-Cell.

Som standard så är användaren av datatypen ansvarig för att avallokera
minnet för datavärdena. Genom att anropa list_setMemHandler och till denna
skicka med en funktion för att avallokera ett dataobjekt så kommer listan
ta över ansvaret för minneshanteringen och automatiskt avallokera värdena
då de tas bort från listan. OBS i detta fall så måste användaren kopiera
värdena om de ska finnas kvar efter att ha ta gits bort från listan.
*/

/*
Syfte: Skapa en ny lista
Returvärde: Den nyskapade listan (list*)
Kommentarer: Då man använt listan färdigt så måste minnet för listan
             avallokeras via funktionen dlist_free
*/
list *list_empty(void){
    list *l=malloc(sizeof(list)) ;
    l->top=malloc(sizeof(two_cell));
    l->bottom=malloc(sizeof(two_cell));
    l->top->next=NULL;  //Oanvända pekare
    l->bottom->next=NULL; //Oanvänd pekare
    l->bottom->value=l->top->value=NULL;  //value i top och bottom är tomma
    l->top->next=l->bottom;
    l->bottom->previous=l->top;
    l->freeFunc=NULL;
    return l;
}

/*
Syfte: Installera en minneshanterare för listan så att den kan ta över
       ansvaret för att avallokera minnet för värdena då de ej finns kvar
       i listan mer.
Parametrar: l - listan
            f - en funktionspekare till en funktion som tar in ett värde
                av typen data (void pekare) och avallokerar minnet för värdet
                den pekar på (ett av den typ av värden som lagras i listan).
Kommentarer: Bara minne för värden som finns i listan vid tidpunkten då en
             minneshanterare satts eller senare kommer tas bort.
             Listan funkar även utan att denna funktion anropas,
             men det är då upp till användaren av datatypen att avallokera allt
             minne för datat som lagras i listan.
*/
void list_setMemHandler(list *l, memFreeFunc *f) {
   l->freeFunc=f;
}

/*
Syfte: Sätter in ett värde på en viss position i listan.
Parametrar: l (list *) listan som vi ska sätta in i
            dp (data) värdet som ska sättas in
            p (list_position) positionen på vilken insättningen ska göras
Returvärde: Positionen fär det nyinstoppade värdet
Kommentarer:
*/
list_position list_insert(list *l,data dp, list_position p){
    list_position newlink=malloc(sizeof(two_cell));
    newlink->value=dp;
    newlink->next=p;
    newlink->previous=p->previous;
    p->previous=newlink;
    newlink->previous->next=newlink;
    return newlink;  
}

/*
Syfte: Kontrollera om listan är tom
Parametrar: l (list *) listan som ska kontrolleras.
Returvärde: true om listan är tom annars false
Kommentarer:
*/
bool list_isEmpty(list *l){
    return (l->top->next==l->bottom);
}

/*
Syfte: Hämta ett värde på en given plats i listan.
Parametrar: l (list *) listan som värdet ska hämtas från
            p (list_position) positionen för värdet
Returvärde: The value at the given position (data)
Kommentarer: funktionen odefinierad för positioner utanför intervalet
             list_first <= pos < list_end
*/
data list_inspect(list *l,list_position pos){
    return pos->value;
}

/*
Syfte: Ta fram den första positionen i listan
Parametrar: l (list *) listan
Returvärde: den första positionen i listan
Kommentarer:
*/
list_position list_first(list *l){
    return l->top->next;
}

/*
Syfte: Ta fram positionen efter det sista värdet i listan
Parametrar: l (list *) listan
Returvärde: Positionen efter det sista värdet i listan
Kommentarer: OBS inspect på denna position är odefinierad
*/
list_position list_end(list *l){
    return l->bottom;
}

/*
Syfte: Ta fram positionen efter den givna i listan
Parametrar: l (list *) listan
            p (list_position) positionen vars efterföljare man vill ta fram
Returvärde: Den efterföljande positionen 
Kommentarer: Odefinierad för end
*/
list_position list_next(list *l,list_position p){
    return p->next;
}

/*
Syfte: Ta fram positionen innan den givna i listan
Parametrar: l (list *) listan
            p (list_position) positionen vars föregångare man vill ta fram
Returvärde: Positionen innan den givna
Kommentarer: Odefinierad för first
*/
list_position list_previous(list *l,list_position p){
    return p->previous;
}

/*
Syfte: Tar bort ett värde ur listan
Parametrar: l (list *) listan.
            p (list_position) positionen för värdet som ska tas bort.
Returvärde: positionen som svarar mot den där värdet togs bort efter borttagandet
Kommentarer: Om en funktion för att avallokera minnet för datavärdena
             via list_setMemFunc så kommer minnet för datat att avallokeras,
             annars är detta användarens ansvar.
             p:s värde är odefinierat efter anropet.
*/
list_position list_remove(list *l,list_position p){
    list_position retur=p->next;
    p->previous->next=p->next;
    p->next->previous=p->previous;
    if(l->freeFunc!=NULL)
        l->freeFunc(p->value);
    free(p);
    return retur;
}

/*
Syfte: Avallokera minne som används av listan.
Parametrar: listan (list *)
Kommentarer: Minne för ev värden i listan avallokeras bara om en funktion
             för detta är satt via list_setMemFunc
*/
void list_free(list *l){
    list_position temppos=list_first(l);

    while(!list_isEmpty(l)){
        temppos=list_remove(l,temppos);
    }
    free(l->top);
    free(l->bottom);
    free(l);
    return;
}

