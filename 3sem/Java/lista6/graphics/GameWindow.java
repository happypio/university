package graphics;

import mazedata.*;
import game.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Random;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;

public class GameWindow extends Frame
{
    private static final long serialVersionUID = 1L;
    private final int rows, columns, startx, starty;
    private final boolean do_rand;
    private GameWindow act;
    public int posx, posy;
    private int[][] maze;


    private Controler controler = new Controler()
    {
        @Override
        public void keyReleased(KeyEvent evt) {
            super.keyReleased(evt);
            if (maze[posx + this.pos_x][posy + this.pos_y] == 1) {
                posx += this.pos_x;
                posy += this.pos_y;
            }
            canvas.repaint();
            if (posx == 1 && posy == 1)
            {
                act.setEnabled(false);
                new End(act, columns, rows, do_rand);
            }
        }
    };

    BufferedImage img = null;
    {
        try {
            img = ImageIO.read(new File("graphics/pinguin.png"));
        } catch (IOException e) {}
    }
    
    private WindowListener frameList = new WindowAdapter()
    {
        @Override
        public void windowClosing (WindowEvent ev)
        {
            GameWindow.this.dispose();
        }
    };

    private Canvas canvas = new Canvas() {
        private static final long serialVersionUID = 1L;

        @Override
        public void paint(Graphics g){
            int window_width = getSize().width;
            int window_height = getSize().height;
            int htOfRow = window_height / ( 2 * rows + 1);
            int wdOfRow = window_width / (2 * columns + 1);
            for(int i = 0 ; i < 2 * columns + 1; i++) {
                for (int j = 0; j < 2 * rows + 1; j++) {
                    if (maze[i][j] == 0)
                        g.setColor(new Color (77, 38, 0));   
                    else
                        g.setColor(Color.lightGray);
                    if (i == 1 && j == 1)
                        g.setColor(new Color (204, 0, 0 ));
                    if (i == startx && j == starty)
                        g.setColor(new Color(38, 153, 0));
                    g.fillRect(i * wdOfRow, j * htOfRow, wdOfRow, htOfRow);

                }
            }
            g.drawImage(img, posx * wdOfRow
            , posy * htOfRow, wdOfRow, htOfRow, canvas);
        }
    };
    public GameWindow(int x, int y, boolean do_rand)
    {
        super("THE MAZE");
        act = this;
        this.do_rand = do_rand;
        columns = x;
        rows = y;
        if (do_rand)
        {
            Random rand = new Random();
            startx = 2 * rand.nextInt(x) - 1;
            starty = 2 * rand.nextInt(y) - 1;
        } else {
            startx = 2 * x - 1;
            starty = 2 * y - 1;
        }
        posx = startx;
        posy = starty;
        Maze maze_tmp = new Maze(x,y);
        maze = maze_tmp.convert_maze();
        setSize(1000, 1000);
        setLocationRelativeTo(null);
        addWindowListener(frameList);
        add(canvas, BorderLayout.CENTER);
        setResizable(true);
        setVisible(true);
        this.addKeyListener(controler);
    }
}