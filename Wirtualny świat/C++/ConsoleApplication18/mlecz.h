#pragma once
#include "roslina.h"
class mlecz :
	public roslina
{
public:
	mlecz(swiat&, int, int);
	~mlecz();
	char rysowanie();
	void nowe(swiat&, int, int);
	void akcja(swiat&);
};

