using System;

class ListaLeniwa
{
	public class List
    {
        public int id;
        public int value;
        public List next;
    }

	public int size_list;
	public List start;
	public List act;

	public ListaLeniwa()
    {
        start = new List();
        start.id = 0;
        act = start;
        size_list = 0;
    }


	Random rand = new Random();
	virtual public int add()
	{
		return rand.Next();
	}

	public void fill_list(int i)
	{
		while(i > size_list)
		{
			List NewList = new List();

			NewList.id = act.id + 1;
			NewList.value = add();
			act.next = NewList;
			act = NewList;
			size_list ++;
		}

	}
	public int element(int i)
	{
		if(i >= size_list)
			fill_list(i);
		List tmp = start;
		for(int j = 0; j < i; j++)
			tmp = tmp.next;
		return tmp.value;
			
	}

	public int size()
	{
		return size_list;
	}
}

class Pierwsze : ListaLeniwa
{
	private bool is_primary(int n)
	{
		if(n < 2)
			return false;
		if(n == 2)
			return true;
		if(n % 2 == 0)
			return false;
		for(int i = 3; i < Math.Sqrt(n); i = i + 2)
			if( n % i == 0)
				return false;
		return true;
	}

	override public int add()
	{
		int next = 2;
		if (act.id == 0)
			return next;
		next = act.value + 1;
		while(!is_primary(next))
			next ++;
		return next;
	}

}

class MainClass
{
    public static void Main(string[] args)
    {
    	ListaLeniwa lista = new ListaLeniwa();
    	Console.WriteLine(lista.size());
    	Console.WriteLine(lista.element(10));
    	Console.WriteLine(lista.size());
    	Console.WriteLine(lista.element(10));
    	Console.WriteLine(lista.size());
    	Console.WriteLine(lista.element(12));
    	for(int i = 1 ;i < 13; i++)
    		Console.WriteLine(lista.element(i));

    	Pierwsze listap = new Pierwsze();
    	Console.WriteLine(listap.size());
    	Console.WriteLine(listap.element(10));
    	Console.WriteLine(listap.size());
    	Console.WriteLine(listap.element(10));
    	Console.WriteLine(listap.size());
    	Console.WriteLine(listap.element(12));
    	for(int i = 1 ;i < 13; i++)
    		Console.WriteLine(listap.element(i));


    }
}