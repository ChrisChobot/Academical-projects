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

struct wierzcholek {

	int numer;
	int tata;
	int waga;
	wierzcholek *next;
	wierzcholek();
};
wierzcholek::wierzcholek() {
	next = NULL;
}



struct lista {

	wierzcholek *pierwszy;
	wierzcholek *ostatni;

	void dodaj(int numer,int tata,int waga) {
		wierzcholek *nowy = new wierzcholek;
		nowy->numer = numer;
		nowy->tata = tata;
		nowy->waga = waga;
		if (pierwszy == NULL) { pierwszy = nowy; ostatni = pierwszy; }			
		else {											
			wierzcholek *temp = ostatni;
			temp->next = nowy;
			nowy->next = NULL;
			ostatni = nowy;
		}
	}
	void usun()
	{
		wierzcholek*stary = pierwszy;
		wierzcholek*temp = stary;
		while(stary->next)
		{
			temp = stary->next;
			delete stary;
			stary = temp;
		}
		delete stary;
	}
	lista();

};
lista::lista() {
	pierwszy = NULL;       
	ostatni = NULL;
}





void szukaj(bool visited[],int **wyniki, lista *tablica, int nr,long long wagatymcz)
{

	wierzcholek *obecny = tablica[nr].pierwszy;
	if(obecny != nullptr){
		wierzcholek *temp=obecny;
		wagatymcz += temp->waga;
		while(temp->next!= NULL)
		{
			temp = temp->next;
			wagatymcz += wyniki[temp->numer][2];
		}
		
		visited[nr] = 1;
		if(obecny->numer < obecny->tata){ // Każdy podział powinien być opisany przez dwie liczby u v – wierzchołki które powinny się rozdzielić (u < v). 
		wyniki[nr][0] = obecny->numer;
		wyniki[nr][1] = obecny->tata;
		}
		else {
			wyniki[nr][0] = obecny->tata;
			wyniki[nr][1] = obecny->numer;
		}
		wyniki[nr][2] = wagatymcz;
	}
}





int main()
{
	int liczwierzch = 0;
	cin >> liczwierzch;

	long long wagacalosc = 0;
	int waga = 0;
	int gdzie = 0;
	cin >> waga;	
	wagacalosc += waga;
	
	lista *tablica = new lista[liczwierzch];
	tablica[0].dodaj(0,-5,waga);


	for(int i=1;i<liczwierzch;i++)
	{		
		cin >> waga;
		cin >> gdzie;
		wagacalosc += waga;
		tablica[i].dodaj(i,gdzie,waga);
		tablica[gdzie].dodaj(i,gdzie, waga);
	}
	
	
	bool *visited = new bool[liczwierzch];
	int **wyniki = new int*[liczwierzch]; //0-skad 1-dokad 2-waga
	for (int i = 0; i < liczwierzch; i++) { 
		visited[i] = 0;
		wyniki[i] = new int[4]; 
		for (int j = 0; j < 4; j++) { wyniki[i][j] = NULL; }
	}
	

	for (int i = liczwierzch-1; i >= 0; i--)
	{
		szukaj(visited, wyniki, tablica, i, 0);
	}

	for (int i = 0; i < liczwierzch; i++) {   // obliczamy roznice
		wyniki[i][2] = wyniki[i][2] - (wagacalosc - wyniki[i][2]);
		if (wyniki[i][2] < 0) { wyniki[i][2] *= -1; }
	}

	delete[] visited;
	for (int i = 0; i < liczwierzch; i++)
	{
		tablica[i].usun();
	}
	delete[] tablica;
	
	wyniki[0][2] = 2147483645; //pierwsza krawedz jest bledna, a to jeden z sposobow wykluczenia


	int **koniec = new int*[liczwierzch]; //0-skad 1-dokad 2-waga
	for (int i = 0; i < liczwierzch; i++) {
		koniec[i] = new int[4];
		for (int j = 0; j < 4; j++) { koniec[i][j] = NULL; }
	}
	int pomoc = 0;
	int max = 2147483645;
	for (int i = 0; i < liczwierzch; i++) {
		if (max > wyniki[i][2]) { max = wyniki[i][2]; }
	}
	for (int i = 0; i < liczwierzch; i++) {
		if (max == wyniki[i][2])
		{
			koniec[pomoc][0] = wyniki[i][0];
			koniec[pomoc][1] = wyniki[i][1];
			koniec[pomoc][2] = wyniki[i][2];
			pomoc++;
		}
	}




	int ile = pomoc, roznica = koniec[0][2];
	cout << roznica << ' ' << ile << '\n';
	for(int i=0;i<ile;i++){cout<< koniec[i][0]<<' '<< koniec[i][1]<<'\n';	}


	for (int i = 0; i < liczwierzch; i++) {
		delete[] koniec[i];
		delete[] wyniki[i];
	}
	delete[] koniec;
	delete[] wyniki;
	return 0;
}