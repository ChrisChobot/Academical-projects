#include "stdafx.h"
#include "trawa.h"


trawa::trawa(swiat& ref, int x, int y) :roslina(ref, x, y)
{
	this->sila = 0;
	this->inicjatywa = 0;
	this->nazwa = 'T';
	this->specjalna_kolizja = 0;
}

char trawa::rysowanie() {
	return this->nazwa;
}
void trawa::nowe(swiat& ref, int x, int y)
{
	organizm *o = new trawa(ref, x, y);
	cout << "dodano: " << this->rysowanie() << " na polu: " << x + 1 << ':' << y + 1 << ":\n";	
}
trawa::~trawa()
{
}
