#pragma once
#include "zwierze.h"
class leniwiec :
	public zwierze
{
public:
	leniwiec(swiat&, int, int);
	bool ruch; //czy moze sie ruszyc
	~leniwiec();
	char rysowanie();
	void akcja(swiat&);
	void nowe(swiat&, int, int);
};

