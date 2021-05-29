// 6/10 - needs improvement
// Sa se redacteze un program care citeste de la intrarea standard doua numere N -reprezentand numarul se noduri si M reprezentand numarul de arce, apoi citeste M perechi de valori, fiecare pereche reprezentand un arc. 
// Programul insereaza N noduri in graf, avand cheile de la 1 la N inclusiv. Apoi insereaza cele M arce. Programul afiseaza in ordine crescatoare cheile care respecta urmatoarea regula:
// pornind de la aceasta cheie, atat parcugerea in adancime cat si in cuprindere a unei componente conexe genereaza aceeasi secventa de chei

// Ex:
// input = 
// 5 6
// 1 2
// 1 3
// 2 3
// 3 4
// 4 5
// 3 5

// output = 1 2 3 

#include <stdio.h>
#include <stdlib.h>

typedef struct Coada {
    int noduri[100];
    int fata;
    int spate;
} Coada;

typedef struct TipArc {
    int idx_nod_1, idx_nod_2;
} Arc;

typedef struct Graf {
  int nr_noduri;
  int Noduri[100];
  int Arce[100][100];
} Graf;

Graf g;
int N, M;
int marc_df[20], nr_nodes1[20];
int marc_bf[20], nr_nodes2[20];
int counter1, counter2;

void initializare(){
  g.nr_noduri = 0;
}

Arc nouA(int cheie1, int cheie2) {
    Arc a;
    a.idx_nod_1 = cheie1;
    a.idx_nod_2 = cheie2;
    return a;
}

Coada *CoadaNoua() {
    Coada *c = (Coada *) malloc(sizeof(Coada));
    c->fata = -1;
    c->spate = -1;
    return c;
}

void InsertNod(int n){
  int index_nod = g.nr_noduri;
  g.Noduri[index_nod] = n; 
  g.nr_noduri++;
  int i;
  for(i = 0; i < g.nr_noduri; i++){
    g.Arce[index_nod][i] = g.Arce[i][index_nod] = 0;
  }  
}

void InsertArc(Arc a){
  g.Arce[a.idx_nod_1][a.idx_nod_2] = g.Arce[a.idx_nod_2][a.idx_nod_1] = 1;
}

void CautaInAdancime(int x)
{
    int y;
    marc_df[x] = 1;

    for(y = 0; y < g.nr_noduri; y++){
        if(g.Arce[x][y] != 0){
            if(marc_df[y] == 0){
                nr_nodes1[counter1++] = g.Noduri[y];
                CautaInAdancime(y);
            }
        }
    }
}

void TraversareInAdancime()
{
    int x;
    for(x = 0; x < g.nr_noduri; x++)
        marc_df[x] = 0;
    
    for(x = 0; x < g.nr_noduri; x++)
        if(marc_df[x] == 0)
            CautaInAdancime(x);
}

void add(Coada *c, int x) {
    if(c->fata == -1) {
        c->fata = 0;
    }
    c->spate++;
    c->noduri[c->spate] = x;
}

int vid(Coada *c){
    return c->spate == -1;
}

int take(Coada *c) {
    int x;
    if(vid(c)){
        x  = -1;
    } else {
        x = c->noduri[c->fata];
        c->fata++;
        if(c->fata > c->spate) {
            c->fata = c->spate = -1;
        }
    }
    return x;
}


void CautaPrinCuprindere(int x){
    Coada *c = CoadaNoua();
    int y;
    marc_bf[x] = 1;
    add(c, x);

    while(vid(c) == 0)
    {
        x = take(c);
        marc_bf[x] = 1;
        for(y = 0; y < g.nr_noduri; y++)
            if(g.Arce[x][y] != 0 && marc_bf[y] == 0)
            {
                marc_bf[y] = 1;
                nr_nodes2[counter2++] = g.Noduri[y];
                add(c, y);
            }
    }
} 

void TraversarePrinCuprindere()
{
    int x;
    for(x = 0; x < g.nr_noduri; x++)
        marc_bf[x] = 0;
    
    for(x = 0; x < g.nr_noduri; x++)
        if(marc_bf[x] == 0)
            CautaPrinCuprindere(x);
} 

void reset(int *v){
    for(int i = 0; i < N; i++)
        v[i] = 0;
    counter1 = 0;
    counter2 = 0;
}

int egal(int *v1, int n1, int n2, int *v2) {
    if(n1 != n2)
        return 0;
    for(int i = 0; i < n1; i++) {
        if(v1[i] != v2[i])
            return 0;
    }
    return 1;
}

int main() 
{
    initializare();
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++) {
        InsertNod(i);
    }
    for(int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        Arc a = nouA(x, y);
        InsertArc(a);
    }

    for(int i = 0; i < g.nr_noduri; i++) {
        nr_nodes1[counter1++] = g.Noduri[i];
        nr_nodes2[counter2++] = g.Noduri[i];
        CautaInAdancime(g.Noduri[i]);
        CautaPrinCuprindere(g.Noduri[i]);
        if(egal(nr_nodes1, counter1, counter2, nr_nodes2)){
            printf("%d ", g.Noduri[i]);
        }
        reset(marc_bf);
        reset(marc_df);
    }
    return 0;
}