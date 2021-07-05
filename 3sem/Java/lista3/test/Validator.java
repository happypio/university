package test;
import structures.*;
public class Validator{
	public static Pair p1 = new Pair("jeden" , 1);
	public static Pair p2 = new Pair("dwa" , 2);
	public static Pair p3 = new Pair("trzy" , 3);
	public static Pair p4 = new Pair("cztery" , 4);

	public static void testSOA(){
		try{
			//testing SetOnArray
			System.out.println("TESTOWANIE ZBIORU NA TABLICY\n\n");
			System.out.println("Tworzymy kolekcje o rozmiarze 3");
			SetOnArray s1 = new SetOnArray(3);
			System.out.println("Wstawiamy 3 elementy");
			s1.insert(p1);
			s1.insert(p2);
			s1.insert(p3);
			System.out.println("Ilosc par to "+s1.size());
			System.out.println("Usuwamy element (\"trzy\" , 3)");
			s1.delete("trzy");
			System.out.println("Ilosc par to "+s1.size());
			try{
				System.out.println("szukamy pary (\"dwa\" , 2)");
				System.out.println(s1.search("dwa").get_value());
				System.out.println("szukamy pary (\"trzy\" , 2)");
				System.out.println(s1.search("trzy").get_value());
			}
			catch(IllegalArgumentException e){
				System.out.println(e.getMessage());
			}
			try{
				System.out.println("Ilosc par to "+s1.size());
				System.out.println("Ustawiamy element (\"piec\" , 2)");
				s1.update(new Pair("piec" , 5));
				System.out.println("Czytamy element \"piec\" "+s1.read("piec"));
				System.out.println("Ilosc par to "+s1.size());
				System.out.println("Usuwamy wszystkie pary");
				s1.clear();
				System.out.println("Ilosc par to "+s1.size());
				try{
					System.out.println("Dodajemy dwa razy element jeden");
					s1.insert(p1);
					s1.insert(p1);
				}
				catch(IllegalArgumentException e){
					System.out.println(e.getMessage());
				}
				System.out.println("Dodajemy jeszcze 3 elementy (o jeden za duzo)");
				s1.insert(p3);
				s1.insert(p2);
				s1.insert(p4);
				
			}
			catch(IllegalArgumentException e)
			{
				System.out.println(e.getMessage());

			}
		}
		catch(IllegalArgumentException e){
			System.out.println(e.getMessage());
		}
		System.out.println("__________________________________\n\n\n");
	}
	public static void testSODA()
	{
		try{

			//testing SetOnDynamicArray
			System.out.println("TESTOWANIE ZBIORU NA TABLICY DYNAMICZNEJ\n\n");

			SetOnDynamicArray s1 = new SetOnDynamicArray();
			System.out.println("Dodajemy do kolekcji o rozmairze 2 trzy elementy");
			s1.insert(p1);
			s1.insert(p2);
			s1.insert(p3);
			System.out.println("Ilosc par to "+s1.size());
			System.out.println("Rozmiar to "+s1.get_size());
			System.out.println("Czytamy element trzy "+s1.read("trzy"));
			try{
				System.out.println("Czytamy element cztery");
				s1.read("cztery");
			}
			catch(IllegalArgumentException e){
				System.out.println(e.getMessage());
			}
			System.out.println("Ustawiamy element cztery");
			s1.update(p4);
			System.out.println("Ilosc par to "+s1.size());
			System.out.println("Rozmiar to "+s1.get_size());
			System.out.println("Nadpisujemy element trzy - (\"trzy\" , 3.3333)");
			s1.update(new Pair("trzy", 3.3333));
			System.out.println("Czytamy element trzy "+s1.read("trzy"));
			System.out.println("Dodajemy 1 element");
			s1.update(new Pair("piec",1000));
			System.out.println("Ilosc par to "+s1.size());
			System.out.println("Rozmiar to "+s1.get_size());
			System.out.println("Usuwamy 4 elementy");
			s1.delete("piec");
			s1.delete("cztery");
			s1.delete("trzy");
			s1.delete("jeden");
			System.out.println("Ilosc par to "+s1.size());
			System.out.println("Rozmiar to "+s1.get_size());
			System.out.println("Czytamy element dwa "+s1.read("dwa"));
			System.out.println("Szukamy elementu jeden");
			s1.search("jeden");
		}
		catch(IllegalArgumentException e)
		{
			System.out.println(e.getMessage());
		}
		System.out.println("__________________________________\n\n\n");

	}
}