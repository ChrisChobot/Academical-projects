#include "stdafx.h"
#include "owca.h"


owca::owca(swiat& ref, int x, int y) :zwierze(ref, x, y)
{
	this->sila = 4;
	this->inicjatywa = 4;
	this->nazwa = 'O';
	this->specjalna_kolizja = 0;
}

char owca::rysowanie() {
	return 'O';
}
void owca::nowe(swiat& ref, int x, int y)
{
	organizm *o = new owca(ref, x, y);
	cout << "dodano: " << this->rysowanie() << " na polu: " << x + 1 << ':' << y + 1 << ":\n";
}
owca::~owca()
{
}
