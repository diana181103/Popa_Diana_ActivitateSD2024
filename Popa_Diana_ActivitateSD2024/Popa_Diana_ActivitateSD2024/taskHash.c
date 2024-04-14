
//7. Implementati o functie care modifica anul construirii unei cladiri identificate prin ID.Functia 
//primeste ca parametri : id - ul cladirii, vechiul an de constructie si noul an de constructie.Aveti grija
//se modifica valoarea atributului folosit pentru clusterizare.

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
typedef struct Cladire Cladire;
typedef struct Nod Nod;
typedef struct Hash Hash;

struct Cladire {
	int id;
	int anConstruire;
	char* nume;
};

struct Nod {
	Cladire cladire;
	Nod* next;
};
struct Hash {
	Nod** vector;
	int dim;
};

int clusterizare(int dim, int anConstruire) {
	if (dim > 0) {
		return anConstruire % dim;
	}
	return -1;
}

Hash initializareHash(int dim) {
	Hash h;
	h.dim = dim;
	h.vector = (Nod**)malloc(sizeof(Nod*) * dim);
	for (int i = 0; i < dim; i++) {
		h.vector[i] = NULL;
	}
	return h;
}

Cladire initializareCladire(int id, int anConstruire, const char* nume) {
	Cladire c;
	c.id = id;
	c.anConstruire = anConstruire;
	c.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(c.nume, nume);
	return c;
}

void inserareLaFinal(Nod** lista, Cladire c) {
	if ((*lista) != NULL) {
		Nod* aux = (*lista);
		while (aux->next != NULL) {
			aux = aux->next;
		}
		Nod* temp = (Nod*)malloc(sizeof(Nod));
		temp->next = NULL;
		temp->cladire = c;
		aux->next = temp;
	}
	else {
		(*lista) = malloc(sizeof(Nod));
		(*lista)->next = NULL;
		(*lista)->cladire = c;
	}
}
void inserareCladireInTabela(Hash h, Cladire c) {
	if (h.dim > 0) {
		int pozitie = clusterizare(h.dim, c.anConstruire);
		if (h.vector[pozitie] != NULL) {
			inserareLaFinal(&(h.vector[pozitie]), c);
		}
		else {
			inserareLaFinal(&(h.vector[pozitie]), c);
		}
	}
}
void afisareCladire(Cladire c) {
	printf("%d: In anul %d a fost construita cladire %s\n", c.id, c.anConstruire, c.nume);
}
void afisareListaCladiri(Nod* cap) {
	while (cap) {
		afisareCladire(cap->cladire);
		cap = cap->next;
	}
}
void afisareHash(Hash h) {
	for (int i = 0; i < h.dim; i++) {
		printf("Clusterul: %d\n", (i + 1));
		afisareListaCladiri(h.vector[i]);
	}
}


void afisareCladiriParam(Hash h, int an)
{
	int pozitie = clusterizare(h.dim, an);
	afisareListaCladiri(h.vector[pozitie]);
}

void stergereCladire(Hash* h, int anConstruire, int id) {
	int pozitie = clusterizare(h->dim, anConstruire);
	if (pozitie > 0 && pozitie < h->dim) {
		Nod* anterior = NULL;
		Nod* curent = h->vector[pozitie];
		while (curent != NULL) {
			if (anConstruire == curent->cladire.anConstruire && id == curent->cladire.id) {
				if (anterior == NULL) {
					h->vector[pozitie] = curent->next;
				}
				else {
					anterior->next = curent->next;
				}
				free(curent->cladire.nume);
				free(curent);
				return;
			}
			else {
				anterior = curent;
				curent = curent->next;
			}
		}
	}
}
void stergereCladireId(Hash* h, int id) {
	int anConstruire = 0;
	for (int i = 0; i < h->dim; i++) {
		Nod* nou = h->vector[i];
		while (nou != NULL) {
			if (nou->cladire.id == id) {
				anConstruire = nou->cladire.anConstruire;
				break;
			}
			nou = nou->next;
		}
	}
	int pozitie = clusterizare(h->dim, anConstruire);
	if (pozitie > 0 && pozitie < h->dim) {
		Nod* anterior = NULL;
		Nod* curent = h->vector[pozitie];
		while (curent != NULL) {
			if (anConstruire == curent->cladire.anConstruire && id == curent->cladire.id) {
				if (anterior == NULL) {
					h->vector[pozitie] = curent->next;
				}
				else {
					anterior->next = curent->next;
				}
				free(curent->cladire.nume);
				free(curent);
				return;
			}
			else {
				anterior = curent;
				curent = curent->next;
			}
		}
	}
}



//6. Implementati o functie care salveaza intr - un vector toate  cladirile dintr - un an primit 
// //ca parametru.Realizati deep copy, astfel incat elementele din vector sa fie diferentiate de cele 
// //din tabela de dispersie.Aveti grija la alocarea de spatiu, deoarece trebuie sa stabiliti pentru 
// //cate elemente veti aloca spatiu.
Cladire* toVector(Hash h, int an, int* nr) {
	*nr = 0;
	int pozitie = clusterizare(h.dim, an);
	Nod* curent = h.vector[pozitie];
	while (curent != NULL) {
		*nr = (*nr) + 1;
		curent = curent->next;
	}
	Cladire* vector = (Cladire*)malloc(sizeof(Cladire) * (*nr));
	curent = h.vector[pozitie];
	int i = 0;
	while (curent != NULL) {
		vector[i] = initializareCladire(curent->cladire.id, curent->cladire.anConstruire, curent->cladire.nume);
		i++;
		curent = curent->next;
	}
	return vector;
}

//7. Implementati o functie care modifica anul construirii unei cladiri identificate prin ID.Functia 
//primeste ca parametri : id - ul cladirii, vechiul an de constructie si noul an de constructie.Aveti grija
//se modifica valoarea atributului folosit pentru clusterizare.

void ModificareCladireId(Hash* h, int id, int anNou) {
	int anConstruire = 0;
	for (int i = 0; i < h->dim; i++) {
		Nod* nou = h->vector[i];
		while (nou != NULL) {
			if (nou->cladire.id == id) {
				anConstruire = nou->cladire.anConstruire;
				break;
			}
			nou = nou->next;
		}
	}
	int pozitie = clusterizare(h->dim, anConstruire);
	if (pozitie > 0 && pozitie < h->dim) {
		Nod* anterior = NULL;
		Nod* curent = h->vector[pozitie];
		while (curent != NULL) {
			if (anConstruire == curent->cladire.anConstruire && id == curent->cladire.id) {
				curent->cladire.anConstruire = anNou;
				int pozitieNoua = clusterizare(h->dim, anNou);
				inserareCladireInTabela(*h, curent->cladire);
				if (anterior == NULL) {
					h->vector[pozitie] = curent->next;
				}
				else {
					anterior->next = curent->next;
				}
				free(curent->cladire.nume);
				free(curent);
				return;
			}
			else {
				anterior = curent;
				curent = curent->next;
			}
		}
	}
}
int main() {
	Cladire c = initializareCladire(1, 2000, "Cladire1");
	Cladire c1 = initializareCladire(2, 2000, "Cladire2");
	Cladire c2 = initializareCladire(3, 2002, "Cladire3");
	Hash h = initializareHash(3);
	inserareCladireInTabela(h, c);
	inserareCladireInTabela(h, c1);
	inserareCladireInTabela(h, c2);
	afisareHash(h);
	afisareCladiriParam(h, 2000);
	/*stergereCladire(&h, 2000, 1);
	afisareHash(h);
	stergereCladireId(&h, 2);
	afisareHash(h);*/
	printf("vector:\n");
	int nr = 0;
	Cladire* vector = toVector(h, 2000, &nr);
	for (int i = 0; i < nr; i++) {
		afisareCladire(vector[i]);
	}
	ModificareCladireId(&h, 1, 2002);
	afisareHash(h);

}