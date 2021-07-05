package graphics;

import data.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class BoardWindow extends JPanel implements MouseListener, KeyListener {
    private static final long serialVersionUID = 1L;
    private static final int rows = 7, columns = 7;
    public Color board_color, pawns_color, in_pawns_color;
    public int game_type;
    public Board data;
    public int right = 0,left = 0;
    public Pair highlight;
    public int pawns = 0, c_moves = 0;
    public JLabel txt;
    public boolean mutable = true;
    public int pos_x = 3, pos_y = 3;
    public class Listener implements ActionListener {
        BoardWindow o;
        boolean v;
        Pair c;
        Pair mv;
        public Listener(boolean v, BoardWindow o, Pair c, Pair mv) {
            this.o = o;
            this.v = v;
            this.c = c;
            this.mv = mv;
        }
        public void actionPerformed(ActionEvent e) {
            if (v) {
                mutable = false;
                o.data.do_move(mv, c);
                o.right = 0;
                o.highlight = null;
                o.repaint();
            }
            else {
                o.highlight = null;
                o.right = 0;
                o.repaint();
            }
        }
    }

    public class PopupMenu extends JPopupMenu {
        private static final long serialVersionUID = 1L;
        public PopupMenu(String[] names, Pair[] moves, Pair c,BoardWindow o) {
            super("MOVES");
            if (names[0] == "No moves!") {
                JMenuItem mo = new JMenuItem(names[0]);
                mo.setFont(new Font("sansserif", 20, 40));
                mo.addActionListener(new Listener(false, o, c, new Pair(0,0)));
                add(mo);
            }
            else {
            for (int i = 0 ;i < names.length; i ++) {
                JMenuItem mo = new JMenuItem(names[i]);
                mo.setFont(new Font("sansserif", 20, 40));
                Pair mv = moves[i];
                mo.addActionListener(new Listener(true, o, c, mv));
                add(mo);
            }
            }
        }
    }

    public BoardWindow(int g, JLabel txt) {
        setFocusable(true);
        board_color = new Color (174, 193, 0);
        pawns_color = new Color (160,160,160);
        in_pawns_color = new Color(0,102,0);
        game_type = g;
        this.txt = txt;
        data = new Board(game_type);
        pawns = data.count_pawns();
        addMouseListener(this);
        addKeyListener(this);
    }

    public Pair[] find_moves(int x, int y) {
        int size = 0;
        Pair[] tmp = new Pair[4];
        Pair[] moves = new Pair[]{new Pair(-1,0), new Pair(0,-1),
            new Pair(1,0), new Pair(0,1) };
            for (Pair m: moves) {
                int new_x = x + m.x;
                int new_y = y + m.y;
                if (0 <= new_x && new_x < 7 && 0 <= new_y && new_y < 7) {
                    if (data.board[new_x][new_y] == 1){
                        new_x += m.x;
                        new_y += m.y;
                        if (0 <= new_x && new_x < 7 && 0 <= new_y && new_y < 7) {
                            if(data.board[new_x][new_y] == 0){
                                tmp[size] = new Pair(new_x, new_y);
                                size += 1;
                            }
                        }
                    }
                }
            }
        Pair[] ans = new Pair[size];
        int k = 0;
        for (int i = 0 ; i < 4; i++) {
            if (tmp[i] != null) {
                ans[k] = tmp[i];
                k+=1;
            }
        }
        return ans;
    }

    public Pair get_coordinates(int x, int y){
        int window_width = getSize().width;
        int window_height = getSize().height;
        int htOfRow = window_height / (rows);
        int wdOfRow = window_width / (columns);
        return new Pair(x / wdOfRow, y / htOfRow);
    }

    @Override
    public void paint(Graphics g) 
    {
        data.find_moves();
        c_moves = data.count_moves;
        pawns = data.count_pawns();
        String message;
        message = pawns + " pawns left!";
        if (c_moves == 0) {
            message = "Congratulations! It's the end of the game, pawns left: " + pawns;
            mutable = true;
        }
        txt.setText(message);
        txt.setFont(new Font("sansserif", 20, 40));
        txt.setHorizontalAlignment(JLabel.CENTER);
        txt.setVerticalAlignment(JLabel.CENTER);

        int window_width = getSize().width;
        int window_height = getSize().height;
        int htOfRow = window_height / (rows);
        int wdOfRow = window_width / (columns);
        for(int i = 0 ; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                if (data.board[i][j] == 1)
                    g.setColor(pawns_color);   
                if (data.board[i][j] == 2)
                    g.setColor(Color.BLACK);
                if (data.board[i][j] == 0)
                    g.setColor(board_color);
                if (i == pos_x && j == pos_y) {
                    g.setColor(new Color (224, 224, 224));
                }
                if (highlight != null && i == highlight.x && j == highlight.y)
                {
                    g.setColor(new Color (0, 162, 255));
                }
                g.fillRect(i * wdOfRow, j * htOfRow, wdOfRow, htOfRow);
                if (data.board[i][j] == 1){
                    g.setColor(in_pawns_color);
                    int x = i * wdOfRow ;//+ (wdOfRow/2);
                    int y = j * htOfRow ;//+ (htOfRow/2);
                    g.fillOval(x,y,wdOfRow,htOfRow);
                }
            }
        }
    }

    @Override
    public void mouseClicked(MouseEvent me) {
        if (me.getButton() == MouseEvent.BUTTON1){
            Pair c = get_coordinates(me.getX(), me.getY());
            if (right == 1 && highlight != null && highlight.x == c.x && highlight.y == c.y) {
                highlight = null;
                right = 0;
                repaint();
            }
            else {
                if (data.board[c.x][c.y] == 1) {
                    highlight = get_coordinates(me.getX(), me.getY());
                    right = 1;
                    repaint();
                }
            }
            if (right == 1 && data.board[c.x][c.y] == 0) {
                if (data.valid_move(c, highlight)) {
                    mutable = false;
                    data.do_move(c, highlight);
                    right = 0;
                    highlight = null;
                    repaint();
                }
            }
        }
        if (me.getButton() == MouseEvent.BUTTON3){
            String names[];
            Pair c = get_coordinates(me.getX(), me.getY());
            if (data.board[c.x][c.y] == 1) {
                highlight = get_coordinates(me.getX(), me.getY());
                repaint();
                Pair[] moves = find_moves(c.x, c.y);
                if (moves.length == 0)
                    names = new String[]{"No moves!"};
                else {
                    names = new String[moves.length];
                    for(int i = 0; i < moves.length; i++) {
                        int dx = moves[i].x - c.x;
                        int dy = moves[i].y - c.y;
                        if (dx > 0)
                            names[i] = "RIGHT";
                        if (dx < 0)
                            names[i] = "LEFT";
                        if (dy > 0)
                            names[i] = "DOWN";
                        if (dy < 0)
                            names[i] = "UP";
                    }
                }
                PopupMenu popupmenu = new PopupMenu(names, moves, c, this);
                popupmenu.show(this , me.getX(), me.getY());
                left = (left + 1)%2;
            }
        }
    }

    @Override
    public void mousePressed(MouseEvent me) {  
    }
 
    @Override
    public void mouseReleased(MouseEvent me) {
    }
 
    @Override
    public void mouseEntered(MouseEvent me) {        
    }
 
    @Override
    public void mouseExited(MouseEvent me) {        
    }

    public void set_board_color(Color c) {
        board_color = c;
        repaint();

    }

    public void set_pawns_color(Color c) {
        pawns_color = c;
        repaint();
    }

    public void set_inside_pawns(Color c) {
        in_pawns_color = c;
        repaint();
    }

    @Override
    public void keyPressed(KeyEvent arg0) {
    }

    @Override
    public void keyReleased(KeyEvent evt) {
        int key = evt.getKeyCode();
        switch (key) {
            case 37: //left
                if (pos_x - 1 >= 0 && data.board[pos_x - 1][pos_y] != 2)
                    pos_x += -1;
                break;
            case 38: //up
                if (pos_y - 1 >= 0 && data.board[pos_x][pos_y - 1] != 2)
                    pos_y += -1;
                break;
            case 39: //right
                if (pos_x + 1 < 7 && data.board[pos_x + 1][pos_y] != 2)
                    pos_x += 1;
                break;
            case 40: //down
                if (pos_y + 1 < 7 && data.board[pos_x][pos_y + 1] != 2)
                    pos_y += 1;
                break;
            case 32: //space
                if(highlight != null && pos_x == highlight.x && pos_y == highlight.y){
                    highlight = null;
                    right = 0;
                    repaint(); 
                }
                if (data.board[pos_x][pos_y] == 1) {
                    highlight = new Pair(pos_x, pos_y);
                    right = 1;
                    repaint();
                }
                if (highlight != null && data.board[pos_x][pos_y] == 0) {
                    if (data.valid_move(new Pair(pos_x, pos_y), highlight)) {
                        mutable = false;
                        data.do_move(new Pair(pos_x, pos_y), highlight);
                        right = 0;
                        highlight = null;
                        repaint();
                    }
                }

                    
                break;
        }
        repaint();
    }

    @Override
    public void keyTyped(KeyEvent arg0) {
    }
    
}
