#include "stdafx.h"
#include "zwierze.h"


zwierze::zwierze(swiat& ref, int x, int y):organizm(ref,x,y)
{

}

void zwierze::akcja(swiat& ref) {

	int r = (rand() % 4) + 1;
	int x = this->x;
	int y = this->y;

	bool co_sprawdzilismy[4] = { 0,0,0,0 };  //gora dol lewo prawo -- gdzie nie mozna isc

	if (this->x == 0 && this->y == 0) //lewa gora
	{
		co_sprawdzilismy[0] = 1; //gora
		co_sprawdzilismy[2] = 1; //lewo
	}
	else if (this->x == N - 1 && this->y == 0)  //prawa gora
	{
		co_sprawdzilismy[0] = 1; //gora
		co_sprawdzilismy[3] = 1; // prawo
	}
	else if (this->x == 0 && this->y == N - 1)  //lewy dol
	{
		co_sprawdzilismy[1] = 1; //dol
		co_sprawdzilismy[2] = 1; //lewo
	}
	else if (this->x == N - 1 && this->y == N - 1) //prawy dol
	{
		co_sprawdzilismy[1] = 1; //dol
		co_sprawdzilismy[3] = 1; // prawo
	}
	else if (this->x == 0 && this->y > 0 && this->y < N) //krawędź lewo
	{
		co_sprawdzilismy[2] = 1; //lewo
	}
	else if (this->x == N - 1 && this->y > 0 && this->y < N) //krawędź prawo
	{
		co_sprawdzilismy[3] = 1; // prawo		
	}
	else if (this->y == 0 && this->x > 0 && this->x < N) //krawędź gora
	{
		co_sprawdzilismy[0] = 1; //gora
	}
	else if (this->y == N - 1 && this->x > 0 && this->x < N) //krawędź dol
	{
		co_sprawdzilismy[1] = 1; //dol
	}
		
		while (co_sprawdzilismy[r-1] != 0) { r = (rand() % 4) + 1; };//losujemy r tak dlugo az trafimy na dozwolone pole

		// czy kolizja?

		switch (r)
		{
		case 1: --y; break;
		case 2: ++y; break;
		case 3: --x; break;
		case 4: ++x; break;
		}
		

		if (ref.czyZajete(x, y)) {
			if(!ref.organizm_na_polu(x, y)->czy_umarl())// jesli umarł to nie ma kolizji , tylko zamieniamy sie miejscami
			{ 
				kolizja(ref, this, ref.organizm_na_polu(x,y));
			}			
		}

	
		if (  this != NULL && (!ref.czyZajete(x, y) || ref.organizm_na_polu(x, y)->czy_umarl())) 
		{
		ref.przesun_organizm_na_mapie(this, x, y, this->x, this->y);
		}
}

void zwierze::kolizja(swiat& ref, organizm* ten, organizm* tamten) 
{
	if (ten->sila_organizmu() == tamten->sila_organizmu()) 
	{
		if (ten->rysowanie() == tamten->rysowanie()) 
		{ 
			rozmnarzanie(ref);
		}
		else
		{
		tamten->ustaw_czy_zyje(false);
		cout << ten->rysowanie() << " zabil " << tamten->rysowanie() << "\n";
		if (tamten->czy_spec_kol() == 1) { tamten->spec_kolizja(ten); }
		}
	}
	else if (ten->sila_organizmu() > tamten->sila_organizmu()) 
	{
		if (ten->rysowanie() == tamten->rysowanie()) 
		{
			rozmnarzanie(ref);

		}
		else 
		{
			tamten->ustaw_czy_zyje(false);
			cout << ten->rysowanie() << " zabil " << tamten->rysowanie() << "\n";
			if (tamten->czy_spec_kol() == 1) { tamten->spec_kolizja(ten); }
		}
	}
	else if (ten->sila_organizmu() < tamten->sila_organizmu()) 
	{
		if (ten->rysowanie() == tamten->rysowanie()) 
		{
			rozmnarzanie(ref);
		}
		else 
		{
			ten->ustaw_czy_zyje(false);
			cout << tamten->rysowanie() << " zabil " << ten->rysowanie() << "\n";
			if (ten->czy_spec_kol() == 1) { ten->spec_kolizja(tamten); }
		}
	}
}
void zwierze::rozmnarzanie(swiat& ref) // 50% szans na nowe
{ 
	if ((rand() % 2) != 0) {
		int r = (rand() % 4) + 1;
		int x = this->x;
		int y = this->y;

		bool co_sprawdzilismy[4] = { 0,0,0,0 };  //gora dol lewo prawo -- gdzie nie mozna isc

		if (this->x == 0 && this->y == 0) //lewa gora
		{
			co_sprawdzilismy[0] = 1; //gora
			co_sprawdzilismy[2] = 1; //lewo
		}
		else if (this->x == N - 1 && this->y == 0)  //prawa gora
		{
			co_sprawdzilismy[0] = 1; //gora
			co_sprawdzilismy[3] = 1; // prawo
		}
		else if (this->x == 0 && this->y == N - 1)  //lewy dol
		{
			co_sprawdzilismy[1] = 1; //dol
			co_sprawdzilismy[2] = 1; //lewo
		}
		else if (this->x == N - 1 && this->y == N - 1) //prawy dol
		{
			co_sprawdzilismy[1] = 1; //dol
			co_sprawdzilismy[3] = 1; // prawo
		}
		else if (this->x == 0 && this->y > 0 && this->y < N) //krawędź lewo
		{
			co_sprawdzilismy[2] = 1; //lewo
		}
		else if (this->x == N - 1 && this->y > 0 && this->y < N) //krawędź prawo
		{
			co_sprawdzilismy[3] = 1; // prawo		
		}
		else if (this->y == 0 && this->x > 0 && this->x < N) //krawędź gora
		{
			co_sprawdzilismy[0] = 1; //gora
		}
		else if (this->y == N - 1 && this->x > 0 && this->x < N) //krawędź dol
		{
			co_sprawdzilismy[1] = 1; //dol
		}

		for (; co_sprawdzilismy[r - 1] != 0; r = (rand() % 4) + 1) {};//losujemy r tak dlugo az trafimy na dozwolone pole																	 

		 // czy kolizja?

		switch (r)
		{
		case 1: --y; break;
		case 2: ++y; break;
		case 3: --x; break;
		case 4: ++x; break;
		}

		
		if (!ref.czyZajete(x, y)) {
			if (ref.organizm_na_polu(x, y) == NULL) {
				this->nowe(ref, x, y);
			}
		}
	}
}

zwierze::~zwierze()
{
}
