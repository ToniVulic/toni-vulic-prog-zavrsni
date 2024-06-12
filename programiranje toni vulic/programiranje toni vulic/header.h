#ifndef HEADER_H
#define HEADER_H

extern const char* imeDatoteke;

typedef enum {
	UNOS_NOVOG_RACUNALA = 1,
	PREGLED_SKLADISTA,
	SORTIRANJE_SKLADISTA,
	BRISANJE_SKLADISTA,
	BRISANJE_RACUNALA_PO_ID,
	IZLAZ
} IzbornikOpcija;

typedef enum {
	SORTIRANJE_PO_CIJENI = 1,
	SORTIRANJE_PO_ID
} OpcijeSortiranja;

typedef struct skladiste {		// struktura koja sadrzi komponente racunala i cijenu te adresu iduceg racunala jer radimo s povezanim popisom
	char* procesor;
	char* graficka;
	char* maticna;
	char* pohrana;
	char* ram;
	char* napajanje;
	float cijena;
	int ID;
	struct skladiste* next;
}RACUNALO;

RACUNALO* dodavanjeNovogRacunala(RACUNALO*);
void ispisRacunalaUDatoteku(RACUNALO*);
void ispisRacunalaUKonzolu();
void izbornik();
void sortiranjeListe(RACUNALO* );
void zamjena(RACUNALO*, RACUNALO*);
RACUNALO* brisanjeSkladista(RACUNALO*);
void brisanjeRacunalaPoID(RACUNALO**);
inline void oslobadjanjeMemorije(RACUNALO* );
void oslobadjanjeMemorijeSvega(RACUNALO* );
RACUNALO* trazenjeRacunalaPoID(RACUNALO* , int );
inline int maxID(RACUNALO*);
void ponovnoZapisivanjeDatoteke(RACUNALO*);
void zapisiRacunaloRekurzivno(FILE* , RACUNALO* );
void ispisivanjeSvega(RACUNALO* );
RACUNALO* ucitajRacunalaIzDatoteke();

#endif

//1. Odabir konkretnih primitivnih tipova podataka za rad s cjelobrojnim i realnim konstantama.				DA
//2. Odabir konkretnih složenih tipova podataka za rad sa specifičnim objektima.							DA	
//3. Primjena typedef sa strukturama i unijama, po potrebi s enum tipovima podataka tamo gdje				DA
//treba.
//4. Imenovanje identifikatora(varijabli, konstanti, polja, funkcija, pokazivača…) – upotreba				DA
//camelCase, PascalCase i snake_case konzistento kroz cijeli projekt.
//5. Primjena ključne riječi static za globalne i lokalne varijable.										DA					
//6. Organizacija izvornog kôda.																			DA
//7. Primjena extern ključne riječi za globalne varijable.													DA
//8. Ako su funkcije jednostavne koristiti makro funkcije ili inline funkcije.								DA
//9. Izbornik / podizbornici.																				DA
//10. Generalno upotreba pokazivača tamo gdje su potrebni.													DA
//11. Generalno upotreba struktura i funkcija.																DA
//12. Zaštita parametara kod svih funkcija.																	DA
//13. Koristiti statički zauzeta polja gdje su potrebna, nikako ne koristiti VLA polja.						DA
//14. Koristiti dinamičko zauzimanje memorije za bilo koji tip podatka, osobito za složene tipove			DA
//podataka.
//15. Koristiti funkcije malloc(), calloc(), realloc(), free() – neku od njih, ako ne i sve.				DA
//16. Sigurno brisanje memorije koja je dinamički zauzeta, anuliranje memorijskog prostora, provjera		DA
//pokazivača kako se ne bi dogodila pogreška double free() i anuliranje svih pokazivača koji su bili
//usmjereni na memorijski prostor koji se dinamički zauzeo.
//17. Datoteke, koristiti tekstualnu ili binarnu, provjera pokazivača i zatvaranje datoteke.				DA
//18. Koristiti funkcije fseek(), ftell(), rewind(), ovisno o potrebi – neku od njih ako ne sve.			DA
//19. Koristiti funkcije remove(), rename(), po potrebi implementirati funkciju za kopiranje datoteka.		DA
//20. Upravljati s pogreškama, errno, perror(), strerror(), feof(), ferror() – neku od njih ako ne sve.		DA
//21. Sortiranje – preporuka koristiti ugrađenu qsort() funkciju.											DA
//22. Pretraživanje – preporuka koristiti ugrađenu bsearch() funkciju.										DA
//23. Rekurzije je najlakše koristiti primjenom rekurzivnih algoritama sortiranja kao što su quick sort,	DA
//merge sort, insert sort ili pretraživanja kao što je binary search.
//24. Pokazivače na funkcije je najlakše koristiti upotrebom funkcije qsort() ili bsearch() iz standardne	DA
//biblioteke.
