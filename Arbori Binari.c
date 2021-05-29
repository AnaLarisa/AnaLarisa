// Sa se citeasca de la tastatura un numar natural reprezentand numarul de noduri dintr-un arbore binar ordonat si apoi pe rand cheile acestor noduri (numere intregi).
// 1. Sa se creeze un arbore binar ordonat folosind implemetarea cu pointeri, continand cheile citite de la tastatura.
// 2. Sa se implementeze urmatoarele functii:
// - void adauga (int cheie) - insereaza in arbore cheia "cheie" (arborele este ordonat);
// - int inaltime() - afiseaza intaltimea arborelui binar ordonat;
// - void preordine() - parcurge arborele in preordine, afisand cheile intalnite in aceasta parcurgere;
// Se va citi numarul de noduri si apoi pe rand fiecare cheie si pentru fiecare cheie citita se va apela functia adauga (int cheie) descrisa mai sus.
// 3. Dupa crearea arborelui binar ordonat, sa se apeleze functia inaltime si sa se afiseze valoarea pe ecran, apoi sa se apeleze functia preordine care va afisa pe o linie noua cheile separate prin spatiu.

// exemplu
// Pentru urmatoarele date citite de la tastatura:
// 3
// 2 1 4

// Rezultatul este:
// 2
// 2 1 4

#include <stdio.h>
#include <stdlib.h>

struct Nod{
    int cheie;
    struct Nod *stang, *drept;
};

struct Nod *rad;
int N;

struct Nod *radacina (int c){
    rad = (struct Nod *)malloc(sizeof(struct Nod));
    rad->cheie = c;
    rad->stang = NULL;
    rad->drept = NULL;
    return rad;
}


void insert(int x, struct Nod *rad, struct Nod *tata){
    if(rad != NULL) {
        if(x < rad->cheie)
            insert(x, rad->stang, rad);
        else insert(x, rad->drept, rad);
    } else {
        rad = (struct Nod *)malloc(sizeof(struct Nod));
        rad->cheie = x;
        rad->stang = NULL;
        rad->drept = NULL;
        if(x < tata->cheie)
            tata->stang = rad;
        else    
            tata->drept = rad;
    }
}

int max(int a, int b){
    if(a > b)
        return a;
    else 
        return b;
}

int inaltime(struct Nod *n){
    int hs, hd;
    if(n == NULL)
        return 0;
    else {
        hs = inaltime(n->stang);
        hd = inaltime(n->drept);
    }
        return (max(hs, hd) + 1); 
}


void preordine(struct Nod *n){
    if(n == NULL) return;
    printf("%d ", n->cheie);
    preordine(n->stang);
    preordine(n->drept);
}


int main(){

    scanf("%d", &N);
    int x, i;

    for(i=0; i<N; i++){
        scanf("%d", &x);
        if(i == 0) rad = radacina(x);
        else insert(x, rad, NULL);
    }

    printf("%d\n", inaltime(rad));
    preordine(rad);

    return 0;
}