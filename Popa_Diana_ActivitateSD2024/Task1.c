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

float sumaPreturi(struct Depozit d) {
	float suma = 0;
	for (int i = 0; i < d.nrProduse; i++) {
		suma = suma + d.preturi[i];
	}
	return suma;
}

int main() {
	struct Depozit depozit1;
	depozit1 = citesteDepozit();
	afiseazaDepozit(depozit1);
	float suma = sumaPreturi(depozit1);
	printf("Suma:%5.2f\n", suma);
	modificareCod(&depozit1, 2);
	afiseazaDepozit(depozit1);
	return 0;
}