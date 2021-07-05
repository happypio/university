package graphics;

import data.*;
import game.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Menu extends JMenuBar {
    private static final long serialVersionUID = 1L;
    public Game state;
    JMenu game,moves,settings,help,board,col_b,col_p,col_in_p;
    JMenuItem new_game, end, board_eng,board_eur, col_b1,col_b2,col_b3, col_p1,col_p2,col_p3, col_in_p1,col_in_p2,col_in_p3, about_game, about_app;
    JMenuItem left, right, up, down, select;
    public class MoveListener implements ActionListener{
        public void actionPerformed(ActionEvent e) {
            BoardWindow tmp = state.board;
            String key = e.getActionCommand();
            switch (key) {
                case "left": // left
                    if (tmp.pos_x - 1 >= 0 && tmp.data.board[tmp.pos_x - 1][tmp.pos_y] != 2)
                        tmp.pos_x += -1;
                    break;
                case "up": // up
                    if (tmp.pos_y - 1 >= 0 && tmp.data.board[tmp.pos_x][tmp.pos_y - 1] != 2)
                        tmp.pos_y += -1;
                    break;
                case "right": // right
                    if (tmp.pos_x + 1 < 7 && tmp.data.board[tmp.pos_x + 1][tmp.pos_y] != 2)
                    tmp.pos_x += 1;
                    break;
                case "down": // down
                    if (tmp.pos_y + 1 < 7 && tmp.data.board[tmp.pos_x][tmp.pos_y + 1] != 2)
                        tmp.pos_y += 1;
                    break;
                case "select": // space
                    if (tmp.highlight != null && tmp.pos_x == tmp.highlight.x && tmp.pos_y == tmp.highlight.y) {
                        tmp.highlight = null;
                        tmp.right = 0;
                        tmp.repaint();
                    }
                    if (tmp.data.board[tmp.pos_x][tmp.pos_y] == 1) {
                        tmp.highlight = new Pair(tmp.pos_x, tmp.pos_y);
                        tmp.right = 1;
                        tmp.repaint();
                    }
                    if (tmp.highlight != null && tmp.data.board[tmp.pos_x][tmp.pos_y] == 0) {
                        if (tmp.data.valid_move(new Pair(tmp.pos_x, tmp.pos_y), tmp.highlight)) {
                            tmp.mutable = false;
                            tmp.data.do_move(new Pair(tmp.pos_x, tmp.pos_y), tmp.highlight);
                            tmp.right = 0;
                            tmp.highlight = null;
                            tmp.repaint();
                        }
                    }

                    break;
            }
            tmp.repaint();
        }
    }
    public Menu(Game o) {
        state = o;
        game = new JMenu("GAME");
        moves = new JMenu("MOVES");
        settings = new JMenu("SETTINGS");
        help = new JMenu("HELP");
        new_game = new JMenuItem("New game");
        new_game.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                new Game(state.game_type, state.col_b, state.col_p, state.col_in_p);
                state.dispose();
			}
        });
        new_game.setMnemonic('g');
        end = new JMenuItem("Exit");
        end.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                state.dispose();
			}
        });
        end.setMnemonic('e');
        left = new JMenuItem("left");
        left.setFont(new Font("sansserif", 20, 40));
        left.addActionListener(new MoveListener());
        right = new JMenuItem("right");
        right.setFont(new Font("sansserif", 20, 40));
        right.addActionListener(new MoveListener());
        up = new JMenuItem("up");
        up.setFont(new Font("sansserif", 20, 40));
        up.addActionListener(new MoveListener());
        down = new JMenuItem("down");
        down.setFont(new Font("sansserif", 20, 40));
        down.addActionListener(new MoveListener());
        select = new JMenuItem("select");
        select.setFont(new Font("sansserif", 20, 40));
        select.addActionListener(new MoveListener());
        up.setAccelerator(KeyStroke.getKeyStroke('u'));
        right.setAccelerator(KeyStroke.getKeyStroke('r'));
        left.setAccelerator(KeyStroke.getKeyStroke('l'));
        down.setAccelerator(KeyStroke.getKeyStroke('d'));
        select.setAccelerator(KeyStroke.getKeyStroke('s'));
        moves.add(left);
        moves.add(up);
        moves.add(right);
        moves.add(down);
        moves.add(select);
        board = new JMenu("Board");
        board_eng = new JMenuItem("English board");
        board_eur = new JMenuItem("European board");
        board_eng.setFont(new Font("sansserif", 20, 40));
        board_eur.setFont(new Font("sansserif", 20, 40));
        board_eng.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                if(state.board.mutable)
                {
                    state.game_type = 0;
                    new Game(state.game_type, state.col_b, state.col_p, state.col_in_p);
                    state.dispose();
                }
			}
        });
        board_eur.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                if(state.board.mutable)
                {
                    state.game_type = 1;
                    new Game(state.game_type, state.col_b, state.col_p, state.col_in_p);
                    state.dispose();
                }
			}
        });
        board.add(board_eng);
        board.add(board_eur);
        col_b = new JMenu("Board color");
        col_b1 = new JMenuItem("Orange");
        col_b1.setFont(new Font("sansserif", 20, 40));
        col_b2 = new JMenuItem("Yellow");
        col_b2.setFont(new Font("sansserif", 20, 40));
        col_b3 = new JMenuItem("Green");
        col_b3.setFont(new Font("sansserif", 20, 40));
        col_b1.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                state.col_b = new Color(221,115,10);
                state.board.set_board_color(state.col_b);
			}
        });
        col_b2.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                state.col_b = new Color(174, 193, 0);
                state.board.set_board_color(state.col_b);
			}
        });
        col_b3.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                state.col_b = new Color(22,137,26);
                state.board.set_board_color(state.col_b);
			}
        });
        col_b.add(col_b1);
        col_b.add(col_b2);
        col_b.add(col_b3);
        col_p = new JMenu("Pawns color");
        col_p1 = new JMenuItem("Grey");
        col_p1.setFont(new Font("sansserif", 20, 40));
        col_p2 = new JMenuItem("Purple");
        col_p2.setFont(new Font("sansserif", 20, 40));
        col_p3 = new JMenuItem("Blue");
        col_p3.setFont(new Font("sansserif", 20, 40));
        col_p1.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                state.col_p = new Color(160,160,160);
                state.board.set_pawns_color(state.col_p);
			}
        });
        col_p2.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                state.col_p = new Color(50,40,90);
                state.board.set_pawns_color(state.col_p);
			}
        });
        col_p3.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                state.col_p = new Color(27,52,107);
                state.board.set_pawns_color(state.col_p);
			}
        });
        col_p.add(col_p1);
        col_p.add(col_p2);
        col_p.add(col_p3);
        col_in_p = new JMenu("Inside pawns color");
        col_in_p1 = new JMenuItem("Green");
        col_in_p1.setFont(new Font("sansserif", 20, 40));
        col_in_p2 = new JMenuItem("Red");
        col_in_p2.setFont(new Font("sansserif", 20, 40));
        col_in_p3 = new JMenuItem("Blue");
        col_in_p3.setFont(new Font("sansserif", 20, 40));
        col_in_p1.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                state.col_in_p = new Color(0,102,0);
                state.board.set_inside_pawns(state.col_in_p);
			}
        });
        col_in_p2.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                state.col_in_p = new Color(144,10,35);
                state.board.set_inside_pawns(state.col_in_p);
			}
        });
        col_in_p3.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                state.col_in_p = new Color(95,134,255);
                state.board.set_inside_pawns(state.col_in_p);
			}
        });
        col_in_p.add(col_in_p1);
        col_in_p.add(col_in_p2);
        col_in_p.add(col_in_p3);
        about_game = new JMenuItem("About game");
        about_app = new JMenuItem("About application");
        game.setFont(new Font("sansserif", 20, 40));
        moves.setFont(new Font("sansserif", 20, 40));
        settings.setFont(new Font("sansserif", 20, 40));
        help.setFont(new Font("sansserif", 20, 40));
        new_game.setFont(new Font("sansserif", 20, 40));
        end.setFont(new Font("sansserif", 20, 40));
        board.setFont(new Font("sansserif", 20, 40));
        col_b.setFont(new Font("sansserif", 20, 40));
        col_p.setFont(new Font("sansserif", 20, 40));
        col_in_p.setFont(new Font("sansserif", 20, 40));
        about_app.setFont(new Font("sansserif", 20, 40));
        about_game.setFont(new Font("sansserif", 20, 40));
        game.add(new_game);
        game.add(end);
        settings.add(board);
        settings.add(col_b);
        settings.add(col_p);
        settings.add(col_in_p);

        about_game.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                new AboutGame();
			}
        });
        about_app.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
                new AboutApp();
			}
        });
        help.add(about_game);
        help.add(about_app);


        add(game);
        add(moves);
        add(settings);
        this.add(Box.createGlue());
        add(help);
    }

    
}
