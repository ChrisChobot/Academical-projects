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

struct wierzcholek
{
	wierzcholek * next;
	int gdzie, waga;
	wierzcholek();
};
wierzcholek::wierzcholek()
{
	next = NULL;
	gdzie = NULL;
	waga = NULL;
}

void usun(wierzcholek *glowa)
{
	if (glowa) {
		wierzcholek * temp = glowa;
		if (temp->next != nullptr) { usun(temp->next); }
		delete temp;
	}
}

int porownaj(char wyraz[])
{
	int m = strlen(wyraz);
	int k = 0;
	int *pi = new int[m+1];
	pi[0] = 0;
	pi[1] = 0;
	for (int q=2;q<m+1;q++)
	{
		while(k>0 && wyraz[k]!=wyraz[q-1])
		{
			k = pi[k];
		}
		if (wyraz[k] == wyraz[q-1])	{k = k + 1;	}  //if z pseudokodu cormena
		pi[q] = k;
	}

	k = pi[m];
	delete[] pi;
	return k;

}

char* polacz(char wyraz1[], char wyraz2[],char wynik[])

{
	int x = strlen(wyraz1);
	int y = strlen(wyraz2);
	int i = 0;
	for (;i<y;i++)
	{
		wynik[i] = wyraz2[i];
	}
	wynik[i] = '#';
	i++;
	for (int j=0; j<x; i++,j++)
	{
		wynik[i] = wyraz1[j];
	};
	return wynik;
}
void inicjalizuj (wierzcholek **wieza,int koszt[], bool przetworzone[], int wys)
{
	for(int i=0;i<wys;i++)
	{
		koszt[i] = 99999;
		przetworzone[i] = 0;
	}
	koszt[0] = 0; // zaczynamy od 0 wierzcholka, dlatego koszt=0
}


void djikstra(wierzcholek **wieza, int koszt[], int wys){


	bool * przetworzone = new bool[wys];
	inicjalizuj(wieza, koszt, przetworzone,wys);
	int i = 0;
	wierzcholek *obecny = NULL;
	while (!przetworzone[1]) // 1 - bo zależy nam tylko na dojściu do 1 wierzchołka
	//while (true)
	{
		for (int j = 0; j < wys; j++)
		{
			if (koszt[i] > koszt[j] && !przetworzone[j])
			{
				i = j;
			}
		}
		if (i == 1) { break; }
		przetworzone[i] = 1;
		obecny = wieza[i];
		for(; obecny != nullptr; obecny = obecny->next)
		{
			if(!przetworzone[obecny->gdzie])
			{
				if (koszt[i] + obecny->waga < koszt[obecny->gdzie])
				{
					koszt[obecny->gdzie] = koszt[i] + obecny->waga;
				}
			}
		}
		i = 1;
	}
	delete[] przetworzone;
}





int main()
{
	int wys = 0;
	cin >> wys;
	int wys2 = wys;
	if (wys < 10) { wys2 = 30; }  // troszke powinno przyspieszyc dla malych testow (mozna zmienic na wartość mniejszą)

	char **slowo = new char*[wys];  // tabela klockow
	for (int i = 0; i < wys; i++) {
		slowo[i] = new char[wys2+5];
		for (int j = 0; j < wys2+5; j++) {
			slowo[i][j] = NULL;
		}
	}

	for ( int petla=0;petla<wys;petla++)
	{		
		cin >> slowo[petla];
	}


	wierzcholek **wieza = new wierzcholek *[wys];
	wierzcholek *obecny = NULL;
	int *koszt = new int[wys];
	bool *przetworzone = new bool[wys];

	


	for (int i = 0; i < wys; i++)
	{
		wieza[i] = NULL;
	}



	char *polaczone = new char[wys2 * 2 + 50];
	for (int i = 0; i < wys; i++) { // z tabeli robimy graf
		for (int j = 0; j < wys; j++) {
			if (i == j && j+1 < wys) { j++; } //omijamy krawedz do samego siebie
			for (int k = 0; k < wys2 * 2 + 50; k++) { polaczone[k] = NULL; }
			int czy_jest = strlen(slowo[j]) - porownaj(polacz(slowo[i], slowo[j], polaczone));
			
			if (czy_jest < strlen(slowo[j])) {
			obecny = new wierzcholek;
			obecny->gdzie = j;
			obecny->waga=czy_jest;
			obecny->next = wieza[i];
			wieza[i] = obecny;
			}
	}
	}


	djikstra(wieza, koszt, wys);


	if (koszt[1] < 99000) { cout << koszt[1] + strlen(slowo[0]) << '\n'; }
	else { cout << "0\n"; }

	delete[] koszt;;
	delete[] przetworzone;
	for (int i = 0; i < wys; i++) { usun(wieza[i]); }
	delete[] wieza;
    return 0;
}







