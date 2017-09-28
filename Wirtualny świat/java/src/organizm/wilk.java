
package organizm;
import swiat.swiat;


public class wilk extends zwierze {
    public wilk(swiat WielkiSwiat, int x, int y)
    {
        super(WielkiSwiat, x, y);
        sila = 9;
	inicjatywa = 5;
        this.nazwa = 'W';
    }
   
    @Override
    public void nowy(swiat WielkiSwiat, int x, int y)
    {
        organizm o = new wilk(WielkiSwiat, x, y);
    }
    public String nazwa()
    {
        return "Wilk";
    }
    
}
