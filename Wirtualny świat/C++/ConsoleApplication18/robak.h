#pragma once
#include "zwierze.h"
class robak :
	public zwierze
{
public:
	robak(swiat&, int, int);
	~robak();
	char rysowanie();
	void spec_kolizja(organizm*);
	void nowe(swiat&, int, int);
};

