
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
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

struct Depozit initializareDepozit(int cod, char* nume, int nrProduse, const float* preturi) {
	struct Depozit d;
	d.cod = cod;
	d.nume = malloc(strlen(nume) + 1);
	strcpy(d.nume, nume);
	d.nrProduse = nrProduse;
	d.preturi = malloc(sizeof(float) * nrProduse);
	for (int i = 0; i < nrProduse; i++) {
		d.preturi[i] = preturi[i];
	}
	return d;
}

struct Depozit citesteDepozit() {
	struct Depozit d;
	printf("Dati cod:");
	scanf("%d", &d.cod);
	char buffer[100];
	printf("Dati nume:");
	scanf("%s", buffer);
	d.nume = malloc(strlen(buffer) + 1);
	strcpy(d.nume, buffer);
	printf("Dati nrProduse:");
	scanf("%d", &d.nrProduse);
	d.preturi = malloc(sizeof(float) * d.nrProduse);
	printf("Preturile:");
	for (int i = 0; i < d.nrProduse; i++) {
		scanf("%f", &d.preturi[i]);
	}
	return d;
}

void modificareCod(struct Depozit* d, int cod) {
	d->cod = cod;
}

int conditie(struct Depozit d) {
	return d.cod >= 2;
}

int conditie1(struct Depozit d) {
	return d.nrProduse > 10;
}

struct Depozit* concatenare(struct Depozit* vector1, struct Depozit* vector2, int lungime1, int lungime2) {
	int lg = lungime1 + lungime2;
	struct Depozit* vectorfinal = malloc(sizeof(struct Depozit) * lg);
	for (int i = 0; i < lungime1; i++) {
		vectorfinal[i] = initializareDepozit(vector1[i].cod, vector1[i].nume, vector1[i].nrProduse, vector1[i].preturi);
	}
	for (int i = 0; i < lungime2; i++) {
		vectorfinal[lungime1 + i] = initializareDepozit(vector2[i].cod, vector2[i].nume, vector2[i].nrProduse, vector2[i].preturi);
	}
	return vectorfinal;
}

struct Depozit* mutare(struct Depozit** vectorDepozite, int nr, int* nrDepoziteCopiate) {
	*nrDepoziteCopiate = 0;
	for (int i = 0; i < nr; i++) {
		if (conditie(*vectorDepozite[i])) {
			(*nrDepoziteCopiate)++;
		}
	}
	struct Depozit* vectorNou = (struct Depozit*)malloc(sizeof(struct Depozit) * (*nrDepoziteCopiate));
	int j = 0;
	for (int i = 0; i < nr; i++) {
		if (conditie(*vectorDepozite[i])) {
			vectorNou[j++] = initializareDepozit(vectorDepozite[i]->cod, vectorDepozite[i]->nume, vectorDepozite[i]->nrProduse, vectorDepozite[i]->preturi);
		}
	}
	int k = 0;
	for (int i = 0; i < nr; i++) {
		if (!conditie1(*vectorDepozite[i])) {
			*vectorDepozite[k++] = initializareDepozit(vectorNou[i].cod, vectorNou[i].nume, vectorNou[i].nrProduse, vectorNou[i].preturi);
		}
	}
	nr = k;
	return vectorNou;
}

struct Depozit* copie(struct Depozit* vectorDepozite, int nr, int* nrDepoziteCopiate) {
	*nrDepoziteCopiate = 0;
	for (int i = 0; i < nr; i++) {
		if (conditie(vectorDepozite[i])) {
			(*nrDepoziteCopiate)++;
		}
	}
	struct Depozit* vectorNou = (struct Depozit*)malloc(sizeof(struct Depozit) * (*nrDepoziteCopiate));
	int j = 0;
	for (int i = 0; i < nr; i++) {
		if (conditie(vectorDepozite[i])) {
			vectorNou[j++] = initializareDepozit(vectorDepozite[i].cod, vectorDepozite[i].nume, vectorDepozite[i].nrProduse, vectorDepozite[i].preturi);
		}
	}
	return vectorNou;
}

float sumaPreturi(struct Depozit d) {
	float suma = 0;
	for (int i = 0; i < d.nrProduse; i++) {
		suma = suma + d.preturi[i];
	}
	return suma;
}

void afisareVectorDepozit(struct Depozit* vectorDepozite, int nr) {
	for (int i = 0; i < nr; i++) {
		afiseazaDepozit(vectorDepozite[i]);
	}
}

int main() {
	float x[] = { 1,2 };
	struct Depozit depozit1 = initializareDepozit(1, "depo", 2, x);
	struct Depozit depozit2 = initializareDepozit(2, "dep", 2, x);
	struct Depozit depozit3 = initializareDepozit(3, "depozit", 2, x);
	struct Depozit depozit4 = initializareDepozit(4, "depozitare", 2, x);
	struct Depozit depozit5 = initializareDepozit(5, "depozitam", 2, x);
	int numarObiecte = 5;
	struct Depozit* vectorDepozite = malloc(numarObiecte * sizeof(struct Depozit));
	vectorDepozite[0] = depozit1;
	vectorDepozite[1] = depozit2;
	vectorDepozite[2] = depozit3;
	vectorDepozite[3] = depozit4;
	vectorDepozite[4] = depozit5;
	afisareVectorDepozit(vectorDepozite, 5);
	/*depozit1 = citesteDepozit();
	afiseazaDepozit(depozit1);
	float suma = sumaPreturi(depozit1);
	printf("Suma:%5.2f\n", suma);
	modificareCod(&depozit1, 2);
	afiseazaDepozit(depozit1);*/
	struct Depozit* vectorNou;
	int nrDepoziteCopiate = 0;
	vectorNou = copie(vectorDepozite, 5, &nrDepoziteCopiate);
	struct Depozit* vectorNou1;
	vectorNou1 = mutare(vectorDepozite, 5, &nrDepoziteCopiate);
	return 0;
}