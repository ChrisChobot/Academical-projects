#pragma once
#include "zwierze.h"
class owca :
	public zwierze
{
public:
	owca(swiat&, int, int);
	~owca();
	char rysowanie();
	void nowe(swiat&, int, int);
};

