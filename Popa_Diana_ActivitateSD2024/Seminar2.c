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

struct Masina* masiniSport(struct Masina* masini, int nrMasini, int* nrMasiniSport) {
	*nrMasiniSport = 0;
	for (int i = 0; i < nrMasini; i++) {
		if (masini[i].nrUsi < 4) {
			(*nrMasiniSport)++;
		}
	}
	struct Masina* vector = (struct Masina*)malloc(sizeof(struct Masina) * (*nrMasiniSport));
	int k = 0;
	for (int i = 0; i < nrMasini; i++) {
		if (masini[i].nrUsi < 4) {
			vector[k++] = masini[i];
		}
	}
	return vector;
}

int main() {

	struct Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireFisier("masini.txt", &nrMasini);
	for (int i = 0; i < nrMasini; i++) {
		printf("Masina are id-ul %d, producatorul %s, nrUsi %d si pretul %5.2f\n", masini[i].id, masini[i].producator, masini[i].nrUsi, masini[i].pret);
	}
	int* nrMasiniSport = 0;
	struct Masina* masiniSport_ = NULL;
	masiniSport_ = masiniSport(masini, 3, &nrMasiniSport);
	for (int i = 0; i < nrMasiniSport; i++) {
		printf("Masina are id-ul %d, producatorul %s, nrUsi %d si pretul %5.2f\n", masiniSport_[i].id, masiniSport_[i].producator, masiniSport_[i].nrUsi, masiniSport_[i].pret);
	}

}
