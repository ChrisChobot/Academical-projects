#pragma once
#include "organizm.h"
class zwierze :
	public organizm
{
protected:
	zwierze(swiat&,int,int);
	~zwierze();
	void akcja(swiat&);
	void kolizja(swiat&,organizm*, organizm*);
	void rozmnarzanie(swiat&);	
};

