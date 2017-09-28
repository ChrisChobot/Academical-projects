#include "stdafx.h"
#include "organizm.h"


organizm::organizm(swiat& swiatref, int x, int y):swiat1(swiatref)
{	
	this->x = x;
	this->y = y;
	czy_zyje = true;
	swiatref.dodaj_organizm_do_mapy(this, this->x, this->y);
	swiatref.dodaj_organizm_do_kolejki(this);
};


bool organizm::czy_umarl()
{
	if (this != NULL) 
	{
		return !czy_zyje;
	}
	else { return 1; }
}
void organizm::ustaw_czy_zyje(bool zycie)
{
	czy_zyje = zycie;
}

int organizm::zwroc_inicjatywa()
{
	return this->inicjatywa;
}

int organizm::sila_organizmu()
{
	return this->sila;
}
void organizm::ustaw_sila_organizmu(int x)
{
	sila = x;
}
int organizm::pozycja_x()
{
	return this->x;
}
int organizm::pozycja_y()
{
	return this->y;
}
void organizm::spec_kolizja(organizm* org) { //domyslnie nic nie robi
	return;
}
void organizm::ustaw_pozycje(int x, int y)
{
	this->x = x;
	this->y = y;
}
bool organizm::czy_spec_kol() {

	return this->specjalna_kolizja;
}
void organizm::usun_org() {
	delete this;
}
organizm::~organizm()
{
	this->sila = NULL;
	this->inicjatywa = NULL;
	this->x = NULL;
	this->y = NULL;
}
