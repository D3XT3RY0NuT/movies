#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"
#include "utilitare.h"
#define NR_MAX_ACTORI_FILM 300 //Numarul maxim de actori dintr-un film

//Determinarea distributiilor (componentelor conexe) din graf
//Se foloseste algoritmul de parcurgere in adancime
//Returneaza numarul de noduri din componenta conexa respectiva
int BFS_distributie(Graf graf, NodGraf *nod_graf, int distributie){
    Coada coada;
    initializare_coada(&coada);
    inserare_coada(&coada, nod_graf);
    ElementCoada *varf; //Elementul din graf situat la varful cozii
    NodLista *vecin; //Numele vecinului nodului din varful cozii
    NodGraf *nod_vecin; //Nodul din graf corespunzator vecinului
    int nr_noduri = 0; //Numarul de noduri din componenta conexa
    nod_graf->distributie = distributie;
    while(!este_coada_vida(coada)){
        varf = extragere_coada(&coada);
        nr_noduri++;
        vecin = varf->nod->lista_adiacenta;
        while(vecin){
            nod_vecin = cautare_actor(graf, vecin->nume);
            if (!nod_vecin->distributie){
                nod_vecin->distributie = distributie;
                inserare_coada(&coada, nod_vecin);
            }
            vecin = vecin->urm;
        }
    }

    return nr_noduri;
}

int comparare_nume(const void *a, const void *b){
    char *pa = (char *) a;
    char *pb = (char *) b;

    return strcmp(pa, pb);
}

//Rezolvarea primei cerinte
void rezolvare_cerinta1(char *fisier_intrare, char *fisier_iesire){
    //Citirea datelor de intrare
    FILE *f_in = fopen(fisier_intrare, "r");
    if (!f_in){
        printf("Fisierul de intrare nu a putut fi deschis.\n");
        exit(1);
    }
    int nr_filme, nr_actori;
    char nume_film[L_MAX], actori[NR_MAX_ACTORI_FILM][L_MAX];
    Graf graf;
    //nod_actori[j] retine nodul pe care se afla actorul cu numele actori[j]
    NodGraf *nod_actori[NR_MAX_ACTORI_FILM];
    initializare_graf(&graf);
    fscanf(f_in, "%d", &nr_filme);
    for (int i = 0; i < nr_filme; i++){
        fgetc(f_in); //Curata caracterul '\n' rezidual ramas de la citirea numarului de film
        fgets(nume_film, L_MAX, f_in);
        fscanf(f_in, "%d", &nr_actori);
        if (nr_actori > NR_MAX_ACTORI_FILM){
            printf("Filmul contine prea multi actori.\n");
            exit(1);
        }
        fgetc(f_in); //Curata caracterul '\n' rezidual ramas de la citirea numarului de actori
        for (int j = 0; j < nr_actori; j++){
            fgets(actori[j], L_MAX, f_in);
            nod_actori[j] = inserare_graf(&graf, actori[j]);
        }
        for (int j = 0; j < nr_actori; j++){
            for (int k = j + 1; k < nr_actori; k++){
                adaugare_lista_adiacenta(nod_actori[j], actori[k]);
                adaugare_lista_adiacenta(nod_actori[k], actori[j]);
            }
        }
    }
    fclose(f_in);

    //Aplicarea algoritmului de cautare in adancime pentru determinarea distributiilor
    //Daca distributia are un numar de actori mai mare decat maximul determinat anterior
    //Indicele acesteia va fi retinut
    int distributie = 1; //Indicii pentru distributii
    int distributie_maxim; //Indicele distributiei cu numarul maxim de actori
    int maxim = 0; //Numarul de actori al distributiei maximale
    int nr;
    NodTabel *aux;
    for (int i = 0; i < NR_ACTORI_MAX; i++){
        aux = graf.actori[i];
        while(aux){
            if (!aux->nod->distributie){
                nr = BFS_distributie(graf, aux->nod, distributie);
                if (nr > maxim){
                    distributie_maxim = distributie;
                    maxim = nr;
                }
                distributie++;
            }
            aux = aux->urm;
        }
    }

    //Aflarea actorilor din distributia maximala
    char actori_distributie_maximala[NR_ACTORI_MAX][L_MAX];
    nr = 0;
    for (int i = 0; i < NR_ACTORI_MAX; i++){
        aux = graf.actori[i];
        while(aux){
            if (aux->nod->distributie == distributie_maxim)
                strcpy(actori_distributie_maximala[nr++], aux->nod->nume);
            aux = aux->urm;
        }
    }
    //Sortarea actorilor din distributia maximala
    qsort(actori_distributie_maximala, nr, L_MAX * sizeof(char), comparare_nume);

    //Afisarea rezultatelor
    FILE *f_out = fopen(fisier_iesire, "w");
    if (!f_out){
        printf("Fisierul de iesire nu a putut fi creat.\n");
        exit(1);
    }
    fprintf(f_out, "%d\n", maxim);
    for (int i = 0; i < nr; i++)
        fprintf(f_out, "%s", actori_distributie_maximala[i]);
    fclose(f_out);
}
