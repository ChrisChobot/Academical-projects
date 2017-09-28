#pragma once
#include "organizm.h"
class roslina :
	public organizm
{
protected:
	roslina(swiat&, int, int);
	~roslina();
	void akcja(swiat& ref);
	void kolizja(swiat&,organizm*, organizm*);
};

