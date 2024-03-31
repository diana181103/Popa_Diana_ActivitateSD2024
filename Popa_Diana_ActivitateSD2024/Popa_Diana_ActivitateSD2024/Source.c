#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Santier Santier;
typedef struct NodLdi NodLdi;
typedef struct ListaDubla ListaDubla;

struct Santier {
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};

struct NodLdi {
    NodLdi* prev;
    NodLdi* next;
    Santier info;
};

struct ListaDubla {
    NodLdi* prim;
    NodLdi* ultim;
};

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
    Santier santier;
    santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
    strcpy(santier.numeProiect, numeProiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;

    return santier;
}



void afisareSantier(Santier santier) {
    printf("Santierul %s are %d muncitori si %5.2f m^2\n", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
}


//numele santierului cu densitatea cea mai mare de muncitori pe m^2

float densitate(Santier santier) {
    if (santier.suprafata != 0) {
        return santier.nrMuncitori / santier.suprafata;
    }
    return 0;
}

void inserareInceput(ListaDubla* lista, Santier s) {
    NodLdi* aux = (NodLdi*)malloc(sizeof(NodLdi));
    aux->info = s;
    aux->next = lista->prim;
    aux->prev = NULL;

    if (lista->prim != NULL) {
        lista->prim->prev = aux;
    }
    else {
        lista->ultim = aux;
        //daca am un singur nod, automat e si primul si ultimul
    }
    lista->prim = aux;
}

void afisareDeLAInceput(ListaDubla lista) {
    NodLdi* nod;
    for (nod = lista.prim; nod != NULL; nod = nod->next) {
        afisareSantier(nod->info);
    }
}

void stergereSantierDupaNume(ListaDubla* lista, const char* numeSantier) {

    NodLdi* nod = lista->prim;

    while (nod != NULL)
    {
        if (strcmp(nod->info.numeProiect, numeSantier) == 0) {
            if (nod->prev == NULL) {

                if (nod->next == NULL) {
                    lista->prim = NULL;
                    lista->ultim = NULL;
                }
                else {
                    nod->next->prev = NULL;
                    lista->prim = nod->next;
                }
            }
            else {
                if (nod->next == NULL) {
                    nod->prev->next = NULL;
                    lista->ultim = nod->prev;
                }
                else {
                    nod->prev->next = nod->next;
                    nod->next->prev = nod->prev;
                }
            }

            free(nod->info.numeProiect);
            free(nod);
            nod = NULL;
        }
        else {
            nod = nod->next;
        }
    }
}

void stergerCompleta(ListaDubla* lista) {
    if (lista != NULL) {
        NodLdi* aux = lista->prim;
        while (aux != NULL)
        {
            free(aux->info.numeProiect);
            NodLdi* temp = aux->next;
            free(aux);
            aux = temp;
        }
        lista->prim = NULL;
        lista->ultim = NULL;
    }
}

int calculNrTotalMuncitori(ListaDubla lista) {
    int s = 0;
    for (NodLdi* i = lista.prim; i != NULL; i = i->next) {
        s += i->info.nrMuncitori;
    }
    return s;
}

//int calculMuncitoriSuprafata(ListaDubla lista) {
//
//    int total = 0;
//    for (NodLdi* i = lista.prim; i != NULL; i = i->next) {
//        total += i->info.nrMuncitori;
//    }
//    return s;
//}

int main() {

    Santier s1 = initializareSantier("Santier 1", 10, 300);
    Santier s2 = initializareSantier("Santier 2", 12, 400);
    Santier s3 = initializareSantier("Santier 3", 15, 200);

    ListaDubla lista;
    lista.prim = NULL;
    lista.ultim = NULL;

    inserareInceput(&lista, s1);
    inserareInceput(&lista, s2);
    inserareInceput(&lista, s3);
    afisareDeLAInceput(lista);

    stergerCompleta(&lista);

    afisareDeLAInceput(lista);

    /*stergereSantierDupaNume(&lista, "Santier 2");
    printf("\n\n");
    afisareDeLAInceput(lista);
    stergereSantierDupaNume(&lista, "Santier 1");
    printf("\n\n");
    afisareDeLAInceput(lista);
    stergereSantierDupaNume(&lista, "Santier 3");
    printf("\n\n");
    afisareDeLAInceput(lista);*/
    return 0;
}
