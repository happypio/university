/*
  Copyright (c) October 2014 by Paweł Rzechonek
  Program definiuje klasę przechowującą jakąś nieznaną liczbę i udostępnia podstawowe
  narzędzia do zgadnięcia tej liczby.
  Istotne elementy w programie:
    * definicja własnego wyjątku;
    * zgłaszanie i łapanie wyjątków;
    * wykorzystanie asercji do sprawdzania niezmienników w programie.
*/

import java.util.*;

class Wątek extends Thread
{
    private final String nazwa;
    private final BlackBox skrzynka;

    public Wątek (String naz, BlackBox skrz)
    {
        if (naz==null || skrz==null) throw new NullPointerException();
        nazwa = naz;
        skrzynka = skrz;
    }

    public void run ()
    {
        try
        {
            for (int d=skrzynka.minBound(), g=skrzynka.maxBound(); d<g; )
            {
                int x = (int)(d+Math.random()*(g-d+1));
                Thread.sleep((int)(100+Math.random()*100)); 
                if (skrzynka.check(x)) d = g = x;
                else { d=skrzynka.minBound(); g=skrzynka.maxBound(); }
                System.out.format("%s: %d - %d\n", nazwa, d, g);
            }
            System.out.format("%s: %d\n", nazwa, skrzynka.result());
        }
        catch (InterruptedException ex) { System.out.println(ex); return; }
        catch (CheckException ex) { System.out.println(ex); return; }
    }
}

class CheckException extends Exception
{
    public CheckException ()
    {
        super("the value is unknown");
    }
    public String toString ()
    {
        return "the value is out of bounds";
    }
}

class BlackBox
{
    public final int MIN = 0, MAX = 1000;
    
    private final int X = (int)(MIN+Math.random()*(MAX-MIN+1));
    private int min = MIN, max = MAX;
    
    public int minBound () { return min; }
    public int maxBound () { return max; }
    
    // wartość argumentu x nie może wykraczać poza przedział
    // określony na podstawie wcześniejszych trafień
    public boolean check (int x)
    {
        assert min<=x && x<=max: "the argument is outside the current scope";
        if (x<=X) { min = x+1; return false; } // an error: change x<=X to x<X
        if (X<=x) { max = x-1; return false; } // an error: change X<=x to X<x
        min = max = x;
        return true;
    }
    
    // wynik jest udostępniany tylko wtedy, gdy wcześniej został odgadnięty
    public int result () throws CheckException
    {
        assert min>X || max<X: "the current scope does not include results";
        if (min==max) return X;
        throw new CheckException();
    }
}

public class Zgadywanka
{
    private static BlackBox schowek = new BlackBox();

    public static void main (String[] args)
    {
        new Wątek("A",schowek).start();
        new Wątek("B",schowek).start();
        //new Wątek("C",schowek).start();
    }
}
