#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>


struct Masina {
    int id;
    char* producator;
    int nrUsi;
    float pret;
};


struct Masina* adaugareInVector(struct Masina* masini, struct Masina m, int* nrMasini) {
    struct Masina* aux = (struct Masina*)malloc(sizeof(struct Masina) * ((*nrMasini) + 1));
    for (int i = 0; i < *nrMasini; i++) {
        aux[i] = masini[i];
    }
    aux[*nrMasini] = m;
    (*nrMasini)++;
    if (masini != NULL) {
        free(masini);
    }
    return aux;
}

struct Masina* citireFisier(const char* numeFisier, int* nrMasini) {
    FILE* file = fopen(numeFisier, "r");
    char buffer[100];
    char delimitare[] = ",\n";
    struct Masina* masini = NULL;
    (*nrMasini) = 0;
    while (fgets(buffer, 100, file) != NULL) {
        char* element = strtok(buffer, delimitare);
        struct Masina m;
        m.id = atoi(element);
        element = strtok(NULL, delimitare);
        m.producator = (char*)malloc(strlen(element) + 1);
        strcpy(m.producator, element);
        element = strtok(NULL, delimitare);
        m.nrUsi = atoi(element);
        element = strtok(NULL, delimitare);
        m.pret = atoi(element);
        masini = adaugareInVector(masini, m, nrMasini);

    }
    fclose(file);
    return masini;
}

//struct Masina* masiniSport(struct Masina* masini, int nrMasini, int* nrMasiniSport) {
//    *nrMasiniSport = 0;
//    for (int i = 0; i < nrMasini; i++) {
//        if (masini[i].nrUsi < 4) {
//            (*nrMasiniSport)++;
//        }
//    }
//    struct Masina* vector = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasiniSport));
//    int k = 0;
//    for (int i = 0; i < nrMasini; i++) {
//        if (masini[i].nrUsi < 4) {
//            vector[k++] = masini[i];
//        }
//    }
//    return vector;
//}

void afisareMatrice(struct Masina** matrice, int nrLinii, int* nrCol) {
    for (int i = 0; i < nrLinii; i++) {
        for (int j = 0; j < nrCol[i]; j++) {
            printf("%d,%s,%d,%5.2f\t", matrice[i][j].id, matrice[i][j].producator, matrice[i][j].nrUsi, matrice[i][j].pret);
        }
        printf("\n");
    }
}

void citireMatrice(const char* numeFisier, struct Masina** matrice, int* nrColoane, int nrLinii) {
    FILE* file = fopen(numeFisier, "r");
    char buffer[100];
    char delimitare[] = ",\n";
    while (fgets(buffer, 100, file) != NULL) {
        char* element = strtok(buffer, delimitare);
        struct Masina m;
        m.id = atoi(element);
        element = strtok(NULL, delimitare);
        m.producator = (char*)malloc(strlen(element) + 1);
        strcpy(m.producator, element);
        element = strtok(NULL, delimitare);
        m.nrUsi = atoi(element);
        element = strtok(NULL, delimitare);
        m.pret = atoi(element);
        matrice[m.nrUsi - 2] = adaugareInVector(matrice[m.nrUsi - 2], m, &(nrColoane[m.nrUsi - 2]));

    }
    fclose(file);
}
//pretul mediu al masinilor cu nr de usi dat ca parametru
float pretMediu(struct Masina** matrice, int nrLinii, int* nrColoane, int nrUsi) {
    if (nrUsi < 2 || nrUsi>4) {
        return 0;
    }
    float pretTotal = 0;
    int index = nrUsi - 2;
    if (nrColoane[index] == 0) {
        return 0;
    }
    for (int i = 0; i < nrColoane[index]; i++) {
        pretTotal = pretTotal + matrice[index][i].pret;
    }
    return pretTotal / nrColoane[index];

}

struct Masina cautaMasinaDupaID(struct Masina** matrice, int nrLinii, int* nrCol, int id) {
    for (int i = 0; i < nrLinii; i++) {
        for (int j = 0; j < nrCol[i]; j++) {
            if (matrice[i][j].id == id) {
                return matrice[i][j];
            }
        }
    }
    struct Masina m;
    m.id = -1;
    m.producator = NULL;
    m.nrUsi = 0;
    m.pret = 0;
    return m;

}

void dezalocareMatrice(struct Masina*** matrice, int nrLinii, int** nrColoane) {
    for (int i = 0; i < nrLinii; i++) {
        for (int j = 0; j < (*nrColoane)[i]; j++) {
            free((*matrice)[i][j].producator);
        }
        free((*matrice)[i]);
    }
    free((*nrColoane));
    free((*matrice));
    (*nrColoane) = NULL;
    (*matrice) = NULL;
}

int main() {

    struct Masina** matrice;
    int nrLinii = 3;
    int* nrCol = (int*)malloc(sizeof(int) * nrLinii);//vect de lungimi
    matrice = (struct Masina**)malloc(sizeof(struct Masina*) * nrLinii);
    for (int i = 0; i < nrLinii; i++) {
        nrCol[i] = 0;
        matrice[i] = NULL;
    }
    citireMatrice("masini.txt", matrice, nrCol, nrLinii);
    afisareMatrice(matrice, nrLinii, nrCol);
    printf("Pretul mediu al masinilor cu 2 usi: %5.2f", pretMediu(matrice, nrLinii, nrCol, 2));
    struct Masina masini = cautaMasinaDupaID(matrice, nrLinii, nrCol, 2);
    printf("\nMasina are id-ul %d, producatorul %s, nrUsi %d si pretul %5.2f\n", masini.id, masini.producator, masini.nrUsi, masini.pret);
    dezalocareMatrice(&matrice, nrLinii, &nrCol);
}
