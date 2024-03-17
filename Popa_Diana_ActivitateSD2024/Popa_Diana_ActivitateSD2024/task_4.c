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

void salvareInFisier(struct Depozit depozit, const char* numeFisier) {
	FILE* file = fopen(numeFisier, "w");
	fprintf(file, "%d,%s,%d", depozit.cod, depozit.nume, depozit.nrProduse);
	for (int i = 0; i < depozit.nrProduse; i++) {
		fprintf(file, ",%f", depozit.preturi[i]);
	}
	fprintf(file, "\n");
	fclose(file);
}

void salvareVectorInFisier(struct Depozit* depozit, int nrDepozite, const char* numeFisier) {
	FILE* file = fopen(numeFisier, "w");
	for (int j = 0; j < nrDepozite; j++) {
		fprintf(file, "%d,%s,%d", depozit[j].cod, depozit[j].nume, depozit[j].nrProduse);
		for (int i = 0; i < depozit[j].nrProduse; i++) {
			fprintf(file, ",%f", depozit[j].preturi[i]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

struct Depozit copiere(const struct Depozit d2)
{
	struct Depozit aux;
	aux.cod = d2.cod;
	aux.nume = malloc((strlen(d2.nume) + 1) * sizeof(char));
	strcpy(aux.nume, d2.nume);
	aux.nrProduse = d2.nrProduse;
	aux.preturi = malloc(sizeof(float) * d2.nrProduse);
	for (int i = 0; i < d2.nrProduse; i++)
	{
		aux.preturi[i] = d2.preturi[i];
	}
	return aux;
}

struct Depozit* adaugareInVector(struct Depozit* depozit, struct Depozit d, int* nrDep) {
	*nrDep = *nrDep + 1;
	struct Depozit* aux = (struct Depozit*)malloc(sizeof(struct Depozit) * (*nrDep));
	for (int i = 0; i < *nrDep - 1; i++) {
		aux[i] = depozit[i];
	}
	aux[*nrDep - 1] = copiere(d);
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
	if (file == NULL) {
		printf("Eroare: Nu se poate deschide fisierul %s\n", numeFisier);
		perror("fopen");
		return NULL;
	}

	while (fgets(buffer, 100, file) != NULL) {
		char* element = strtok(buffer, delimitare);
		struct Depozit d;
		d.cod = atoi(element);
		element = strtok(NULL, delimitare);
		d.nume = (char*)malloc(strlen(element) + 1);
		strcpy(d.nume, element);
		element = strtok(NULL, delimitare);
		d.nrProduse = atoi(element);
		d.preturi = malloc(sizeof(float) * d.nrProduse + 1);
		for (int i = 0; i < d.nrProduse; i++) {
			element = strtok(NULL, delimitare);
			d.preturi[i] = atof(element);
		}
		depozit = adaugareInVector(depozit, d, nrDep);

	}
	fclose(file);
	return depozit;
}

struct Depozit** creeazaMatrice(struct Depozit* depozite, int** dimensiuni, int numarStructuri, int* numarCateg)
{
	struct Depozit** matrice;
	*numarCateg = 3;
	matrice = malloc(sizeof(struct Depozit*) * (*numarCateg));
	*dimensiuni = malloc(sizeof(int) * (*numarCateg));
	for (int i = 0; i < *numarCateg; i++) {
		(*dimensiuni)[i] = 0;
		matrice[i] = NULL;
	}
	for (int i = 0; i < numarStructuri; i++) {
		int index = depozite[i].nrProduse;
		matrice[index] = adaugareInVector(matrice[index], depozite[i], &((*dimensiuni)[index]));
	}

	return matrice;
}

void afisareMatrice(struct Depozit** matriceDep, int* dimensiuni, int nrLinii)
{
	for (int i = 0; i < nrLinii; i++) {
		afisareVectorDepozit(matriceDep[i], dimensiuni[i]);
		printf("\n\n");
	}
}

int main() {

	struct Depozit* depozit = NULL;
	int nrDep = 0;
	depozit = citireFisier("depozite.txt", &nrDep);
	//afisareVectorDepozit(depozit, nrDep);

	//struct Depozit depozit1;
	//depozit1.cod = 1;
	//depozit1.nume = "Depozit1";
	//depozit1.nrProduse = 3;
	//depozit1.preturi = (float*)malloc(3 * sizeof(float));
	//depozit1.preturi[0] = 10.5;
	//depozit1.preturi[1] = 20.3;
	//depozit1.preturi[2] = 15.8;

	//// Salvăm obiectul în fișier
	//salvareInFisier(depozit1, "depozit.txt");

	//struct Depozit depozit2;
	//depozit2.cod = 2;
	//depozit2.nume = "Depozit2";
	//depozit2.nrProduse = 3;
	//depozit2.preturi = (float*)malloc(3 * sizeof(float));
	//depozit2.preturi[0] = 9.5;
	//depozit2.preturi[1] = 10.3;
	//depozit2.preturi[2] = 1.8;

	//struct Depozit* vDepozit=(struct Depozit*)malloc(sizeof(struct Depozit)*2);
	//vDepozit[0] = depozit1;

	//vDepozit[1] = depozit2;

	//salvareVectorInFisier(vDepozit, 2, "vectorDepozite.txt");
	//int nr_dep;
	//struct Depozit* dep = citireFisier("depozit.txt", &nr_dep);

	struct Depozit** matriceDep;
	int* dimensiuni;
	int numarCateg;
	matriceDep = creeazaMatrice(depozit, &dimensiuni, nrDep, &numarCateg);
	afisareMatrice(matriceDep, dimensiuni, numarCateg);


}