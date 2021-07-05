package game;

import graphics.*;
import graphics.Menu;

import java.awt.*;
import javax.swing.*;

public class Game extends JFrame {
    private static final long serialVersionUID = 1L;
    public int game_type = 0;
    public Color col_b, col_p, col_in_p;
    public BoardWindow board;
    public JLabel txt;
    public Menu menu;
    public Game() {
        super("SOLITAIRE");
        col_b = new Color (174, 193, 0);
        col_p = new Color (160,160,160);
        col_in_p = new Color(0,102,0);
        setSize(800,900);
        txt = new JLabel();
        board = new BoardWindow(game_type, txt);
        menu = new Menu(this);
        
        add(menu, BorderLayout.NORTH);
        add(txt, BorderLayout.SOUTH);
        add(board);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }
    public Game(int game_type, Color col_b, Color col_p, Color col_in_p) {
        this.game_type = game_type;
        this.col_b = col_b;
        this.col_p = col_p;
        this.col_in_p = col_in_p;
        setSize(800,900);
        txt = new JLabel();
        board = new BoardWindow(game_type, txt);
        board.set_board_color(col_b);
        board.set_inside_pawns(col_in_p);
        board.set_pawns_color(col_p);
        menu = new Menu(this);
        add(menu, BorderLayout.NORTH);
        add(txt, BorderLayout.SOUTH);
        add(board);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }
}
