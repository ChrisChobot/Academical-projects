
package organizm;
import swiat.swiat;
import java.util.Random;


public abstract class zwierze extends organizm {
    zwierze(swiat WielkiSwiat, int x, int y)
    {
        super(WielkiSwiat, x, y);
    }

    
    @SuppressWarnings("empty-statement")
 public void akcja(swiat ref) {

	

    Random r = new Random();
        int ra = r.nextInt(4)+1; //starts at 0, so add 1


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
		
		while (co_sprawdzilismy[ra-1] != false) { ra = r.nextInt(4)+1; };//losujemy r tak dlugo az trafimy na dozwolone pole

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

    @Override 
    public void kolizja(organizm ten, organizm tamten) 
{
    int a = this.sila_organizmu();
    int b = tamten.sila_organizmu();
    char c = this.rysowanie();
    char d = tamten.rysowanie();       
	if (a == b) 
	{
		if (c == d) 
		{ 
			rozmnarzanie(ref);
		}
		else
		{
		tamten.ustaw_czy_zyje(false);
		   System.out.println( c + " zabil " + d + " na polu: " + tamten.pozycja_x()+":"+tamten.pozycja_y() );
		if (tamten.specjalna_kolizja == true) { tamten.spec_kolizja(ten); }
		}
	}
	else if (a > b) 
	{
		if (c == d) 
		{
			rozmnarzanie(ref);

		}
		else 
		{
			tamten.ustaw_czy_zyje(false);
			  System.out.println( c + " zabil " + d + " na polu: " + tamten.pozycja_x()+":"+tamten.pozycja_y() );
		if (tamten.specjalna_kolizja == true) { tamten.spec_kolizja(this); }
		}
	}
	else if (a < b) 
	{
		if (c == d) 
		{
			rozmnarzanie(ref);
		}
		else 
		{
			this.ustaw_czy_zyje(false);
                          System.out.println( d + " zabil " + c + " na polu: " + tamten.pozycja_x()+":"+tamten.pozycja_y() );
		if (this.specjalna_kolizja == true) { this.spec_kolizja(tamten); }
		}
	}
}
public void rozmnarzanie(swiat ref) // 50% szans na nowe
{ 
    Random r = new Random();
    if (r.nextBoolean()) {
		int ra = r.nextInt(4)+1; //starts at 0, so add 1
		int x = this.x;
		int y = this.y;

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

		while (co_sprawdzilismy[ra-1] != false) { ra = r.nextInt(4)+1; };//losujemy r tak dlugo az trafimy na dozwolone pole
		 // czy kolizja?

		switch (ra)
		{
		case 1: --y; break;
		case 2: ++y; break;
		case 3: --x; break;
		case 4: ++x; break;
		}

		
		if (!ref.czyZajete(x, y)) {
			if (ref.organizm_na_polu(x, y) == null) {
				this.nowy(ref, x, y);
                                System.out.println("dodano " + this.rysowanie() + " na polu: " + (x+1) + ":" + (y+1));
			}
		}
	}
}
}
