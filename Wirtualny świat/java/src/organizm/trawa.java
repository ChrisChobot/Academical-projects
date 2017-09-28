
package organizm;
import java.util.Random;
import swiat.swiat;


public class trawa extends roslina {
    public trawa(swiat WielkiSwiat, int x, int y)
    {
        super(WielkiSwiat, x, y);
        this.nazwa = 'T';
    }
    
    public void nowy(swiat WielkiSwiat, int x, int y)
    {
        organizm o = new trawa(WielkiSwiat, x, y);
    }
    public String nazwa()
    {
        return "Trawa";
    }

}