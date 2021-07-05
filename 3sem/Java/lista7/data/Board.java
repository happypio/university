package data;
public class Board {
    public int board[][];
    public int pawns = 0;
    public int count_moves = 0;
    public Board(int b) {
        board = new int[7][7];
        if (b == 0)
            generate_english();
        else
            generate_european();
    }
    public int count_pawns() {
        int tmp = 0;
        for (int i = 0; i < 7; i ++) {
            for (int j = 0 ; j < 7 ; j++)
                if(board[i][j] == 1)
                    tmp += 1;
        }
        pawns = tmp;
        return tmp;
    }
    public void generate_english() {
        for(int i = 0; i < 7; i++) {
            for(int j = 0; j < 7; j++) {
                board[i][j] = 1;
                if (i < 2 || i > 4)
                    if (j < 2 || j > 4)
                        board[i][j] = 2;
            }
        }
        board[3][3] = 0;
    }
    public void generate_european() {
        generate_english();
        board[1][1] = 1;
        board[5][1] = 1;
        board[1][5] = 1;
        board[5][5] = 1;
    }
    public void check_possible(int x, int y) {
        Pair[] moves = new Pair[]{new Pair(-1,0), new Pair(0,-1),
        new Pair(1,0), new Pair(0,1) };
        for (Pair m: moves) {
            int new_x = x + m.x;
            int new_y = y + m.y;
            if (0 <= new_x && new_x < 7 && 0 <= new_y && new_y < 7) {
                if (board[new_x][new_y] == 1){
                    new_x += m.x;
                    new_y += m.y;
                    if (0 <= new_x && new_x < 7 && 0 <= new_y && new_y < 7) {
                        if(board[new_x][new_y] == 1){
                            count_moves += 1;
                        }
                    }
                }
            }
        }
    }
    public void find_moves() {
        count_moves = 0;
        for (int i = 0; i < 7; i ++) {
            for (int j = 0; j < 7; j++) {
                if (board[i][j] == 0) {
                    check_possible(i,j);
                }
            }
        }
    }
    private int abs(int x){
        if (x > 0) return x;
        return -x;
    }
    public boolean valid_move(Pair p1, Pair p2) {
        if (abs(p1.x - p2.x) != 2 && abs(p1.y - p2.y) != 2)
            return false;
        if (abs(p1.x - p2.x) == 2 && abs(p1.y - p2.y) != 0)
            return false;
        if (abs(p1.x - p2.x) != 0 && abs(p1.y - p2.y) == 2)
            return false;

        int x = (p1.x + p2.x) / 2;
        int y = (p1.y + p2.y) / 2;
        if (board[p1.x][p1.y] == 0 && board[p2.x][p2.y] == 1)
            if(board[x][y] == 1)
                return true;
        return false;
    }
    public void do_move(Pair p1, Pair p2) {
        int x = (p1.x + p2.x) / 2;
        int y = (p1.y + p2.y) / 2;
        board[p1.x][p1.y] = 1;
        board[p2.x][p2.y] = 0;
        board[x][y] = 0;
    }
    public void print() {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                System.out.print(board[j][i]);
            }
            System.out.println();
        }
    }
    public int[][] get_board() {
        return board;
    }
}