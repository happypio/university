package graphics;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.image.*;
import java.io.*;
import javax.imageio.*;
import java.util.ArrayList;

public class Board extends JPanel implements KeyListener{
    private static final long serialVersionUID = 1L;
    public data.Board b;
    public game.Game game;
    private int pos_x, pos_y, rows, columns;
    private boolean give_gift = false;
    ArrayList<data.Pair> gifts;
    public Thread[] kids;
    public Timer timer;
    public data.Children[] ch;
    BufferedImage sc = null;
    {
        try {
            sc = ImageIO.read(new File("graphics/santaclaus.png"));
        } catch (IOException e) {}
    }
    BufferedImage gift = null;
    {
        try {
            gift = ImageIO.read(new File("graphics/gift.png"));
        } catch (IOException e) {}
    }
    BufferedImage kid = null;
    {
        try {
            kid = ImageIO.read(new File("graphics/kid.png"));
        } catch (IOException e) {}
    }
    public data.Draw time_listener;
    public Board(game.Game game, int c, int n, int m) {
        setFocusable(true);
        gifts = new ArrayList<>();
        this.game = game;
        b = new data.Board(game, c, n, m);
        pos_x = b.m_x; pos_y = b.m_y;
        rows = n; columns = m;
        kids = new Thread[c];
        ch = new data.Children[c];
        for(int i = 0; i < c; i++) {
            ch[i] = new data.Children(b.kids.get(i).x, b.kids.get(i).y, b, i);
            kids[i] = new Thread(ch[i]);
        }
        time_listener = new data.Draw(this);
        timer = new Timer(10,time_listener);//create the timer which calls the actionperformed method for every 10 millisecond(1 second=1000 millisecond)
        timer.start();//start the task*/
        addKeyListener(this);
        for(int i = 0; i < c; i++) {
            kids[i].start();
        }
    }

    @Override
    public synchronized void paint(Graphics g) 
    {
        int window_width = getSize().width;
        int window_height = getSize().height;
        int htOfRow = window_height / (rows);
        int wdOfRow = window_width / (columns);
        for(int i = 0 ; i < columns; i++) {
            for (int j = 0; j < rows; j++) {   
                g.setColor(new Color (255, 166, 77)); 
                g.fillRect(i * wdOfRow, j * htOfRow, wdOfRow, htOfRow);
                g.setColor(Color.BLACK);
                g.drawRect(i * wdOfRow, j * htOfRow, wdOfRow, htOfRow); 
            }
        }
        for (data.Children c : ch) {
            g.drawImage(kid, c.x * wdOfRow
                    , c.y * htOfRow, wdOfRow, htOfRow, this);
        }
        if (give_gift) {
            give_gift = false;
            b.board[pos_y][pos_x] = 3;
            gifts.add(new data.Pair(pos_x, pos_y));
        }
        for (data.Pair p: gifts) {
            g.drawImage(gift, p.x * wdOfRow
            , p.y * htOfRow, wdOfRow, htOfRow, this);
        }
        g.drawImage(sc, pos_x * wdOfRow
            , pos_y * htOfRow, wdOfRow, htOfRow, this);
    }

    @Override
    public void keyPressed(KeyEvent arg0) {
        // TODO Auto-generated method stub

    }

    @Override
    public void keyReleased(KeyEvent arg0) {
        int key = arg0.getKeyCode();
        switch (key) {
            case 37: //left
                if (pos_x - 1 >= 0) {
                    pos_x += -1;
                    b.move(-1,0);
                }
                break;
            case 38: //up
                if (pos_y - 1 >= 0) {
                    pos_y += -1;
                    b.move(0,-1);
                }
                break;
            case 39: //right
                if (pos_x + 1 < columns) {
                    pos_x += 1;
                    b.move(1,0);
                }
                break;
            case 40: //down
                if (pos_y + 1 < rows) {
                    pos_y += 1;
                    b.move(0,1);
                }
                break;
            case 32: //space
                give_gift = true;
                break;
        }
        repaint();

    }

    @Override
    public void keyTyped(KeyEvent arg0) {
        // TODO Auto-generated method stub

    }
}
