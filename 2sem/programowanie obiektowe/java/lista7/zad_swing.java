import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

class Figure implements Serializable
{
	Double area;
	String name;
	String colour;

	public String toString()
	{
		return "Figure: " + this.name + ", area: " + Double.toString(this.area) + ", colour: " + this.colour;
	}
}

class Circle extends Figure
{
	double PI = 3.14159265359;
	double radius;

	class circle_swing extends JFrame implements ActionListener
	{
		Circle outer;

		JTextField figure;
		JTextField colour;
		JTextField radius;
		public void actionPerformed(ActionEvent e)
		{
			double R = Double.valueOf(radius.getText());
			outer.radius = R;
			double tmp_area = R*R*PI;
			outer.name = figure.getText();
			outer.area = tmp_area;
			outer.colour = colour.getText();
			System.out.println(outer.toString());
			// Serialization
		    try
	        {
	            FileOutputStream file = new FileOutputStream("circle.ser"); 
	            ObjectOutputStream out = new ObjectOutputStream(file); 
	            out.writeObject(outer);  
	            out.close(); 
	            file.close(); 
	            System.out.println("Circle has been serialized"); 
	  
	        } 
	          
	        catch(IOException ex) 
	        { 
	            System.out.println("IOException is caught"); 
	        } 
		}
		public circle_swing(Circle outer,String e1, String e2, String e3)
		{
			this.outer = outer;
			this.radius = new JTextField(e1, 40);
			this.figure = new JTextField(e2, 40);
			this.colour =new JTextField(e3, 40);
			JFrame frame = new JFrame("Circle edition");
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			Container cont = frame.getContentPane();
			GridLayout layout = new GridLayout(4, 2);
			cont.setLayout(layout);

			JLabel radius_lab = new JLabel("RADIUS");
			cont.add(radius_lab);
			cont.add(radius);

			JLabel figure_lab = new JLabel("FIGURE");
			cont.add(figure_lab);
			cont.add(figure);

			JLabel colour_lab = new JLabel("COLOUR");
			cont.add(colour_lab);
			cont.add(colour);

			JButton b = new JButton("Save figure");
			b.addActionListener(this);
			cont.add(b);
			frame.setSize(500,300);
			frame.setVisible(true);
		}	
	}
	public Circle()
	{
		new circle_swing(this,"radius","figure","colour");
	}
	public Circle(String e1, String e2, String e3)
	{
		new circle_swing(this,e1,e2,e3);
	}

}

class Triangle extends Figure
{

	double basis;
	double height;
	class triangle_swing extends JFrame implements ActionListener
	{
		Triangle outer;

		JTextField figure;
		JTextField colour;
		JTextField basis;
		JTextField height;
		public void actionPerformed(ActionEvent e)
		{
			double a = Double.valueOf(basis.getText());
			double h = Double.valueOf(height.getText());
			outer.basis = a;
			outer.height = h;
			double tmp_area = (a*h)/2;
			outer.name = figure.getText();
			outer.area = tmp_area;
			outer.colour = colour.getText();
			System.out.println(outer.toString());
			// Serialization
		    try
	        {
	            FileOutputStream file = new FileOutputStream("triangle.ser"); 
	            ObjectOutputStream out = new ObjectOutputStream(file); 
	            out.writeObject(outer);  
	            out.close(); 
	            file.close(); 
	            System.out.println("Triangle has been serialized"); 
	  
	        } 
	          
	        catch(IOException ex) 
	        { 
	            System.out.println("IOException is caught"); 
	        } 
		}
		public triangle_swing(Triangle outer,String e1, String e2, String e3,String e4)
		{
			this.outer = outer; 
			this.figure = new JTextField(e1, 40);
			this.colour =new JTextField(e2, 40);
			this.basis = new JTextField(e3, 40);
			this.height = new JTextField(e4, 40);
			JFrame frame = new JFrame("Triangle edition");
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			Container cont = frame.getContentPane();
			GridLayout layout = new GridLayout(5, 2);
			cont.setLayout(layout);

			JLabel basis_lab = new JLabel("BASIS");
			cont.add(basis_lab);
			cont.add(basis);

			JLabel height_lab = new JLabel("HEIGHT");
			cont.add(height_lab);
			cont.add(height);

			JLabel figure_lab = new JLabel("FIGURE");
			cont.add(figure_lab);
			cont.add(figure);

			JLabel colour_lab = new JLabel("COLOUR");
			cont.add(colour_lab);
			cont.add(colour);

			JButton b = new JButton("Save figure");
			b.addActionListener(this);
			cont.add(b);
			frame.setSize(500,300);
			frame.setVisible(true);
		}	
	}
	public Triangle()
	{
		new triangle_swing(this,"figure","colour","basis","height");
	}
	public Triangle(String e1, String e2, String e3,String e4)
	{
		new triangle_swing(this,e1,e2,e3,e4);
	}

}

class Vehicle implements Serializable
{
	Double max_speed;
	String name;
	String colour;

	public String toString()
	{
		return "Vehicle: " + this.name + ", max speed: " + Double.toString(this.max_speed) + ", colour: " + this.colour;
	}
}

class Tram extends Vehicle
{

	class tram_swing extends JFrame implements ActionListener
	{
		Tram outer;

		JTextField vehicle;
		JTextField colour;
		JTextField max_speed;
		public void actionPerformed(ActionEvent e)
		{
			double speed = Double.valueOf(max_speed.getText());
			outer.name = vehicle.getText();
			outer.max_speed = speed;
			outer.colour = colour.getText();
			System.out.println(outer.toString());
			// Serialization
		    try
	        {
	            FileOutputStream file = new FileOutputStream("tram.ser"); 
	            ObjectOutputStream out = new ObjectOutputStream(file); 
	            out.writeObject(outer);  
	            out.close(); 
	            file.close(); 
	            System.out.println("Tram has been serialized"); 
	  
	        }
	        catch(IOException ex) 
	        { 
	            System.out.println("IOException is caught"); 
	        } 
		}
		public tram_swing(Tram outer,String e1, String e2, String e3)
		{
			this.outer = outer; 
			this.vehicle = new JTextField(e1, 40);
			this.colour =new JTextField(e2, 40);
			this.max_speed = new JTextField(e3, 40);
			JFrame frame = new JFrame("Tram edition");
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			Container cont = frame.getContentPane();
			GridLayout layout = new GridLayout(4, 2);
			cont.setLayout(layout);

			JLabel speed_lab = new JLabel("MAX_SPEED");
			cont.add(speed_lab);
			cont.add(max_speed);

			JLabel vehicle_lab = new JLabel("VEHICLE");
			cont.add(vehicle_lab);
			cont.add(vehicle);

			JLabel colour_lab = new JLabel("COLOUR");
			cont.add(colour_lab);
			cont.add(colour);

			JButton b = new JButton("Save vehicle");
			b.addActionListener(this);
			cont.add(b);
			frame.setSize(500,300);
			frame.setVisible(true);
		}	
	}
	public Tram()
	{
		new tram_swing(this,"vehicle","colour","max_speed");
	}
	public Tram(String e1, String e2, String e3)
	{
		new tram_swing(this,e1,e2,e3);
	}

}

class Car extends Vehicle
{

	class car_swing extends JFrame implements ActionListener
	{
		Car outer;

		JTextField vehicle;
		JTextField colour;
		JTextField max_speed;
		public void actionPerformed(ActionEvent e)
		{
			double speed = Double.valueOf(max_speed.getText());
			outer.name = vehicle.getText();
			outer.max_speed = speed;
			outer.colour = colour.getText();
			System.out.println(outer.toString());
			// Serialization
		    try
	        {
	            FileOutputStream file = new FileOutputStream("car.ser"); 
	            ObjectOutputStream out = new ObjectOutputStream(file); 
	            out.writeObject(outer);  
	            out.close(); 
	            file.close(); 
	            System.out.println("Car has been serialized"); 
	  
	        } 
	          
	        catch(IOException ex) 
	        { 
	            System.out.println("IOException is caught"); 
	        } 
		}
		public car_swing(Car outer,String e1, String e2, String e3)
		{
			this.outer = outer; 
			this.vehicle = new JTextField(e1, 40);
			this.colour =new JTextField(e2, 40);
			this.max_speed = new JTextField(e3, 40);
			JFrame frame = new JFrame("Car edition");
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			Container cont = frame.getContentPane();
			GridLayout layout = new GridLayout(4, 2);
			cont.setLayout(layout);

			JLabel speed_lab = new JLabel("MAX_SPEED");
			cont.add(speed_lab);
			cont.add(max_speed);

			JLabel vehicle_lab = new JLabel("VEHICLE");
			cont.add(vehicle_lab);
			cont.add(vehicle);

			JLabel colour_lab = new JLabel("COLOUR");
			cont.add(colour_lab);
			cont.add(colour);

			JButton b = new JButton("Save vehicle");
			b.addActionListener(this);
			cont.add(b);
			frame.setSize(500,300);
			frame.setVisible(true);
		}	
	}
	public Car()
	{
		new car_swing(this,"vehicle","colour","max_speed");
	}
	public Car(String e1, String e2, String e3)
	{
		new car_swing(this,e1,e2,e3);
	}

}

public class zad_swing extends JFrame
{

	public static void main (String[] args)
	{		
        //Deserialization 
        String file_name = args[0];
        String class_name = args[1];
        switch(class_name)
            {
            case "Circle":
            	try
		        {    
		            FileInputStream file = new FileInputStream(file_name); 
		            ObjectInputStream in = new ObjectInputStream(file); 
		            @SuppressWarnings("unchecked")
		            Circle circle = (Circle)in.readObject();       
		            in.close(); 
		            file.close();  
		            System.out.println("Circle has been deserialized");
		            System.out.println(circle.toString());
		            Circle circle2 = new Circle(Double.toString(circle.radius),circle.name,circle.colour);
		        }
        		catch(IOException ex) 
        		{ 
            		System.out.print("There is not such file, creating new: ");
            		new Circle();
            		System.out.print(class_name + "\n");
            	}
            	catch(ClassNotFoundException ex) 
		        { 
		            System.out.println("ClassNotFoundException is caught"); 
		        }
            	break;
            case "Triangle":
            	try
		        {    
		            FileInputStream file = new FileInputStream(file_name); 
		            ObjectInputStream in = new ObjectInputStream(file); 
		            @SuppressWarnings("unchecked")
		            Triangle triangle = (Triangle)in.readObject();       
		            in.close(); 
		            file.close();  
		            System.out.println("Triangle has been deserialized");
		            System.out.println(triangle.toString());
		            Triangle triangle2 = new Triangle(triangle.name,triangle.colour,Double.toString(triangle.basis),Double.toString(triangle.height));
		        }
        		catch(IOException ex) 
        		{ 
            		System.out.print("There is not such file, creating new: ");
            		new Triangle();
            		System.out.print(class_name + "\n");
            	}
            	catch(ClassNotFoundException ex) 
		        { 
		            System.out.println("ClassNotFoundException is caught"); 
		        }
            	break;
            case "Tram":
            	try
		        {    
		            FileInputStream file = new FileInputStream(file_name); 
		            ObjectInputStream in = new ObjectInputStream(file); 
		            @SuppressWarnings("unchecked")
		            Tram tram = (Tram)in.readObject();       
		            in.close(); 
		            file.close();  
		            System.out.println("Tram has been deserialized");
		            System.out.println(tram.toString());
		            Tram tram2 = new Tram(tram.name,tram.colour,Double.toString(tram.max_speed));
		        }
        		catch(IOException ex) 
        		{ 
            		System.out.print("There is not such file, creating new: ");
            		new Tram();
            		System.out.print(class_name + "\n");
            	}
            	catch(ClassNotFoundException ex) 
		        { 
		            System.out.println("ClassNotFoundException is caught"); 
		        }
            	break;
            case "Car":
            	try
		        {    
		            FileInputStream file = new FileInputStream(file_name); 
		            ObjectInputStream in = new ObjectInputStream(file); 
		            @SuppressWarnings("unchecked")
		            Car car = (Car)in.readObject();       
		            in.close(); 
		            file.close();  
		            System.out.println("Car has been deserialized");
		            System.out.println(car.toString());
		            Car car2 = new Car(car.name,car.colour,Double.toString(car.max_speed));
		        }
        		catch(IOException ex) 
        		{ 
            		System.out.print("There is not such file, creating new: ");
            		new Car();
            		System.out.print(class_name + "\n");
            	}
            	catch(ClassNotFoundException ex) 
		        { 
		            System.out.println("ClassNotFoundException is caught"); 
		        }
            	break;
            default:
            	System.out.println("There is not such class, please select one:");
            	System.out.println("Circle,Triangle,Tram,Car");


            }   
	}

}