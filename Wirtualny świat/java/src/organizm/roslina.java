
package organizm;
import java.util.Random;
import swiat.swiat;

public abstract class roslina extends organizm {
    roslina(swiat WielkiSwiat, int x, int y)
    {
        super(WielkiSwiat, x, y);
    }
        public void kolizja(organizm o,organizm o2)
    {
         }
        
    @Override
    public void akcja(swiat ref) {
	Random r = new Random();
        if (r.nextBoolean()) { // 50% szansy na rozmnorzenie rosliny
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
