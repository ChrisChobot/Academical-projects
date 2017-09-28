#include "stdafx.h"
#include "zmija.h"


zmija::zmija(swiat& ref, int x, int y) :zwierze(ref, x, y)
{
	this->sila = 2;
	this->inicjatywa = 3;
	this->nazwa = 'Z';
	this->specjalna_kolizja = 1;
}
char zmija::rysowanie() 
{
	return this->nazwa;
}

void zmija::spec_kolizja(organizm* org) 
{
	org->ustaw_czy_zyje(false);
	cout << org->rysowanie() << " umarl od jadu\n";
}

void zmija::nowe(swiat& ref, int x, int y)
{
	organizm *o = new zmija(ref, x, y);
	cout << "dodano: " << this->rysowanie() << " na polu: " << x + 1 << ':' << y + 1 << ":\n";
}

zmija::~zmija()
{
}
