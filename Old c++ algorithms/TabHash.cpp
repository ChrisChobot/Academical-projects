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

struct komorka {
	unsigned int dlugosc;
	char klucz[35];
	int kwota;
	komorka *next;
	komorka();
};

komorka::komorka() {
	next = 0;
	kwota = 0;
	dlugosc = 0;

}

struct tablica {
	komorka *pierwsza;
	komorka *ostatnia;
	void dodaj(char od[], char dokogo[], int kwota) {

		komorka *temp = pierwsza;
		int k = strlen(od) + strlen(dokogo);
		while (temp) {


			if (k == temp->dlugosc) {
				int j = 0;
				for (; j < 18 && od[j] != NULL; j++)
				{
					if (temp->klucz[j] != od[j]) { j = 40; break; }
				}
				for (int jj = 0; j<35 && dokogo[jj] != NULL; j++, jj++)
				{
					if (temp->klucz[j] != dokogo[jj]) { j = 45; break; }
				}
				if (j == temp->dlugosc) { temp->kwota += kwota; return; }
			}

			temp = temp->next;
		}


		komorka *nowy = new komorka;
		int i = 0;
		for (; i<18 && od[i] != NULL; i++)
		{
			nowy->klucz[i] = od[i];
		}
		for (int j = 0; i<35 && dokogo[j] != NULL; j++, i++)
		{
			nowy->klucz[i] = dokogo[j];
		}
		nowy->dlugosc = i;

		nowy->kwota = kwota;
		if (!pierwsza) { pierwsza = nowy; ostatnia = nowy; }            // sprawdzamy czy to pierwszy element listy
		else {                                            // w przeciwnym wypadku w?drujemy na koniec listy				
			ostatnia->next = nowy;
			ostatnia = nowy;
			ostatnia->next = NULL;
		}

	};

	void wyswietl(char od[], char dokogo[]) const
	{
		komorka *temp = pierwsza;
		int k = strlen(od) + strlen(dokogo);
		while (temp) {

			if (k == temp->dlugosc) {
				int j = 0;
				for (; j < 18 && od[j] != NULL; j++)
				{
					if (temp->klucz[j] != od[j]) { j = 40; break; }
				}
				for (int jj = 0; j<35 && dokogo[jj] != NULL; j++, jj++)
				{
					if (temp->klucz[j] != dokogo[jj]) { j = 45; break; }
				}
				if (j == temp->dlugosc) { cout << temp->kwota << '\n'; return; }
			}

			temp = temp->next;
		}
		cout << "0\n";
	}

	void usun(komorka *stary) {
		if (ostatnia == pierwsza) { ostatnia = NULL; pierwsza = NULL; delete stary; }
		else {
			komorka *temp = stary->next;
			delete stary;
			if (temp) { pierwsza = temp; usun(temp); }
			else { ostatnia = NULL; pierwsza = NULL; }
		}
	}
	tablica();
};

tablica::tablica() {
	pierwsza = 0;       // konstruktor
	ostatnia = 0;
}

int hashuj(char tab[], char tab2[])
{
	unsigned int wynik = 0;

	for (int j = 0; tab[j] != NULL; j++)
	{
		wynik = (wynik + 2 * tab[j] + tab2[j]) + 3 * tab2[j];
	}
	return wynik % 27;
}

int main()
{
	tablica *hash = new tablica[27];
	char metoda = NULL;
	char od[18] = { NULL };
	char dokogo[18] = { NULL };
	int ile = 0;

	while (cin >> metoda >> od >> dokogo)
	{
		if (metoda == '+')
		{
			cin >> ile;
			hash[hashuj(od, dokogo)].dodaj(od, dokogo, ile);
		}
		else
		{
			hash[hashuj(od, dokogo)].wyswietl(od, dokogo);
		}


		for (int i = 0; i < 18; i++) {
			od[i] = NULL; dokogo[i] = NULL;
		}
		ile = 0;
	}




	for (int j = 0; j<27; j++)
	{
		if (hash[j].pierwsza) { hash[j].usun(hash[j].pierwsza); }
	}
	return 0;
}

