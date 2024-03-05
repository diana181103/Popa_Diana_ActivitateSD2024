#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>


struct Depozit {
	int cod;
	char* nume;
	int nrProduse;
	float* preturi;

};

void afiseazaDepozit(struct Depozit d) {
	printf("Cod: %d\n", d.cod);
	if (d.nume != NULL) {
		printf("Nume: %s\n", d.nume);
	}
	printf("Nr produse: %d\n", d.nrProduse);
	if (d.preturi != NULL) {
		printf("Salarii: ");
		for (int i = 0; i < d.nrProduse; i++) {
			printf("%5.2f, ", d.preturi[i]);
		}
	}
	printf("\n");
}
void afisareVectorDepozit(struct Depozit* vectorDepozite, int nr) {
	for (int i = 0; i < nr; i++) {
		afiseazaDepozit(vectorDepozite[i]);
	}
}


struct Depozit* adaugareInVector(struct Depozit* depozit, struct Depozit d, int* nrDep) {
	struct Depozit* aux = (struct Depozit*)malloc(sizeof(struct Depozit) * ((*nrDep) + 1));
	for (int i = 0; i < *nrDep; i++) {
		aux[i] = depozit[i];
	}
	aux[*nrDep] = d;
	(*nrDep)++;
	if (depozit != NULL) {
		free(depozit);
	}
	return aux;
}

struct Depozit* citireFisier(const char* numeFisier, int* nrDep) {
	FILE* file = fopen(numeFisier, "r");
	char buffer[100];
	char delimitare[] = ",\n";
	struct Depozit* depozit = NULL;
	(*nrDep) = 0;
	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare);
		struct Depozit d;
		d.cod = atoi(element);
		element = strtok(NULL, delimitare);
		d.nume = (char*)malloc(strlen(element) + 1);
		strcpy(d.nume, element);
		element = strtok(NULL, delimitare);
		d.nrProduse = atoi(element);
		d.preturi = malloc(sizeof(float) * d.nrProduse+1);
		for (int i = 0; i < d.nrProduse; i++) {
			element = strtok(NULL, delimitare);
			d.preturi[i] = atoi(element);
		}
		depozit = adaugareInVector(depozit, d, nrDep);

	}
	fclose(file);
	return depozit;
}



int main() {

	struct Depozit* depozit= NULL;
	int nrDep = 0;
	depozit = citireFisier("depozit.txt", &nrDep);
	afisareVectorDepozit(depozit, nrDep);
	

}