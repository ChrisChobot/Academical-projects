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
#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable : 4996)  

typedef struct wierzcholek
{
	int  ilosc;
	char kolor;
	char klucz[1000];
	struct wierzcholek* gora;
	struct wierzcholek *lewo;
	struct wierzcholek *prawo;
}wierzcholek;



typedef struct drzewo
{
	wierzcholek * korzen;
	wierzcholek straznik;	
}drzewo;

struct wierzcholek *nowy(char klucz[], int ile, drzewo *wieza)
{
	wierzcholek *p;
	if ((p = (wierzcholek*)malloc(sizeof *p)) != NULL) {
		p->gora= &wieza->straznik;
		p->lewo = &wieza->straznik;
		p->prawo = &wieza->straznik;
		int i = 0;
		for(; i<1000 && klucz[i];i++){ p->klucz[i] = klucz[i]; }
		for (; i<1000; i++) { p->klucz[i] = '\0'; }
		p->ilosc = ile;
		p->kolor = 'R';
	}
	return p;
}
struct drzewo *nowe()
{
	drzewo *neww = (drzewo*)malloc(sizeof(*neww));
	neww->straznik.kolor = 'B';
	neww->straznik.gora = &neww->straznik;
	neww->straznik.lewo = &neww->straznik;
	neww->straznik.prawo = &neww->straznik;
	neww->korzen = &neww->straznik;
	return neww;
}


void wlewo(drzewo *wieza, wierzcholek *obecny)
{
	wierzcholek *y = obecny->prawo;
		obecny->prawo = y->lewo;
		if (y->lewo != &wieza->straznik) { y->lewo->gora = obecny; }

		y->gora = obecny->gora;

		if (obecny->gora == &wieza->straznik)
		{
			wieza->korzen = y;
		}
		else if (obecny == obecny->gora->lewo)
		{
			obecny->gora->lewo = y;
		}
		else
		{
			obecny->gora->prawo = y;
		}

		y->lewo = obecny;
		obecny->gora = y;
}


void wprawo(drzewo *wieza, wierzcholek *obecny)
{
	wierzcholek *y = obecny->lewo;

	obecny->lewo = y->prawo;
	if (y->prawo != &wieza->straznik) { y->prawo->gora = obecny; }

	 y->gora = obecny->gora; 

	if (obecny->gora == &wieza->straznik)
	{
		wieza->korzen = y;
	}
	else if (obecny == obecny->gora->prawo)
	{
		obecny->gora->prawo = y;
	}
	else
	{
		obecny->gora->lewo = y;
	}

	y->prawo = obecny;
	obecny->gora = y;
}

void naprawdodaj(drzewo *wieza, wierzcholek *obecny)
{
	wierzcholek *y = &wieza->straznik;
	while(obecny->gora->kolor=='R' && obecny != wieza->korzen){
		if (obecny->gora == obecny->gora->gora->lewo ) {
			y = obecny->gora->gora->prawo;
			if (y->kolor == 'R')
			{
				obecny->gora->kolor = 'B';
				y->kolor = 'B';
				obecny->gora->gora->kolor = 'R'; 
				obecny = obecny->gora->gora;
			}
			else {
				if (obecny == obecny->gora->prawo)
				{
					obecny = obecny->gora;
					wlewo(wieza, obecny);
				}
				obecny->gora->kolor = 'B';
				obecny->gora->gora->kolor = 'R';
				wprawo(wieza, obecny->gora->gora);
			}		
		}
		else
		{
			y = obecny->gora->gora->lewo;
			if (y->kolor == 'R')
			{
				obecny->gora->kolor = 'B';
				y->kolor = 'B';
				obecny->gora->gora->kolor = 'R';
				obecny = obecny->gora->gora;
			}
			else {
				if (obecny == obecny->gora->lewo)
				{
					obecny = obecny->gora;
					wprawo(wieza, obecny);
				}
				obecny->gora->kolor = 'B';
				obecny->gora->gora->kolor = 'R';
				wlewo(wieza, obecny->gora->gora);
			}
		}
		wieza->straznik.kolor = 'B';
	}
	wieza->korzen->kolor = 'B';
	
}


wierzcholek *minimum(drzewo *wieza, wierzcholek *obecny)
{
	if (obecny == &wieza->straznik) { return obecny; }
	wierzcholek *y = obecny;
	while (y->lewo != &wieza->straznik) { y = y->lewo; }
	return y;
}

wierzcholek *nastepnik(drzewo *wieza, wierzcholek *obecny)
{
	wierzcholek *y = obecny; //current
	wierzcholek *x = &wieza->straznik; // gora
	if (y->prawo != &wieza->straznik) { x = minimum(wieza, y->prawo); return x; }
	x = y->gora;
	while (x != &wieza->straznik&& y == x->prawo)
	{
		y = x;
		x = x->gora;
	}
	return x;
}
void kopiuj(wierzcholek *od, wierzcholek *cel)
{
	for (int i = 0; i<1000; i++)
	{
		cel->klucz[i] = od->klucz[i];
	}
	cel->ilosc = od->ilosc;

}



void naprawusun(drzewo *wieza, wierzcholek *obecny)
{
	wierzcholek *y = &wieza->straznik;
	obecny->kolor = 'B'; //przejscie czarnego koloru w gore (podwojnie czarny)
	while(obecny!=wieza->korzen && obecny != &wieza->straznik && obecny->kolor=='B'){ 
		if(obecny==obecny->gora->lewo)   
		{
			y = obecny->gora->prawo;
			if(y->kolor=='R')
			{
				y->kolor = 'B';
				obecny->gora->kolor = 'R';
				wlewo(wieza, obecny->gora);
				y = obecny->gora->prawo;
			}
			if(y->lewo->kolor=='B' && y->prawo->kolor == 'B') 
			{
				y->kolor = 'R';
				obecny = obecny->gora;
			}
			else
			{
				if(y->prawo->kolor=='B')
				{
					y->lewo->kolor = 'B';
					y->kolor = 'R';
					wprawo(wieza,y);
					y = obecny->gora->prawo;
				}				
				y->kolor = obecny->gora->kolor;
				obecny->gora->kolor = 'B';
				y->prawo->kolor = 'B';
				wlewo(wieza, obecny->gora);
				obecny = wieza->korzen;
				}
		}
		else
		{
			y = obecny->gora->lewo;
			if (y->kolor == 'R')
			{
				y->kolor = 'B';
				obecny->gora->kolor = 'R';
				wprawo(wieza, obecny->gora);
				y = obecny->gora->lewo;
			}
			if (y->lewo->kolor == 'B' && y->prawo->kolor == 'B')
			{
				y->kolor = 'R';
				obecny = obecny->gora;
			}
			else
			{
					if (y->lewo->kolor == 'B')
					{
						y->prawo->kolor = 'B';
						y->kolor = 'R';
						wlewo(wieza, y);
						y = obecny->gora->lewo;
					}
					y->kolor = obecny->gora->kolor;
					obecny->gora->kolor = 'B';
					y->lewo->kolor = 'B';
					wprawo(wieza, obecny->gora);
					obecny = wieza->korzen;
			}			
		}
		wieza->straznik.kolor = 'B';
	}
	obecny->kolor = 'B';
}





int porownaj(char a, char b)
{
	// 0 = identyczne,  1=a>b,  2=a<b,  3=takie same zwiekszamy ilosc
	if (a == '\0' && b == '\0') { return 3; }
	else if (a == b) { return 0; }
	else if (a == '\0' && b != '\0') { return 1; }
	else if(a != '\0' && b == '\0') { return 2; }
	else if (a < b) { return 1; }
	else if (a > b) { return 2; }


	return 0; // nie nastąpi
}


void dodaj(drzewo *wieza,wierzcholek *obecny) 
{
	
	wierzcholek *y = &wieza->straznik;
	wierzcholek *x = wieza->korzen;
	while(x!=&wieza->straznik)
	{
		y = x;
		int i = 0;
		for (; i < 1000 && porownaj(obecny->klucz[i], x->klucz[i]) == 0; i++);
		switch (porownaj(obecny->klucz[i], x->klucz[i]))
		{
		case 1: 
			x = x->lewo;
			break;
		case 2: 
			x = x->prawo;
			break;
		default: // gdy 0(koniec tablicy) lub 3,  NIE POWINNO NIGDY NASTAPIC
			return;
		}
	}
	obecny->gora = y;
	if(y== &wieza->straznik) 
	{
		wieza->korzen = obecny;
		obecny->kolor = 'B';
		return;
	}
	else
	{
		int i = 0;
		for (; i < 1000 && porownaj(obecny->klucz[i], y->klucz[i]) == 0; i++);
		if (porownaj(obecny->klucz[i], y->klucz[i]) == 1)
		{
			y->lewo = obecny;
		}
		else
		{
			y->prawo = obecny;
		}
	}
	obecny->kolor = 'R';
	naprawdodaj(wieza, obecny);
}



void usun(drzewo *wieza, wierzcholek *obecny)
{
	wierzcholek *y = &wieza->straznik; // usuwany
	wierzcholek *x = &wieza->straznik; // potomek
	if (obecny->lewo == &wieza->straznik || obecny->prawo == &wieza->straznik) { y = obecny; }
	else { y = nastepnik(wieza, obecny); }

	if (y->lewo != &wieza->straznik) { x = y->lewo; }
	else { x = y->prawo; }

	if (x != &wieza->straznik) {
		x->gora = y->gora;///
	}

	if (y->gora == &wieza->straznik) { wieza->korzen = x; }
	else if (y == y->gora->lewo)
	{
		  y->gora->lewo = x; 
		
	}
	else { y->gora->prawo = x; }

	if (y!=obecny) { kopiuj(y, obecny); }

	char kol = y->kolor;
	if(x == &wieza->straznik){ x = nastepnik(wieza, obecny); }
	free(y);

	if(kol =='B'){naprawusun(wieza, x);}
	
}

wierzcholek* szukaj(drzewo *wieza,wierzcholek *korzen, char klucz[]) 
{
	wierzcholek *obecny = korzen;

	
	int wynik = 4;
	while (obecny!= &wieza->straznik && wynik!=0 && wynik!=3 )
	{
		int i = 0;
		for (; i < 1000 && porownaj(obecny->klucz[i], klucz[i]) == 0; i++);
		wynik = porownaj(obecny->klucz[i], klucz[i]);
		switch (wynik)
		{
		case 1:
			obecny = obecny->prawo;
			break;
		case 2:

			obecny = obecny->lewo;
			break;
		default: // gdy 0(koniec tablicy) lub 3
			return obecny;
	}		
	}

	return obecny;

}

void inorder(drzewo *wieza, wierzcholek*korzen)
{
	if (korzen != &wieza->straznik)
	{
		inorder(wieza, korzen->lewo);
		printf("%s %d\n", korzen->klucz, korzen->ilosc);
		inorder(wieza, korzen->prawo);
	}
}
int specjalnieporownaj(char a, char b)
{
	// 0 = identyczne,  1=a>b,  2=a<b,  3=takie same zwiekszamy ilosc
	if (a == '\0' && b == '\0') { return 3; }
	else if (a == b) { return 0; }
	else if (a == '\0' && b != '\0') { return 1; }
	else if (a != '\0' && b == '\0') { return 3; }
	else if (a < b) { return 1; }
	else if (a > b) { return 2; }


	return 0; // nie nastąpi
}
void prefinorder(drzewo *wieza, wierzcholek*korzen, char klucz[])
{
	if (korzen != &wieza->straznik)
	{
		prefinorder(wieza, korzen->lewo, klucz);
		int i = 0;
		for (; i < 1000 && specjalnieporownaj(korzen->klucz[i], klucz[i]) == 0; i++);
		if (specjalnieporownaj(korzen->klucz[i], klucz[i]) == 3) {printf("%s %d\n", korzen->klucz, korzen->ilosc);}
		prefinorder(wieza, korzen->prawo, klucz);
	}
}
void pref(drzewo *wieza, char klucz[])
{
	wierzcholek *obecny = wieza->korzen;


	int wynik = 4;
	while (obecny != &wieza->straznik && wynik != 0 && wynik != 3)
	{
		int i = 0;
		for (; i < 1000 && porownaj(obecny->klucz[i], klucz[i]) == 0; i++);
		wynik = porownaj(obecny->klucz[i], klucz[i]);
		switch (wynik)
		{
		case 1:
			obecny = obecny->prawo;
			break;
		case 2:
			obecny = obecny->lewo;
			break;
		default: // gdy 0(koniec tablicy) lub 3
			prefinorder(wieza, obecny->lewo, klucz);
			return;
		}
	}




}


void drzeworder(drzewo *wieza, wierzcholek*korzen)
{
	printf("(");
	if (korzen != &wieza->straznik)
	{	
		printf(" ");
		drzeworder(wieza, korzen->lewo);
		printf("%c %s %d ", korzen->kolor, korzen->klucz, korzen->ilosc);
		drzeworder(wieza, korzen->prawo);
	}
	printf(") ");
}


void usunorder(drzewo *wieza, wierzcholek*korzen)
{
	if (korzen != &wieza->straznik)
	{
		usunorder(wieza, korzen->lewo);
		usunorder(wieza, korzen->prawo);
		free(korzen);
	}
}


int main()
{
	struct drzewo *wieza = nowe();


	char komenda[20];
	char seria[1000];
	char seria2[1000];
	for (int i = 0; i < 1000; i++) { seria2[i] = '\0'; }
	for (int i = 0; i < 20; i++) { komenda[i] = '\0'; }
	for (int i = 0; i < 1000; i++) { seria[i] = '\0'; }
	int ile = 0;
	wierzcholek *pomoc = &wieza->straznik;


	while(scanf("%s", komenda)!= EOF)
	{
		switch (komenda[0])
		{
		case 'K'://kup
			scanf("%s %d", seria, &ile);
			if (wieza->korzen != &wieza->straznik)
			{
				pomoc = szukaj(wieza, wieza->korzen, seria);
			}
			if (pomoc == &wieza->straznik) { dodaj(wieza, nowy(seria, ile, wieza)); }
			else { pomoc->ilosc += ile; }

			for (int i = 0; i < 1000; i++) { seria[i] = '\0'; }
			ile = 0;
			break;


		case 'I'://ile
			scanf("%s", seria);
			pomoc = szukaj(wieza, wieza->korzen, seria);
			if (pomoc != &wieza->straznik) { printf("%d\n",pomoc->ilosc); }
			else{ printf("0\n"); }

			for (int i = 0; i < 1000; i++) { seria[i] = '\0'; }
			break;


		case 'S'://sprzedaj
			scanf("%s %d", seria, &ile);
			pomoc = szukaj(wieza, wieza->korzen, seria);
			if(pomoc == &wieza->straznik){ printf("strazak\n"); } // nie powinno nigdy nastąpić
			if (ile > pomoc->ilosc)
			{
				printf("BLAD\n");
			}
			else if (ile == pomoc->ilosc) { usun(wieza, pomoc); }
			else { pomoc->ilosc -= ile; }

			for (int i = 0; i < 1000; i++) { seria[i] = '\0'; }
			break;


		case 'W':
			if(komenda[2]=='P'&&komenda[6]=='\0')//wypisz
			{
				inorder(wieza, wieza->korzen);
			}
			else if(komenda[2] == 'P')//wypisztylko
			{
				scanf("%s", seria);
				prefinorder(wieza, wieza->korzen, seria);
				for (int i = 0; i < 1000; i++) { seria[i] = '\0'; }
			}
			else if (komenda[2] == 'M')//wymien
			{		
				scanf("%s %s", seria, seria2);
				pomoc = szukaj(wieza, wieza->korzen, seria);
				if(pomoc == &wieza->straznik)
				{
					printf("BLAD\n");
				}
				else{
					pomoc->ilosc--;
					if (pomoc->ilosc <= 0) { usun(wieza, pomoc); }
					pomoc = szukaj(wieza, wieza->korzen, seria2);		
					if (pomoc == &wieza->straznik) { dodaj(wieza, nowy(seria2, 1, wieza)); }			
					else { pomoc->ilosc++; }
				}
				for (int i = 0; i < 1000; i++) { seria[i] = '\0'; }
				for (int i = 0; i < 1000; i++) { seria2[i] = '\0'; }
			}
			break;


		case 'D':
			drzeworder(wieza, wieza->korzen);
			printf("\n");
			break;

		}


		for (int i = 0; i < 20; i++) { komenda[i] = '\0'; }		
		pomoc = &wieza->straznik; //teoretycznie nie potrzebne
	}
	
	usunorder(wieza, wieza->korzen);
	free(wieza);
	return 0;
}