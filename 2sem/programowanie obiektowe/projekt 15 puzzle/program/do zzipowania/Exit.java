import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

class Exit extends JFrame implements ActionListener
{
	JFrame main_frame;
	public static int HEIGHT;
	public static int WIDTH;
	JPanel background;

	public Exit(JFrame frame)
	{
		background = new JPanel();
		this.main_frame = frame;
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		screenSize.getHeight();
		HEIGHT = (int)(Math.round(screenSize.height / 5));
		WIDTH = (int) (Math.round(HEIGHT*2));
		display();
	}
	public void actionPerformed(ActionEvent e)
	{
		JButton b = (JButton) e.getSource();
		String name = b.getActionCommand();
		if (name == "YES")
		{
			main_frame.dispatchEvent(new WindowEvent(main_frame, WindowEvent.WINDOW_CLOSING));
			this.dispatchEvent(new WindowEvent(this, WindowEvent.WINDOW_CLOSING));
		}
		if (name == "NO")
		{
			this.setVisible(false);
			this.dispose();
		}
	}
	public void display()
	{
		int textsize = (int) (Math.round(HEIGHT / 16));

		this.setSize(WIDTH,HEIGHT);
		this.setTitle("Exit");

		this.background.setLayout(new GridLayout(4,1,10,10));
		this.background.setPreferredSize(new Dimension(WIDTH, HEIGHT));
		
		JButton button1 = new JButton();
 		button1.setVisible(false); 
		this.background.add(button1);
		JPanel text = new JPanel();
		JLabel are_you = new JLabel("ARE YOU SURE?");
		are_you.setFont(new Font("Arial", Font.PLAIN, textsize));
		text.add(are_you);
		this.background.add(text);

		JPanel buttons = new JPanel();
		buttons.setLayout(new GridLayout(1,5,10,10));
		Boolean was_not = true;
		for(int i = 0; i< 5; i ++)
		{
			if (i == 1)
			{
				JButton button = new JButton("YES");
				button.addActionListener(this);
				button.setFont(new Font("Arial", Font.PLAIN, textsize));
				buttons.add(button);
				was_not = false;
			}
			if(i == 3)
			{
				JButton button = new JButton("NO");
				button.addActionListener(this);
				button.setFont(new Font("Arial", Font.PLAIN, textsize));
				buttons.add(button);
				was_not = false;
			}
			if (was_not)
			{
				JButton button = new JButton();
 				button.setVisible(false); 
 				buttons.add(button);
			}
			was_not = true;
		}

		this.background.add(buttons);
		this.background.add(button1);

		this.add(background);
  		this.setResizable(false);

		this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		this.setLocationRelativeTo(null);
		this.setVisible(true);
	}
}