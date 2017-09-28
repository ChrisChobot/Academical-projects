#include "stdafx.h"
#include "leniwiec.h"


leniwiec::leniwiec(swiat& ref, int x, int y) :zwierze(ref, x, y)
{
	this->sila = 2;
	this->inicjatywa = 1;
	this->nazwa = 'L';
	this->ruch = true;
	this->specjalna_kolizja = 0;
}
char leniwiec::rysowanie() {
	return this->nazwa;
}
void leniwiec::akcja(swiat& ref) {
	if (ruch == 1) {
		ruch = 0;		
		zwierze::akcja(ref);
	}
	else { 
	ruch = 1;
	cout << "leniwiec spi \n";
	}
}
void leniwiec::nowe(swiat& ref, int x, int y)
{
	organizm *o = new leniwiec(ref, x, y);
	cout << "dodano: " << this->rysowanie() << " na polu: " << x + 1 << ':' << y + 1 << ":\n";
}
leniwiec::~leniwiec()
{
}
