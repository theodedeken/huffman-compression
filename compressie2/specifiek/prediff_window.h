#pragma once
#ifndef PREDIF_WINDOW
#define PREDIF_WINDOW

#define G 16
/*
* struct om verschil voor te stellen met predictie.
* a: extra term om verschil zo klein mogelijk te maken
* bytes: aantal bytes van het verschil
* neg: moet het verschil opgeteld of afgetrokken worden
* differenct: verschil
*/
typedef struct {
	unsigned int a;
	unsigned int bytes;
	unsigned int neg;
	unsigned long long difference;
} Match;

/*
* struct voor het venster dat de predictie mogelijk maakt, het houdt de laatste G getallen bij.
* window_buffer: de laatste G getallen
* length: grootte van het venster
* pointer: wijzer naar het laatste getal van het venster
*/
typedef struct {
	unsigned long long* window_buffer;
	int length;
	int pointer;
} PDWindow;

/*
* Aanmaken van een venster met de eerste twee getallen van de reeks direct ingevuld.
*/
PDWindow* window_create(unsigned long long first,unsigned long long second);

/*
* Zoek de beste match om het verschil naar het volgende getal voor te stellen. Er wordt
* gezocht naar één van de vorige getallen in het venster waar voor het verschil met het laatste getal in het venster
* de beste predictie geeft naar het volgende getal, zo kan het verschil soms met minder bits voorgesteld worden.
*/
Match* window_search_match(PDWindow* window, unsigned long long next);

/*
* Reconstrueer het volgende getal in de reeks aan de hand van het verschil met predictie.
*/
unsigned long long window_retrieve_match(PDWindow* window, Match* match);

/*
* Geef het geheugen vrij van het venster
*/
void window_free(PDWindow* window);

/*
* Vul het venster aan met het volgende getal in de reeks.
*/
void window_add(PDWindow* window, unsigned long long next);

/*
* Geef het aantal bytes terug dat het getal l minimaal inneemt.
*/
int long_num_bytes(unsigned long long l);

#endif