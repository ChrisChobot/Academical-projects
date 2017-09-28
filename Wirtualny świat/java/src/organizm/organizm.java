package organizm;
import swiat.swiat;
import java.util.Random;

public abstract class organizm implements Comparable<organizm>{
   public organizm(swiat WielkiSwiat, int x, int y)
   {
       	ref = WielkiSwiat;
	sila = 0;
	inicjatywa = 0;
	wiek = 0;
	nazwa = 0;
        specjalna_kolizja=false;
	czy_zyje = true;
        ruch = true;
	this.x = x;
	this.y = y;
	if (ref.czyZajete(x, y))
	{
		boolean kontynuowac = true;
		for (int j = 0; j < N; j++)
		{
			for (int i = 0; i < N; i++)
			{
				kontynuowac = ref.czyZajete(i, j);
				if (kontynuowac == false)
				{
					this.x = i;
					this.y = j;
					break;
				}
			}
			if (kontynuowac == false)
			{
				break;
			}
		}
	}
	ref.dodaj_organizm_do_mapy(this, this.x, this.y);
	ref.dodaj_organizm_do_kolejki(this);
	ref.dodanie_organizmu();
   }
   public abstract void nowy(swiat ref, int x, int y);
   public abstract void akcja(swiat ref);
   public abstract void kolizja(organizm o, organizm o2);
  public char rysowanie()
  {
  return this.nazwa ;
  }

   
   public boolean czy_umarl()
   {
       return !czy_zyje;
   }
   public void ustaw_czy_zyje(boolean zycie)
   {
       czy_zyje = zycie;
   }
   public int Wiek()
   {
       return wiek;
   }
   public void ustaw_wiek(int x)
   {
       wiek = x;
   }
   public int initiative()
   {
       return inicjatywa; 
   }
   public void ustaw_initiative(int x)
   {
       inicjatywa = x;
   }
   public int sila_organizmu()
   {
       return sila;
   }
   public void ustaw_sila_organizmu(int x)
   {
       sila = x;
   }
   public int pozycja_x()
   {
       return x;
   }
   public int pozycja_y()
   {
      return y;
   }
   public void zwieksz_Wiek()
   {
       wiek += 1;
   }
   public void ustaw_pozycje(int x, int y)
   {
       this.x = x;
       this.y = y;
   }
    public void spec_kolizja(organizm o){}
   
  @Override
  public int compareTo(organizm o) 
  {
      int porownanie = o.inicjatywa - this.inicjatywa;
 
      if(porownanie == 0) {
          return o.dlugosc_zycia - this.dlugosc_zycia;
      }
      else 
      {
          return porownanie;
      }
  }

   public static final int N = 20;
   protected int sila;
   protected int inicjatywa;
   protected int dlugosc_zycia;
   protected int wiek;
   protected int x;
   protected int y;
   protected char nazwa;
   protected boolean czy_zyje;
   protected boolean ruch;
   protected boolean specjalna_kolizja;
   protected swiat ref;
}