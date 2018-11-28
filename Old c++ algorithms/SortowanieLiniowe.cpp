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

int main()
{

	char wczyt[100] = { NULL };
	fgets(wczyt, 100, stdin);
	int IleWierszy = atoi(wczyt); //ile wierszy do posortowania
	int ** tab = new int *[IleWierszy];
	for (int p = 0; p < IleWierszy; p++)
	{
		tab[p] = new int[2];
	}
	for (int j = 0; j < IleWierszy; j++) { tab[j][0] = 0; tab[j][1] = 0; }
	int * tabsort = new int[IleWierszy];
	for (int j = 0; j < IleWierszy; j++) { tabsort[j] = 0; }//wypelniamy zerami, by przy dodawaniu nic sie nie wywalilo
	int licznik = 0;
	for (int p = 0; p<IleWierszy; p++) {
		for (int j = 0; j < 100; j++) { wczyt[j] = NULL; }
		fgets(wczyt, 100, stdin);
		int i = 0, k = 0;
		char bufor[100] = { NULL };
		for (; wczyt[i] != ' ' && wczyt[i] != NULL; k++)
		{
			bufor[k] = wczyt[i];
			i++;
		};
		i++;
		tab[licznik][0] = atoi(bufor);
		tabsort[tab[licznik][0]]++;
		for (int j = 0; j < 100; j++) { bufor[j] = NULL; }
		k = 0;
		for (; wczyt[i] != ' ' && wczyt[i] != NULL; k++)
		{
			bufor[k] = wczyt[i];
			i++;
		};
		tab[licznik][1] = atoi(bufor);
		licznik++;
	}


	for (int j = 0; j < 100; j++) { wczyt[j] = NULL; }
	fgets(wczyt, 100, stdin);
	bool tryb = wczyt[0] - 48;
	for (int j = 1; j<IleWierszy; j++) {
		tabsort[j] += tabsort[j - 1];
	}
	int ** posort = new int *[IleWierszy+1];
	for (int p = 0; p < IleWierszy+1; p++)
	{
		posort[p] = new int[2];
	}
	for (int j = 0; j < IleWierszy+1; j++) { posort[j][0] = 0; posort[j][1] = 0; }



	int kopia = licznik;


	licznik--;
	for (; licznik >= 0; ) {

		posort[tabsort[tab[licznik][0]]][0] = tab[licznik][0];
		posort[tabsort[tab[licznik][0]]][1] = tab[licznik][1];

		tabsort[tab[licznik][0]]--;

		licznik--;
	}
	if (tryb == 0) {
		for (int j = 1; j <= kopia; j++) {
			cout << posort[j][0] << "\n";
		}
	}
	else {
		for (int j = 1; j <= kopia; j++) {
			cout << posort[j][0] << "," << posort[j][1] << "\n";
		}
	}


	delete[] tabsort;
	for (int i = 0; i < IleWierszy; i++)
	{
		delete[] tab[i];
	}
	delete[] tab;
	for (int i = 0; i < IleWierszy+1; i++)
	{
		delete[] posort[i];
	}
	delete[] posort;
	return 0;
}