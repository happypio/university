/*
  Copyright (c) November 2015 by Paweł Rzechonek
  Program wczytuje dane linia po linii ze standardowego wejścia,
  przekształca każdą linię tekstu na liczbę i sprawdza czy jest ona pierwsza czy nie.
  Istotne elementy w programie:
    * łapanie wyjątku, który może powstać przy przekształcaniu tekstu na liczbę całkowitą;
    * wykorzystanie asercji do sprawdzania czy podane liczby są dodatnie;
    * użycie dziennika z rejestratorem plikowym do notowania każdego wywołania funkcji
      testującej pierwszość liczby.
*/

import java.io.*;
import java.util.logging.*;

public class Dziennik
{
    private static boolean pierwsza (int p)
    {
        if (p < 2) return false;
        if (p == 2) return true;
        if (p % 2 == 0) return false;
        for (int i = 3; i * i <= p; i += 2)
            if (p % i == 0) return false;
        return true;
    }
    public static void main (String[] args) throws IOException
    {
        // utworzenie dziennika
        Logger logger = Logger.getLogger(Dziennik.class.getName());
        // utworzenie rejestratora komunikatów związanego z plikiem
        Handler handler = new FileHandler(Dziennik.class.getName() + ".log", true);
        // ustawienie prostego tekstowego formatera dla komunikatów w rejestratorze
        handler.setFormatter(new SimpleFormatter());
        // dodanie rejestratora do dziennika
        logger.addHandler(handler);
        System.out.println("Nazwa klasy/dziennika: " + Dziennik.class.getName());
        System.out.println("Wpisuj tylko liczby naturalne!");
        BufferedReader we = new BufferedReader(new InputStreamReader(System.in));
        // początek logowania komunikatów
        logger.entering(Dziennik.class.getName(), "main");
        for (String ln = we.readLine(); ln != null; ln = we.readLine())
        {
            ln = ln.trim();
            if (ln.equals("")) continue;
            int n = 0;
            try 
            {
                n = new Integer(ln);
                // asercja sprawdzająca, czy wpisana liczba jest liczbą naturalną
                assert n > 0: "oczekiwano liczby naturalnej";
                if (pierwsza(n)) System.out.println("pierwsza");
                else System.out.println("złożona");
                // wstawienie komunikatu do dziennika
                logger.log(Level.INFO, "pierwsza(" + n + ")");
            }
            catch (NumberFormatException ex) { System.out.println("Czy to jest liczba?"); }
        }
        // zakończenie logowania komunikatów
        logger.exiting(Dziennik.class.getName(), "main");
        System.out.println("=======================");
    }
}
