import java.util.concurrent.ThreadLocalRandom;
class FIFO<T>
{
	private Element first;
	private Element last;
	private int max_size;
	public int act_size;

	private class Element
	{
		public Element previous = null;
		public Element next = null;
		public T value = null;
	}

	public FIFO(int x)
	{
		this.max_size = x;
		this.first = null;
		this.act_size = 0;
	}

	public synchronized boolean is_full()
	{
		if (act_size == max_size)
			return true;
		return false;
	}

	public synchronized boolean is_empty()
	{
		if (act_size == 0)
			return true;
		return false;
	}

	public synchronized void push(T elem) throws Exception
	{
		while (this.is_full())
		{
        	try 
        	{
        		System.out.println("FIFO is full, producer is waiting, size: " + Integer.toString(this.act_size));
            	wait();
        	}
        	catch (InterruptedException e) 
        	{}
        }
		if (act_size == max_size)
			throw new Exception();

		Element tmp = new Element();
		tmp.value = elem;
		if (act_size == 0)
		{
			first = tmp;
			last = tmp;
			first.next = last;
			last.previous = first;
			act_size += 1;
		}
		else{
			last.next = tmp;
			tmp.previous = last;
			last = tmp;
			act_size += 1;
		}
		this.notifyAll();
	}

	public synchronized T pop() throws Exception
	{
		while(this.is_empty())
		{
        	try 
        	{
        		System.out.println("FIFO is empty, consumer is waiting, size: " + Integer.toString(this.act_size));
            	wait();
        	}
        	catch (InterruptedException e) 
        	{
        		System.out.println("Interrupted in consumer");
        	}
        }
		if (act_size == 0)
			throw new Exception();

		if (act_size == 1)
		{
			T result = first.value;
			act_size = 0;
			first = null;
			last = null;
			this.notifyAll();
			return result;
		}
		else
		{
			T result = first.value;
			act_size -= 1;
			first = first.next;
			first.previous = null;
			this.notifyAll();
			return result;
		}
	}
}

class producer extends Thread
{
	FIFO<String> shared_fifo;
	producer(FIFO<String> x)
	{
		this.shared_fifo = x;
	}
	String generate_word()
	{
		String result = "";
		for (int i = 0; i < 5; i ++){
			int randomletter = ThreadLocalRandom.current().nextInt(65, 123);
			result += Character.toString((char)randomletter);
		}
		return result;
	}
	public void run()
	{
		int i = 50;
		while (i > 0)
		{
			String product  = generate_word();

        	try
        	{
        		shared_fifo.push(product);
        		System.out.println("produced: " + product);
        	}
        	catch(Exception e)
        	{
        		System.out.println("Interrupted in producer");
        	}
			i -= 1;
		}

	}

}

class consumer extends Thread
{
	FIFO<String> shared_fifo;
	consumer(FIFO<String> x)
	{
		this.shared_fifo = x;
	}
	public void run()
	{
		while (true)
		{
        	try
        	{
        		String product = shared_fifo.pop();
        		System.out.println("consumed: " + product);
        	}
        	catch(Exception e)
        	{}
		}

	}

}
public class zad3 {
    public static void main(String[] args) throws Exception
    {
    	FIFO<String> shared_fifo = new FIFO<String>(5);
    	consumer cons = new consumer(shared_fifo);
    	producer prod = new producer(shared_fifo);
    	prod.start();
    	cons.start();
    }
}