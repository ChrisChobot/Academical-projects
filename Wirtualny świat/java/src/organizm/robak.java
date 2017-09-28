
package organizm;
import swiat.swiat;


public class robak extends zwierze {
    public robak(swiat WielkiSwiat, int x, int y)
    {
        super(WielkiSwiat, x, y);
      	this.sila = 1;
	this.inicjatywa = 1;
	this.nazwa = 'R';
	this.specjalna_kolizja = true;
    }
    
    @Override
  public void spec_kolizja(organizm org) {
	org.ustaw_sila_organizmu(org.sila_organizmu() + 2);
        System.out.println(org.rysowanie() + " na polu: " + (x+1) + ":" + (y+1) + " zwiekszyl swoja sile o 2");
}


    public void nowy(swiat WielkiSwiat, int x, int y)
    {
        organizm o = new zmija(WielkiSwiat, x, y);
    }

}
