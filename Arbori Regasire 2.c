// Sa se redacteze un program care citeste de la intrarea standard un numar N si apoi N siruri de carectere scise cu litere mici de tipar ('a'-'z'). Programul insereaza cuvintele intr-un dictionar de cuvinte implementat printr-un arbore de regasire si afiseaza:
// cel mai mare cuvant in ordine lexicografica
// Ex:
// input =
// 4
// arma
// armata
// zi
// zinc
// output = zinc

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct NodArboreDeRegasire {
	struct NodArboreDeRegasire *alfabet[27];
}NodArboreDeRegasire;

char cuv_mare[30];

void Initializare(NodArboreDeRegasire *Nod)
{
	char c;
	for (c = 'a'; c <= '{'; c++)
		Nod->alfabet[c - 'a'] = NULL;
}

void Atribuie(NodArboreDeRegasire *Nod, char c, NodArboreDeRegasire *p)
{
	Nod->alfabet[c - 'a'] = p;
}

NodArboreDeRegasire *Valoare(NodArboreDeRegasire *Nod, char c)
{
	return Nod->alfabet[c - 'a'];
}

void NodNou(NodArboreDeRegasire *Nod, char c)
{
	Nod->alfabet[c - 'a'] = (NodArboreDeRegasire *)malloc(sizeof(struct NodArboreDeRegasire));
	Initializare(Nod->alfabet[c - 'a']);
}

void Adauga(char *x, NodArboreDeRegasire *cuvinte)
{
	unsigned i;
	NodArboreDeRegasire *t;
	t = cuvinte;

	for (i = 0; i < strlen(x);i++) 
	{
		if (Valoare(t, x[i]) == NULL)
			NodNou(t, x[i]);
		t = Valoare(t, x[i]);
	}
	Atribuie(t, '{', t);
}


void Cuvant(NodArboreDeRegasire *Nod, char cuv[], int nivel)
{
    char c;
    for(c = 'a'; c < '{'; c++)
    {
        if(Nod->alfabet[c - 'a'])
        {
            cuv[nivel] = c;
            Cuvant(Nod->alfabet[c - 'a'], cuv, nivel+1);
        }
    }
    if(Nod->alfabet['{'-'a'])
    {
        cuv[nivel]='\0';
        if (strcmp(cuv, cuv_mare) > 0)  
            strcpy(cuv_mare, cuv);
    }
}


int main()
{
    NodArboreDeRegasire *arbore;
    arbore =(NodArboreDeRegasire *)malloc(sizeof(struct NodArboreDeRegasire));
    Initializare(arbore);

    int n, i;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        char cuv[25];
        scanf("%s", cuv);
        Adauga(cuv, arbore);
    }

    char cuv_nou[25];
    Cuvant(arbore, cuv_nou, 0);
    printf("%s", cuv_mare);

    return 0;
}