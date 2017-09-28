
package organizm;
import java.util.Random;
import static organizm.organizm.N;
import swiat.swiat;


public class leniwiec extends zwierze {
    public leniwiec(swiat WielkiSwiat, int x, int y)
    {
        super(WielkiSwiat, x, y);
	this.sila = 2;
	this.inicjatywa = 1;
	this.nazwa = 'L';
        this.ruch = true;
        this.specjalna_kolizja = false;
    }
    
    @Override
    public void akcja(swiat ref)
    {       
        if (this.ruch == true) {
		this.ruch = false;		
		Random r = new Random();
          Random rr = new Random();
        int ra = rr.nextInt(4)+1; //starts at 0, so add 1


	int x = this.x;
	int y = this.y;

	//boolean[] co_sprawdzilismy = new boolean[4];  //gora dol lewo prawo -- gdzie nie mozna isc
       boolean[] co_sprawdzilismy = { false,false,false,false };
        
	if (this.x == 0 && this.y == 0) //lewa gora
	{
		co_sprawdzilismy[0] = true; //gora
		co_sprawdzilismy[2] = true; //lewo
	}
	else if (this.x == N - 1 && this.y == 0)  //prawa gora
	{
		co_sprawdzilismy[0] = true; //gora
		co_sprawdzilismy[3] = true; // prawo
	}
	else if (this.x == 0 && this.y == N - 1)  //lewy dol
	{
		co_sprawdzilismy[1] = true; //dol
		co_sprawdzilismy[2] = true; //lewo
	}
	else if (this.x == N - 1 && this.y == N - 1) //prawy dol
	{
		co_sprawdzilismy[1] = true; //dol
		co_sprawdzilismy[3] = true; // prawo
	}
	else if (this.x == 0 && this.y > 0 && this.y < N) //krawędź lewo
	{
		co_sprawdzilismy[2] = true; //lewo
	}
	else if (this.x == N - 1 && this.y > 0 && this.y < N) //krawędź prawo
	{
		co_sprawdzilismy[3] = true; // prawo		
	}
	else if (this.y == 0 && this.x > 0 && this.x < N) //krawędź gora
	{
		co_sprawdzilismy[0] = true; //gora
	}
	else if (this.y == N - 1 && this.x > 0 && this.x < N) //krawędź dol
	{
		co_sprawdzilismy[1] = true; //dol
	}
		
		while (co_sprawdzilismy[ra-1] != false) { ra = rr.nextInt(4)+1; };//losujemy r tak dlugo az trafimy na dozwolone pole

		// czy kolizja?

		switch (ra)
		{
		case 1: --y; break;
		case 2: ++y; break;
		case 3: --x; break;
		case 4: ++x; break;
		}
		

		if (ref.czyZajete(x, y)) {
			if(!ref.organizm_na_polu(x, y).czy_umarl())// jesli umarł to nie ma kolizji , tylko zamieniamy sie miejscami
			{ 
				kolizja(this, ref.organizm_na_polu(x,y));
			}			
		}

	
		if (  this != null && (!ref.czyZajete(x, y) || ref.organizm_na_polu(x, y).czy_umarl())) 
		{
                   // System.out.println("dsawauhdwahibdriwab");
		ref.przesun_organizm_na_mapie(this, x, y, this.x, this.y);
		}
	}
        else { 
	this.ruch = true;
	System.out.println("leniwiec spi");
	}
   
    }

    public void nowy(swiat WielkiSwiat, int x, int y)
    {
        organizm o = new leniwiec(WielkiSwiat, x, y);
    }
    public String nazwa()
    {
        return "Leniwiec";
    }

}
