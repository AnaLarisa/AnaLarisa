// Sa se redacteze un program care citeste de la intrarea standard doua numere N-reprezentand numarul de noduri si M-reprezentand numarul de arce, apoi M triplete de valori (sursa destinatie pondere), fiecare pereche reprezentand un arc al unui graf neorientat si ponderat. 

// Programul insereaza N noduri in graf, avand cheile de la 1 la N inclusiv. Apoi insereaza cele M arce. Folosind, la alegere, algoritmul lui Prim sau Kruskal, programul va trebui sa calculeze arborele de acoperire minim si sa afiseze suma ponderilor arcelor acestuia.

// Limite date de intrare:
// 1 <= N <= 256
// 0 <= M <= 256
// -1024 <= pondere_arc <= 1024

// Exemplu:
// input = 
// 9 11
// 2 6 6
// 9 4 9
// 4 8 9
// 3 8 6
// 6 5 -2
// 7 1 -5
// 1 3 10
// 1 4 -3
// 9 7 -4
// 1 5 -10
// 3 2 -5

// output = -17

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define MAX 256

typedef struct TipNod {
  int cheie;
} Nod;

typedef struct TipArc {
    int idx_nod_1, idx_nod_2;
    int pondere;
} Arc;

typedef struct Graf {
  int nr_noduri;
  Nod Noduri[MAX];
  int Arce[MAX][MAX];//matricea de adiacenta
} Graf;

Graf g;
Arc a;
Nod n[MAX];
int N, M, suma_ponderi;
int marc[MAX];

void Initializare(){
  g.nr_noduri = 0;
}

void InsertNod(Nod n){
  g.Noduri[n.cheie] = n; 
  for(int i=1; i<=N; i++)
  {
    g.Arce[n.cheie][i] = g.Arce[i][n.cheie] = 0;
  }  
}

Arc CreateArc(int x, int y, int z) {
  Arc a;
  a.idx_nod_1 = x;
  a.idx_nod_2 = y;
  a.pondere = z;
  return a;
}

void InsertArc(Arc a){
  g.Arce[a.idx_nod_1][a.idx_nod_2] = g.Arce[a.idx_nod_2][a.idx_nod_1] = a.pondere;
}


void suma(int *T) {
  for(int i = 2; i<=N; i++) 
  {
    suma_ponderi = suma_ponderi + g.Arce[i][T[i]];
  }
}

int minKey(int *v)
{
  int min = INT_MAX, min_index;

  for(int i=1; i<=N; i++)
    if(!marc[i] && v[i]<min)
    {
      min = v[i];
      min_index = i;
    }
  return min_index;
}

void prim(){
    int T[N];
    T[1] = 0;
    int U[N];
    U[1] = 1;
    for(int i=2; i<=N; i++)
        U[i] = INT_MAX;
    
    for (int i=1; i<N; i++)
    {
        int min = minKey(U);
        marc[min] = 1;

        for(int j=1; j<=N; j++)
          if(!marc[j] && g.Arce[min][j] && U[j] > g.Arce[min][j])
          {
            T[j] = min;
            U[j] = g.Arce[min][j];
          }
    }

  suma(T);
}


int main()
{
    Initializare();
    scanf("%d %d", &N, &M);
    
    for(int i=1; i<=N; i++)
    {
        n[i].cheie = i;
        InsertNod(n[i]);
    }

    for(int i=1; i<=M; i++)
    {
      int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        Arc arc = CreateArc(a, b, c);
        InsertArc(arc);
    }

    prim();
    printf("%d", suma_ponderi);

    return 0;
}