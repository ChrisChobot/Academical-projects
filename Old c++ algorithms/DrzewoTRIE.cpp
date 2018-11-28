/*
Copyright 2017 Krzysztof Chobot

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/

#include "stdafx.h"
#include <iostream>

using namespace std;




struct tekst {

	char wartosc;
	int klucz;
	tekst *next;
	tekst();
};
tekst::tekst() {
	next = 0;
}

struct lista {
	tekst *pierwsza;
	tekst *ostatnia;
	lista *next;
	void dodaj(char wartosc,int klucz) {
		tekst *nowy = new tekst;



		nowy->wartosc = wartosc;
		nowy->klucz = klucz;
		if (pierwsza == 0 || pierwsza == NULL) { pierwsza = nowy; ostatnia = nowy; }            // sprawdzamy czy to pierwszy element listy
		else {                                            // w przeciwnym wypadku w?drujemy na koniec listy
			ostatnia->next = nowy;
			ostatnia = nowy;
		}

	};


	void wyswietl(tekst *temp) {
		if (temp != nullptr)
		{
			cout << temp->wartosc;
			temp = temp->next;
			wyswietl(temp);
		}
	};

	void zeruj() {
		if (pierwsza!= NULL) {
			tekst *temp;
			temp = pierwsza;
			pierwsza = temp->next;
			delete temp;
			zeruj();			
		}
	}
	int dlugosc_listy(tekst *temp,int dlugosc) {
		if (temp != nullptr) {
			if (temp->wartosc == ' ') {
				dlugosc++;
			}
			temp = temp->next;
			dlugosc_listy(temp, dlugosc);
			
		}
		else{ return dlugosc; }
	}

	lista();
};
lista::lista() {

	pierwsza = 0;      
	ostatnia = 0;
	next = 0;
}



struct listalist {
	lista *pierwsza;
	lista *ostatnia;

	void dodaj(char wartosc[], int klucz[]) {
		lista *nowy = new lista;
		for (int i = 0; wartosc[i] != NULL; i++) {
			nowy->dodaj(wartosc[i], klucz[i]);
		}	
		if (pierwsza == 0 || pierwsza == NULL) { pierwsza = nowy; ostatnia = nowy; }            // sprawdzamy czy to pierwszy element listy
		else {    // w przeciwnym wypadku w?drujemy na koniec listy
			ostatnia->next = nowy;
			ostatnia = nowy;
			ostatnia->next = 0;			
		}

	};
	void wyswietl() {
		lista*temp = pierwsza;
		while (temp->next) {
			temp->wyswietl(temp->pierwsza);
			cout << " ";
			temp = temp->next;
		}
		temp->wyswietl(temp->pierwsza);
	}
	void zeruj() {
		if (pierwsza != NULL) {
			lista *temp;
			temp = pierwsza;
			temp->zeruj();
			pierwsza = temp->next;
			delete temp;
			zeruj();
		}
	}

	int dlugosc() {
		lista*temp = pierwsza;
		int i = 1;
		for (; temp != nullptr; i++) { temp = temp->next; };
		return i;
	}
	listalist();
};
listalist::listalist() {
	pierwsza = 0;       // konstruktor
	ostatnia = 0;
}





lista* porownaj(lista *a, lista*b) {
	lista *wynik = NULL;
	if (a == NULL) { return b; }
	else if (b == NULL){return a;}
	
	tekst*tym = a->pierwsza;
	tekst*tymcz = b->pierwsza;
	bool zmiana = 0; //czy byla zmiana
	while (tym != nullptr&&tymcz != nullptr) { //porownanie kluczy w slowach
		if (tym->klucz > tymcz->klucz) {
			wynik = b;
			wynik->next = porownaj(a, b->next);
			zmiana = 1;
			break;
		}
		else if (tym->klucz < tymcz->klucz) {
			wynik = a;
			wynik->next = porownaj(a->next, b);

			zmiana = 1;
			break; 
		}
		tym = tym->next;
		tymcz = tymcz->next;
	}
	if (tym != nullptr&&tymcz == nullptr) {

		wynik = b;
		wynik->next = porownaj(a, b->next);
		zmiana = 1;
	}
	else if (zmiana==0) {
		wynik = a;
		wynik->next = porownaj(a->next, b);
	}


	return wynik;
}


void split(lista *jaka, lista **pocz, lista **koniec) {
	lista* kon;
	lista* polowa;
	if (jaka == NULL || jaka->next == NULL)
	{
		*pocz = jaka;
		*koniec = NULL;
	}
	else
	{
		polowa = jaka;
		kon = jaka->next;
		while (kon != NULL){
			kon = kon->next;
			if (kon != NULL)
			{
				polowa = polowa->next;
				kon = kon->next;
			}
		}
		*pocz = jaka;
		*koniec = polowa->next;
		polowa->next = NULL;
	}

}



void merdzszort(lista ** glowaref) {
	lista *glowa = *glowaref;
	lista *a;
	lista *b;
	if (glowa == NULL || glowa->next == NULL) { return; }
	split(glowa, &a, &b);
	merdzszort(&a);
	merdzszort(&b);
	*glowaref = porownaj(a, b);
}





struct drzewo
{
	drzewo * up;
	drzewo *next[26];
	int klucz;
	char litera;
	bool koniec;	
	drzewo();
};
drzewo::drzewo() {
	up = NULL;
	for (int i = 0; i < 26; i++) { next[i] = NULL; }
	koniec = false;
}




void wyczysc(drzewo *to)
{
	if(to)
	{
		for(int i=0;i<26;i++){
			if (to->next[i] != NULL) { wyczysc(to->next[i]); }
		}
			delete to;
	}
}

int atoii(int klucz[], int wynik) {  // sprawdzamy czy mala liczba
	for (int i = 0; i < 3 && klucz[i] != NULL; i++) {
		wynik *= 10;
		wynik += klucz[i];
	}
	return wynik;
}

void przypisz(drzewo*lisc, int klucz, char znak) {
	for (int i = 0; i < 26; i++) { lisc->next[i] = NULL; }  //może chyba być nieprzydatne
	lisc->klucz = klucz; 
	lisc->litera = znak;
}

void dodaj(drzewo *&root, int klucz[], char znak[])
{
	int dlugosc=0;//dlug-jak duzo znakow w tablicy, x-ktory znak
	drzewo *nowy;
	drzewo *korz;
	drzewo *poprzednia;
	
	for (int i = 0; znak[i] != NULL; i++) { dlugosc++; } // ostatnia litera
	
	if (root == NULL&&atoii(klucz,0) / 10 == 0) { nowy = new drzewo; przypisz(nowy, klucz[0], znak[0]); nowy->koniec = 1; root = nowy; return; }
	else if (root == NULL) {

		int k = 0;
		nowy = new drzewo;
		przypisz(nowy, klucz[k], znak[k]);
		root = new drzewo;
		nowy->up = root;

			root->next[nowy->litera-97] = nowy;

		korz = nowy;
	
		k++;
		while (k < dlugosc) {
			bool znalazlo = 0;
				if (korz->next[znak[k] - 97] != NULL) {
					if (korz->next[znak[k] - 97]->litera == znak[k]) {
						znalazlo = 1;
						korz = korz->next[znak[k] - 97];//przechodzimy o poziom nizej
						k++;
					}
				}

			if (znalazlo == 0) {
					if (korz->next[znak[k]-97] == NULL) {
					korz->next[znak[k]-97] = new drzewo;
					przypisz(korz->next[znak[k]-97], klucz[k], znak[k]);
						
					poprzednia = korz;
					korz = korz->next[znak[k]-97];
					k++;
					korz->up = poprzednia;
				}
			}
		}
		korz->koniec = 1;

	}
	else if(root!= NULL){
		korz = root;
		for (int k = 0; k < 100 && klucz[k] != NULL; k++) {

			while (k < dlugosc) {
				bool znalazlo = 0;
					if (korz->next[znak[k] - 97] != NULL) {
						if (korz->next[znak[k] - 97]->litera == znak[k]) {
							
							znalazlo = 1;
							korz = korz->next[znak[k] - 97];//przechodzimy o poziom nizej
							k++;
						}
					}

				if (znalazlo == 0) {
					if (korz->next[znak[k] - 97] == NULL) {
						korz->next[znak[k] - 97] = new drzewo;
						przypisz(korz->next[znak[k] - 97], klucz[k], znak[k]);
						poprzednia = korz;
						korz = korz->next[znak[k] - 97];
						k++;
						korz->up = poprzednia;
					}
				}
			}
		}
		korz->koniec = 1;
	}

}


int sprawdz_znak(char znak) {
		if (znak < 'd') { return 2; }
		else if (znak < 'g') { return 3; }
		else if (znak < 'j') { return 4; }
		else if (znak < 'm') { return 5; }
		else if (znak < 'p') { return 6; }
		else if (znak < 't') { return 7; }
		else if (znak < 'w') { return 8; }
		else { return 9; }
}





void podajwyraz(drzewo*lisc, int x, char wyraz[],char zdanie[]) { //gdy napotkamy jakis znak konca odpalamy ta funkcje, i lecimy do gory zapisujac spotkane litery
	wyraz[x] = lisc->litera;


	if (lisc->up->up!=NULL) {
		x++; 
		podajwyraz(lisc->up, x, wyraz,zdanie); 
	}
	else {
		int i = 0;
		
		for (; x >= 0; ) { //przypracamy poprawna kolejnosc znakow i wrzucamy wynik na liste
			zdanie[i] = wyraz[x];

			x--; 
			i++;
		}

	}

}


void przejzyj(drzewo *korz, listalist* wynik, int klucz[]) { //koniecq = koniec kolejki	
	int poziom = 0;
	drzewo *temp = korz;

	while (temp->up != NULL){
		temp = temp->up;
		poziom++;
	}

	for (int i = 0; i < 26; i++) {
		if (korz->next[i] != NULL) {
			if (klucz[poziom] == NULL) {
				przejzyj(korz->next[i], wynik, klucz);
				if (korz->next[i]->koniec == 1) {
					char zdanie[100] = { NULL };
					char wyraz[100] = { NULL };
					int kluczzdania[100] = { NULL };
					podajwyraz(korz->next[i], 0, wyraz, zdanie);
					for (int jj = 0; zdanie[jj] != NULL; jj++) { kluczzdania[jj] = sprawdz_znak(zdanie[jj]); }
					wynik->dodaj(zdanie, kluczzdania);

				}
			}
		
			else if (klucz[poziom] != NULL) {
				if(klucz[poziom] == korz->next[i]->klucz) {
					przejzyj(korz->next[i], wynik, klucz);
					if (korz->next[i]->koniec == 1) {
						int k = 0;
						for (; klucz[k] != NULL; k++); 
						if (poziom >= k-1) { //zabezpieczenie przed za długimi kluczami
						char wyraz[100] = { NULL };
						char zdanie[100] = { NULL };
						int kluczzdania[100] = { NULL };
						podajwyraz(korz->next[i], 0, wyraz, zdanie);
						for (int jj = 0; zdanie[jj] != NULL; jj++) { kluczzdania[jj] = sprawdz_znak(zdanie[jj]); }
						wynik->dodaj(zdanie, kluczzdania);

					}
					}
				}
			}
		}
	}
	


}

void sprawdz_klucz(char tab[], int wynik[]) {	
	for (int i = 0; tab[i] !=NULL && i < 100; i++) {		
		if (tab[i] < 'd') { wynik[i] = 2; }
		else if (tab[i] < 'g') { wynik[i] = 3; }
		else if (tab[i] < 'j') { wynik[i] = 4; }
		else if (tab[i] < 'm') { wynik[i] = 5; }
		else if (tab[i] < 'p') { wynik[i] = 6; }
		else if (tab[i] < 't') { wynik[i] = 7; }
		else if (tab[i] < 'w') { wynik[i] = 8; }
		else { wynik[i] = 9; }

	}
}

int main()
{
	drzewo * root =  NULL ; 
	listalist *wyniki = new listalist;
	int ilewynikow = 0;
	char wczyt[100] = { NULL };
	int klucz[100] = { NULL };
	fgets(wczyt, 100, stdin);
	int petla = atoi(wczyt);
	while (petla > 0) {
		petla--;
		for (int i = 0; i < 100; i++) { wczyt[i] = NULL; klucz[i] = NULL;}
		fgets(wczyt, 100, stdin);
		for (int y = 0; y < 100 && wczyt[y] != NULL; y++) {if (wczyt[y + 1] == NULL) {wczyt[y] = NULL;}} // usuwamy enter na koncu tablicy
		sprawdz_klucz(wczyt, klucz);
		dodaj(root, klucz, wczyt);
	}

	for (int i = 0; i < 100; i++) { wczyt[i] = NULL; }
	fgets(wczyt, 100, stdin);
	petla = atoi(wczyt);
	while (petla > 0) {
		petla--;
		for (int i = 0; i < 100; i++) { wczyt[i] = NULL; klucz[i] = NULL; }
		fgets(wczyt, 100, stdin);
		for (int y = 0; y < 100 && wczyt[y] != NULL; y++) { if (wczyt[y + 1] == NULL) { wczyt[y] = NULL; } } // usuwamy enter na koncu tablicy
		for (int i = 0; wczyt[i] != NULL && i < 100; i++) { klucz[i] = wczyt[i] - 48; }
		przejzyj(root, wyniki, klucz);
		if (wyniki->pierwsza == 0 || wyniki->pierwsza == NULL) { cout << "-\n"; }
		else {
			merdzszort(&wyniki->pierwsza);
			wyniki->wyswietl(); wyniki->zeruj();
			cout << " \n";
		}




	
}

	wyczysc(root);
	delete wyniki;
	return 0;
}
