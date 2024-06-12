#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "header.h"

const char* imeDatoteke = "Skladiste.txt";

RACUNALO* dodavanjeNovogRacunala(RACUNALO* prvoRacunalo) {		// funkcija za dodavanje novog racunala
	int (*pokazivacNaMaxID)(RACUNALO*);							//deklaracija pokazivaca na funkciju
	pokazivacNaMaxID = maxID;									//inicijalizacija
	int duljinaImenaKomponente = 100;
	RACUNALO* iduceRacunalo = (RACUNALO*)calloc(1, sizeof(RACUNALO));
	if (iduceRacunalo == NULL) {
		perror("Kreiranje racunala");
		return prvoRacunalo;
	}
	else {													// dinamicko zauzimanje memorije za svaku komponentu 
		iduceRacunalo->procesor = (char*)calloc(duljinaImenaKomponente, sizeof(char));
		iduceRacunalo->graficka = (char*)calloc(duljinaImenaKomponente, sizeof(char));
		iduceRacunalo->maticna = (char*)calloc(duljinaImenaKomponente, sizeof(char));
		iduceRacunalo->pohrana = (char*)calloc(duljinaImenaKomponente, sizeof(char));
		iduceRacunalo->ram = (char*)calloc(duljinaImenaKomponente, sizeof(char));
		iduceRacunalo->napajanje = (char*)calloc(duljinaImenaKomponente, sizeof(char));
		if (iduceRacunalo->graficka == NULL || iduceRacunalo->procesor == NULL || iduceRacunalo->pohrana == NULL || iduceRacunalo->maticna == NULL || iduceRacunalo->ram == NULL || iduceRacunalo->napajanje == NULL ) {
			perror("Pogreska pri zauzimanju memorije za racunalo");
			oslobadjanjeMemorije(iduceRacunalo);
			return prvoRacunalo;
		}
		if (prvoRacunalo == NULL) iduceRacunalo->ID = 100;		// ako je racunalo koje unosimo prvo u popisu onda mu je ID 100 
		else iduceRacunalo->ID = pokazivacNaMaxID(prvoRacunalo)+1;			// svaki iduci ID je za 1 veci od trenutnog najveceg
		printf("Unesite podatke o racunalu:\n");
		printf("Procesor: ");
		fgets(iduceRacunalo->procesor, duljinaImenaKomponente, stdin);					// unosenje imena komponente do 100 znakova
		iduceRacunalo->procesor[strcspn(iduceRacunalo->procesor, "\n")] = '\0';			// brisanje \n na kraju stringa
		printf("Graficka: ");
		fgets(iduceRacunalo->graficka, duljinaImenaKomponente, stdin);
		iduceRacunalo->graficka[strcspn(iduceRacunalo->graficka, "\n")] = '\0';
		printf("RAM: ");
		fgets(iduceRacunalo->ram, duljinaImenaKomponente, stdin);
		iduceRacunalo->ram[strcspn(iduceRacunalo->ram, "\n")] = '\0';
		printf("Maticna: ");
		fgets(iduceRacunalo->maticna, duljinaImenaKomponente, stdin);
		iduceRacunalo->maticna[strcspn(iduceRacunalo->maticna, "\n")] = '\0';
		printf("Pohrana: ");
		fgets(iduceRacunalo->pohrana, duljinaImenaKomponente, stdin);
		iduceRacunalo->pohrana[strcspn(iduceRacunalo->pohrana, "\n")] = '\0';
		printf("Napajanje: ");
		fgets(iduceRacunalo->napajanje, duljinaImenaKomponente, stdin);
		iduceRacunalo->napajanje[strcspn(iduceRacunalo->napajanje, "\n")] = '\0';
		printf("Cijena: ");
		scanf("%f", &iduceRacunalo->cijena);
		getchar();
		iduceRacunalo->next = prvoRacunalo;
		ispisRacunalaUDatoteku(iduceRacunalo);				// ispis unesenog racunala u datoteku
	}
	return iduceRacunalo;
}

void ispisRacunalaUDatoteku(RACUNALO *trenutnoRacunalo) {		//funkcija koja pri svakom unosenju novog racunala ga ispisuje u datoteku
	FILE* fp = fopen(imeDatoteke, "a+");
	if (fp == NULL) {
		perror("Pogreska pri zapisivanju u datoteku");
		return;
	}
	fprintf(fp, "Racunalo %d\n\tProcesor: %s\n\tGraficka: %s\n\tMaticna: %s\n\tPohrana: %s\n\tRAM: %s \n\tNapajanje: %s \n\tCijena: %f eura\n", trenutnoRacunalo->ID, trenutnoRacunalo->procesor, trenutnoRacunalo->graficka,
		trenutnoRacunalo->maticna, trenutnoRacunalo->pohrana, trenutnoRacunalo->ram, trenutnoRacunalo->napajanje, trenutnoRacunalo->cijena);
	rewind(fp);
	fclose(fp);
}

void ispisRacunalaUKonzolu(){		// funkcija koja ispisuje sadrzaj datoteke u konzolu
	FILE* fp = fopen(imeDatoteke, "r");
	if (fp == NULL) {
		perror("Pogreska pri citanju datoteke");
		return;
	}
	char c;
	while ((c = fgetc(fp)) != EOF) {
		putchar(c);
	}
	fclose(fp);
}


void izbornik() {			//glavni izbornik koji se cijelo vrijeme poziva dok ne unesemo "6" da izadjemo
	static int izlaz = 1;
	IzbornikOpcija izbornikOpcija;
	RACUNALO* prvoRacunalo = ucitajRacunalaIzDatoteke();

	while (izlaz) {
		printf("1. Unesite novo racunalo\n");
		printf("2. Pregledajte skladiste\n");
		printf("3. Sortirajte skladiste\n");
		printf("4. Brisanje skladista\n");
		printf("5. Brisanje racunala po ID\n");
		printf("6. Izadjite iz izbornika\n");

		char unos[10]; 
		fgets(unos, sizeof(unos), stdin); 
		int opcija;
		if (sscanf(unos, "%d", &opcija) == 1) {
			izbornikOpcija = (IzbornikOpcija)opcija;
			switch (izbornikOpcija) {
			case UNOS_NOVOG_RACUNALA:
				prvoRacunalo = dodavanjeNovogRacunala(prvoRacunalo);
				break;
			case PREGLED_SKLADISTA:
				ispisRacunalaUKonzolu();
				break;
			case SORTIRANJE_SKLADISTA:
				sortiranjeListe(prvoRacunalo);
				break;
			case BRISANJE_SKLADISTA:
				prvoRacunalo = brisanjeSkladista(prvoRacunalo);
				break;
			case BRISANJE_RACUNALA_PO_ID:
				brisanjeRacunalaPoID(&prvoRacunalo);
				ponovnoZapisivanjeDatoteke(prvoRacunalo);
				break;
			case IZLAZ:
				izlaz = 0;
				break;
			default:
				printf("Krivi unos\n");
				break;
			}
		}
		else {
			printf("Niste unijeli valjani broj.\n");
		}
	}
	oslobadjanjeMemorijeSvega(prvoRacunalo);
}


void sortiranjeListe(RACUNALO* prvoRacunalo) {		// funckija za sortiranje liste pomocu bubble sorta
	if (prvoRacunalo == NULL) return;

	OpcijeSortiranja opcijeSortiranja;
	int zamjenjen;
	RACUNALO* ptr1;
	RACUNALO* lptr = NULL;

	printf("1: Sortiranje po cijeni\n2: Sortiranje po ID\n");
	char unos[10];
	fgets(unos, sizeof(unos), stdin);

	int opcija;
	if (sscanf(unos, "%d", &opcija) != 1) {
		printf("Krivi unos\n");
		return;
	}

	opcijeSortiranja = (OpcijeSortiranja)opcija;

	switch (opcijeSortiranja) {
	case SORTIRANJE_PO_CIJENI:		// opcija 1 sortiranje po cijeni
		do {
			zamjenjen = 0;
			ptr1 = prvoRacunalo;

			while (ptr1->next != lptr) {
				if (ptr1->cijena > ptr1->next->cijena) {
					zamjena(ptr1, ptr1->next);
					zamjenjen = 1;
				}
				ptr1 = ptr1->next;
			}
			lptr = ptr1;
		} while (zamjenjen);
		break;

	case SORTIRANJE_PO_ID:			// opcija 2 sortiranje po ID
		do {
			zamjenjen = 0;
			ptr1 = prvoRacunalo;

			while (ptr1->next != lptr) {
				if (ptr1->ID > ptr1->next->ID) {
					zamjena(ptr1, ptr1->next);
					zamjenjen = 1;
				}
				ptr1 = ptr1->next;
			}
			lptr = ptr1;
		} while (zamjenjen);
		break;

	default:
		printf("Krivi izbor\n");
		return;
	}

	ponovnoZapisivanjeDatoteke(prvoRacunalo);		// ponovno zapisivanje sortirane liste
}


void zamjena(RACUNALO* a, RACUNALO* b) {		// funkcija koju pozivamo kada sortiramo listu da zamjenimo racunala
	char* tempProcesor = a->procesor;
	char* tempGraficka = a->graficka;
	char* tempMaticna = a->maticna;
	char* tempPohrana = a->pohrana;
	char* tempRam = a->ram;
	char* tempNapajanje = a->napajanje;
	float tempCijena = a->cijena;
	int tempID = a->ID;

	a->procesor = b->procesor;
	a->graficka = b->graficka;
	a->maticna = b->maticna;
	a->pohrana = b->pohrana;
	a->ram = b->ram;
	a->napajanje = b->napajanje;
	a->cijena = b->cijena;
	a->ID = b->ID;

	b->procesor = tempProcesor;
	b->graficka = tempGraficka;
	b->maticna = tempMaticna;
	b->pohrana = tempPohrana;
	b->ram = tempRam;
	b->napajanje = tempNapajanje;
	b->cijena = tempCijena;
	b->ID = tempID;
}

RACUNALO* brisanjeSkladista(RACUNALO* prvoRacunalo) {		//funkcija koja brise cijelo skladiste (cijelu listu i datoteku u koju zapisujemo) te oslobadja memoriju pomocu posebne funkcije
	if (remove(imeDatoteke) != 0) {
		perror("Pogreska pri brisanju datoteke");
	}
	RACUNALO* brisanje = NULL;
	while (prvoRacunalo) {
		brisanje = prvoRacunalo;
		prvoRacunalo = prvoRacunalo->next;
		printf("Obrisano racunalo: %d\n", brisanje->ID);
		oslobadjanjeMemorije(brisanje);
	}
	return NULL;
}

void brisanjeRacunalaPoID(RACUNALO** prvoRacunalo) {		// funkcija koja brise racunalo koje ima ID koji smo upisali
	int trazeniID;
	printf("Unesite ID racunala koje zelite obrisati: ");
	scanf("%d", &trazeniID);
	getchar();

	RACUNALO* trazenoRacunalo = trazenjeRacunalaPoID(*prvoRacunalo, trazeniID);

	if (trazenoRacunalo == NULL) {
		printf("Racunalo s ID %d nije pronadeno.\n", trazeniID);
		return;
	}

	if (*prvoRacunalo == trazenoRacunalo) {
		*prvoRacunalo = (*prvoRacunalo)->next;
	}
	else {
		RACUNALO* trenutnoRacunalo = *prvoRacunalo;
		while (trenutnoRacunalo->next && trenutnoRacunalo->next != trazenoRacunalo) {
			trenutnoRacunalo = trenutnoRacunalo->next;
		}
		if (trenutnoRacunalo->next) {
			trenutnoRacunalo->next = trazenoRacunalo->next;
		}
	}

	printf("Obrisano racunalo: %d\n", trazenoRacunalo->ID);
	oslobadjanjeMemorije(trazenoRacunalo);
}

RACUNALO* trazenjeRacunalaPoID(RACUNALO* prvoRacunalo,const int ID) {			//funkcija koja prolazi kroz popis dok ne pronadje racunalo s ID-em koji smo proslijedili funkciji
	while (prvoRacunalo) {
		if (prvoRacunalo->ID == ID) {
			return prvoRacunalo;
		}
		else {
			prvoRacunalo = prvoRacunalo->next;
		}
	}
	return NULL;

}

void oslobadjanjeMemorijeSvega(RACUNALO* trenutnoRacunalo) {		//funkcija koju pozivamo na kraju izvodjenja programa koja oslobadja svu memoriju
	RACUNALO* temp;
	while (trenutnoRacunalo != NULL) {
		temp = trenutnoRacunalo;
		trenutnoRacunalo = trenutnoRacunalo->next;
		free(temp->procesor);
		free(temp->graficka);
		free(temp->maticna);
		free(temp->pohrana);
		free(temp->ram);
		free(temp->napajanje);
		free(temp);
	}
}

inline void oslobadjanjeMemorije(RACUNALO* trenutnoRacunalo){			//funkcija za oslobadjanje memorije koju pozivamo pri brisanju racunala
	if (trenutnoRacunalo) {
		free(trenutnoRacunalo->procesor);
		free(trenutnoRacunalo->graficka);
		free(trenutnoRacunalo->maticna);
		free(trenutnoRacunalo->pohrana);
		free(trenutnoRacunalo->ram);
		free(trenutnoRacunalo->napajanje);
		free(trenutnoRacunalo);
	}
}

inline int maxID(RACUNALO* trenutnoRacunalo) {			//funkcija koju pozivamo svaki put kad unosimo novo racunalo da nam je novi ID uvijek za 1 veci od najveceg u popisu
	int max = 0;
	while (trenutnoRacunalo != NULL) {
		if (trenutnoRacunalo->ID > max) max = trenutnoRacunalo->ID;
		trenutnoRacunalo = trenutnoRacunalo->next;
	}
	return max;
}
void zapisiRacunaloRekurzivno(FILE* fp, RACUNALO* racunalo) {		// rekurzivno zapisivanje racunala u datoteku
	if (racunalo == NULL) {
		return;
	}
	fprintf(fp, "Racunalo %d\n\tProcesor: %s\n\tGraficka: %s\n\tMaticna: %s\n\tPohrana: %s\n\tRAM: %s \n\tNapajanje: %s \n\tCijena: %f eura\n",
		racunalo->ID, racunalo->procesor, racunalo->graficka,
		racunalo->maticna, racunalo->pohrana, racunalo->ram,
		racunalo->napajanje, racunalo->cijena);
	zapisiRacunaloRekurzivno(fp, racunalo->next);
}

void ponovnoZapisivanjeDatoteke(RACUNALO* prvoRacunalo) {		//pomocna funkcija za rekurzivno zapisivanje racunala u datoteku 
	FILE* fp = fopen(imeDatoteke, "w");
	if (fp == NULL) {
		perror("Pogreska pri otvaranju datoteke");
		return;
	}
	zapisiRacunaloRekurzivno(fp, prvoRacunalo);
	fclose(fp);
}


RACUNALO* ucitajRacunalaIzDatoteke() {		//ucitava prethodna upisana racunala iz datoteke "skladiste.txt" i sprema ih u povezani popis
	FILE* fp = fopen(imeDatoteke, "r");
	if (fp == NULL) {
		perror("Pogreska pri citanju datoteke");
		return NULL;
	}

	RACUNALO* prvoRacunalo = NULL;
	RACUNALO* trenutnoRacunalo = NULL;

	char line[256];
	while (fgets(line, sizeof(line), fp)) {
		if (strncmp(line, "Racunalo", 8) == 0) {
			RACUNALO* novoRacunalo = (RACUNALO*)calloc(1, sizeof(RACUNALO));
			if (novoRacunalo == NULL) {
				perror("Pogreska pri zauzimanju memorije za racunalo");
				fclose(fp);
				return prvoRacunalo;
			}

			novoRacunalo->procesor = (char*)calloc(100, sizeof(char));
			novoRacunalo->graficka = (char*)calloc(100, sizeof(char));
			novoRacunalo->maticna = (char*)calloc(100, sizeof(char));
			novoRacunalo->pohrana = (char*)calloc(100, sizeof(char));
			novoRacunalo->ram = (char*)calloc(100, sizeof(char));
			novoRacunalo->napajanje = (char*)calloc(100, sizeof(char));

			sscanf(line, "Racunalo %d", &novoRacunalo->ID);
			fgets(line, sizeof(line), fp); sscanf(line, "\tProcesor: %99[^\n]", novoRacunalo->procesor);
			fgets(line, sizeof(line), fp); sscanf(line, "\tGraficka: %99[^\n]", novoRacunalo->graficka);
			fgets(line, sizeof(line), fp); sscanf(line, "\tMaticna: %99[^\n]", novoRacunalo->maticna);
			fgets(line, sizeof(line), fp); sscanf(line, "\tPohrana: %99[^\n]", novoRacunalo->pohrana);
			fgets(line, sizeof(line), fp); sscanf(line, "\tRAM: %99[^\n]", novoRacunalo->ram);
			fgets(line, sizeof(line), fp); sscanf(line, "\tNapajanje: %99[^\n]", novoRacunalo->napajanje);
			fgets(line, sizeof(line), fp); sscanf(line, "\tCijena: %f", &novoRacunalo->cijena);

			if (prvoRacunalo == NULL) {
				prvoRacunalo = novoRacunalo;
			}
			else {
				trenutnoRacunalo->next = novoRacunalo;
			}
			trenutnoRacunalo = novoRacunalo;
		}
	}

	fclose(fp);
	return prvoRacunalo;
}