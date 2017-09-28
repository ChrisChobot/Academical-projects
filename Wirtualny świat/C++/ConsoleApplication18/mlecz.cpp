#include "stdafx.h"
#include "mlecz.h"


mlecz::mlecz(swiat& ref, int x, int y) :roslina(ref, x, y)
{
	this->sila = 0;
	this->inicjatywa = 0;
	this->nazwa = 'M';
	this->specjalna_kolizja = 0;
}

char mlecz::rysowanie() {
	return this->nazwa;
}
void mlecz::nowe(swiat& ref, int x, int y)
{
	organizm *o = new mlecz(ref, x, y);
	cout << "dodano: " << this->rysowanie() << " na polu: " << x + 1 << ':' << y + 1 << ":\n";
}
void mlecz::akcja(swiat& ref) {
	for (int i = 0; i < 3; i++) { roslina::akcja(ref); }
}


mlecz::~mlecz()
{
}
