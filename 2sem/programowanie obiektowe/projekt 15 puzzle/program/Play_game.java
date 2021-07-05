import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Random;
import java.util.*; 

class Pair
{
	public int x;
	public int y;
	public Pair(int a, int b)
	{
		this.x = a;
		this.y = b;
		
	}
	public void set_val(int a, int b)
	{
		this.x = a;
		this.y = b;
	}
}

class Pair_of_pairs
{
	public Pair a;
	public Pair b;
	public Pair_of_pairs(Pair x, Pair y)
	{
		this.a = x;
		this.b = y;
	}
	public void set_val(Pair x, Pair y)
	{
		this.a = x;
		this.b = y;
	}
}

class Button extends JButton
{
	public int x;
	public int y;
	public String name;
	public ImageIcon icon;
	public ImageIcon alter_icon;
	public Button(int a, int b,String n)
	{
		this.x = a;
		this.y = b;
		this.name = n;
	}
}
class Play_game extends Game_window implements ActionListener
{
	public Board game_board;
	public Button buttons[];
	public int count_moves;
	public Boolean end_game;
	public JLabel c_moves;
	public JLabel left_moves;
	public void actionPerformed(ActionEvent e)
	{
		Button tmp = new Button(0,0,"");
		
		JButton jb = (JButton) e.getSource();

		if(jb.getClass() == tmp.getClass())
		{
			Button b = (Button) jb;
			int y = b.y;
			int x = b.x;

			Pair result = game_board.make_move(x,y);
			if (result != null)
			{
				if(this.end_game != true)
				{
					this.count_moves += 1;
					c_moves.setText("Your moves: " + count_moves);
					
				}
				int new_y = result.y;
				int new_x = result.x;
				String old_name = buttons[new_y * 4 + new_x].name;
				ImageIcon old_icon = buttons[new_y * 4 + new_x].icon;
				ImageIcon old_alter_icon = buttons[new_y * 4 + new_x].alter_icon;
				buttons[new_y * 4 + new_x].name = buttons[y * 4 + x].name;
				buttons[new_y * 4 + new_x].icon = buttons[y * 4 + x].icon;
				buttons[new_y * 4 + new_x].alter_icon = buttons[y * 4 + x].alter_icon;
				buttons[new_y * 4 + new_x].setIcon(buttons[y * 4 + x].icon);
				
				buttons[y * 4 + x].name = old_name;
				buttons[y * 4 + x].icon = old_icon;
				buttons[y * 4 + x].alter_icon = old_alter_icon;
				buttons[y * 4 + x].setIcon(old_icon);
				for(int i = 0; i < 16; i++)
				{
					ImageIcon icon = buttons[i].icon;
					buttons[i].setIcon(icon);
				}
				if(game_board.terminal() && !this.end_game)
				{
					new End(count_moves);
					this.end_game = true;
				}

				if(this.end_game != true)
				{
					Pair[] moves;
					moves = this.game_board.BFS();
					if(moves != null)
					{
						int m = moves.length;
						left_moves.setText("<html>" + "Moves to solve <br> this puzzle now:<br>" + m + "</html>");
					}
					else
						left_moves.setText("<html>" + "Moves to solve <br> this puzzle now:<br>" + ">34" + "</html>");
				}
				else 
					left_moves.setText("<html>" + "Moves to solve <br> this puzzle now:<br>" + "0" + "</html>");
					
				setVisible(true);
			} 
		}

		String name = jb.getActionCommand();
		if(name == "HINT")
		{
			Pair[] moves;
			moves = this.game_board.BFS();
			if (moves != null)
			{
				Pair first_move = moves[0];
				buttons[first_move.y * 4 + first_move.x].setIcon(buttons[first_move.y * 4 + first_move.x].alter_icon);

			}
			
		}
		if(name == "RESTART")
		{
			this.setVisible(false);
			this.dispose();
			new Play_game();

		}
		if(name == "MENU")
		{
			this.setVisible(false);
			this.dispose();
			new Menu("Menu");
		}


	}
	public Play_game()
	{

		super("Game");
		this.game_board = new Board();
		this.count_moves = 0;
		this.end_game = false;
		display_mod();
	}
	public void display_mod()
	{
		buttons = new Button[16];
		int margin = (int) Math.round(WIDTH / 8);
		this.background.setLayout(new GridLayout(7,6));
		this.background.setPreferredSize(new Dimension(WIDTH, HEIGHT));

		game_board.generate_board();
		int cnt = 0;
		int textsize = (int) (Math.round(WIDTH / 56));
		for(int i = 0;i < 42; i++)
		{
			if( i > 5 && i%6 !=0 && i%6 != 5 && i < 29)
			{
				int name = game_board.act_board[cnt / 4][cnt % 4];
				Button button = new Button(cnt % 4, cnt / 4,Integer.toString(name));
				buttons[cnt] = button;
				button.addActionListener(this);
    			this.background.add(button);
    			cnt += 1;
			}
			else
			{
				if(i == 34)
				{
					JPanel panel = new JPanel();
					panel.setLayout(new GridLayout(2,1));
					
					JButton button = new JButton();
					button.setText("HINT");
					button.setFont(new Font("Arial", Font.PLAIN, textsize));
					button.addActionListener(this);
					panel.add(button);
					JButton button1 = new JButton();
					button1.setText("MENU");
					button1.setFont(new Font("Arial", Font.PLAIN, textsize));
					button1.addActionListener(this);
					panel.add(button1);
					this.background.add(panel);
				}
				//Moves to solve this puzzle
				else
				{
					if(i == 31)
					{
						Pair[] moves;
						moves = this.game_board.BFS();
						if(moves != null)
						{
							int m = moves.length;
							JLabel label1 = new JLabel("<html>" + "Moves to solve <br> this puzzle <br> at the beginning:<br>" + m + "</html>",SwingConstants.CENTER);
							label1.setFont(new Font("Arial", Font.PLAIN, textsize));
							this.background.add(label1);
						}
					}
					else
					{
						if(i == 32)
						{
							Pair[] moves;
							moves = this.game_board.BFS();
							if (moves != null)
							{
								int m = moves.length;
								left_moves = new JLabel("<html>" + "Moves to solve <br> this puzzle now:<br>" + m + "</html>",SwingConstants.CENTER);
								left_moves.setFont(new Font("Arial", Font.PLAIN, textsize));
								this.background.add(left_moves);
							}

						}
						else
						{
							if(i == 37)
							{
								c_moves = new JLabel("Your moves: " + count_moves,SwingConstants.CENTER);
								c_moves.setFont(new Font("Arial", Font.PLAIN, textsize));
								this.background.add(c_moves);
							}
							else
							{
								JButton button = new JButton();
	 							button.setVisible(false); 
	 							this.background.add(button);
							}
						}
						
 					}
				}
				
			}
			
		}
		
		
    	this.add(background);

    	setVisible(true);
    	cnt = 0;
		for(int i = 0;i < 42; i++)
		{
			if( i > 5 && i%6 !=0 && i%6 != 5 && i < 29)
			{
				ImageIcon icon = null;
				ImageIcon alter_icon = null;
				if(game_board.act_board[cnt / 4][cnt % 4] == 0)
				{
					alter_icon = new ImageIcon("zero.jpg");
					icon = new ImageIcon("zero.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 1)
				{
					alter_icon = new ImageIcon("yone.jpg");
					icon = new ImageIcon("bone.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 2)
				{
					alter_icon = new ImageIcon("ytwo.jpg");
					icon = new ImageIcon("btwo.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 3)
				{
					alter_icon = new ImageIcon("ythree.jpg");
					icon = new ImageIcon("bthree.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 4)
				{
					alter_icon  = new ImageIcon("yfour.jpg");
					icon = new ImageIcon("bfour.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 5)
				{
					alter_icon  = new ImageIcon("yfive.jpg");
					icon = new ImageIcon("bfive.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 6)
				{
					alter_icon  = new ImageIcon("ysix.jpg");
					icon = new ImageIcon("bsix.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 7)
				{
					alter_icon = new ImageIcon("yseven.jpg");
					icon = new ImageIcon("bseven.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 8)
				{
					alter_icon = new ImageIcon("yeight.jpg");
					icon = new ImageIcon("beight.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 9)
				{
					alter_icon = new ImageIcon("ynine.jpg");
					icon = new ImageIcon("bnine.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 10)
				{
					alter_icon = new ImageIcon("yten.jpg");
					icon = new ImageIcon("bten.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 11)
				{
					alter_icon = new ImageIcon("yeleven.jpg");
					icon = new ImageIcon("beleven.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 12)
				{
					alter_icon = new ImageIcon("ytwelve.jpg");
					icon = new ImageIcon("btwelve.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 13)
				{
					alter_icon = new ImageIcon("ythirteen.jpg");
					icon = new ImageIcon("bthirteen.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 14)
				{
					alter_icon = new ImageIcon("yfourteen.jpg");
					icon = new ImageIcon("bfourteen.jpg");
				}
				if(game_board.act_board[cnt / 4][cnt % 4] == 15)
				{
					alter_icon = new ImageIcon("yfifteen.jpg");
					icon = new ImageIcon("bfifteen.jpg");
				}
				Button button = buttons[cnt];
    			Image img = icon.getImage() ;  
   				Image newimg = img.getScaledInstance( button.getSize().width, button.getSize().height,  java.awt.Image.SCALE_SMOOTH ) ;
   				Image img2 = alter_icon.getImage() ;  
   				Image newimg2 = img2.getScaledInstance( button.getSize().width, button.getSize().height,  java.awt.Image.SCALE_SMOOTH ) ;
   				icon = new ImageIcon( newimg );
   				alter_icon = new ImageIcon (newimg2);
				button.setIcon(icon);
				button.alter_icon = alter_icon;
				button.icon = icon;
				cnt += 1;
			}
			
		}
		setVisible(true);
	}
}