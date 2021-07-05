using System;
using System.Collections;

public class Primes : IEnumerator
{
	int current_prime;
	int MAX_PRIME = 2147483647;
	public Primes()
	{
		current_prime = 0;
	}
	private bool is_primary(int n)
	{
		
		for(int i = 3; i < Math.Sqrt(n); i = i + 2)
			if( n % i == 0)
				return false;
		return true;
	}
	private int nextprime()
	{
		if(this.current_prime == 0)
		{
			return 2;
		}
		if(this.current_prime == 2)
			return 3;
		this.current_prime += 2;
		while(!is_primary(this.current_prime))
			this.current_prime += 2;
		return this.current_prime;
	}
	public bool MoveNext()
	{
		if(this.current_prime == MAX_PRIME)
			return false;
		this.current_prime = nextprime();
			return true;
	}
	public object Current
	{
		get{
			return this.current_prime;
		}
	}
	public void Reset()
	{
		this.current_prime = 0;
	}
}

public class PrimeCollection : IEnumerable
{
	public IEnumerator GetEnumerator()
    {
    	return new Primes();
    }
}
class MainClass
{
    public static void Main(string[] args)
    {
    	PrimeCollection pc = new PrimeCollection();
    	foreach(int p in pc)
    		Console.WriteLine(p);
    }
}