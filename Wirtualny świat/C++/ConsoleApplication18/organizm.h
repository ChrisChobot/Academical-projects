#pragma once
#include "swiat.h"
#include <string>

class organizm //: public swiat
{
public:
	swiat& swiat1;
	virtual void akcja(swiat&) = 0;
	virtual void kolizja(swiat&, organizm*, organizm*) = 0;
	virtual void spec_kolizja(organizm*);
	virtual char rysowanie() = 0;
	bool czy_umarl();
	void ustaw_czy_zyje(bool zycie);
	int zwroc_inicjatywa();
	int sila_organizmu();
	bool czy_spec_kol();
	void ustaw_sila_organizmu(int x);
	int pozycja_x();
	int pozycja_y();
	void ustaw_pozycje(int x, int y);
	virtual void nowe(swiat&, int, int) = 0;
	void usun_org();
protected:
	organizm(swiat&, int, int);
	~organizm();
	int sila, inicjatywa, x, y;
	char nazwa;
	bool czy_zyje, specjalna_kolizja;

};

