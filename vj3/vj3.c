#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Osoba {
	char ime[50];
	char prezime[50];
	int godina_rodjenja;
	struct Osoba* next;
} Osoba;

void dodajIza(Osoba* prev, const char* ime, const char* prezime, int godina_rodjenja) {
	if (prev == NULL) return;

	Osoba* novaOsoba = (Osoba*)malloc(sizeof(Osoba));
	strcpy(novaOsoba->ime, ime);
	strcpy(novaOsoba->prezime, prezime);
	novaOsoba->godina_rodjenja = godina_rodjenja;
	novaOsoba->next = prev->next;
	prev->next = novaOsoba;
}

void dodajIspred(Osoba** head, Osoba* next, const char* ime, const char* prezime, int godina_rodjenja) {
	Osoba* novaOsoba = (Osoba*)malloc(sizeof(Osoba));
	strcpy(novaOsoba->ime, ime);
	strcpy(novaOsoba->prezime, prezime);
	novaOsoba->godina_rodjenja = godina_rodjenja;

	if (*head == NULL || *head == next) {
		novaOsoba->next = *head;
		*head = novaOsoba;
		return;
	}

	Osoba* temp = *head;
	while (temp->next && temp->next != next) {
		temp = temp->next;
	}

	if (temp->next == next) {
		novaOsoba->next = temp->next;
		temp->next = novaOsoba;
	}
}

void sortiraListu(Osoba* head) {
	if (head == NULL) return;

	Osoba* i;
	Osoba* j;
	Osoba* temp;

	for (i = head; i != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if (strcmp(i->prezime, j->prezime) > 0) {

				char tempIme[50], tempPrezime[50];
				int tempGodina;

				strcpy(tempIme, i->ime);
				strcpy(tempPrezime, i->prezime);
				tempGodina = i->godina_rodjenja;

				strcpy(i->ime, j->ime);
				strcpy(i->prezime, j->prezime);
				i->godina_rodjenja = j->godina_rodjenja;

				strcpy(j->ime, tempIme);
				strcpy(j->prezime, tempPrezime);
				j->godina_rodjenja = tempGodina;
			}
		}
	}
}
void upisiUDatoteku(Osoba* head, const char* filename) {
	FILE* file = fopen(filename, "w");
	if (!file) return;

	Osoba* temp = head;
	while (temp != NULL) {
		fprintf(file, "%s %s %d\n", temp->ime, temp->prezime, temp->godina_rodjenja);
		temp = temp->next;
	}

	fclose(file);
}

Osoba* citajIzDatoteke(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (!file) return NULL;

	Osoba* head = NULL;
	Osoba* tail = NULL;

	while (!feof(file)) {
		Osoba* novaOsoba = (Osoba*)malloc(sizeof(Osoba));
		if (fscanf(file, "%49s %49s %d", novaOsoba->ime, novaOsoba->prezime, &novaOsoba->godina_rodjenja) != 3) {
			free(novaOsoba);
			break;
		}
		novaOsoba->next = NULL;

		if (head == NULL) {
			head = novaOsoba;
			tail = novaOsoba;
		}
		else {
			tail->next = novaOsoba;
			tail = novaOsoba;
		}
	}

	fclose(file);
	return head;
}

void ispisiListu(Osoba* head) {
	Osoba* temp = head;
	while (temp != NULL) {
		printf("%s %s %d\n", temp->ime, temp->prezime, temp->godina_rodjenja);
		temp = temp->next;
	}
}

int main() {
	Osoba* lista = NULL;

	dodajIspred(&lista, NULL, "Marko", "Marković", 1990);
	dodajIza(lista, "Ana", "Anić", 1985);
	dodajIza(lista, lista, "Ivana", "Ivić", 1992);

	sortiraListu(lista);

	printf("Lista osoba:\n");
	ispisiListu(lista);

	upisiUDatoteku(lista, "osobe.txt");

	Osoba* novaLista = citajIzDatoteke("osobe.txt");
	printf("\nLista osoba iz datoteke:\n");
	ispisiListu(novaLista);

	return 0;
}