// Sa se redacteze un program care citeste de la intrarea standard doua numere N -reprezentand numarul se noduri si M reprezentand numarul de arce, apoi citeste M perechi de valori, fiecare pereche reprezentand un arc. 
// Programul insereaza N noduri in graf, avand cheile de la 1 la N inclusiv. Apoi insereaza cele M arce. Programul afiseaza in ordine:
// numarul de componente conexe ale grafului 
// 1 daca draful este ciclic, si 0 daca acesta este aciclic

// Ex:
// input = 
// 7 6
// 1 2
// 2 3
// 3 4
// 4 5
// 5 3
// 6 7

// output = 2 1

#include <stdio.h>
#include <stdlib.h>

typedef struct TipArc {
    int idx_nod_1, idx_nod_2;
} Arc;

typedef struct Graf {
  int nr_noduri;
  int Noduri[100];
  int Arce[100][100];
} Graf;

Graf g;
int N, M, k;
int marc_df[20], nodes[20];

void initializare(){
  g.nr_noduri = 0;
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

Arc nouA(int cheie1, int cheie2) {
    Arc a;
    a.idx_nod_1 = cheie1;
    a.idx_nod_2 = cheie2;
    return a;
}

void InserareArc(Arc a){
  g.Arce[a.idx_nod_1][a.idx_nod_2] = g.Arce[a.idx_nod_2][a.idx_nod_1] = 1;
}

void CautaInAdancime(int x)
{
    int y;
    marc_df[x] = 1;

    for(y = 1; y <= g.nr_noduri; y++)
        if(g.Arce[x][y] != 0 && marc_df[y] == 0)
            CautaInAdancime(y);
}

int TraversareInAdancime()
{
    int x, counter_c = 0;
    for(x = 1; x <= g.nr_noduri; x++)
        marc_df[x] = 0;
    
    for(x = 1; x <= g.nr_noduri; x++)
        if(marc_df[x] == 0){
            CautaInAdancime(x);
            counter_c++;
        }
    return counter_c;      
}

void reset(int *v){
    for(int i = 0; i < N; i++)
        v[i] = 0;
    k = 0;
}

int Cautare_ciclu(int nr, int nod_parinte){
    marc_df[nr]=1;
    for(int i = 1; i <= N; i++)
        if(g.Arce[nr][i]){
            if (marc_df[i]==0){
                if(Cautare_ciclu(i, nr))
                    return 1;
            }else if(marc_df[i]==1 && i != nod_parinte)
                    return 1;
        }
    return 0;
}


int g_ciclic(){
    for (int i = 1; i <= N; i++)
        if(!marc_df[i] && Cautare_ciclu(i+1,0))
            return 1;
    return 0;
}

int main() 
{
    initializare();
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++)
        InsertNod(i);

    for(int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        Arc a = nouA(x, y);
        InserareArc(a);
    }

    int comp_conexe, ciclic;

    for(int i = 0; i < g.nr_noduri; i++) {
        nodes[k++] = g.Noduri[i];
        comp_conexe = TraversareInAdancime(g.Noduri[i]);
        reset(marc_df);
    }
    printf("%d ", comp_conexe);

    reset(marc_df);
    ciclic = g_ciclic();
    printf("%d", ciclic);

    return 0;
}
