#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Cladire Cladire;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;
typedef struct NodSimplu NodSimplu;

struct Cladire {
    int id;
    int anConstruire;
    char* nume;
};

struct Nod {
    Cladire cladire;
    Nod* prev;
    Nod* next;
};

struct ListaDubla {
    Nod* prim;
    Nod* ultim;
};

struct NodSimplu {
    Cladire cladire;
    Nod* next;
};

Cladire initializareCladire(int id, int anConstruire, const char* nume) {
    Cladire c;
    c.id = id;
    c.anConstruire = anConstruire;
    c.nume = (char*)malloc(strlen(nume) + 1);
    strcpy(c.nume, nume);
    return c;
}

void afisareCladire(Cladire c) {
    printf("%d: In anul %d a fost construita cladire %s\n", c.id, c.anConstruire, c.nume);
}

void afisareLdiDeLaInceput(ListaDubla lista) {
    Nod* nod;
    for (nod = lista.prim; nod != NULL; nod = nod->next) {
        afisareCladire(nod->cladire);
    }
    printf("\n\n");
}

void inserareInceput(ListaDubla* ld, Cladire c) {
    Nod* nod = malloc(sizeof(Nod));
    nod->next = ld->prim;
    nod->prev = NULL;
    nod->cladire = c;
    if (ld->prim != NULL) {
        ld->prim->prev = nod;
    }
    else {
        ld->ultim = nod;
    }
    ld->prim = nod;
}

void stergere(ListaDubla* ld, int pozitie) {
    Nod* nod = ld->prim;

    int k = 0;
    while (nod != NULL) {
        k = k + 1;
        if (k == pozitie) {
            if (nod->prev == NULL) {
                if (nod->next == NULL) {
                    ld->prim = NULL;
                    ld->ultim = NULL;
                }
                else {
                    nod->next->prev = NULL;
                    ld->prim = nod->next;
                }
            }
            else {
                if (nod->next == NULL) {
                    nod->prev->next = NULL;
                    ld->ultim = nod->prev;
                }
                else {
                    nod->next->prev = nod->prev;
                    nod->prev->next = nod->next;
                }

            }
            free(nod->cladire.nume);
            free(nod);
            nod = NULL;
        }
        else {
            nod = nod->next;
        }
    }
}



void inserareOrdonat(ListaDubla* ld, Cladire c) {
    Nod* nod = malloc(sizeof(Nod));
    nod->cladire = c;
    int k = c.id;

    if (ld->prim == NULL) {
        nod->prev = NULL;
        nod->next = NULL;
        ld->prim = nod;
        ld->ultim = nod;
        return;
    }

    if (k < ld->prim->cladire.id) {
        nod->prev = NULL;
        nod->next = ld->prim;
        ld->prim->prev = nod;
        ld->prim = nod;
        return;
    }

    if (k > ld->ultim->cladire.id) {
        nod->next = NULL;
        nod->prev = ld->ultim;
        ld->ultim->next = nod;
        ld->ultim = nod;
        return;
    }

    Nod* current = ld->prim->next;
    while (current != NULL) {
        if (k < current->cladire.id) {
            nod->next = current;
            nod->prev = current->prev;
            current->prev->next = nod;
            current->prev = nod;
            return;
        }
        current = current->next;
    }
}
Nod* inserareInceputS(Nod* lista, Cladire c) {
    NodSimplu* nod = (NodSimplu*)malloc(sizeof(Nod));

    nod->cladire = initializareCladire(c.id, c.anConstruire, c.nume);
    nod->next = lista;
    return nod;
}

NodSimplu* toLista(ListaDubla* ld) {
    Nod* nod = ld->prim;
    NodSimplu* nodS = NULL;
    while (nod != NULL) {
        if (nod->cladire.anConstruire > 2000) {
            nodS = inserareInceputS(nodS, nod->cladire);
        }
        nod = nod->next;
    }

    return nodS;
}

/*NodSimplu* toLista(ListaDubla* ld) {
    Nod* nod = ld->prim;
    NodSimplu* nodS = NULL;

    while (nod != NULL) {
        if (nod->cladire.anConstruire > 2000) {
            NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
            nou->cladire = initializareCladire(nod->cladire.id, nod->cladire.anConstruire, nod->cladire.nume);
            nou->next = nodS;
            nodS = nou;
        }
        nod = nod->next;
    }

    return nodS;
}*/

void afisareLsi(NodSimplu* lista) {
    while (lista != NULL) {
        afisareCladire(lista->cladire);
        lista = lista->next;
    }
}

//5. Implementati o functie care primeste lista dublu inlantuita si doua pozitii.In cadrul functiei 
//trebuie sa interschimbati elementele de pe cele doua pozitii din lista primit*//*a.Interschimbati informatiile utile din cele doua noduri.*/

void inserareFinal(ListaDubla* ld, Cladire c) {
    Nod* nod = malloc(sizeof(Nod));
    nod->next = NULL;
    nod->prev = ld->ultim;
    nod->cladire = c;
    if (ld->ultim != NULL) {
        ld->ultim->next = nod;
    }
    else {
        ld->prim = nod;
    }
    ld->ultim = nod;
}

int main() {
    Cladire c = initializareCladire(1, 2000, "Cladire1");
    Cladire c1 = initializareCladire(2, 2000, "Cladire2");
    Cladire c2 = initializareCladire(3, 2002, "Cladire3");
    ListaDubla ld;
    ld.prim = NULL;
    ld.ultim = NULL;
    inserareFinal(&ld, c);
    inserareFinal(&ld, c1);
    inserareInceput(&ld, c2);
    afisareLdiDeLaInceput(ld);
    stergere(&ld, 1);
    afisareLdiDeLaInceput(ld);
    Cladire c4 = initializareCladire(4, 2002, "Cladire4");
    inserareOrdonat(&ld, c4);
    afisareLdiDeLaInceput(ld);
    NodSimplu* ns = NULL;
    ns = toLista(&ld);
    afisareLsi(ns);
    return 0;
}
