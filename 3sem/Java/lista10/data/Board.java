package data;
import java.util.concurrent.ThreadLocalRandom;
import java.util.ArrayList;
public class Board {
    game.Game game;
    public int c;
    public volatile int children, width, height, m_x, m_y;;
    public ArrayList<Pair> kids;
    public volatile int[][] board;  
    public volatile boolean e = false, g = false;
    public Board(game.Game game, int x, int n, int m) {
        this.game = game;
        c = x;
        children = x;
        width = m;
        height = n;
        board = new int[n][m];
        m_x = ThreadLocalRandom.current().nextInt(0, (width - 1) + 1);
        m_y = ThreadLocalRandom.current().nextInt(0, (height - 1) + 1);
        board[m_y][m_x] = 2;
        int n_x, n_y;
        kids = new ArrayList<Pair>();
        while (x > 0) {
            n_x = ThreadLocalRandom.current().nextInt(0, (width - 1) + 1);
            n_y = ThreadLocalRandom.current().nextInt(0, (height - 1) + 1);
            if (board[n_y][n_x] == 0 && Math.abs(n_x - m_x) + Math.abs(n_y - m_y) >= 6) {
                board[n_y][n_x] = 1;
                kids.add(new Pair(n_x,n_y));
                x -= 1;
            }
        }
        
    }
    public synchronized void move(int x, int y) {
        if (board[m_y][m_x] != 3 && board[m_y][m_x] != 1)
            board[m_y][m_x] = 0;
        m_x += x;
        m_y += y;
        board[m_y][m_x] = 2;
    }

    public synchronized Pair do_move(int x, int y, int id, boolean sleep) {
        // check whether kid was sleeping, if so then try to find gifts
        if (true) { // sleep
            int d_x[] = {-1, -1,0, 1, 1, 0};
            int d_y[] = {0, -1, -1, 0, 1, 1};
            Pair move = null;
            for (int i = 0; i < 4; i ++) {
                int new_x = x + d_x[i];
                int new_y = y + d_y[i];
                if (0 <= new_x && new_x < width && 0 <= new_y && new_y < height) {
                    if (board[new_y][new_x] == 3) {
                        move = new Pair(new_x, new_y);
                    }
                }
            }
            if (move != null) {
                board[y][x] = 0;
                if (board[move.y][move.x] == 2)
                    e = true;
                else {
                    board[move.y][move.x] = 1;
                    g = true;
                    children--;
                    //System.out.println(children);
                }
                return move;
            }
        }
        // check where is santa claus
        if (Math.abs(x - m_x) + Math.abs(y - m_y) <= 5) {
            //System.out.println(x + " " + y);
            if (x - m_x < 0 && board[y][x+1] != 1){
                board[y][x] = 0;
                if (board[y][x+1] == 2)
                    e = true;
                else
                    board[y][x+1] = 1;
                return new Pair(x + 1, y);
            } // go right
            if (x - m_x > 0 && board[y][x-1] != 1) {
                board[y][x] = 0;
                if (board[y][x-1] == 2)
                    e = true;
                else
                    board[y][x-1] = 1;
                return new Pair(x - 1, y);
            } // go left
            if (x - m_x == 0 && y - m_y < 0 && board[y + 1][x] != 1) {
                board[y][x] = 0;
                if (board[y+1][x] == 2)
                    e = true;
                else
                    board[y+1][x] = 1;
                return new Pair(x, y + 1);
            } // go down
            if (x - m_x == 0 && y - m_y > 0 && board[y-1][x] != 1) {
                board[y][x] = 0;
                if (board[y-1][x] == 2)
                    e = true;
                    else
                board[y-1][x] = 1;
                return new Pair(x, y - 1);
            } // go up

        }
        return random_move(x, y, id);
    }

    public synchronized Pair random_move(int x, int y, int id) {
        int d_x[] = {-1, 0, 1, 0};
        int d_y[] = {0, -1, 0, 1};
        ArrayList<Integer> xs = new ArrayList<Integer>();
        ArrayList<Integer> ys = new ArrayList<Integer>();
        for (int i = 0; i < 4; i ++) {
            int new_x = x + d_x[i];
            int new_y = y + d_y[i];
            if (0 <= new_x && new_x < width && 0 <= new_y && new_y < height) {
                if (board[new_y][new_x] != 1) {
                    xs.add(new_x);
                    ys.add(new_y);
                }
            }
        }
        int r = 0;
        if (xs.size() > 0)
            r = ThreadLocalRandom.current().nextInt(0, xs.size());
        else
            System.out.println(x + " " + y + " MAKABRA");
        board[y][x] = 0;
        if (board[ys.get(r)][xs.get(r)] == 2)
            e = true;
        else
            board[ys.get(r)][xs.get(r)] = 1;
        //System.out.println(x + " " + y + " " + xs.get(r) + " " + ys.get(r) + " ID: " + id);
        return new Pair(xs.get(r), ys.get(r));
    }

    public synchronized void draw() throws Exception{
        int c = 0;
        for (int i = 0; i < height; i ++) {
            for (int j = 0; j < width; j++) {
                if (board[i][j] == 1)
                    c += 1;
                System.out.print(board[i][j]);
            }
            System.out.println();
        }
        if (c > children)
            throw new Exception("ERROR!");
    }

    public synchronized boolean end(int x, int y) {
        if (children == 0) {
            new game.End(game ,c, height, width);
            return true;
        }
        if (g) {
            g = false;
            return true;
        }
        if (e ) {//|| board[y][x] == 2){
            //e = false;
            return true;
        }
        return false;
    }
}