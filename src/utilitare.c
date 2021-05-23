#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"

//Creeaza un nod de graf si il returneaza
NodGraf *creare_nod_graf(char *nume_actor){
    NodGraf *aux = (NodGraf *) malloc(sizeof(NodGraf));
    strcpy(aux->nume, nume_actor);
    aux->lista_adiacenta = NULL;
    aux->distributie = 0;

    return aux;
}

//Sterge un nod de graf, eliberand memoria ocupata de acesta
//Si a listei sale de adiacenta
void stergere_nod_graf(NodGraf *nod){
    NodLista *aux1, *aux2;
    aux1 = nod->lista_adiacenta;
    while(aux1){
        aux2 = aux1;
        aux1 = aux1->urm;
        free(aux2);
    }
    free(nod);
}

//Creeaza un nod de lista si il returneaza
NodLista *creare_nod_lista(char *nume_actor){
    NodLista *aux = (NodLista *) malloc(sizeof(NodLista));
    strcpy(aux->nume, nume_actor);
    aux->urm = NULL;

    return aux;
}

//Adauga un element in lista de adiacenta daca acesta nu exista deja
void adaugare_lista_adiacenta(NodGraf *nod_graf, char *nume_actor){
    NodLista *aux = nod_graf->lista_adiacenta;
    while(aux && strcmp(aux->nume, nume_actor))
        aux = aux->urm;
    if (!aux){
        aux = creare_nod_lista(nume_actor);
        aux->urm = nod_graf->lista_adiacenta;
        nod_graf->lista_adiacenta = aux;
    }
}

//Initializeaza un graf vid
void initializare_graf(Graf *graf){
    for (int i = 0; i < NR_ACTORI_MAX; i++)
        graf->actori[i] = NULL;
}

//Sterge graful eliberand memoria ocupata de acesta
void stergere_graf(Graf *graf){
    NodTabel *aux1, *aux2;
    for (int i = 0; i < NR_ACTORI_MAX; i++){
        aux1 = graf->actori[i];
        while(aux1){
            stergere_nod_graf(aux1->nod);
            aux2 = aux1;
            aux1 = aux1->urm;
            free(aux2);
        }
    }
}

//Genereaza cheia pentru tabela de dispersie corespunzatoare numelui dat ca argument
int generare_cheie(char *nume_actor){
    int l = strlen(nume_actor);
    int rez = 0;
    for (int i = 0; i < l; i++)
        rez += nume_actor[i] * (i + 1);

    return rez % NR_ACTORI_MAX;
}

//Returneaza nodul corespunzatorul numelui actorului din tabela de dispersie
NodGraf *cautare_actor(Graf graf, char *nume_actor){
    int cheie = generare_cheie(nume_actor);
    NodTabel *aux = graf.actori[cheie];
    while(aux && strcmp(aux->nod->nume, nume_actor))
        aux = aux->urm;

    if (aux)
        return aux->nod;
    return NULL;
}

//Daca actorul nu exista deja in graf, acesta va fi adaugat
//Este returnat pointerul catre nodul corespunzator actorului
NodGraf *inserare_graf(Graf *graf, char *nume_actor){
    int cheie = generare_cheie(nume_actor);
    NodGraf *nod_graf = cautare_actor(*graf, nume_actor);
    if (!nod_graf){
        nod_graf = creare_nod_graf(nume_actor);
        NodTabel *aux = (NodTabel *) malloc(sizeof(NodTabel));
        aux->nod = nod_graf;
        aux->urm = graf->actori[cheie];
        graf->actori[cheie] = aux;
    }

    return nod_graf;
}

//Initializeaza o coada vida
void initializare_coada(Coada *coada){
    coada->inceput = coada->sfarsit = NULL;
}

//Insereaza un nou element in coada
void inserare_coada(Coada *coada, NodGraf *nod_graf){
    ElementCoada *aux = (ElementCoada *) malloc(sizeof(ElementCoada));
    aux->nod = nod_graf;
    aux->prec = NULL;
    aux->urm = coada->sfarsit;
    if (coada->sfarsit)
        coada->sfarsit->prec = aux;
    else
        coada->inceput = aux;
    coada->sfarsit = aux;
}

//Returneaza 0 daca coada este vida
//Returneaza o valoare nenula daca coada este nevida
int este_coada_vida(Coada coada){
    return coada.inceput == NULL;
}

//Extrage elementul de la inceputul cozii, daca acesta exista
ElementCoada *extragere_coada(Coada *coada){
    ElementCoada *aux = coada->inceput;
    if (coada->inceput){
        if (coada->sfarsit == coada->inceput)
            coada->sfarsit = coada->inceput->prec;
        coada->inceput = coada->inceput->prec;
    }

    return aux;
}

//Functia de comparare a doua siruri de caractere folosita de qsort
int comparare_nume(const void *a, const void *b){
    char *pa = (char *) a;
    char *pb = (char *) b;

    return strcmp(pa, pb);
}
