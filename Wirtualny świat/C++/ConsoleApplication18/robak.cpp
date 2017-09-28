#include "stdafx.h"
#include "robak.h"


robak::robak(swiat& ref, int x, int y) :zwierze(ref, x, y)
{
	this->sila = 1;
	this->inicjatywa = 1;
	this->nazwa = 'R';
	this->specjalna_kolizja = 1;
}
char robak::rysowanie() {
	return this->nazwa;
}
void robak::spec_kolizja(organizm* org) {
	org->ustaw_sila_organizmu(org->sila_organizmu() + 2);
	cout << org->rysowanie() << " zwiekszyl swa sile o 2\n";
}
void robak::nowe(swiat& ref, int x, int y)
{
	organizm *o = new robak(ref, x, y);
	cout << "dodano: " << this->rysowanie() << " na polu: " << x + 1 << ':' << y + 1 << ":\n";
}
robak::~robak()
{
}
