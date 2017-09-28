#include "stdafx.h"
#include "swiat.h"
#include "organizm.h"
#include "wilk.h"
#include "owca.h"
#include "trawa.h"
#include "leniwiec.h"
#include "zmija.h"
#include "robak.h"
#include "mlecz.h"
#include "guarana.h"
//#include "zwierze.h"

swiat::swiat()
{
	mapa = new organizm**[N];
	for (int i = 0; i < N; i++) 
	{
		mapa[i] = new organizm*[N]; // Tworzymy wiersze
	}

	for (int i = 0; i < N; i++)  //czyscimy macierz
	{
		for (int j = 0; j < N; j++) 
		{
			mapa[i][j] = NULL; 
		}
	}
	kolejka_ruchu = new organizm*[(N*N*N)+1];

	for (int i = 0; i < (N*N*N) + 1; i++) //czyscimy macierz
	{
		kolejka_ruchu[i] = NULL;
	}
	for (int i = 0; i < 30; i++) { legenda[i] = " "; }

	legenda[0] = "W - WILK" ;
	legenda[1] = "O - OWCA";
	legenda[2] = "Z - ZMIJA";
	legenda[3] = "R - ROBAK";
	legenda[4] = "L - LENIWIEC";
	legenda[5] = "T - TRAWA";
	legenda[6] = "G - GUARANA";
	legenda[7] = "M - MLECZ";	

}

void swiat::start(swiat& oo)
{
		organizm* o = new wilk(oo, 1, 2);		
		 o = new wilk(oo, 3, 6);	
		 o = new wilk(oo,1,4);
	
		 o = new owca(oo, 3, 2);
		 o = new owca(oo, 5, 3);
		 o = new owca(oo, 7, 2);

		 o = new leniwiec(oo, 8, 13);
		 o = new leniwiec(oo, 10, 16);
		 o = new leniwiec(oo, 12, 11);
		 o = new leniwiec(oo, 9, 6);

		 o = new robak(oo, 17, 1);
		 o = new robak(oo, 17, 3);
		 o = new robak(oo, 19, 2);

		 o = new zmija(oo, 12, 5);
		 o = new zmija(oo, 14, 7);
		 o = new zmija(oo, 16, 10);

		 o = new trawa(oo, 18, 19);

		 o = new guarana(oo, 7, 5);

		 o = new mlecz(oo, 1, 11);
}
bool swiat::czyZajete(int x, int y)
{
	if (mapa[x][y] == NULL || mapa[x][y] == nullptr) { return 0; }
	else { return 1; }
}
void swiat::gra()
{
	int ile_usunac = 0;//ile nulli w kolejce usunac
	for (int j = 0; j < ktory_el_kolejki; j++)//sortowanie bąbelkowe po inicjatywie
	{
		for (int i = 0; i < ktory_el_kolejki; i++)
	  {
		if (kolejka_ruchu[i] != nullptr && kolejka_ruchu[i]->pozycja_x() + 1 >= 0) 
		{						
			if(kolejka_ruchu[i + 1]!=NULL&& kolejka_ruchu[i + 1]->zwroc_inicjatywa() != NULL)
			{

				if (kolejka_ruchu[i]->zwroc_inicjatywa() < kolejka_ruchu[i + 1]->zwroc_inicjatywa()) 
				{
					organizm *org = kolejka_ruchu[i];
					kolejka_ruchu[i] = kolejka_ruchu[i + 1];
					kolejka_ruchu[i + 1] = org;
				}

			}
				
		}
		if ((kolejka_ruchu[i] == NULL || kolejka_ruchu[i]->sila_organizmu() <0) && i < (ktory_el_kolejki - ile_usunac))
		{
			organizm *org = kolejka_ruchu[ktory_el_kolejki - ile_usunac - 1];
			kolejka_ruchu[i] = org;
			kolejka_ruchu[ktory_el_kolejki - ile_usunac - 1] = NULL;
			//	kolejka_ruchu[i] = org;
			ile_usunac++;
		}
		
	  }
	}
	for (int j = ktory_el_kolejki; j < ktory_el_kolejki + ile_usunac; j++)  // od konca zerujemy kolejke
	{
		int i = (j - ktory_el_kolejki);
		kolejka_ruchu[ktory_el_kolejki - i] = NULL;
	}

	ktory_el_kolejki = ktory_el_kolejki - ile_usunac;
	int x = ktory_el_kolejki;


	for (int i = 0; i < x; ++i)
	{
		organizm *org = kolejka_ruchu[i];
		
		if (org != nullptr)
		{
			if (org->czy_umarl())
			{
				int x = org->pozycja_x();
				int y = org->pozycja_y();
				org->usun_org();
				kolejka_ruchu[i] = NULL;
				if (x>=0&&x<=20&&y>=0&&y<=20) { dodaj_organizm_do_mapy(NULL, x, y);				}//ustawiamy puste pole
				
			}
			else if(kolejka_ruchu[i]->pozycja_x() >= 0)
			{

				org->akcja(*this);

				if (org->czy_umarl())
				{
					int x = org->pozycja_x();
					int y = org->pozycja_y();
					org->usun_org();
					kolejka_ruchu[i] = NULL;
					if (x >= 0 && x <= 20 && y >= 0 && y <= 20) { dodaj_organizm_do_mapy(NULL, x, y); } //ustawiamy puste pole
					
				}
			}
		}
	}
}
organizm* swiat::organizm_na_polu(int x, int y)
{
	return mapa[x][y];
}
void swiat::dodaj_organizm_do_kolejki(organizm* org)
{
	kolejka_ruchu[ktory_el_kolejki] = org;
	ktory_el_kolejki++;
}
void swiat::dodaj_organizm_do_mapy(organizm *org, int x, int y)
{
	mapa[x][y] = org;
}

void swiat::przesun_organizm_na_mapie(organizm *org, int nx, int ny, int x, int y)
{
	if (this->czyZajete(nx, ny))
	{
		organizm *a = mapa[nx][ny];
		a->ustaw_pozycje(x, y);
		mapa[x][y] = a; 
		org->ustaw_pozycje(nx, ny);
		mapa[nx][ny] = org;	
	}
	else
	{
		mapa[x][y] = NULL;
		org->ustaw_pozycje(nx, ny);
		mapa[nx][ny] = org;		
	}
}
void swiat::rysujSwiat()
{
	cout << "\n   ";
	for (int j = 1; j < N+1; j++)
	{
		if (j < 10)
		{
			cout << j << "  ";
		}
		else
		{
			cout << j << " ";
		}
	}
	cout << "   LEGENDA:\n";
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			if (i == 0 && j < 9)
			{
				cout << j+1 << "  ";
			}
			if (i == 0 && j > 8)
			{
				cout << j+1 << " ";
			}

			if (mapa[i][j] != NULL)
				cout << mapa[i][j]->rysowanie() << "  ";
			else
				cout << (".  ");
		}
		cout<<"    " <<legenda[j]<< "\n";
	}
	cout << "\n";
}
swiat::~swiat()
{
}
