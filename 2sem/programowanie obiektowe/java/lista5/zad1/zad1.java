class Lista <T extends Comparable<T> >
{
	private class Element
	{
		public Element previous = null;
		public Element next = null;
		public T value = null;
	}
	private Element first;
	public Lista()
	{
		this.first = null;	
	}
	//method to add element before first bigger one
	public void add(T val)
	{
		int cnt = 0;
		Element act = first;
		Element new_elem = new Element();
		new_elem.value = val;
		//check if list is empty
		if(first == null)
		{
			first = new_elem;
			return;
		}
		while(val.compareTo(act.value) == 1)
		{
			cnt++;
			//statement to avoid null errors
			if(act.next == null)
				break;
			act = act.next;
		}
		//we check where to place new_elem
		//checking first element
		if(cnt == 0)
		{
			new_elem.next = act;
			act.previous = new_elem;
			this.first = new_elem;
		}else
		{
			//check if it is last element
			if(act.next == null && val.compareTo(act.value) == 1)
			{
				new_elem.previous = act;
				act.next = new_elem;
			}else
			{
				//then it is middle element
				Element tmp = act.previous;
				new_elem.next = act;
				new_elem.previous = act.previous;
				act.previous = new_elem;
				tmp.next = new_elem;

			}
		}
	}
	//method to pop smallest element
	public T pop() throws Exception
	{
		Element tmp = first;
		if(tmp == null)
			throw new Exception();
		first.previous = null;
		first = first.next;
		return tmp.value;
	}
	//method to print all elements
	public void print_all() throws Exception
	{
		if(first == null)
			throw new Exception();
		Element act = first;
		while(act != null)
		{
			System.out.println(act.value);
			act = act.next;
		}
	}
}
	
abstract class Figura implements Comparable<Figura>
{
	public Double area;
	public int compareTo(Figura o)
	{
		return area.compareTo(o.area);
	}
	public String toString()
	{
		return Double.toString(area);
	}
}
class Okrag extends Figura
{
	private double R;
	public Okrag(double r){
		this.R = r;
		this.area = 3.14*r*r;

	}
}
class Kwadrat extends Figura
{
	private double a = 0;
	public Kwadrat(double x){
		this.a = x;
		this.area = x*x;

	}
}
class Prostokat extends Figura
{
	private double a = 0;
	private double b =0;
	public Prostokat(double x,double y){
		this.a = x;
		this.b = y;
		this.area = x*y;

	}
}
class Trojkat extends Figura
{
	private double a = 0;
	private double h = 0;
	public Trojkat (double x, double y){
		this.a = x;
		this.h = y;
		this.area = (x*y)/2;
	}
}
public class zad1 {
    public static void main(String[] args)
    {
    	System.out.println("THE LIST WITH FIGURES:");
    	Figura tablica[] = new Figura[4];
    	tablica[0] = new Trojkat(1.43,2.8);
    	tablica[1] = new Prostokat(10,0.2);
    	tablica[2] = new Okrag(10.4);
    	tablica[3] = new Kwadrat(4.32);
    	Lista<Figura> lista_figur = new Lista<Figura>();
    	System.out.println("Adding 2 elements");
    	lista_figur.add(tablica[0]);
    	lista_figur.add(tablica[1]);
    	try{
    		System.out.println("Removing 1 elements");
    	System.out.println(lista_figur.pop().area);
    	System.out.println("Adding 2 elements");
    	lista_figur.add(tablica[0]);
    	lista_figur.add(tablica[2]);
    	System.out.println("Printing all elements");
    	lista_figur.print_all();
    	System.out.println("Removing 3 elements");
    	System.out.println(lista_figur.pop());
    	System.out.println(lista_figur.pop());
    	System.out.println(lista_figur.pop());
    	System.out.println("Adding 2 elements");
    	lista_figur.add(tablica[3]);
    	lista_figur.add(tablica[1]);
    	System.out.println("Printing all elements");
    	lista_figur.print_all();
    	}
    	catch(Exception e){
    		System.out.println("The list is empty!");
    	}

    	Lista<Integer> lista = new Lista<Integer>();
    	//adding different integers
    	System.out.println("THE LIST WITH INTEGERS:");
        lista.add(2);
        lista.add(-3);
        lista.add(10);
        lista.add(0);
        lista.add(-1);
        lista.add(9);
        lista.add(8);
        lista.add(1111);
        //poping and printing
        try{
        System.out.println("Printing all elements");
        lista.print_all();
        System.out.println("Removing 2 elements");
        System.out.println(lista.pop());
        System.out.println(lista.pop());
        System.out.println("Printing all elements");
        lista.print_all();
        System.out.println("Removing 5 elements");
        System.out.println(lista.pop());
        System.out.println(lista.pop());
        System.out.println(lista.pop());
        System.out.println(lista.pop());
        System.out.println(lista.pop());
        System.out.println("Printing all elements");
        lista.print_all();
        System.out.println("Removing 1 element");
        System.out.println(lista.pop());
        System.out.println("NOW THE LIST IS EMPTY");
    	}
    	catch(Exception e){
    		System.out.println("The list is empty!");
    	}
    	System.out.println("Trying to print empty list:");
    	try{
    		lista.print_all();
    	}
    	catch(Exception e){
    		System.out.println("The list is empty!");
    	}
    	System.out.println("Trying to remove element from empty list:");
    	try{
    		lista.pop();
    	}
    	catch(Exception e){
    		System.out.println("The list is empty!");
    	}
    }
}