
package organizm;
import java.util.Random;
import swiat.swiat;


public class guarana extends roslina {
    public guarana(swiat WielkiSwiat, int x, int y)
    {
        super(WielkiSwiat, x, y);
    	this.nazwa = 'G';
        this.specjalna_kolizja = true;
    }
    @Override
  public void spec_kolizja(organizm org) {
	org.ustaw_sila_organizmu(org.sila_organizmu() + 3);
        System.out.println(org.rysowanie() + " na polu: " + (x+1) + ":" + (y+1) + " zwiekszyl swoja sile o 3");
}
    public void nowy(swiat WielkiSwiat, int x, int y)
    {
        organizm o = new guarana(WielkiSwiat, x, y);
    }


}