#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Autobuz Autobuz;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct Autobuz {
	int linie;
	char* capatLinie;
};

struct NodPrincipal {
	Autobuz info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	NodPrincipal* nod;
	NodSecundar* next;
};

Autobuz initializareAutobuz(int linie, const char* capat) {
	Autobuz a;
	a.linie = linie;
	a.capatLinie = (char*)malloc(strlen(capat) + 1);
	strcpy(a.capatLinie, capat);
	return a;
}



void inserareListaPrincipala(NodPrincipal** graf, Autobuz a) {
	NodPrincipal* nod = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nod->info = a;
	nod->next = NULL;
	nod->vecini = NULL;
	if (*graf != NULL) {
		NodPrincipal* aux = (*graf);
		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nod;
	}
	else {
		(*graf) = nod;
	}
}



NodPrincipal* cautaLinie(NodPrincipal* graf, int linie) {
	while (graf && graf->info.linie != linie) {
		graf = graf->next;
	}
	return graf;
}

NodSecundar* inserareListaSecundara(NodSecundar* cap, NodPrincipal* info) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->next = NULL;
	nou->nod = info;
	if (cap) {
		NodSecundar* p = cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}


void inserareMuchie(NodPrincipal* graf, int linieStart, int linieStop) {
	NodPrincipal* nodStart = cautaLinie(graf, linieStart);
	NodPrincipal* nodStop = cautaLinie(graf, linieStop);
	nodStart->vecini = inserareListaSecundara(nodStart->vecini, nodStop);
	nodStop->vecini = inserareListaSecundara(nodStop->vecini, nodStart);

}

int getNrNoduri(NodPrincipal* graf) {
	int s = 0;
	while (graf) {
		s++;
		graf = graf->next;
	}
	return s;
}

//parcurgerea in latime
//se face cu coada -> FIFO
//pt parc in adancime se face cu stiva -> LIFO
#pragma region Coada

typedef struct nodCoada NodCoada;
struct nodCoada
{
	int id;
	NodCoada* next;
};

void inserareCoada(NodCoada** cap, int id) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->id = id;
	nou->next = NULL;
	if (*cap) {
		NodCoada* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

void inserareStiva(NodCoada** cap, int id) {
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->id = id;
	nou->next = *cap;
	*cap = nou;
}


int extragereDinCoada(NodCoada** cap) {
	if (*cap) {
		int rezultat = (*cap)->id;
		NodCoada* temp = (*cap)->next;
		free(*cap);
		*cap = temp;
		return rezultat;
	}
	else {
		return -1;
	}
}

int extrageStiva(NodCoada** cap) {
	return extragereDinCoada(*cap);
}

#pragma endregion

void afisareAutobuz(Autobuz a) {
	printf("%d. Are capatul la %s\n", a.linie, a.capatLinie);
}

void afisareCuParcurgereInLatime(NodPrincipal* graf, int nodPlecare) {

	NodCoada* coada = NULL;
	int nrNoduri = getNrNoduri(graf);
	char* vizitate = (char*)malloc(sizeof(char) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	inserareCoada(&coada, nodPlecare);
	vizitate[nodPlecare] = 1;

	while (coada) {
		
		int idnNodCurent = extragereDinCoada(&coada);
		NodPrincipal* nodCurent = cautaLinie(graf, idnNodCurent);
		afisareAutobuz(nodCurent->info);

		
		NodSecundar* temp = nodCurent->vecini;
		while (temp) {
			if (vizitate[temp->nod->info.linie] == 0) {
				vizitate[temp->nod->info.linie] = 1;
				inserareCoada(&coada, temp->nod->info.linie);
			}
			temp = temp->next;
		}
	}

	if (vizitate) {
		free(vizitate);
	}

}

void afisareCuParcurgereInAdancime(NodPrincipal* graf, int nodPlecare) {

	NodCoada* stiva = NULL;
	int nrNoduri = getNrNoduri(graf);
	char* vizitate = (char*)malloc(sizeof(char) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++) {
		vizitate[i] = 0;
	}
	inserareStiva(&stiva, nodPlecare);
	vizitate[nodPlecare] = 1;

	while (stiva) {
	
		int idnNodCurent = extragereDinCoada(&stiva);
		NodPrincipal* nodCurent = cautaLinie(graf, idnNodCurent);
		afisareAutobuz(nodCurent->info);


		NodSecundar* temp = nodCurent->vecini;
		while (temp) {
			if (vizitate[temp->nod->info.linie] == 0) {
				vizitate[temp->nod->info.linie] = 1;
				inserareStiva(&stiva, temp->nod->info.linie);
			}
			temp = temp->next;
		}
	}
	if (vizitate) {
		free(vizitate);
	}
}

void stergereListaVecini(NodSecundar** cap) {
	NodSecundar* p = (*cap);
	while (p) {
		NodSecundar* aux = p;
		p = p->next;
		free(aux);
	}
	*cap = NULL;
}

void stergereGraf(NodPrincipal** graf) {
	while (*graf) {
		free((*graf)->info.capatLinie);
		stergereListaVecini(&((*graf)->vecini)); 
		NodPrincipal* temp = (*graf);
		*graf = temp->next;
		free(temp);
	}
}

void main() {
	NodPrincipal* graf = NULL;
	inserareListaPrincipala(&graf, initializareAutobuz(0, "Romana"));
	inserareListaPrincipala(&graf, initializareAutobuz(1, "Universitate"));
	inserareListaPrincipala(&graf, initializareAutobuz(2, "Unirii"));
	inserareListaPrincipala(&graf, initializareAutobuz(3, "Victoriei"));
	inserareListaPrincipala(&graf, initializareAutobuz(4, "Militari"));


	inserareMuchie(graf, 0, 4);
	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 3, 4);
	inserareMuchie(graf, 2, 4);


	afisareCuParcurgereInLatime(graf, 0);
	printf("\n\n");
	afisareCuParcurgereInAdancime(graf, 0);

	stergereGraf(&graf);
}