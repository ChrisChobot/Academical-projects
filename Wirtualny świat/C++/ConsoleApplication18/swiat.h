#include <cstddef>
#include <vector>
#include <iostream>
#define N 20 //wielkosc mapy
using namespace std;
#pragma once
class organizm;
class swiat
{

public:
	swiat();
	void gra();
	void rysujSwiat();
	bool czyZajete(int x, int y);
	organizm* organizm_na_polu(int x, int y);
	void dodaj_organizm_do_kolejki(organizm *org);
	void dodaj_organizm_do_mapy(organizm *org, int x, int y);
	void przesun_organizm_na_mapie(organizm *org, int nx, int ny, int x, int y);
	void start(swiat&);
	
private:
	~swiat();
	organizm*** mapa;
	organizm **kolejka_ruchu;
	//const int N = 20;
	int ktory_el_kolejki = 0;
	char* legenda[30];
};

