import javax.swing.*; 
import java.awt.*;
import java.awt.event.*;
import java.io.*;

class ImagePanel extends JPanel {

    private Image image = null;

    public ImagePanel(int WIDTH,int HEIGHT) {
        this.image = new ImageIcon(new ImageIcon("background.jpg").getImage().getScaledInstance(WIDTH, HEIGHT, Image.SCALE_DEFAULT)).getImage();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(image, 0, 0, image.getWidth(null), image.getHeight(null), null);
    }
}

class Game_window extends JFrame
{
	public static int HEIGHT;
	public static int WIDTH;
	public ImagePanel background;

	public Game_window(String title)
	{
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		screenSize.getHeight();
		HEIGHT = (int)(Math.round(screenSize.height / 1.4));
		WIDTH = HEIGHT;
		background = new ImagePanel(WIDTH,HEIGHT);
		display(title);
	}

	
	public void display(String title)
	{
		this.setSize(WIDTH,HEIGHT);
		this.setTitle(title);
        
        this.add(background);
        
  		this.setResizable(false);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setLocationRelativeTo(null);
		this.setVisible(true);
	}
}