#include <stdio.h>
#include<malloc.h>
typedef struct Depozit Depozit;
typedef struct Nod Nod;

struct Depozit {
    int cod;
    char* nume;
    int nrProduse;
    float* preturi;
};

struct Nod {
    Depozit depozit;
    Nod* next;
};

Depozit initializareDepozit(int cod, const char* nume, int nrProduse, float* preturi) {
    Depozit depozit;
    depozit.cod = cod;
    depozit.nume = (char*)malloc(strlen(nume) + 1);
    strcpy(depozit.nume, nume);
    depozit.nrProduse = nrProduse;
    depozit.preturi = (float*)malloc(nrProduse*sizeof(float));
    for (int i = 0; i < nrProduse; i++) {
        depozit.preturi[i] = preturi[i];
    }
    return depozit;
}

int sumaProduse(Nod* lista)
{
    int suma = 0;
    while (lista != NULL) {
        suma = suma + lista->depozit.nrProduse;
        lista = lista->next;
    }
    return suma;
}

Nod* inserareInceput(Depozit depozit, Nod* lista) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->depozit = depozit;
    nod->next = lista;
    return nod;
}

void afisareDepozit(Depozit depozit) {
    printf(" COD:%d Depozitul %s are %d produse", depozit.cod,depozit.nume, depozit.nrProduse);
    printf("\n\n");
}
void afiseazaLista(Nod* lista) {
    while (lista != NULL) {
        afisareDepozit(lista->depozit);
        lista = lista->next;

    }
}

void stergereNod(Nod** lista, int pozitie) {
    if (*lista == NULL) {
        return;
    }
    Nod* temp = *lista;//aici preiau primul nod in temp
    if (pozitie == 1) {//aici tratez cazul cand e un singur nod
        *lista = temp->next;//lista devine next
        free(temp->depozit.nume);//sterg temp(adica primul nod)
        free(temp->depozit.preturi);
        free(temp);
        return;
    }
    int i = 1;

    while (temp != NULL && i < pozitie - 1) {//verific sa nu se termine lisa si sa ajung la nodul dinaintea celui pe care trebuie sa il sterg
  
        temp = temp->next;//aici o sa am nodul dinainte
        i++;
    }
    if (temp == NULL || temp->next == NULL) {//depaseste lungimea
        return;
    }
    Nod* nod_de_sters = temp->next;
    temp->next = temp->next->next;
    free(nod_de_sters->depozit.nume);
    free(nod_de_sters->depozit.preturi);
    free(nod_de_sters);
}

void stergereLista(Nod** lista) {
    while ((*lista) != NULL) {
        free((*lista)->depozit.nume);
        free((*lista)->depozit.preturi);
        Nod* aux = (*lista)->next;
        free(*lista);
        (*lista) = aux;
    }
    (*lista) = NULL;
}

void inserareFinal(Nod** primNod, Depozit d)
{
    if (*primNod != NULL)
    {
        Nod* aux = *primNod;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }

        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->depozit = d;
        nou->next = NULL;
        aux->next = nou;
    }
    else
    {
        *primNod = malloc(sizeof(Nod));
        (*primNod)->depozit = d;
        (*primNod)->next = NULL;
    }
}

Nod* inserareOrdonat(Depozit depozit, Nod* lista) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->depozit = depozit;
    nod->next = NULL;

    if (lista == NULL || lista->depozit.cod >= depozit.cod) {
        nod->next = lista;
        return nod;
    }
    while (lista->next != NULL && lista->next->depozit.cod < depozit.cod) {
        lista = lista->next;
    }
    if (lista->next == NULL) {
        inserareFinal(&lista, depozit);
    }
 
    else {
        nod->next = lista->next;
        lista->next = nod;
    }
    return lista;
}


Depozit* filtrareLista(Nod* lista) {
    int count = 0;
    Nod* lista1 = lista;
    while (lista1 != NULL) {
        if (lista1->depozit.nrProduse > 2) {
            count++;
        }
        lista1 = lista1->next;
    }
    int index = 0;
    Depozit* dep = (Depozit*)malloc(sizeof(Depozit) * count);
    lista1 = lista;
    while (lista1 != NULL) {
        if (lista1->depozit.nrProduse > 2) {
            dep[index].cod = lista1->depozit.cod;
            dep[index].nume = (char*)malloc(sizeof(char) * strlen(lista1->depozit.nume));
            strcpy(dep[index].nume, lista1->depozit.nume);
            dep[index].nrProduse = lista1->depozit.nrProduse;
            dep[index].preturi = (float*)malloc(sizeof(float) * lista1->depozit.nrProduse);
            for (int i = 0; i < lista1->depozit.nrProduse; i++) {
                dep[index].preturi[i] = lista1->depozit.preturi[i];
            }
            index++;
        }
        lista1 = lista1->next;
    }
    return dep;
}

//4. Implementati o functie care primeste lista si doua pozitii.In cadrul functiei 
//trebuie sa interschimbati elementele de pe cele doua pozitii din lista primita.


void interschimbare(Nod** lista, int poz1, int poz2) {
    if (poz1 == poz2) {
        return; 
    }

    int index = 0;
    Nod* prev1 = NULL;
    Nod* prev2 = NULL;
    Nod* current1 = *lista;
    Nod* current2 = *lista;

 
    while (current1 != NULL && index < poz1) {
        prev1 = current1;
        current1 = current1->next;
        index++;
    }

    index = 0;
    while (current2 != NULL && index < poz2) {
        prev2 = current2;
        current2 = current2->next;
        index++;
    }

  
    if (current1 == NULL || current2 == NULL) {
        return; 
    }

    
    if (prev1 != NULL) {
        prev1->next = current2;
    }
    else {
        *lista = current2;
    }

    if (prev2 != NULL) {
        prev2->next = current1;
    }
    else {
        *lista = current1;
    }

    Nod* temp = current1->next;
    current1->next = current2->next;
    current2->next = temp;
}

int main() {
    Nod* lista = NULL;
    int x[] = { 1,2,3 };

    Depozit s1 = initializareDepozit(1,"depozit1", 3, x);
    Depozit s2 = initializareDepozit(2,"depozit2", 3,x);
    Depozit s3 = initializareDepozit(3,"depozit3", 3, x);
    lista = inserareInceput(s1, lista);
    lista = inserareInceput(s2, lista);
    lista = inserareInceput(s3, lista);
    lista = inserareInceput(initializareDepozit(4, "depozit4", 3, x), lista);
    afiseazaLista(lista);
    stergereNod(&lista, 2);
    afiseazaLista(lista);
    int suma = 0;
    suma = sumaProduse(lista);
    printf("Suma este %d", suma);
   
    Nod* nod = NULL;
    printf("\nLista ordonata:\n");
    Depozit s5 = initializareDepozit(5, "depozit5", 3, x);

    nod = inserareOrdonat(s5, nod);
    nod = inserareOrdonat(s1, nod);
    nod = inserareOrdonat(s2, nod);
    afiseazaLista(nod);
    Depozit* depp = NULL;
    depp = filtrareLista(nod);

    interschimbare(&lista, 1, 3);

    printf("Lista dupa interschimbare: ");
    afiseazaLista(lista);
    return 0;
}