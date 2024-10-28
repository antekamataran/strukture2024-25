

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MEMORY_NOT_ALLOCATED_CORRECT (-1)

struct _person;
typedef struct _person* position;

typedef struct _person {
	char name[MAX_LINE];
	char lastName[MAX_LINE];
	int birthYear;

	position next;
}person;



position CreateNewPerson(char* name, char* lastName, int birthYear);
int PrependList(position p, char* name, char* lastName, int birthYear);
int PrintList(position p);
position FindLast(position p);
int AppendList(position p, char* name, char* lastName, int birthYear);
position FindByLastName(position p, char* lastName);
int DeleteByLastName(position p, position toDelete);
position FindPrevious(position p, position q);
int DeleteList(position p);

int main(void) {

	char name[MAX_LINE] = { 0 };
	char lastName[MAX_LINE] = { 0 };
	int birthYear = 0;
	char lastNameDel[MAX_LINE] = { 0 };


	int choice;

	position temp = NULL;
	temp = (position)malloc(sizeof(person));

	if (temp == NULL) {
		printf("greska!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	position head = NULL;
	head = (position)malloc(sizeof(person));

	if (head == NULL) {
		printf("greska!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	position q = NULL;
	q = (position)malloc(sizeof(person));

	if (q == NULL) {
		printf("greska!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	strcpy(head->name, "");
	strcpy(head->lastName, "");
	head->birthYear = 0;
	head->next = NULL;

	while (1) {

		printf("\nizsberi sto zelis:\n");
		printf("1 - ubaci osobu na pocetak liste\n");
		printf("2 - ubaci osobu na kraj lsite\n");
		printf("3 -pronadi osobu sa doredenim prezimenom\n");
		printf("4 - izbrisi osobu sa doredenim prezimenom:\n");
		printf("5 - ispisi listu\n");
		printf("6 - izbrisi list\n");
		printf("7 - izlaz\n");
		printf("tvoj izbor: ");
		scanf(" %d", &choice);

		switch (choice)
		{
		case 1:
			printf("upisi ime ospbe koju zelis ubacit: ");
			scanf(" %s", name);
			printf("upisi prezime osobe koju zellsi ubacit: ");
			scanf(" %s", lastName);
			printf("upsii godinu rodenja osobe koju zelis ubaciti: ");
			scanf("%d", &birthYear);
			PrependList(head, name, lastName, birthYear);
			break;

		case 2:
			printf("upisi ime ospbe koju zelis ubacit:: ");
			scanf(" %s", name);
			printf("upisi prezime osobe koju zellsi ubacit: ");
			scanf(" %s", lastName);
			printf("upsii godinu rodenja osobe koju zelis ubaciti: ");
			scanf("%d", &birthYear);
			AppendList(head, name, lastName, birthYear);
			break;

		case 3:
			printf("upsi prezime osobe koju zelis pronaci ");
			scanf(" %s", lastName);
			temp = FindByLastName(head, lastName);
			printf("\nosoba koku si trazio je: %s %s, %d\n", temp->name, temp->lastName, temp->birthYear);
			break;

		case 4:
			printf("upsii prezijme osobe koju zelis izbrisati: ");
			scanf(" %s", lastNameDel);
			q = FindByLastName(head, lastNameDel);
			DeleteByLastName(head, q);
			break;

		case 5:
			PrintList(head->next);
			break;

		case 6:
			DeleteList(head);
			break;

		case 7:
			return EXIT_SUCCESS;
			break;
		}

	}


	return EXIT_SUCCESS;
}


position CreateNewPerson(char* name, char* lastName, int birthYear) {

	position newPerson = NULL;
	newPerson = (position)malloc(sizeof(person));

	if (newPerson == NULL)
	{
		printf("greska!\n");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->lastName, lastName);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}



int PrependList(position p, char* name, char* lastName, int birthYear) {

	position q = NULL;
	q = CreateNewPerson(name, lastName, birthYear);

	if (q == NULL) {
		printf("greska!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	q->next = p->next;
	p->next = q;

	return EXIT_SUCCESS;
}

int PrintList(position p) {

	if (p == NULL) {
		printf("greska!");
		return FILE_DIDNT_OPEN_ERROR;
	}

	else {
		while (p != NULL) {
			printf("%s\n", p->name);
			printf("%s\n", p->lastName);
			printf("%d\n", p->birthYear);

			p = p->next;
		}
		return EXIT_SUCCESS;
	}
}

position FindLast(position p) {

	while (p->next != NULL) {
		p = p->next;
	}

	return p;
}

int AppendList(position p, char* name, char* lastName, int birthYear) {
	position q = NULL;
	position last = NULL;

	q = CreateNewPerson(name, lastName, birthYear);

	if (q == NULL) {
		printf("greska!");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	last = FindLast(p);

	q->next = last->next;
	last->next = q;

	return EXIT_SUCCESS;
}


position FindByLastName(position p, char* lastName)
{
	while (p != NULL && strcmp(p->lastName, lastName) != 0)
	{
		p = p->next;
	}

	if (p == NULL) {
		printf("nema tog elementa u lsiti\n");
	}

	return p;
}

int DeleteByLastName(position p, position toDelete) {
	position temp = NULL;
	position prev = NULL;

	temp = (position)malloc(sizeof(person));
	prev = (position)malloc(sizeof(person));


	if (temp == NULL)
	{
		printf(greska!\n");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	if (prev == NULL)
	{
		printf("greska!\n");
		return MEMORY_NOT_ALLOCATED_CORRECT;
	}

	temp = toDelete;
	prev = FindPrevious(p, toDelete);

	prev->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

position FindPrevious(position p, position q) {

	position temp = p;

	while (temp != NULL && temp->next != q)
	{
		temp = temp->next;
	}

	return temp;

}

int DeleteList(position p) {
	position temp = p;

	while (temp->next != NULL)
	{
		temp = p->next;
		p->next = p->next->next;
		free(temp);
	}

	return EXIT_SUCCESS;
}