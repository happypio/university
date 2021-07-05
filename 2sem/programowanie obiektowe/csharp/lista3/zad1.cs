using System;

namespace zad1_dll
{
	public class Element<T>
	{
		public Element<T> prev = null;
		public Element<T> next = null;
		public T val;
	}

	public class Lista<T>
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
}
