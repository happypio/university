using System;

namespace zad2_dll
{
	public class Element<K,V> where K : IComparable<K>
	{
		public Element<K,V> prev = null;
		public Element<K,V> next = null;
		public K key;
		public V value;
	}

	public class Slownik<K,V> where K : IComparable<K>
	{
		public Element<K,V> first;
		public Element<K,V> start;

		public Slownik()
		{
			first = null;
			start = null;
		}

		public void add (K ky, V val) //funkcja dodajaca element na koncu listy
		{
			if(first == null && start == null)
			{
				first = new Element<K,V>();
				first.value = val;
				first.key = ky;
				start = first;
			}
			else
			{
				first.next = new Element<K,V>();
				first.next.prev = first;
				first = first.next;
				first.value = val;
				first.key = ky;
			}
		}

		public Element<K,V> find_r(K key, Element<K,V> act) //funkcja szukajaca po kluczu elementu rekurencyjnie
		{
			if(act == null){
				Console.WriteLine("There is no such key.");
				return null;
			}
			if(act.key.CompareTo(key) == 0){
				Console.WriteLine(act.value);
				return act;
			}
			else
				return find_r(key, act.next);
		}

		public void find (K key)
		{
			find_r(key, start);
		}

		public void delete (K key) // funkcja usuwajaca element po kluczu
		{
			Element<K,V> to_delete = find_r(key, start);
			if(to_delete != null)
			{
				Element<K,V> previous = to_delete.prev;
				Element<K,V> next = to_delete.next;	
				if(previous != null)
					to_delete.prev.next = next;
				if(next != null)
					to_delete.next.prev = previous;
			}
		}

	}
}