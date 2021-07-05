package structures;

public class Pair{
	public final String key;
	private double value;

	public boolean check_letters(String word)
	{
		for(int i = 0; i < word.length(); i++)
		{
			int ascii = (int) word.charAt(i);
			if ( ascii < 97 || ascii > 122 )
				return false;
		}
		return true;
	}

	public Pair(String key, double value) throws IllegalArgumentException
	{
		if(key == null || key == "" || !check_letters(key))
			throw new IllegalArgumentException("The key \""+key+"\" is wrong!");
		this.key = key;
		this.value = value;
	}

	public void set_value(double value)
	{
		this.value = value;

	}
	public double get_value()
	{
		return this.value;
	}
	public String toString()
	{
		return "Pair: ("+key+" , "+value+")";
	}
	@Override
	public boolean equals(Object obj)
	{
		if (obj == null)
			return false;
		if(obj.getClass() != this.getClass())
			return false;
		Pair other = (Pair) obj;
		if(!other.key.equals(this.key))
			return false;
		return true;
	}
}