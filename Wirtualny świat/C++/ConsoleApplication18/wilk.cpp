#include "stdafx.h"
#include "wilk.h"


wilk::wilk(swiat& ref, int x, int y):zwierze(ref,x,y)
{
	this->sila = 9;
	this->inicjatywa = 5;
	this->nazwa = 'W';
	this->specjalna_kolizja = 0;
}

char wilk::rysowanie() 
{
	return this->nazwa;
}
void wilk::nowe(swiat& ref, int x, int y)
{
	organizm *o = new wilk(ref, x, y);
	cout << "dodano: " << this->rysowanie() << " na polu: " << x + 1 << ':' << y + 1 << ":\n";
}
wilk::~wilk()
{
}
