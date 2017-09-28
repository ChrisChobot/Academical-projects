package swiat;
import swiat.swiat;


import java.io.FileNotFoundException;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener; 
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.BorderLayout;
import java.awt.Container;
import javax.swing.ImageIcon;
import javax.swing.JLabel;




public class Interfejs extends JFrame implements ActionListener {

// DEKLARACJE, przyciski, obrazki       
    static int wysokosc = 20;
    static int szerokosc = 20;
    
    GridLayout mapa = new GridLayout(wysokosc, szerokosc);
    JButton nastepnaTura = new JButton("Nastepna Tura");
    JButton zapisz = new JButton("Zapisz");
    JButton wczytaj = new JButton("Wczytaj"); 
    
    ImageIcon tlo = new ImageIcon("tlo.jpg");
    ImageIcon owca = new ImageIcon("owca.jpg");
    ImageIcon wilk = new ImageIcon("wilk.jpg");
    ImageIcon zmija = new ImageIcon("zmija.jpg");
    ImageIcon robak = new ImageIcon("robak.jpg");
    ImageIcon leniwiec = new ImageIcon("leniwiec.jpg");
    ImageIcon trawa =  new ImageIcon("trawa.jpg");
    ImageIcon guarana = new ImageIcon("guarana.jpg");
    ImageIcon mlecz = new ImageIcon("mlecz.jpg");
    ImageIcon tab[][] = new ImageIcon[szerokosc][wysokosc];
    
    
    
    static Interfejs gui;
    JPanel mapka;
    static swiat swiat;
 
    
    public Interfejs() {
        super("Krzysztof Chobot");
        nastepnaTura.addActionListener(this);
        zapisz.addActionListener(this);
        wczytaj.addActionListener(this);
        ustawTablice();
	setResizable(true);
    }
  
    
// wypelnienie mapy    
    public void ustawTablice() {
        for(int y = 0; y < wysokosc; y++) {
            for(int x = 0; x < szerokosc; x++) {
                if (swiat.czyZajete(x,y) == false)
                {
                    tab[y][x] =  tlo;
                }
                else if(swiat.mapa[x][y].rysowanie()=='O')
                {                  
                    tab[y][x] =  owca;
                }
                else if(swiat.mapa[x][y].rysowanie()=='W')
                {
                    tab[y][x] = wilk;
                }
                else if(swiat.mapa[x][y].rysowanie()=='L')
                {
                    tab[y][x] =  leniwiec;
                }
                else if(swiat.mapa[x][y].rysowanie()=='Z')
                {
                    tab[y][x] =  zmija;
                }
                else if(swiat.mapa[x][y].rysowanie()=='R')
                {
                    tab[y][x] =  robak;
                }
                else if(swiat.mapa[x][y].rysowanie()=='T')
                {
                    tab[y][x] = trawa;
                }
                else if(swiat.mapa[x][y].rysowanie()=='G')
                {
                    tab[y][x] =  guarana;
                }
                else if(swiat.mapa[x][y].rysowanie()=='M')
                {
                    tab[y][x] =  mlecz;
                }
                else
                {
                      tab[y][x] =  tlo;
                }
            }
        }
    }
    
// rozmiar mapy  
    public void dodajElementy(final Container warstwa){
		mapka = new JPanel();
		mapka.setLayout(mapa);
                
		for (int i = 0;i<wysokosc;i++){
                      // mapka.add(new JLabel(String.valueOf(i)));
			for (int j =0;j<szerokosc;j++){
                            mapka.add(new JLabel(tab[i][j]));
                        }
                }      

//umiejscowienie przyciskow
                warstwa.add(nastepnaTura,BorderLayout.PAGE_START);
                warstwa.add(zapisz,BorderLayout.CENTER);
                warstwa.add(wczytaj,BorderLayout.LINE_END);
                warstwa.add(mapka,BorderLayout.LINE_START);
		
 
	}
    
//akcje dla przyciskow    
    
    @Override
	 public void actionPerformed(ActionEvent e) {
             Object source = e.getSource();
 
        if(source == nastepnaTura)
        {
            swiat.wykonajTure();
            swiat.rysujSwiat();
            ustawTablice();
            gui.getContentPane().removeAll();	 
            gui.dodajElementy(gui.getContentPane());
            gui.revalidate();
        }
        else if(source == zapisz)
        {
               try
             {
                 swiat.zapisz_swiat();
             }
             catch(FileNotFoundException w)
             {
                 System.out.println("BŁĄD PRZY OTWIERANIU PLIKU!");
             }
        }
         else if(source == wczytaj)
        {
            try
            {
                  swiat.wczytaj_swiat();                  
                  swiat.rysujSwiat();
                  ustawTablice();
                  gui.getContentPane().removeAll();	 
                  gui.dodajElementy(gui.getContentPane());
                  gui.revalidate();
                 
            }
            catch(FileNotFoundException s)
            {
                  System.out.println("BŁĄD PRZY OTWIERANIU PLIKU!");
            }
        }
        }
                 

 // interfejs on   
         private static void pokaz() {
            gui = new Interfejs();
            gui.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            gui.dodajElementy(gui.getContentPane());
            gui.pack();
            gui.setVisible(true);
         }
         
 // MAIN        
         public static void main(String[] args) {
	
               swiat = new swiat();
               swiat.start(swiat);
		javax.swing.SwingUtilities.invokeLater(new Runnable() {
                    public void run() {
                        pokaz();
                    }
                });
        }
}