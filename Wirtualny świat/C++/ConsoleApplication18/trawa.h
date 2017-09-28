#pragma once
#include "roslina.h"
class trawa :
	public roslina
{
public:
	trawa(swiat&, int, int);
	~trawa();
	char rysowanie();
	void nowe(swiat&, int, int);
};

