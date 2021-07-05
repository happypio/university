import java.io.*;

class Lista <T extends Comparable<T> > implements Serializable
{
	private class Element implements Serializable
	{
		public Element previous = null;
		public Element next = null;
		public T value = null;
	}
	private Element first;
	public Lista()
	{
		this.first = null;	
	}
	//method to add element before first bigger one
	public void add(T val)
	{
		int cnt = 0;
		Element act = first;
		Element new_elem = new Element();
		new_elem.value = val;
		//check if list is empty
		if(first == null)
		{
			first = new_elem;
			return;
		}
		while(val.compareTo(act.value) == 1)
		{
			cnt++;
			//statement to avoid null errors
			if(act.next == null)
				break;
			act = act.next;
		}
		//we check where to place new_elem
		//checking first element
		if(cnt == 0)
		{
			new_elem.next = act;
			act.previous = new_elem;
			this.first = new_elem;
		}else
		{
			//check if it is last element
			if(act.next == null && val.compareTo(act.value) == 1)
			{
				new_elem.previous = act;
				act.next = new_elem;
			}else
			{
				//then it is middle element
				Element tmp = act.previous;
				new_elem.next = act;
				new_elem.previous = act.previous;
				act.previous = new_elem;
				tmp.next = new_elem;

			}
		}
	}
	//method to pop smallest element
	public T pop() throws Exception
	{
		Element tmp = first;
		if(tmp == null)
			throw new Exception();
		first.previous = null;
		first = first.next;
		return tmp.value;
	}
	//method to print all elements
	public void print_all() throws Exception
	{
		if(first == null)
			throw new Exception();
		Element act = first;
		while(act != null)
		{
			System.out.println(act.value);
			act = act.next;
		}
	}
}


public class zad1{
    public static void main(String[] args)
    {
    	Lista<Integer> lista = new Lista<Integer>();
	    //adding different integers
	    System.out.println("THE LIST WITH INTEGERS:");
	    lista.add(2);
	    lista.add(-3);
	    lista.add(10);
	    lista.add(0);
	    lista.add(-1);
	    lista.add(9);
	    lista.add(8);
	    lista.add(1111);
	    //printing
	    try{
        	System.out.println("Printing all elements");
        	lista.print_all();
    	}
    	catch(Exception e){
    		System.out.println("The list is empty!");
    	}
	    // Serialization
	    try
        {
            FileOutputStream file = new FileOutputStream("serialized_list.ser"); 
            ObjectOutputStream out = new ObjectOutputStream(file); 
            out.writeObject(lista);  
            out.close(); 
            file.close(); 
            System.out.println("Object has been serialized"); 
  
        } 
          
        catch(IOException ex) 
        { 
            System.out.println("IOException is caught"); 
        } 
        // Deserialization 
        //Lista<Integer> lista2 = null;
        try
        {    
            FileInputStream file = new FileInputStream("serialized_list.ser"); 
            ObjectInputStream in = new ObjectInputStream(file); 
            @SuppressWarnings("unchecked")
            Lista<Integer> lista2 = (Lista<Integer>)in.readObject();       
            in.close(); 
            file.close(); 
            System.out.println("Object has been deserialized "); 
            try{
        		System.out.println("Printing all elements");
        		lista2.print_all();
    		}
    		catch(Exception e){
    			System.out.println("The list is empty!");
    		}
        } 
          
        catch(IOException ex) 
        { 
            System.out.println("IOException is caught"); 
        } 
        catch(ClassNotFoundException ex) 
        { 
            System.out.println("ClassNotFoundException is caught"); 
        } 
    }
}