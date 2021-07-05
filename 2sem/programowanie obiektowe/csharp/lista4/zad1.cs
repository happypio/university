using System;
using System.Collections;
interface Lista_inter<T>
{
	void push_front(T obj);
	bool is_empty();
}

public class Element<T>
{
	public Element<T> prev = null;
	public Element<T> next = null;
	public T val;
}

public class Lista<T> : Lista_inter<T>
{
	public Element<T> first;
	public Element<T> last;

	public bool is_empty()
	{
		if(first == null && last == null)
			return true;
		else
			return false;
	}

	public Lista()
	{
		first = null;
		last = null;
	}

	public void push_back (T val) //funkcja dodajaca element na koncu listy
	{
		if(first == null && last == null)
		{
			first = new Element<T>();
			first.val = val;
			last = first;
		}
		else
		{
			first.next = new Element<T>();
			first.next.prev = first;
			first = first.next;
			first.val = val;
		}
	}

	public void push_front (T val) //funkcja dodajaca element na poczatku listy
	{
		if(first == null && last == null)
		{
			first = new Element<T>();
			first.val = val;
			last = first;
		}
		else
		{
			last.prev = new Element<T>();
			last.prev.next = last;
			last = last.prev;
			last.val = val;
		}
	}

	public T pop_front () // funkcja usuwajaca element na poczatku listy
	{
		if (last.next != null)
		{
			T ans = last.val;
			last = last.next;
			last.prev = null;
			return ans;
		}
		else
		{
			T ans = last.val;
			last = null;
			first = null;
			return ans;
		}
	}
	public T pop_back () // funkcja usuwajaca element na koncu listy
	{
		if (first.prev != null)
		{
			T ans = first.val;
			first = first.prev;
			first.next = null;
			return ans;
		}
		else
		{
			T ans = first.val;
			last = null;
			first = null;
			return ans;
		}
	}
}

public class List
{
    public int id;
    public int value;
    public List next;
    public int this[int indeks]
    {
    	get{
    		if(indeks == 0) return value;
    		return this.next[indeks-1];
    	}
    }
}

public class ListaLeniwa : Lista_inter<int>, IEnumerable
{

	public override string ToString()
    {
    	return String.Format("akutalny element to: {0}",this.act.value);
    }

    public int this[int indeks] 
    {
    	get 
    	{
    		return start[indeks];
    	}
    }
    public int Length
	{
		get
		{return size_list;}
	}


    public IEnumerator GetEnumerator()
    {
    	return new ListEnum(start);
    }

    public void cout_lista()
    {
    	var enumerator = this.GetEnumerator();
    	enumerator.MoveNext();
    	while(enumerator.MoveNext())
    		Console.WriteLine("aktualny element to " + enumerator.Current);
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
	virtual public void push_front(int elemencik)
	{
		List NewList = new List();

		NewList.id = act.id + 1;
		NewList.value = elemencik;
		act.next = NewList;
		act = NewList;
		size_list ++;
	}

	public int element(int i)
	{
		if(i >= size_list)
			while(i > size_list)
				push_front(rand.Next());
		List tmp = start;
		for(int j = 0; j < i; j++)
			tmp = tmp.next;
		return tmp.value;
			
	}

	public bool is_empty()
	{
		if(size_list == 0)
			return true;
		else
			return false;
	}
}


public class ListEnum : IEnumerator
{
	List current;
	List lista;
	public ListEnum(List element)
	{
		this.lista = element;
	}
	public bool MoveNext()
	{
		if(this.current == null) this.current = this.lista;
		else this.current = this.current.next;

		return this.current != null;
	}
	public object Current 
	{
		get {
			return current.value;
		}
	}
	public void Reset()
	{
		this.current = this.lista;
	}

}
class MainClass
{
    public static void Main(string[] args)
    {
    	ListaLeniwa lista = new ListaLeniwa();
    	Console.WriteLine(lista.Length);
    	Console.WriteLine(lista.element(10));
    	Console.WriteLine(lista.ToString());
    	Console.WriteLine(lista.Length);
    	Console.WriteLine(lista.element(10));
    	Console.WriteLine(lista.Length);
    	Console.WriteLine(lista.element(12));
    	for(int i = 1 ;i < 13; i++)
    		Console.WriteLine(lista.element(i));
    	lista.cout_lista();
    	for(int i = 1; i < 13; i++)
    		Console.WriteLine(lista[i]);
    	
    }
}