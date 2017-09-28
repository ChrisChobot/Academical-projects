
package organizm;
import swiat.swiat;


public class owca extends zwierze {
    public owca(swiat WielkiSwiat, int x, int y)
    {
        super(WielkiSwiat, x, y);
        sila = 2;
	inicjatywa = 4;
        this.nazwa = 'O';
        
    }
   
    @Override
    public void nowy(swiat WielkiSwiat, int x, int y)
    {
        organizm o = new owca(WielkiSwiat, x, y);
    }
    public String nazwa()
    {
        return "Owca";
    }
}