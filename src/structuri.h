#ifndef __STRUCTURI__
#define __STRUCTURI__
#define L_MAX 100 //Lungimea maxima a numelui unui actor sau film
#define NR_ACTORI_MAX 10000 //Numarul maxim de actori

//Structura de date ce implementeaza un nod din lista de adiacenta
//Lista este o lista simplu inlantuita
typedef struct NodLista{
    char nume[L_MAX]; //Numele actorului
    struct NodLista *urm; //Nodul urmator din lista
}NodLista;

//Structura de date ce implementeaza un nod dintr-un graf
typedef struct NodGraf{
    char nume[L_MAX]; //Campul de date este numele autorului
    int distributie;
    NodLista *lista_adiacenta; //Lista de adiacenta
}NodGraf;

//Lista simplu inlantuita pentru rezolvarea coliziunilor din tabela de dispersie
typedef struct NodTabel{
    NodGraf *nod;
    struct NodTabel *urm;
}NodTabel;

//Structura de date ce reprezinta graful
//Adresarea nodurilor se face printr-o tabela de dispersie
typedef struct Graf{
    NodTabel *actori[NR_ACTORI_MAX]; //Lista actorilor
}Graf;

//Elementul dintr-o coada
//Campul de date este un pointer catre un nod al grafului
typedef struct ElementCoada{
    NodGraf *nod;
    struct ElementCoada *urm, *prec;
}ElementCoada;

//Coada folosita pentru cautarile in adancime
//Pentru implementarea cozii, s-au folosit liste dublu inlantuite
typedef struct Coada{
    ElementCoada *inceput, *sfarsit;
}Coada;

#endif // __STRUCTURI__
