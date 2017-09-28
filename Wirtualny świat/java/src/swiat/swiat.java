
package swiat;
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.util.Random;
import java.util.Scanner;
import java.io.File;
import java.awt.EventQueue;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import javax.swing.ImageIcon;
import organizm.organizm;
import organizm.wilk;
import organizm.owca;
import organizm.zmija;
import organizm.robak;
import organizm.leniwiec;
import organizm.trawa;
import organizm.guarana;
import organizm.mlecz;


public class swiat {
    
    public  swiat()
    {
        for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			mapa[i][j] = null;
		}
	}
	

    }
public void start(swiat ref){
		organizm o = new wilk(this, 1, 2);		
		 o = new wilk(this, 3, 6);	
		 o = new wilk(this,1,4);
	
		 o = new owca(this, 3, 2);
		 o = new owca(this, 5, 3);
		 o = new owca(this, 7, 2);

		 o = new leniwiec(this, 8, 13);
		 o = new leniwiec(this, 10, 16);
		 o = new leniwiec(this, 12, 11);
		 o = new leniwiec(this, 9, 6);

		 o = new robak(this, 17, 1);
		 o = new robak(this, 17, 3);
		 o = new robak(this, 19, 2);

		 o = new zmija(this, 12, 5);
		 o = new zmija(this, 14, 7);
		 o = new zmija(this, 16, 10);

		 o = new trawa(this, 18, 19);

		 o = new guarana(this, 7, 5);

		 o = new mlecz(this, 1, 11);
}
public void wykonajTure()
    {

//KOLEJKA
        
        Collections.sort(kolejka_ruchu);
        
        int wielkosc_kolejki = kolejka_ruchu.size();
	for (int i = 0; i < wielkosc_kolejki; ++i)
	{
		organizm org = kolejka_ruchu.get(i);
              
		if (org != null)
		{
			if (org.czy_umarl())
			{
				int x = org.pozycja_x();
				int y = org.pozycja_y();
				org = null;
				kolejka_ruchu.set(i, null);
				dodaj_organizm_do_mapy(null, x, y);
				this.usuniecie_organizmu();
			}
			if (org == null)
				continue;
                        else{
			//if (org.Wiek() > 0)
				org.akcja(this);

			org.zwieksz_Wiek();

			

			if (org.czy_umarl())
			{
				int x = org.pozycja_x();
				int y = org.pozycja_y();
				org = null;
				kolejka_ruchu.set(i, null);
				dodaj_organizm_do_mapy(null, x, y);
				this.usuniecie_organizmu();
			}
                        }}
	}
        for (int i=0; i<kolejka_ruchu.size();i++)
        {
            kolejka_ruchu.remove(null);
        }      
    }
    
public void zapisz_swiat() throws FileNotFoundException
    {
        PrintWriter swiat = new PrintWriter("zapis.txt");
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			if (mapa[i][j] != null)
                            swiat.println(mapa[i][j].rysowanie() + " " + i + " " + j + " " + mapa[i][j].sila_organizmu() + " " + mapa[i][j].initiative() + " " + mapa[i][j].Wiek());
		}
	} 
        swiat.close();
    }
    
 public void wczytaj_swiat() throws FileNotFoundException
    {
       for (int j = 0; j < N; j++)
       {
            for (int i = 0; i < N; i++)
            {
		mapa[i][j] = null;
            }
       }
       kolejka_ruchu.clear();
       this.ustaw_organizmy(0);
        
        
      FileReader fr = new FileReader("zapis.txt");
      BufferedReader bfr = new BufferedReader(fr);
      String zdanie; 
      char zwierze;
      int x;
      int y;
      int sila;
      int inicjatywa;
      int wiek;
    
      String[] pola;
     // int numer=0;
      try 
      {
            while((zdanie = bfr.readLine()) != null)
            {
                 pola = zdanie.split(" ");
                 zwierze = pola[0].charAt(0);;
                 x = Integer.parseInt(pola[1]);
                 y = Integer.parseInt(pola[2]);
                 sila = Integer.parseInt(pola[3]);
                 inicjatywa = Integer.parseInt(pola[4]);
                 wiek = Integer.parseInt(pola[5]);                 
//		if (zwierze == 'W') { numer = 1; }
//		else if (zwierze == 'L') { numer = 2; }
//		else if (zwierze == 'R') { numer = 3; }
//		else if (zwierze == 'O') { numer = 4; }
//		else if (zwierze == 'Z') { numer = 5; }
//		else if (zwierze == 'T') { numer = 6; }
//		else if (zwierze == 'G') { numer = 7; }
//                else if (zwierze == 'M') { numer = 8; }
                organizm o = null;
                 
                 switch (zwierze)
		{
		case 'W': 
			o = new wilk(this, x ,y);
			break;
		case 'L': 
			o = new leniwiec(this, x, y); 
			break;
		case 'R': 
			o = new robak(this, x, y);
			break;
		case 'O': 
			o = new owca(this, x, y);
			break;
		case 'Z': 
			o = new zmija(this, x, y);
			break;
		case 'T': 
			o = new trawa(this, x, y);
			break;
		case 'G': 
			o = new guarana(this, x, y);
			break;
		case 'M': 
			o = new mlecz(this, x, y);
			break;
		}
		//o.ustaw_pozycje(x, y);
		o.ustaw_sila_organizmu(sila);
		o.ustaw_initiative(inicjatywa);
		o.ustaw_wiek(wiek);
		
		//this.dodaj_organizm_do_mapy(o, x, y);
            }
            return;
      }
      catch (IOException e) 
      {
        System.out.println("BŁĄD ODCZYTU Z PLIKU!");
        System.exit(1);
      }
    }



































 // rysowanie konsola   
    public void rysujSwiat()
    {
        System.out.print("   ");
	for (int j = 0; j < N; j++)
	{
		if (j < 9)
		{
			 System.out.print((j+1) + "  ");
		}
		else
		{
			 System.out.print((j+1) + " ");
		}
	}
	System.out.println("");
	for (int j = 0; j < N; j++)
	{
		for (int i = 0; i < N; i++)
		{
			if (i == 0 && j < 9)
			{
				 System.out.print((j+1) + "  ");
			}
			if (i == 0 && j > 8) 
			{
				System.out.print((j+1) + " ");
			}

			if (mapa[i][j] != null)
                            System.out.print(mapa[i][j].rysowanie() + "  ");
			else
                             System.out.print(".  ");
		}
		System.out.println("");
	}
	System.out.println("");
    }
    public boolean czyZajete(int x, int y)
    {
        return mapa[x][y] != null;
    }
    public organizm organizm_na_polu(int x, int y)
    {
        return mapa[x][y];
    }
    public void dodaj_organizm_do_kolejki(organizm org)
    {
	kolejka_ruchu.add(org);
    }
    public void dodaj_organizm_do_mapy(organizm org, int x, int y)
    {
        mapa[x][y] = org;
    }
    public void przesun_organizm_na_mapie(organizm org, int nx, int ny, int x, int y)
    {
        if (this.czyZajete(nx, ny))
	{
		organizm a = mapa[nx][ny];
		a.ustaw_pozycje(x, y);
		mapa[x][y] = a;
                org.ustaw_pozycje(nx, ny);
		mapa[nx][ny] = org;
	}
	else
	{
		mapa[x][y] = null;
                org.ustaw_pozycje(nx, ny);
		mapa[nx][ny] = org;
	}
    }
    public void dodanie_organizmu()
    {
        ile_organizmow += 1;
    }
    public void usuniecie_organizmu()
    {
        ile_organizmow -= 1;
    }
    public void ustaw_organizmy(int org)
    {
        ile_organizmow = org;
    }
    public int ilosc_organizmow()
    {
        return ile_organizmow;
    }
    

    

    
   
    
    
    public static final int N = 20;
    protected organizm[][] mapa = new organizm[N][N];
    protected List<organizm> kolejka_ruchu = new ArrayList<organizm>();
    protected int ile_organizmow;
    
}
