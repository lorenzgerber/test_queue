//Written by Johan Eliasson <johane@cs.umu.se>.
//May be used in the course Datastrukturer och Algoritmer (C) at Ume� University.
//Usage exept those listed above requires permission by the author.

#include <stdlib.h>
#include <stdio.h>
#include "list_2cell.h"

/*

Datatypen Lista enligt definitionen p� sidan 44 i Lars-Erik Janlert,
Torbj�rn Wiberg Datatyper och algoritmer 2., [rev.] uppl.,Lund,
Studentlitteratur, 2000, x, 387 s. ISBN 91-44-01364-7

Denna implementation anv�nder sig av en 2-Cell.

Som standard s� �r anv�ndaren av datatypen ansvarig f�r att avallokera
minnet f�r datav�rdena. Genom att anropa list_setMemHandler och till denna
skicka med en funktion f�r att avallokera ett dataobjekt s� kommer listan
ta �ver ansvaret f�r minneshanteringen och automatiskt avallokera v�rdena
d� de tas bort fr�n listan. OBS i detta fall s� m�ste anv�ndaren kopiera
v�rdena om de ska finnas kvar efter att ha ta gits bort fr�n listan.
*/

/*
Syfte: Skapa en ny lista
Returv�rde: Den nyskapade listan (list*)
Kommentarer: D� man anv�nt listan f�rdigt s� m�ste minnet f�r listan
             avallokeras via funktionen dlist_free
*/
list *list_empty(void){
    list *l=malloc(sizeof(list)) ;
    l->top=malloc(sizeof(two_cell));
    l->bottom=malloc(sizeof(two_cell));
    l->top->next=NULL;  //Oanv�nda pekare
    l->bottom->next=NULL; //Oanv�nd pekare
    l->bottom->value=l->top->value=NULL;  //value i top och bottom �r tomma
    l->top->next=l->bottom;
    l->bottom->previous=l->top;
    l->freeFunc=NULL;
    return l;
}

/*
Syfte: Installera en minneshanterare f�r listan s� att den kan ta �ver
       ansvaret f�r att avallokera minnet f�r v�rdena d� de ej finns kvar
       i listan mer.
Parametrar: l - listan
            f - en funktionspekare till en funktion som tar in ett v�rde
                av typen data (void pekare) och avallokerar minnet f�r v�rdet
                den pekar p� (ett av den typ av v�rden som lagras i listan).
Kommentarer: Bara minne f�r v�rden som finns i listan vid tidpunkten d� en
             minneshanterare satts eller senare kommer tas bort.
             Listan funkar �ven utan att denna funktion anropas,
             men det �r d� upp till anv�ndaren av datatypen att avallokera allt
             minne f�r datat som lagras i listan.
*/
void list_setMemHandler(list *l, memFreeFunc *f) {
   l->freeFunc=f;
}

/*
Syfte: S�tter in ett v�rde p� en viss position i listan.
Parametrar: l (list *) listan som vi ska s�tta in i
            dp (data) v�rdet som ska s�ttas in
            p (list_position) positionen p� vilken ins�ttningen ska g�ras
Returv�rde: Positionen f�r det nyinstoppade v�rdet
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
Syfte: Kontrollera om listan �r tom
Parametrar: l (list *) listan som ska kontrolleras.
Returv�rde: true om listan �r tom annars false
Kommentarer:
*/
bool list_isEmpty(list *l){
    return (l->top->next==l->bottom);
}

/*
Syfte: H�mta ett v�rde p� en given plats i listan.
Parametrar: l (list *) listan som v�rdet ska h�mtas fr�n
            p (list_position) positionen f�r v�rdet
Returv�rde: The value at the given position (data)
Kommentarer: funktionen odefinierad f�r positioner utanf�r intervalet
             list_first <= pos < list_end
*/
data list_inspect(list *l,list_position pos){
    return pos->value;
}

/*
Syfte: Ta fram den f�rsta positionen i listan
Parametrar: l (list *) listan
Returv�rde: den f�rsta positionen i listan
Kommentarer:
*/
list_position list_first(list *l){
    return l->top->next;
}

/*
Syfte: Ta fram positionen efter det sista v�rdet i listan
Parametrar: l (list *) listan
Returv�rde: Positionen efter det sista v�rdet i listan
Kommentarer: OBS inspect p� denna position �r odefinierad
*/
list_position list_end(list *l){
    return l->bottom;
}

/*
Syfte: Ta fram positionen efter den givna i listan
Parametrar: l (list *) listan
            p (list_position) positionen vars efterf�ljare man vill ta fram
Returv�rde: Den efterf�ljande positionen 
Kommentarer: Odefinierad f�r end
*/
list_position list_next(list *l,list_position p){
    return p->next;
}

/*
Syfte: Ta fram positionen innan den givna i listan
Parametrar: l (list *) listan
            p (list_position) positionen vars f�reg�ngare man vill ta fram
Returv�rde: Positionen innan den givna
Kommentarer: Odefinierad f�r first
*/
list_position list_previous(list *l,list_position p){
    return p->previous;
}

/*
Syfte: Tar bort ett v�rde ur listan
Parametrar: l (list *) listan.
            p (list_position) positionen f�r v�rdet som ska tas bort.
Returv�rde: positionen som svarar mot den d�r v�rdet togs bort efter borttagandet
Kommentarer: Om en funktion f�r att avallokera minnet f�r datav�rdena
             via list_setMemFunc s� kommer minnet f�r datat att avallokeras,
             annars �r detta anv�ndarens ansvar.
             p:s v�rde �r odefinierat efter anropet.
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
Syfte: Avallokera minne som anv�nds av listan.
Parametrar: listan (list *)
Kommentarer: Minne f�r ev v�rden i listan avallokeras bara om en funktion
             f�r detta �r satt via list_setMemFunc
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

