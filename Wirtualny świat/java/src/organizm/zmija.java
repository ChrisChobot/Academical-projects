
package organizm;
import swiat.swiat;


public class zmija extends zwierze {
    public zmija(swiat WielkiSwiat, int x, int y)
    {
        super(WielkiSwiat, x, y);
      	this.sila = 2;
	this.inicjatywa = 3;
	this.nazwa = 'Z';
	this.specjalna_kolizja = true;
    }
    
    @Override
    public void spec_kolizja(organizm org) 
{
	org.ustaw_czy_zyje(false);
        System.out.print(org.rysowanie() + " umarl od jadu");
	
}

    public void nowy(swiat WielkiSwiat, int x, int y)
    {
        organizm o = new zmija(WielkiSwiat, x, y);
    }

}
