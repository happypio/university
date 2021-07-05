package game;
import graphics.*;
import javax.swing.*;

public class Game extends JFrame {
    private static final long serialVersionUID = 1L;
    public Board board;
    public int c, n, m;
    public Game(int c, int n, int m) {
        super("SANTA CLAUS");
        setSize(800,900);
        this.c = c;
        this.n = n;
        this.m = m;
        board = new Board(this,c,n,m);
        add(board);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }
}
