
import java.util.HashMap;

abstract class Wyrazenie
{
	public abstract double oblicz() throws Exception;
}
abstract class Operator extends Wyrazenie
{
	public Wyrazenie a;
	public Wyrazenie b;
	public Operator(Wyrazenie x, Wyrazenie y)
	{
		this.a = x;
		this.b = y;
	}
	public String toString()
	{
		try{
			return Double.toString(this.oblicz());
		}
		catch(Exception e){
			System.out.println("DIVIDING BY 0!");
		}
		return "Error";
	}
}
class Dodaj extends Operator
{
	public Dodaj(Wyrazenie x,Wyrazenie y)
	{
		super(x,y);
	}
	public double oblicz()
	{
		try{
			return (a.oblicz() + b.oblicz());
		}
		catch(Exception e){
			System.out.println("DIVIDING BY 0!");
		}
		return -1;
	
	}
}
class Odejmij extends Operator
{
	public Odejmij(Wyrazenie x,Wyrazenie y)
	{
		super(x,y);
	}
	public double oblicz()
	{
		try{
			return (a.oblicz() - b.oblicz());
		}
		catch(Exception e){
			System.out.println("DIVIDING BY 0!");
		}
		return -1;
	}
}
class Pomnoz extends Operator
{
	public Pomnoz(Wyrazenie x,Wyrazenie y)
	{
		super(x,y);
	}
	public double oblicz()
	{
		try{
			return (a.oblicz() * b.oblicz());
		}
		catch(Exception e){
			System.out.println("DIVIDING BY 0!");
		}
		return -1;
	}
}
class Podziel extends Operator
{
	public Podziel(Wyrazenie x,Wyrazenie y)
	{
		super(x,y);
	}
	public double oblicz() throws Exception
	{
		if(b.oblicz() == 0)
			throw new Exception();
		try{
			return (a.oblicz() / b.oblicz());
		}
		catch(Exception e){
			System.out.println("DIVIDING BY 0!");
		}
		return -1;
	}
}
class Stala extends Wyrazenie
{
	public double a;
	public Stala(double x)
	{
		this.a = x;
	}
	public double oblicz()
	{
		return a;
	}

}
class Zmienna extends Wyrazenie
{
	public String zmienna;
	public static zbior_zmiennych zbior = new zbior_zmiennych();
	public Zmienna(String x)
	{
		this.zmienna = x;
	}
	public double oblicz()
	{
		return zbior.get(zmienna);
	}
}
class zbior_zmiennych
{
	public static HashMap<String,Double> tablica_hasz = new HashMap<String,Double>();
	public void add(String nazwa, double wartosc)
	{
		tablica_hasz.put(nazwa,wartosc);
	}
	public double get(String zmienna)
	{
		return tablica_hasz.get(zmienna);
	}
}
public class zad2 {
    public static void main(String[] args)
    {
    	zbior_zmiennych nasz_zbior = new zbior_zmiennych();
    	nasz_zbior.add("x",10);
    	nasz_zbior.add("y",20);
    	nasz_zbior.add("z",55);
    	nasz_zbior.add("e",2);
    	nasz_zbior.add("pi",3.14);
    	Wyrazenie w1 = new Pomnoz(
    		new Dodaj(new Odejmij(new Stala(3),new Zmienna("e")),new Stala (0)),
    		new Podziel(new Stala(2), new Zmienna("x"))); // ((3-e)+ 0)*(2/x)) ~ 0,2
    	try{
    		System.out.println(w1);
    	}
    	catch(Exception e)
    	{
    		System.out.println("DIVIDING BY ZERO!!!");
    	}
    	Wyrazenie w2 = new Podziel(new Pomnoz(new Stala(5), new Stala(5)), new Zmienna("pi"));
    	// 5^2/pi ~ 7,96
    	try{
    		System.out.println(w2);
    	}
    	catch(Exception e)
    	{
    		System.out.println("DIVIDING BY ZERO!!!");
    	}
    	Wyrazenie w3_error = new Podziel(new Dodaj(new Stala(10),new Zmienna("y")),
    		new Podziel(new Zmienna("z"),new Stala(0)));
    	// (10 + y)/(z/0)
    	try{
    		System.out.println(w3_error);
    	}
    	catch(Exception e)
    	{
    		System.out.println("DIVIDING BY ZERO!!!");
    	}
    }
}