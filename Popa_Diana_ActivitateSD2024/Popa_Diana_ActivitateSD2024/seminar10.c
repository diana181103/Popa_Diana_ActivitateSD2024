#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct Rezervare Rezervare;
struct Rezervare {
	int id;
	char* numeClient;
	int nrPersoane;
};
typedef struct Nod Nod;
struct Nod {
	Nod* stanga;
	Nod* dreapta;
	Rezervare info;
};

Rezervare citireRezervare(FILE* f) {
	Rezervare r;
	char aux[30];
	fgets(aux, 30, f);
	fscanf(f, "%d", &r.id);
	fscanf(f, "%s", &aux);
	r.numeClient = malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(r.numeClient, aux);
	fscanf(f, "%d", &r.nrPersoane);
	return r;
}

Nod* inserareInArbore(Nod* arbore, Rezervare rez) {
	if (arbore != NULL) {
		if (arbore->info.id < rez.id) {
			arbore->dreapta = inserareInArbore(arbore->dreapta, rez);
		}
		else {
			arbore->stanga = inserareInArbore(arbore->stanga, rez);
		}
	}
	else {
		Nod* temp = (Nod*)malloc(sizeof(Nod));
		temp->info = rez;
		temp->dreapta = NULL;
		temp->stanga = NULL;

		arbore = temp;
	}
	return arbore;
}

void citireFisier(const char* numeFisier, Nod** radacina) {
	FILE* f = fopen(numeFisier, "r");
	int nrRezervari;
	fscanf(f, "%d", &nrRezervari);
	for (int i = 0; i < nrRezervari; i++) {
		Rezervare rez;
		rez = citireRezervare(f);
		*radacina = inserareInArbore(*radacina, rez);
	}
}

void afisareRezervare(Rezervare rez) {
	printf("Rezervarea  %d a fost facuta de %s pentru %d persoane\n", rez.id, rez.numeClient, rez.nrPersoane);
}

void afisareArborePreOrdine(Nod* arbore) {
	//RSD-PREORDINE
	//SDR-POSTORDINE
	//SRD-INORDINE
	if (arbore != NULL) {
		afisareRezervare(arbore->info);
		afisareArborePreOrdine(arbore->stanga);
		afisareArborePreOrdine(arbore->dreapta);
	}
}
void afisareArboreInOrdine(Nod* arbore) {
	if (arbore != NULL) {
		afisareArboreInOrdine(arbore->stanga);
		afisareRezervare(arbore->info);
		afisareArboreInOrdine(arbore->dreapta);
	}
}

void afisareArborePostOrdine(Nod* arbore) {
	if (arbore != NULL) {
		afisareArboreInOrdine(arbore->stanga);
		afisareArboreInOrdine(arbore->dreapta);
		afisareRezervare(arbore->info);
	}
}
Rezervare cautaRezervareDupaId(Nod* rad, int id) {
	if (rad != NULL) {
		if (rad->info.id < id) {
			return cautaRezervareDupaId(rad->dreapta, id);
		}
		else {
			if (rad->info.id > id) {
				return cautaRezervareDupaId(rad->stanga, id);
			}
			else {
				return rad->info;
			}
		}
	}
	else {
		Rezervare r;
		r.id = -1;
		r.numeClient = NULL;
		r.nrPersoane = -1;
		return r;
	}
}

int calculNrTotalPersoane(Nod* rad) {
	if (rad != NULL) {
		int rPersoane = rad->info.nrPersoane;
		int sPersoane = calculNrTotalPersoane(rad->stanga);
		int dPersoane = calculNrTotalPersoane(rad->dreapta);
		int suma = rPersoane + sPersoane + dPersoane;
		return suma;
	}
	else {
		return 0;
	}
}

void main() {
	Nod* radacina = NULL;
	citireFisier("Rezervari.txt", &radacina);
	printf("Preordine\n");
	afisareArborePreOrdine(radacina);
	printf("Inordine\n");
	afisareArboreInOrdine(radacina);
	printf("Postordine\n");
	afisareArborePostOrdine(radacina);
	printf("Cautare dupa id:\n");
	afisareRezervare(cautaRezervareDupaId(radacina, 8));
	int nrTotal = calculNrTotalPersoane(radacina);
	printf("Nr persoane :%d", nrTotal);
}