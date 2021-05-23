#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structuri.h"
#include "utilitare.h"
#define NR_MAX_ACTORI_FILM 300 //Numarul maxim de actori dintr-un film

//Determinarea distributiilor (componentelor conexe) din graf
//Se foloseste algoritmul de parcurgere in latime
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
        free(varf);
    }

    return nr_noduri;
}

//Determinarea distantelor de la nodul de graf dat ca argument
//La toate celelalte noduri la care se poate ajunge
//Se foloseste parcurgerea in latime
//Variabila distributie din nodul de graf are sensul de distanta in acest context
void BFS_distanta(Graf graf, NodGraf *nod_graf){
    Coada coada;
    initializare_coada(&coada);
    inserare_coada(&coada, nod_graf);
    ElementCoada *varf; //Elementul din graf situat la varful cozii
    NodLista *vecin; //Numele vecinului nodului din varful cozii
    NodGraf *nod_vecin; //Nodul din graf corespunzator vecinului
    nod_graf->distributie = 1;
    while(!este_coada_vida(coada)){
        varf = extragere_coada(&coada);
        vecin = varf->nod->lista_adiacenta;
        while(vecin){
            nod_vecin = cautare_actor(graf, vecin->nume);
            if (!nod_vecin->distributie){
                nod_vecin->distributie = varf->nod->distributie + 1;
                inserare_coada(&coada, nod_vecin);
            }
            vecin = vecin->urm;
        }
        free(varf);
    }
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

    //Aplicarea algoritmului de cautare in latime pentru determinarea distributiilor
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
    stergere_graf(&graf);
}

void rezolvare_cerinta2(char *fisier_intrare, char *fisier_iesire){
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
    //Cei doi actori pentru care se doreste determinarea distantei dintre ei
    fgets(actori[0], L_MAX, f_in);
    fgets(actori[1], L_MAX, f_in);
    nod_actori[0] = cautare_actor(graf, actori[0]);
    nod_actori[1] = cautare_actor(graf, actori[1]);
    fclose(f_in);

    //Rezolvarea cerintei
    BFS_distanta(graf, nod_actori[0]);

    //Afisarea rezultatului
    FILE *f_out = fopen(fisier_iesire, "w");
    if (!f_out){
        printf("Fisierul de iesire nu a putut fi creat.\n");
        exit(1);
    }
    fprintf(f_out, "%d\n", nod_actori[1]->distributie - 1);
    fclose(f_out);
    stergere_graf(&graf);
}

void DFS_punti(Graf graf, NodGraf *nod_graf, int timp, Punte *punti, int *nr_punti){
    nod_graf->timp_descoperire = timp;
    nod_graf->minim = timp;
    NodLista *aux = nod_graf->lista_adiacenta;
    while(aux){
        if (strcmp(aux->nume, nod_graf->parinte)){
            NodGraf *nod_copil = cautare_actor(graf, aux->nume); //Nodul copil al nodului graf
            if (!nod_copil->timp_descoperire){
                strcpy(nod_copil->parinte, nod_graf->nume);
                DFS_punti(graf, nod_copil, timp + 1, punti, nr_punti);
                if (nod_copil->minim < nod_graf->minim)
                    nod_graf->minim = nod_copil->minim;
                if (nod_copil->minim > nod_graf->timp_descoperire){
                    if (strcmp(nod_graf->nume, nod_copil->nume) < 0){
                        strcpy(punti[*nr_punti].actor1, nod_graf->nume);
                        strcpy(punti[*nr_punti].actor2, nod_copil->nume);
                    }
                    else{
                        strcpy(punti[*nr_punti].actor1, nod_copil->nume);
                        strcpy(punti[*nr_punti].actor2, nod_graf->nume);
                    }
                    (*nr_punti)++;
                }
            }
            else if (nod_copil->timp_descoperire < nod_graf->minim)
                nod_graf->minim = nod_copil->timp_descoperire;
        }
        aux = aux->urm;
    }
}

void rezolvare_cerinta3(char *fisier_intrare, char *fisier_iesire){
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

    //Aplicarea algoritmului de parcurgere in adancime modificat
    //Pentru a determina puntile din graf
    Punte punti[NR_ACTORI_MAX];
    int nr_punti = 0;
    for (int i = 0; i < NR_ACTORI_MAX; i++){
        NodTabel *aux = graf.actori[i];
        while(aux){
            if (!aux->nod->timp_descoperire)
                DFS_punti(graf, aux->nod, 1, punti, &nr_punti);
            aux = aux->urm;
        }
    }

    //Sortarea puntilor
    qsort(punti, nr_punti, sizeof(Punte), comparare_punti);

    //Afisarea rezultatelor
    FILE *f_out = fopen(fisier_iesire, "w");
    fprintf(f_out, "%d\n", nr_punti);
    for (int i = 0; i < nr_punti; i++){
        //Caracterul de trecere la linie noua este eliminat pentru a putea fi scrise
        //mai multe nume pe acelasi rand
        punti[i].actor1[strlen(punti[i].actor1) - 1] = '\0';
        fprintf(f_out, "%s %s", punti[i].actor1, punti[i].actor2);
    }
    fclose(f_out);
    stergere_graf(&graf);
}
