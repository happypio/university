/*
  Copyright (c) December 2010 by Paweł Rzechonek
  Aplikacja okienkowa Swing - losuje 6 liczb z zakresu 1...49.
  Wylosowane liczby są wyświetlane w liście JList: liczby złożone na niebieski
  a liczby pierwsze na czerwono (przykład MVC).
*/

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

// kreślarz danych związanych z listą
class KreslarzElementowListy extends JLabel implements ListCellRenderer
{
    // sito Eratostenesa
	private static final boolean[] sito = new boolean [ModelDanych.ZAKRES+1];
	static
	{
	    sito[2] = true;
	    for (int i=2; i<=ModelDanych.ZAKRES; sito[i++]=true);
	    for (int i=2; i*i<=ModelDanych.ZAKRES; i++)
	        if (sito[i])
	            for (int j=i*2; j<=ModelDanych.ZAKRES; j+=i) sito[j] = false;
	}

    // w konstruktorze ustawiamy globalne parametry wyswietlania elementów listy
    public KreslarzElementowListy ()
    {
        setHorizontalAlignment(CENTER);
    }

    // sposób wyświetlania elementu listy (liczby pierwsze na czerwono, pozostale na niebiesko)
    public Component getListCellRendererComponent (
    JList lista, Object elem, int indeks, boolean zazn, boolean fokus)
    {
        String napis = elem.toString();
        setText(napis);
        if (sito[((Integer)elem).intValue()]) setForeground(Color.RED);
        else setForeground(Color.BLUE);
        return this;
    }
}

// model danych zwiazany z lista
class ModelDanych extends AbstractListModel
{
    public static final int zakres = 6; // liczba losowanych kul
    public static final int ZAKRES = 49; // liczba wszystkich kul

    private static final Random generator = new Random(); // generator liczb losowych

    // tablica ze wszystkimi kulami (1...49)
    private static Integer[] Tablica = new Integer[ZAKRES];
    static
    {
        for (int i=0; i<ZAKRES; i++) Tablica[i] = new Integer(i+1);
    }

    // tablica z wylosowanymi kulami
    private Integer[] tablica = null;

    // wylosowanie nowego zestawu kul
	public void losuj ()
	{
	    if (tablica==null) tablica = new Integer[zakres];
	    for (int i=0; i<zakres; i++)
	    {
	        int j = generator.nextInt(ZAKRES-i)+i;
	        Integer k = Tablica[j];
	        Tablica[j] = Tablica[i];
	        tablica[i] = Tablica[i] = k ;
	    }
	    fireContentsChanged(this,0,getSize()-1); // powiawomienie o zmianie danych
	}

    // w konstruktorze okreslamy poczatkowy zestaw danych
	public ModelDanych ()
	{
	}

    // pobranie i-tego elementu (metoda potrzebna do wyswietlenia listy)
	public Object getElementAt (int i)
	{
		return tablica[i];
	}

    // dlugosc listy (metoda potrzebna do wyswietlenia listy)
	public int getSize ()
	{
		return tablica==null?0:tablica.length;
	}
}

public class Totolotek extends JFrame
{
	protected JList lista;
	protected ModelDanych model;
	protected JButton losowanie;

    private class Zdarzenie implements ActionListener
    {
    	public void actionPerformed(ActionEvent ev)
    	{
    		model.losuj();
    	}
    }
    
	public Totolotek ()
	{
		super("Totolotek");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		model = new ModelDanych();
		lista = new JList(model);
		lista.setCellRenderer(new KreslarzElementowListy());
		getContentPane().add(new JScrollPane(lista),BorderLayout.CENTER);
		losowanie = new JButton("losowanie nowych numerów w totolotku");
		losowanie.addActionListener(new Zdarzenie());
		getContentPane().add(losowanie,BorderLayout.SOUTH);
		setSize(300,150);
		setVisible(true);
	}

	public static void main (String[] args)
	{
		new Totolotek();
	}
}

