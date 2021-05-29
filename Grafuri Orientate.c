// Sa se redacteze un program care citeste de la intrarea standard doua numere N-reprezentand numarul de noduri si M-reprezentand numarul de arce, apoi M triplete de valori (sursa destinatie pondere), fiecare pereche reprezentand un arc al unui graf orientat si ponderat. 
// Programul insereaza N noduri in graf, avand cheile de la 1 la N inclusiv. Apoi insereaza cele M arce. Folosind algoritmul lui Dijkstra, programul va calcula si afisa n-1 valori separate prin spatiu, reprezentand distanta minima de la primul nod (nodul cu cheia 1) la toate celalalte noduri(2, 3, ..., n). Atentie, este posibil sa nu existe drum de la primul nod la unele noduri, caz in care se va afisa lungimea 0.

// Limite date de intrare:
// 1 <= N <= 256
// 0 <= M <= 256
// 1 <= pondere_arc <= 1024

// Exemplu:
// input = 4 9
// 2 1 64
// 1 4 12
// 2 4 72
// 3 2 94
// 3 4 27
// 1 2 95
// 4 1 97
// 3 1 96
// 4 2 16

// output = 28 0 12

// Explicatie:
// 28 - distanta minima de la 1 la 2 (1 -> 4 -> 2)
// 0 - nu exista drum de la 1 la 3 
// 12 - distanta minima de la 1 la 4 (1 -> 4)

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
int N, M;
int marc[MAX], length[MAX];

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
  g.Arce[a.idx_nod_1][a.idx_nod_2] = a.pondere;
}

int dist_min(){
  int nod, min=30000;
  for(int i=1; i<=N; i++)
    if(!marc[g.Noduri[i].cheie] && length[g.Noduri[i].cheie] < min)
    {
      min=length[g.Noduri[i].cheie];
      nod=i;
    }
  
  return nod;
}


void Dijkstra(int begin){

  for(int i=1; i<=N; i++)
  {
      if(g.Arce[begin][g.Noduri[i].cheie])
        length[i] = g.Arce[begin][g.Noduri[i].cheie];
      else 
        length[i] = 300000;
      
      marc[g.Noduri[i].cheie]=0;
  }

  length[begin]=0;
  marc[begin]=1;
  for (int i=1; i<=N; i++)
  {
    int min = dist_min();
    marc[min]=1;
    for (int j=1; j<=N; j++)
      if (!marc[g.Noduri[j].cheie] && g.Arce[g.Noduri[min].cheie][g.Noduri[j].cheie] && length[g.Noduri[min].cheie] != 300000)
        if(length[g.Noduri[min].cheie] + g.Arce[g.Noduri[min].cheie][g.Noduri[j].cheie] < length[g.Noduri[j].cheie])
        {
          length[g.Noduri[j].cheie] = length[g.Noduri[min].cheie] + g.Arce[g.Noduri[min].cheie][g.Noduri[j].cheie];
          //marc[g.Noduri[j].cheie] = 1;
        } 
  }
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

    Dijkstra(1);
    for(int i=2; i<=N; i++)
    {
      if(length[g.Noduri[i].cheie] == 300000)
        length[g.Noduri[i].cheie] = 0;
      printf("%d ", length[g.Noduri[i].cheie]);
    }

    return 0;
}