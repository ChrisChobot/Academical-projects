#pragma once
#include "roslina.h"
class guarana :
	public roslina
{
public:
	guarana(swiat&, int, int);
	~guarana();
	char rysowanie();
	void nowe(swiat&, int, int);
	void spec_kolizja(organizm*);
};

