#pragma once
#include "zwierze.h"
class zmija :
	public zwierze
{
public:
	zmija(swiat&, int, int);
	~zmija();
	char rysowanie();
	void spec_kolizja(organizm*);
	void nowe(swiat&, int, int);
};

