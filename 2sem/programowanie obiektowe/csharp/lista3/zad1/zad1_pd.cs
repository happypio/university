using System;
using zad1_dll;

class MainClass
{
	public static void Main(string[] args)
	{
		Lista<int> lista = new Lista<int>();
		Console.WriteLine(lista.is_empty());
		for(int i = 0; i < 5; i ++){
			lista.push_back(i);
			lista.push_front(-i);
		}
		Console.WriteLine(lista.pop_back());
		Console.WriteLine(lista.pop_back());
		Console.WriteLine(lista.pop_back());
		Console.WriteLine(lista.pop_back());
		Console.WriteLine(lista.pop_back());
		Console.WriteLine(lista.pop_back());
		Console.WriteLine(lista.pop_back());
		Console.WriteLine(lista.pop_front());
		Console.WriteLine(lista.is_empty());
		Console.WriteLine(lista.pop_front());
		Console.WriteLine(lista.is_empty());
		Console.WriteLine(lista.pop_front());
		Console.WriteLine(lista.is_empty());
	}
}