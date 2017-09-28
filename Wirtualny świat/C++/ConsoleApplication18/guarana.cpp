#include "stdafx.h"
#include "guarana.h"


guarana::guarana(swiat& ref, int x, int y) :roslina(ref, x, y)
{
	this->sila = 0;
	this->inicjatywa = 0;
	this->nazwa = 'G';
	this->specjalna_kolizja = 1;
}

char guarana::rysowanie() {
	return this->nazwa;
}
void guarana::nowe(swiat& ref, int x, int y)
{
	organizm *o = new guarana(ref, x, y);
	cout << "dodano: " << this->rysowanie() << " na polu: " << x + 1 << ':' << y + 1 << ":\n";
}
void guarana::spec_kolizja(organizm* org) {
	org->ustaw_sila_organizmu(org->sila_organizmu() + 3);
	cout << org->rysowanie() << " zwiekszyl swa sile o 3\n";
}
guarana::~guarana()
{
}
