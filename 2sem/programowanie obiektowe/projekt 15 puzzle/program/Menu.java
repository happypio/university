import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

class Menu extends Game_window implements ActionListener
{
	
	public Menu(String title)
	{
		super(title);
		display_mod();
	}
	public void actionPerformed(ActionEvent e)
	{
		JButton b = (JButton) e.getSource();
		String name = b.getActionCommand();
		if (name == "EXIT")
		{
			new Exit(this);
			
		}
		if (name == "PLAY GAME")
		{
			this.setVisible(false);
			this.dispose();
			new Play_game();
		}

		
	}
	
	public void display_mod()
	{
		this.background.setLayout(new GridLayout(6,3,10,40));
		this.background.setPreferredSize(new Dimension(WIDTH, HEIGHT));
		int textsize = (int) (Math.round(WIDTH / 35));
		int was_not = 1;
		for(int i=0; i<18; i++)
		{
			if (i == 4)
			{
				JButton button = new JButton("PLAY GAME");
				button.addActionListener(this);
				button.setFont(new Font("Arial", Font.PLAIN, textsize));
				this.background.add(button);
				was_not = 0;
			}
			if (i == 7)
			{
				JButton button = new JButton();
 				button.setVisible(false); 
 				this.background.add(button);
				was_not = 0;
			}
			if (i == 13)
			{
				JButton button = new JButton("EXIT");
				button.addActionListener(this);
				button.setFont(new Font("Arial", Font.PLAIN, textsize));
				this.background.add(button);
				was_not = 0;
			}
			if (was_not == 1)
 			{
 				JButton button = new JButton();
 				button.setVisible(false); 
 				this.background.add(button);
 			}
 			was_not = 1;
 		}
 		this.add(background);
		setVisible(true);


	}

}