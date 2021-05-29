//arbori AVL - functii utile 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define max(a, b) (a > b) ? a : b

// structura unui nod
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};
int N;
struct Node *root = NULL;
FILE *fOUT;

void fileWrite();

// calculeaza inaltimea pentru fiecare nod
int height(struct Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

//functie de ajutor care returneaza numarul de nivele ale arborelui
int tree_height(struct Node *node)
{
    if (node == NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lefth = tree_height(node->left);
        int righth = tree_height(node->right);

        /* use the larger one */
        if (lefth > righth)
            return (lefth + 1);
        else
            return (righth + 1);
    }
}

//creeaza cate un nod nou ca frunza
struct Node *newNode(int key)
{
    struct Node *node = (struct Node *)
        malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // il punem ca frunza
    return (node);
}

// functie de rotire dreapta
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // o rotatie
    x->right = y;
    y->left = T2;

    // facem update la height
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// functie de rotire stanga
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    //facem rotatie
    y->left = x;
    x->right = T2;

    // facem update la height
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// calculeaza factorul de balanta
int getBalance(struct Node *n)
{
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

// functia de inserare cu balansare
struct Node *insert(struct Node *node, int key)
{
    //ceaza o cheie noua frunza
    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else //nu avem chei egale
        return node;

    //update la height
    node->height = 1 + max(height(node->left),
                           height(node->right));

    //vedem daca e cumva nebalansat
    int balance = getBalance(node);

    //Daca e nebalansat apreciem 4 cazuri:

    // stanga stanga
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    //dreapta dreapta
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // stanga dreapta
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // dreapta stanga
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

//gaseste cea mai mica valoare
struct Node *minValueNode(struct Node *node)
{
    struct Node *current = node;
    while (current->left != NULL)
        current = current->left;

    return current;
}

// functie ajutatoare de stergere de nod
struct Node *deleteNode(struct Node *root, int key)
{
    //stergere obisnuita de arbore binar de cautare
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;

            free(temp);
        }
        else
        {

            struct Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left),
                           height(root->right));

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

//functia de suprimare
void suprimare(struct Node *root, int k)
{
    if (root != NULL && k != 0)
    {
        deleteNode(root, root->key);
        suprimare(root->left, k - 1);
        suprimare(root->right, k - 1);
    }
    else
        return;
}

//functie de initializare si inserare a nodurilor in arbore
void initialize()
{
    FILE *fIN;
    fIN = fopen("INPUT.DAT", "rb");
    if (fIN == NULL)
    {
        perror("Err file open");
        exit(EXIT_FAILURE);
    }
    fseek(fIN, 0, SEEK_END);
    N = ftell(fIN);

    N = N / sizeof(unsigned int);
    fseek(fIN, 0, SEEK_SET);
    printf("Doc are %d elemente\n", N);

    int buf;
    for (int i = 0; i < N; i++)
    {
        fread(&buf, sizeof(buf), 1, fIN);
        //printf("%d\n", buf);
        root = insert(root, buf);
    }

    fclose(fIN);
}

//functie ce afiseaza cheia parintelui unui nod cand ii dai cheia (k)
void parent(struct Node *nod, int k, int p)
{
    if (nod == NULL)
        return;
    if (nod->key == k)
        printf("\nTata = %d", p);

    else
    {
        parent(nod->left, k, nod->key);
        parent(nod->right, k, nod->key);
    }
}

//functie ce afiseaza fiul din stanga al unui nod
void firstChild(struct Node *nod, int k)
{

    if (nod == NULL)
        return;
    if (nod->key == k)
    {
        printf("\nPrimul copil al lui %d e %d", k, nod->left->key);
        return;
    }
    else
    {
        firstChild(nod->left, k);
        firstChild(nod->right, k);
    }
}

//functie ce afiseaza fratele unui nod
void rightSibling(struct Node *nod, int k)
{

    if (nod == NULL)
        return;
    struct Node *curent = NULL;
    while (nod)
    {
        if (k < nod->key)
        {
            curent = nod;
            nod = nod->left;
        }
        else if (k > nod->key)
        {
            curent = nod;
            nod = nod->right;
        }
        else
            break;
    }

    if (k == curent->left->key)
        printf("\nFratele = %d", curent->right->key);
    if (k == curent->right->key)
        printf("\nFratele = %d", curent->left->key);
}

//functie ce afiseaza cheia unui nod
void getKey(struct Node *nod, int k)
{
    if (nod == NULL)
        return;
    if (nod->key == k)
        printf("\nCheia = %d", nod->key);

    else
    {
        getKey(nod->left, k);
        getKey(nod->right, k);
    }
}

//functie ce afiseaza cheia radacinii arborelui
void getRoot(struct Node *root)
{
    if (root != NULL)
        printf("\nRoot: %d", root->key);
}

//functie de afisare a arborelui
void display(struct Node *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->key);
    if (root->left != NULL)
        printf("%d ", root->left->key);
    if (root->right != NULL)
        printf("%d ", root->right->key);
    printf("\n");

    display(root->left);
    display(root->right);
}

//functie de preordine
void preOrder(struct Node *root)
{
    if (root != NULL)
    {
        fprintf(fOUT, "%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
    else
        return;
}

//functie de postordine
void postOrder(struct Node *root)
{
    if (root != NULL)
    {
        postOrder(root->left);
        postOrder(root->right);
        fprintf(fOUT, "%d ", root->key);
    }
    else
        return;
}

//functie de inordine
void inOrder(struct Node *root)
{

    if (root != NULL)
    {
        inOrder(root->left);
        fprintf(fOUT, "%d ", root->key);
        inOrder(root->right);
    }
    else
        return;
}

//functie ajutatoare pentru afisarea unui nivel
void displayNivel(struct Node *root, int nivel)
{
    if (root == NULL)
        return;
    if (nivel == 1)
    {
        fprintf(fOUT, "%d ", root->key);
    }
    else if (nivel > 1)
    {
        displayNivel(root->left, nivel - 1);
        displayNivel(root->right, nivel - 1);
    }
}

//functia de traversare prin cuprindere
void levelOrder(struct Node *root)
{
    int h = tree_height(root);
    printf("\nInaltimea arborelui intreg e de %d nivele\n", h);
    for (int i = 1; i <= h; i++)
    {
        displayNivel(root, i);
    }
}

//functie care deschide fisierul pentru scriere
void fileWrite()
{
    fOUT = fopen("AVL.DAT", "wt");
    if (fOUT == NULL)
    {
        perror("Err file open 2");
        exit(EXIT_FAILURE);
    }
}

//main-u
int main(int argc, char *argv[])
{
    clock_t t1 = clock();
    initialize();
    int k = atoi(argv[1]);
    printf("\nK = %d\n", k);

    display(root);            //afisare a arborelui pentru fiecare grup de tata&fii
    firstChild(root, 3270);   //afisare a fiului stanga a unui nod
    getKey(root, 20);         //afisare a cheii unui nod
    rightSibling(root, 7869); //afisarea fratelui unui nod
    suprimare(root, k);       //stergerea a primilor k noduri intalniti in arbore, k se din cmd line
    parent(root, 9336, 0);    //afisarea parintelui unui nod
    getRoot(root);            //afisarea cheii radacinii

    fileWrite();

    fprintf(fOUT, "\nPreordine------------\n");
    preOrder(root);
    fprintf(fOUT, "\nInordine------------\n");
    inOrder(root);
    fprintf(fOUT, "\nPostordine------------\n");
    postOrder(root);
    fprintf(fOUT, "\nCuprindere------------\n");
    levelOrder(root);
    fclose(fOUT);
    clock_t t2 = clock();
    double run_time = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("Timp de rulare a acestui program = %lf;", run_time);

    return 0;
}