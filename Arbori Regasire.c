// Sa se redacteze un program care citeste de la intrarea standard un numar N si apoi N siruri de carectere scise cu litere mici de tipar ('a'-'z'). Programul insereaza cuvintele intr-un dictionar de cuvinte implementat printr-un arbore de regasire si afiseaza in ordine, urmatoarele valori:

// inaltimea arborelui de regasire;
// numarul de pagini din arbore (incluzand radacina)
// Ex:
// input =
// 4
// arma
// armata
// zi
// zinc
// output = 7 11

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct NodArboreDeRegasire {
	struct NodArboreDeRegasire *alfabet[27]; //alfabetul a b..z {
}NodArboreDeRegasire;

int h, nr_pag;

void Initializare(NodArboreDeRegasire *Nod)//ATENTIE, aceasta functie trebuie apelata cu *Nod deja alocat
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

void Adauga(char *x, NodArboreDeRegasire *cuvinte)  //x=cuvantul, cuvinte=radacina arborelui de regasire
{
	unsigned i;
	NodArboreDeRegasire *t;
	t = cuvinte;

	for (i = 0; i < strlen(x);i++) 
	{
		if (Valoare(t, x[i]) == NULL) //nodul curent nu are fiu pentru caracterul x[i], deci se creaza unul nou
			NodNou(t, x[i]);
		t = Valoare(t, x[i]); //avansez in arborele de regasire
	}
	Atribuie(t, '{', t); //se face o bucla pentru '[', pentru a marca un nod terminal
}

void Inaltime(NodArboreDeRegasire *Nod, char cuv[], int nivel)
{
    int l;
    char c;

    for(c = 'a'; c < '{'; c++)
    {
        if(Nod->alfabet[c - 'a'])
        {
            cuv[nivel] = c;
            Inaltime(Nod->alfabet[c - 'a'], cuv, nivel+1);
        }
    }
    if(Nod->alfabet['{'-'a'])
    {
        cuv[nivel]='\0';
        l = strlen(cuv);
        if (l > h)  
            h=l;
    }
}

void Pagini(NodArboreDeRegasire *Nod, char cuv[], int nivel)
{
    char c;
    for(c = 'a'; c < '{'; c++)
    {
        if(Nod->alfabet[c - 'a'])
        {
            cuv[nivel] = c;
            nr_pag++;
            Pagini(Nod->alfabet[c - 'a'], cuv, nivel+1);
        }
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
    Inaltime(arbore, cuv_nou, 0);
    printf("%d", h+1);

    Pagini(arbore, cuv_nou, 0);
    printf(" %d", nr_pag+1);

    return 0;
}