import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

class End extends JFrame
{
	public static int HEIGHT;
	public static int WIDTH;
	JPanel background;

	public End(int moves)
	{
		background = new JPanel();
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		screenSize.getHeight();
		HEIGHT = (int)(Math.round(screenSize.height / 5));
		WIDTH = (int) (Math.round(HEIGHT*2));
		display(moves);
	}
	public void display(int moves)
	{
		int textsize = (int) (Math.round(HEIGHT / 16));

		this.setSize(WIDTH,HEIGHT);
		this.setTitle("End of game");

		this.background.setLayout(new GridLayout(4,1,10,10));
		this.background.setPreferredSize(new Dimension(WIDTH, HEIGHT));
		
		JButton button1 = new JButton();
 		button1.setVisible(false); 
		this.background.add(button1);
		JPanel text = new JPanel();
		JLabel congrats = new JLabel("Congratulations,");
		JLabel you_made = new JLabel("you solved the puzzle in " + moves + " moves!");
		congrats.setFont(new Font("Arial", Font.PLAIN, textsize));
		you_made.setFont(new Font("Arial", Font.PLAIN, textsize));
		text.add(congrats);
		text.add(you_made);
		this.background.add(text);

		this.add(background);
  		this.setResizable(false);

		this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		this.setLocationRelativeTo(null);
		this.setVisible(true);
	}
}