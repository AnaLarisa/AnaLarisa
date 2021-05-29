// Sa se citeasca de la tastatura un numar natural reprezentand numarul de noduri dintr-un arbore generalizat si apoi pe rand n perechi de numere intregi reprezentand cheia nodului si cheia parintelui. (Nota: Pentru radacina cheia parintelui va fi chiar cheia radacinii).

// 1. Sa se implementeze un arborele generalizat folosind metoda indicata de cadrul didactic de la laborator (tablou cu indicatori spre parinte sau tablou cu indicatori primul fiu frate drept), avand nodurile cu cheile citite de la tastatura.
// 2. Sa se implementeze urmatoarele functii:

// - void adauga (int cheie, int cheie_parinte) - insereaza in arbore un nod cu cheia "cheie" ca fiu al nodului cu cheia cheie_parinte;
// - int inaltime() - afiseaza intaltimea arborelui generalizat;
// - void grad() - afiseaza gradul arborelui generalizat;

// Se va citi numarul de noduri si apoi pe rand perechile de numere intregi reprezentand cheia nodului si cheia parintelui, apeland pentru fiecare pereche cheie nod - cheie parinte, functia adauga descrisa mai sus.

// 3. Dupa crearea arborelui generalizat, sa se apeleze functia inaltime si sa se afiseze valoarea pe ecran, apoi sa se apeleze functia grad si sa se afiseze valoarea pe ecran.

// exemplu:
// Pentru urmatoarele date citite de la tastatura:
// 5
// 1 1
// 2 1
// 3 1
// 4 1
// 5 1

// Rezultatul este:
// 2
// 4

// Ex2:
// Input:
// 4
// 1 1
// 2 1
// 3 2
// 4 2

// Output:
// 3
// 2

#include <stdlib.h>
#include <stdio.h>

typedef struct Nod{
    int cheie;
    int cheie_parinte;
}Nod;

Nod nod[10];
int n, i;
int v[10];

void adauga(int c, int cp){
    if (i<n){
        nod[i].cheie = c;
        nod[i].cheie_parinte = cp;
    }
    i++;
}

int inaltime(){
    int j, h=1;
    for(j=0; j<i; j++)
        v[nod[j].cheie_parinte]++;
    for(j=0; j<10; j++)
        if (v[j]!=0)
            h++;
    return h;
}

void grad(){
    int j, max = 0;
    for(j=0; j<10; j++){
        if(max < v[j])
            max = v[j];
    }
    printf("%d\n", max-1);
}


int main(){
    int c, cp, h;

    scanf("%d", &n);
    for(int j=0; j<n; j++){
        scanf("%d %d", &c, &cp);
        adauga(c, cp);
    }
   
    h = inaltime();
    printf("%d\n", h);

    grad();
    return 0;
}
