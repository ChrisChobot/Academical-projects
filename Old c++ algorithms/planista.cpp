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
#include <conio.h>
#include <fstream>
using namespace std;

struct tekst {
	int id;
	tekst *next;
	tekst();
};

tekst::tekst() {
	next = 0;
}

struct lista {
	tekst *pierwsza;
	tekst *ostatnia;
	void dodaj(int id) {
		tekst *nowy = new tekst;
		nowy->id = id;
		if (pierwsza == 0 || pierwsza == NULL) { pierwsza = nowy; ostatnia = nowy; }           
		else {                                            			
			ostatnia->next = nowy;
			ostatnia = nowy;
			ostatnia->next = pierwsza; //cyklicznosc listy
		}
	};

	void wyswietl(tekst *temp) {		
		if (temp)
		{
			cout << temp->id << " ";
			temp = temp->next;
			if (temp != pierwsza) { wyswietl(temp); }
		}
	};
	void usun(tekst *stary, tekst *poprzednia) {
		if (ostatnia == pierwsza) { ostatnia = NULL; pierwsza = NULL; delete stary; }
		else {
			if (pierwsza == stary) { pierwsza = stary->next; }
			if (ostatnia == stary) { ostatnia = poprzednia; }
			poprzednia->next = stary->next;
			delete stary;
		}
	}
lista();
};

lista::lista() {
	pierwsza = 0;      
	ostatnia = 0;
}


bool przeszukaj_i_usun(int id, lista listy[]) { //jesli false nie znaleziono, jesli true usunieto
	tekst *pocz = listy->pierwsza;
	tekst *poprzednia= listy->ostatnia;
		if (pocz) {
			do {
				if (pocz->id == id) 
				{ 
					listy->usun(pocz,poprzednia); 
					return true; 
				}
				else 
				{
					if (pocz->next) {
					poprzednia = pocz;
					pocz = pocz->next; }
				}
			} while (pocz != listy->pierwsza);					
		}
		return false;
}



int main()
{
	char wczyt[100000];
	lista *glowna[3];
	for (int k = 0; k < 3; k++) { glowna[k] = new lista;  };
	int pior;//0,1,2
	int id;
	while (fgets(wczyt, 100000, stdin) != NULL) {
		char metoda;
		int i = 0; //ktory wczytany znak
		metoda = wczyt[i];
		i++;
		if(wczyt[i+1] != NULL){ 
			i++;  //przeskakujemy spacje, jeśli jest
			char bufor[100] = {NULL};
			for (int k = 0; wczyt[i] != ' ' && wczyt[i] != NULL; k++) {
				bufor[k] = wczyt[i];
				i++;
			};
			 id = atoi(bufor);// = wczyt[i] -48;			
		}
		if (wczyt[i+1] != NULL) {
			i++;  //przeskakujemy spacje, jeśli jest
			if (wczyt[i] != 45) { pior = wczyt[i] - 48 + 1; } //jesli nie ma minusa
			else { i++; pior = wczyt[i] - 49;}
		}
		switch (metoda)
		{
		case 'n':				
			for (int k = 2, koniec = 0,wszystko=0; (k > -1)&& (koniec==0);wszystko++,k--){
			if(glowna[k]->pierwsza)			{
				cout << glowna[k]->pierwsza->id << "\n";
				
				if (glowna[k]->pierwsza != glowna[k]->ostatnia) {
					tekst *temp = glowna[k]->pierwsza;
					glowna[k]->pierwsza = glowna[k]->pierwsza->next;
					glowna[k]->ostatnia = temp;
				}
				koniec = 1;			
			}
			if ((wszystko == 2) && (koniec == 0)) { cout << "idle\n"; }
			}
			break;
		case 'c': glowna[pior]->dodaj(id);
			break;
		case 't':for (int k = 2; (k>-1)&&(przeszukaj_i_usun(id, glowna[k]) != true); k--) {}
			break;
		case 'p':
			for (int k = 2; (k>-1) && (przeszukaj_i_usun(id, glowna[k]) != true); k--) {}
			glowna[pior]->dodaj(id);
			break;
		case 'l':for(int k = 2; k>-1; k--) 
			{
			cout << k - 1 <<": ";
			glowna[k]->wyswietl(glowna[k]->pierwsza);
			cout << "\n";
			}
			break;
		default:
			break;
		}
	}
	

	
    return 0;
}

