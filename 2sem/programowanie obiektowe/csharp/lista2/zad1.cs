using System;
class IntStream
{
	protected int i = 0;
	protected bool end = false;
	virtual public int next()
	{
		if(i == 2147483647)
			this.end = true;
		if(this.end == false)
			this.i = i + 1;
		if(i == 2147483647)
			this.end = true;
		return i;
	}

	public bool eos()
	{
		return this.end;
	}

	public void reset()
	{
		i = 0;
		this.end = false;
	}
}

class PrimeStream : IntStream
{
	private int MaxValue = 2147483647;
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
	private int next_primary(int i)
	{
		if(i == MaxValue)
			return i;
		int next = i + 1;
		while(!is_primary(next))
			next ++;
		return next;
	}

	override public  int next()
	{
		if(this.end == false)
			this.i = next_primary(i);
		return i;
	}
}

class RandomStream : IntStream
{
	Random rand = new Random();
	override public int next()
	{
		if(this.end == false)
			this.i = rand.Next();
		return i;
	}
}

class RandomWordStream
{
	PrimeStream length = new PrimeStream();
	RandomStream random = new RandomStream();
	public string next()
	{
		int size = length.next();
		char[] chars = new char[size];
		for(int i = 0;i < size; i++)
		{
			chars[i] = Convert.ToChar((random.next())%128);
		}
		string sequence = new string (chars);
		return sequence;
	}

}
class Program
{
	public static void Main(string[] args)
	{
		PrimeStream ps = new PrimeStream();
		Console.WriteLine("A oto 30 liczb pierwszych wikeszych od 100 :");
		for(int i = 0; i < 30; i ++){
			int tmp = ps.next();
			if(tmp < 100)
				i --;
			else
				Console.WriteLine(tmp);
		}

		string eos = "false";
		string reset = "false";
		RandomStream rs = new RandomStream();
		Console.WriteLine("A oto strumien 15 losowych liczb (demonstracja reset() i eos() )");
		for(int i = 0;i < 15; i ++){
			if(i == 9){
				rs.eos();
				eos = "true";
			}
			if(i == 12){
				rs.reset();
				eos = "false";
				reset = "true";
			}
			Console.WriteLine(rs.next() + " EOS: " + eos + " RESET: " + reset);
		}

		RandomWordStream rws = new RandomWordStream();
		Console.WriteLine("A oto strumien 10 losowych, coraz dluzszych slow:");
		for(int i = 0; i < 10;i ++)
			Console.WriteLine(rws.next());
	}
}