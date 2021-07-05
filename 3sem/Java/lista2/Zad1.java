class Wektor
{
	public final double dx;
	public final double dy;
	public Wektor(double dx, double dy)
	{
		this.dx = dx;
		this.dy = dy;
	}
	public static Wektor zloz(Wektor v1, Wektor v2)
	{
		return new Wektor(v1.dx + v2.dx, v1.dy + v2.dy);
	}
}

class Prosta
{
	public final double a;
	public final double b;
	public final double c;

	public Prosta(double a, double b, double c)
	{
		this.a = a;
		this.b = b;
		this.c = c;
	}
	public static Prosta przesun(Prosta a, Wektor v)
	{
		double new_c = a.c - a.a * v.dx - a.b * v.dy;
		return new Prosta(a.a, a.b, new_c);

	}
	public static boolean rownoleglosc(Prosta a, Prosta b)
	{
		if (a.a * b.b == b.a * a.b)
			return true;
		return false;

	}
	public static boolean prostopadlosc(Prosta a, Prosta b)
	{
		if (a.a * b.a == -a.b * b.b)
			return true;
		return false;

	}
	public static Punkt przeciecie(Prosta a, Prosta b)
	{
		//wspolczynniki a1 i a2 sa niezerowe jednoczesnie i a1b2 - b1a2 niezerowe bo proste z zal. nierownolegle
		double y = (a.c*b.a - a.a*b.c) / (a.a*b.b - a.b*b.a);
		double x;
		if (a.a == 0)
			x = (-b.c - b.b*y) / b.a;
		else
			x = (-a.c - a.b*y) / a.a;
		return new Punkt(x,y);
	}
}

class Punkt
{
	private Double x;
	private Double y;

	@Override 
	public boolean equals(Object obj)
	{
		if(this == obj)
			return true;
		if(obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Punkt other = (Punkt) obj;
		if (x == null && other.x != null)
			return false;
		if (y == null && other.y != null)
			return false;
		if (!x.equals(other.x)|| !y.equals(other.y))
			return false;
		return true;

	}
	public Punkt(double x, double y)
	{
		this.x = x;
		this.y = y;
	}
	public double getx()
	{
		return x;
	}
	public double gety()
	{
		return y;
	}
	public void przesun(Wektor v)
	{
		this.x += v.dx;
		this.y += v.dy;
	}
	public void obroc(Punkt p, double kat)
	{
		if (!p.equals(this))
		{
			this.przesun(new Wektor(p.getx(),p.gety()));
			double new_x = this.x * Math.cos(kat) - this.y * Math.sin(kat);
			double new_y = this.x * Math.sin(kat) + this.y * Math.cos(kat);
			this.przesun(new Wektor(-p.getx(),-p.gety()));

		}

	}
	public void odbij(Prosta p)
	{
		double a = - p.b;
		double b = p.a;
		double c = -a * this.x - b * this.y;
		
		Prosta prostopadla_p = new Prosta(a,b,c);
		Punkt w = Prosta.przeciecie(p,prostopadla_p);
	
		Wektor odbicie = new Wektor( (w.getx() - this.x) * 2, (w.gety() - this.y) * 2);

		this.przesun(odbicie);


	}
	public String toString()
	{
		return "( "+x+" , "+y+" )";
	}


}
class Odcinek
{
	private Punkt a;
	private Punkt b;

	public Odcinek(Punkt a, Punkt b) throws IllegalArgumentException
	{
		if (a.equals(b))
			throw new IllegalArgumentException("wprowadzone punkty są takie same.");

		this.a = a;
		this.b = b;
	}
	public void przesun(Wektor v)
	{
		this.a.przesun(v);
		this.b.przesun(v);
	}
	public void obroc(Punkt p, double kat)
	{
		this.a.obroc(p,kat);
		this.b.obroc(p,kat);
	}
	public void odbij(Prosta p)
	{
		this.a.odbij(p);
		this.b.odbij(p);
	}
	public String toString()
	{
		return "( "+a.toString()+" , "+b.toString()+" )";
	}

}
class Trojkat
{
	private Punkt a;
	private Punkt b;
	private Punkt c;

	private boolean wspoliniowe(Punkt x1, Punkt x2, Punkt x3)
	{
		double a,b;
		if (x1.getx() == x2.getx())
		{
			if (x3.getx() == x1.getx())
				return true;
			return false;
		}
		a = (x1.gety() - x2.gety()) / (x1.getx() - x2.getx());
		b = (x2.gety()*x1.getx() - x1.gety()*x2.getx()) / (x1.getx() - x2.getx());
		if (a*x3.getx() + b == x3.gety())
			return true;
		return false;
	}

	public Trojkat(Punkt a, Punkt b, Punkt c) throws IllegalArgumentException
	{
		if (a.equals(b) || a.equals(c) || b.equals(c))
			throw new IllegalArgumentException("wprowadzone punkty sa takie same.");
		if (wspoliniowe(a,b,c))
			throw new IllegalArgumentException("wprowadzone punkty sa wspoliniowe");
		this.a = a;
		this.b = b;
		this.c = c;
	}
	public void przesun(Wektor v)
	{
		this.a.przesun(v);
		this.b.przesun(v);
		this.c.przesun(v);
	}
	public void obroc(Punkt p, double kat)
	{
		this.a.obroc(p,kat);
		this.b.obroc(p,kat);
		this.c.obroc(p,kat);
	}
	public void odbij(Prosta p)
	{
		this.a.odbij(p);
		this.b.odbij(p);
		this.c.odbij(p);
	}
	public String toString()
	{
		return "( "+a.toString()+" , "+b.toString()+" , "+c.toString()+" )";
	}


}

public class Zad1
{
    public static void main (String[] args)
    {
    	Wektor v1 = new Wektor(-2.0,-2.0);
    	Punkt p0 = new Punkt(2,5);
    	Prosta p1 = new Prosta(-1.0,5.0,9.0);
    	double kat = 1.0/2.0;

    	try{
    		Odcinek o1 = new Odcinek(new Punkt(2.0,2.0), new Punkt(1.0,2.0));
    		Odcinek o2 = new Odcinek(new Punkt(-1.0,10.0), new Punkt(-20.0,-11.0));
    		System.out.println("o1 i o2 na poczatku:");
    		System.out.println(o1.toString());
    		System.out.println(o2.toString());
    		//przesuwanie
    		System.out.println("o1 i o2 po przesunieciu:");
    		o1.przesun(v1);
    		o2.przesun(v1);
    		System.out.println(o1.toString());
    		System.out.println(o2.toString());
    		//obracanie
    		o1.obroc(p0,kat);
    		o2.obroc(p0,kat);
    		System.out.println("o1 i o2 po obrocie i przesunieciu:");
    		System.out.println(o1.toString());
    		System.out.println(o2.toString());
    		//odbijanie
    		o1.odbij(p1);
    		o2.odbij(p1);
    		System.out.println("o1 i o2 po odbiciu, obrocie i przesunieciu:");
    		System.out.println(o1.toString());
    		System.out.println(o2.toString());
    	}
    	catch(IllegalArgumentException e)
    	{
    		System.out.println("Error: " + e.getMessage());
    	}
    	try{
    		Trojkat t1 = new Trojkat(new Punkt(2.0,2.0), new Punkt(1.0,2.0),new Punkt(3.0,7.0));
    		Trojkat t2 = new Trojkat(new Punkt(5.0,2.0), new Punkt(-2.0,-3.0),new Punkt(3.0,77.0));
    		System.out.println("t1 i t2 na poczatku:");
    		System.out.println(t1.toString());
    		System.out.println(t2.toString());
    		//przesuwanie
    		t1.przesun(v1);
    		t2.przesun(v1);
    		System.out.println("t1 i t2 po przesunieciu o:");
    		System.out.println(t1.toString());
    		System.out.println(t2.toString());
    		//obracanie
    		t1.obroc(p0,kat);
    		t2.obroc(p0,kat);
    		System.out.println("t1 i t2 po obrocie i przesunieciu:");
    		System.out.println(t1.toString());
    		System.out.println(t2.toString());
    		//odbijanie
    		t1.odbij(p1);
    		t2.odbij(p1);
    		System.out.println("t1 i t2 po odbiciu, obrocie i przesunieciu:");
    		System.out.println(t1.toString());
    		System.out.println(t2.toString());
    	}
    	catch(IllegalArgumentException e)
    	{
    		System.out.println("Error: " + e.getMessage());
    	}

    }
}