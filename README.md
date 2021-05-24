# Filme
***
## Cuprins
1. [Informații generale](#informații-generale)
2. [Conținutul proiectului](#conținutul-proiectului)
3. [Algoritmi](#algoritmi)
4. [Tehnologii folosite](#tehnologii-folosite)
5. [Instalare și utilizare](#instalare-și-utilizare)
6. [Probleme](#probleme)

### Informații generale
***
Proiectul a constat în aplicarea cunoștințelor legate de teoria grafurilor pe o aplicație concretă:
o colecție de filme în care nodurile sunt actorii.
Cerințele au fost următoarele:
1. Determinarea distribuției maximale din lista de filme date
2. Determinarea gradului de înrudire a doi actori
3. Determinarea punților din graf

### Conținutul proiectului
***
Acest proiect conține 6 fișiere sursă, un Makefile, licența de distribuire și fișierul curent README.
Fișierele sursă sunt următoarele:
1. **main.c**: fișierul ce decide ce sarcină va fi rezolvată în funcție de primul parametru dat.
2. **rezolvare_cerinte.c**: conține 3 funcții principale, pentru fiecare sarcină în parte, 
împreună cu funcțiile pentru parcurgerea grafurilor.
3. **rezolvare_cerinte.h**: în interiorul acestui fișier se află definițiile tuturor funcțiilor din **rezolvare_cerințe.c** care sunt apelate de alte module.
4. **utilitare.c**: un set de funcții cu utilitate ridicată și folosite de-a lungul proiectului.
5. **utilitare.h**: definițiile funcțiilor din **utilitare.c**.
6. **structuri.h**: fișier antet ce definește cele două structuri utilizate în proiect: arbori și cozi.

### Algoritmi
***
Pentru rezolvarea cerințelor, s-au aplicat algoritmii clasici de parcurgere a grafurilor.
1. Pentru prima cerință, s-a folosit algoritmul BFS pentru determinarea tuturor componentelor conexe, 
cât și a numărului de noduri din fiecare. Odată determinată componenta conexă maximală, se reține într-un vector
numele tuturor actorilor din aceștia sortat cu ajutorul algoritmului de sortare rapidă.
2. Pentru a doua cerință, ca și la subpunctul anterior, s-a folosit parcurgerea în lățime pentru a determina 
distanța dintre doi actori. Dacă nu se poate ajunge de la un actor la altul, se afișează -1.
3. Pentru determinarea punților din graf, s-a folosit parcurgerea în adâncime modificată conform algoritmului 
lui Tarjan. Punților sunt apoi sortate în funcție de numele primului actor, iar în caz de egalitate, după cel de al doilea.

### Tehnologii folosite
***
Mediu integrat de dezvoltare: [CodeBlocks](https://www.codeblocks.org/), ver 20.03.    
Compilator: [gcc](https://gcc.gnu.org/), ver 9.3.0.    
Limbaj de programare: C.    
Sistem de versionare: [git](https://git-scm.com/), ver 2.25.1, împreună cu serviciul web de stocare [GitHub](https://github.com/)

### Instalare și utilizare
***
Pentru instalare, se descarcă dosarul **src**, iar din interiorul acestuia se rulează comanda **make** specifică fișierului **Makefile**. Se va genera un fișier binar cu denumirea de **movies**.    
Pentru utilizare, se rulează executabilul **movies** cu următoarele argumente:
1. Primul argument va fi **-c1**, **-c2** sau **-c3** în funcție de cerința de rezolvare dorită.
2. Al doilea argument reprezintă numele fișierului din care se vor citi datele.
3. Al treilea argument reprezintă numele fișierului în care se vor stoca rezultatele.

Pentru vizualizarea rezultatelor, este suficient să se deschidă fișierul de ieșire cu orice editor de text.

### Probleme
***
Versiunea curentă (ver 1.0) nu conține probleme cunoscute. Programul a fost testat pe Windows 10, 64 de biți și pe distribuția de Linux Ubuntu 20.04. Dacă observați orice comportament neașteptat, vă rog să-l semnalați prin intermediul acestui depozit https://github.com/D3XT3RY0NuT/movies.
***
Notă: Depozitul GitHub a fost publicat la data de 29 mai 2021.
