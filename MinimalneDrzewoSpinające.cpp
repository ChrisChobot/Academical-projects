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
		if (temp->next != nullptr)
		{
			wierzcholek * tempy = temp->next;
			delete temp;
			usun(tempy);
		}
		else { delete temp; }
	}
}


struct kolejka
{
	int skad;
	wierzcholek *wsk;
	kolejka *next;
	kolejka();
};
kolejka::kolejka()
{
	skad = NULL;
	wsk = NULL;
	next = NULL;
}
struct cala
{
	kolejka * pierwszy;

	void dodaj(wierzcholek *temp, int skad) {
		kolejka *nowy = new kolejka;
		nowy->skad = skad;
		nowy->wsk = temp;
		nowy->next = NULL;

		if (pierwszy == 0 || pierwszy == NULL)   // sprawdzamy czy to pierwszy element listy
		{
			pierwszy = nowy;
			pierwszy->next = NULL;
		}
		else {
			kolejka *obecny = pierwszy;
			kolejka *nastepny = NULL;
			if (pierwszy->next != NULL) { nastepny = pierwszy->next; }
			int wag = nowy->wsk->waga;
			if (wag < pierwszy->wsk->waga)
			{
				nowy->next = pierwszy;
				pierwszy = nowy;
				return;
			}



			while (nastepny != NULL&&wag > nastepny->wsk->waga)
			{
				obecny = nastepny;
				if (nastepny->next) { nastepny = nastepny->next; }
				else { nastepny = NULL; break; }
			}
			obecny->next = nowy;
			nowy->next = nastepny;
		}
	}
	void usun()
	{
		kolejka *stary = pierwszy;
		if (pierwszy->next != nullptr) { pierwszy = pierwszy->next; }
		else { pierwszy = NULL; }
		delete stary;
	}
	cala();
};
cala::cala()
{
	pierwszy = NULL;

}


bool czy_wojewodztwo(int nr, int *okolice, int **tabela) 
{
	bool wynik = 0;

	if (nr == tabela[okolice[nr]][0])
	{

		wynik = 1;
	}

	return wynik;
}
int ktore_wojewodztwo(int nr, int l_wojew, int **tabela)
{
	for (int i = 0; i < l_wojew; i++)
	{
		if (nr == tabela[i][0])
		{
			return i;
		}
	}

	return 0; // jesli tutaj dojdzie = błąd
}



void szukaj(int y, int x, wierzcholek **wieza, int l_wojew, int **tabela, int licz, int koszt, int lmiast, int w_start, int okolice[], int mijan[]) {
	int obecny_koszt = koszt;
	int mijane[5];
	for (int i = 0; i < 5; i++)
	{
		if (mijan != NULL) { mijane[i] = mijan[i]; }
		else { mijane[i] = 99999; }

	}

	if (x >= 3) { return; }	 // x= ktory obieg,   y= ktore "mijane" wojwodztwo
	else
	{
		int pusto = 0;
		for (; pusto < 5 && mijane[pusto] <99999; pusto++);
		if (pusto > 0 && mijane[pusto - 1] == okolice[licz])
		{
			y++;
		}
		else { mijane[pusto] = okolice[licz]; pusto++; }
		x++;
		if (y > 1)
		{
			return;
		}
		wierzcholek *wsk = wieza[licz];
		for (; wsk != NULL &&wsk->waga != NULL; wsk = wsk->next)
		{
			if (wsk->gdzie != w_start) {
				if (okolice[wsk->gdzie] != mijane[pusto - 1] && pusto > 1)
				{
					continue;
				}





				if (czy_wojewodztwo(wsk->gdzie, okolice, tabela))
				{
					//w_start = wierzcholek z ktorego startujemy, sprawdzamy zeby nie robic krawedzi do samego siebie
					wierzcholek *obecny = new wierzcholek;
					obecny->gdzie = wsk->gdzie;
					obecny->waga = obecny_koszt + wsk->waga;
					obecny->next = wieza[lmiast];
					wieza[lmiast] = obecny;

				}
				else 
				{
					szukaj(y, x, wieza, l_wojew, tabela, wsk->gdzie, obecny_koszt + wsk->waga, lmiast, w_start, okolice, mijane);																														 
				}
			}
			if (!wsk->next) { break; }
		}
	}
}


void poszukaj(cala *kolejka, wierzcholek**drzewo, int l_wojew, int nr_woj, int **tabela) {
	wierzcholek *obecny = drzewo[ktore_wojewodztwo(nr_woj, l_wojew, tabela)];
	int skad = nr_woj;
	while (obecny) {
		kolejka->dodaj(obecny, skad);
		if (obecny->next)
		{
			obecny = obecny->next;
		}
		else { break; }
	}
}


int main()
{
	int lmiast, lwojewodztw, ile, cel, waga;

	cin >> lmiast;

	wierzcholek **wieza = new wierzcholek *[lmiast + 2];
	wierzcholek *obecny = NULL;

	for (int i = 0; i < lmiast + 2; i++)
	{
		wieza[i] = NULL;
	}


	for (int i = 0; i<lmiast; i++) {
		cin >> ile;

		for (int j = 0; j<ile; j++) {

			cin >> cel >> waga;

			obecny = new wierzcholek;
			obecny->gdzie = cel;
			obecny->waga = waga;
			obecny->next = wieza[i];
			wieza[i] = obecny;
		}
	}

	cin >> lwojewodztw;

	int **tabela = new int*[lwojewodztw];
	for (int i = 0; i < lwojewodztw; i++) {
		tabela[i] = new int[25];
	}
	int *okolice = new int[lmiast];
	for (int i = 0; i < lmiast; i++) { okolice[i] = 0; }

	for (int i = 0; i <lwojewodztw; i++) {
		cin >> cel;
		cin >> ile;
		tabela[i][0] = cel; // ktore wojewodztwo (nr miasta)
		tabela[i][1] = 0; // czy przetworzone
		okolice[cel] = i;
		for (int k = 0; k<ile; k++)
		{
			cin >> cel;
			tabela[i][k + 2] = cel;
			okolice[cel] = i;
		}
	}

	//wytyczanie scierzek 

	wierzcholek **drzewo = new wierzcholek *[lmiast + 2];
	for (int i = 0; i < lmiast + 2; i++)
	{
		drzewo[i] = NULL;
	}
	wierzcholek *wsk = NULL;
	for (int i = 0; i < lwojewodztw; i++) {
		szukaj(0, 0, wieza, lwojewodztw, tabela, tabela[i][0], 0, lmiast + 1, tabela[i][0], okolice, NULL);  // lmiast+1 tak zeby nic nie nadpisalo
																											 //po kazdym obiegu petli mamy zalatwiony 1 wierzcholek
																											 //teraz trzeba zrobic nowy graf
		wsk = wieza[lmiast + 1];
		if (wsk != NULL) {
			while (true) {
				obecny = new wierzcholek;
				obecny->gdzie = wsk->gdzie;
				obecny->waga = wsk->waga;
				obecny->next = drzewo[i];
				drzewo[i] = obecny;
				if (wsk->next == NULL) { break; }
				else { wsk = wsk->next; }
			}
			usun(wieza[lmiast + 1]);
			wieza[lmiast + 1] = NULL;
		}
	}

	//usunac wieze
	for (int i = 0; i<lmiast + 2; i++)
	{
		usun(wieza[i]);
	}
	delete[] wieza;



	bool *przetw = new bool[lmiast];
	for (int i = 0; i<lmiast; i++)
	{
		przetw[i] = 0;
	}

	cala *kolejka = new cala;
	int koszt = 0;

	poszukaj(kolejka, drzewo, lwojewodztw, tabela[0][0], tabela);
	przetw[tabela[0][0]] = 1;
	for (int i = lwojewodztw - 1; i >0;)
	{
				if (kolejka->pierwszy) {
			int gdzie = kolejka->pierwszy->wsk->gdzie;
			if (!przetw[kolejka->pierwszy->skad] || !przetw[gdzie])
			{				
				przetw[gdzie] = 1;
				koszt += kolejka->pierwszy->wsk->waga;

				kolejka->usun();
				i--;

				poszukaj(kolejka, drzewo, lwojewodztw, gdzie, tabela);
			}
			else {
				kolejka->usun();			
			}


		}
		else
		{
			break;
		}
	}
	cout << koszt;



	for (int i = 0; i < lmiast + 2; i++)
	{
		usun(drzewo[i]);
	}
	delete[]drzewo;
	for (int i = 0; i < lwojewodztw; i++) {
		delete[] tabela[i];
	}
	delete[] tabela;
	delete[] okolice;
	delete[] przetw;
	while (kolejka->pierwszy != NULL) { kolejka->usun(); }
	delete kolejka;
	return 0;
}

