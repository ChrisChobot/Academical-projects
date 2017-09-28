#pragma once
#include "zwierze.h"
class wilk :
	public zwierze
{
public:
	wilk(swiat&, int, int);
	~wilk();
	char rysowanie();
	void nowe(swiat&, int, int);
};

