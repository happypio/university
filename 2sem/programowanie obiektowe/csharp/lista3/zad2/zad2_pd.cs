using System;
using zad2_dll;



	class MainClass
	{
		public static void Main(string[] args)
		{
			Slownik<int, string> dict = new Slownik<int, string>();
			dict.add(30, "cos");
			Console.WriteLine("Finding element with key 30:");
			dict.find(30);
			//dict.add(41, "hej");
			dict.add(86, "raz");
			//dict.add(6, "slowko");
			///dict.add(4320, "fajne");
			//dict.add(89, "abrakadabra");
			//dict.add(9, "usun mnie");
			dict.add(3120, "lampa");
			Console.WriteLine("Finding element with key 0:");
			dict.find(0);
			Console.WriteLine("Finding element with key 86:");
			dict.find(86);
			Console.WriteLine("Deleting element with key 86:");
			dict.delete(86);
			Console.WriteLine("Finding element with key 86:");
			dict.find(86);
			Console.WriteLine("Finding element with key 3120:");
			dict.find(3120);
			Console.WriteLine("Deleting element with key 30:");
			dict.delete(30);
			Console.WriteLine("Deleting element with key 3120:");
			dict.delete(3120);

		}
	}