#ifndef __UTILITARE__
#define __UTILITARE__

//Creeaza un nod de graf si il returneaza
NodGraf *creare_nod_graf(char *);

//Sterge un nod de graf, eliberand memoria ocupata de acesta
void stergere_nod_graf(NodGraf *);

//Creeaza un nod de lista si il returneaza
NodLista *creare_nod_lista(char *);

//Adauga un element in lista de adiacenta daca acesta nu exista deja
void adaugare_lista_adiacenta(NodGraf *, char *);

//Initializeaza un graf vid
void initializare_graf(Graf *);

//Sterge graful eliberand memoria ocupata de acesta
void stergere_graf(Graf *);

//Genereaza cheia pentru tabela de dispersie corespunzatoare numelui dat ca argument
int generare_cheie(char *);

//Returneaza nodul corespunzatorul numelui actorului din tabela de dispersie
NodGraf *cautare_actor(Graf, char *);

//Insearaza un nou nod daca actorul nu face parte deja din graf
NodGraf *inserare_graf(Graf *, char *);

//Initializeaza o coada vida
void initializare_coada(Coada *);

//Insereaza un nou element in coada
void inserare_coada(Coada *, NodGraf *);

//Returneaza 0 daca coada este vida
//Returneaza o valoare nenula daca coada este nevida
int este_coada_vida(Coada);

//Extrage elementul de la inceputul cozii, daca acesta exista
ElementCoada *extragere_coada(Coada *);

#endif // __UTILITARE__
