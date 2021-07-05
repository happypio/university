package mazedata;

import java.util.Arrays;
import java.util.ArrayList;
import java.util.Random;

public class Maze {
    private class Chamber {
        public int[] walls;
        public Chamber() {
            walls = new int[]{0,0,0,0}; // left up right down
        }
    }
    private class Pair {
        public int x;
        public int y;
        public Pair(int a, int b) {
            x = a;
            y = b;
        }
    }
    private Chamber[][] maze;
    int W,H;
    private void change_walls(int x, int y, int x_b, int y_b) {
        if(x - x_b < 0) {
            maze[x][y].walls[2] = 1;
            maze[x_b][y_b].walls[0] = 1;
        }
        if(x - x_b > 0) {
            maze[x][y].walls[0] = 1;
            maze[x_b][y_b].walls[2] = 1;
        }
        if(y - y_b < 0) {
            maze[x][y].walls[3] = 1;
            maze[x_b][y_b].walls[1] = 1;
        }
        if(y - y_b > 0) {
            maze[x][y].walls[1] = 1;
            maze[x_b][y_b].walls[3] = 1;
        }
    }

    private void rand_dfs (boolean[][] path, int x, int y, int x_b, int y_b) {
        path[x][y] = true;
        change_walls(x,y,x_b,y_b);
        ArrayList <Pair> neighbours = new ArrayList<>();
        Pair[] moves_x = new Pair[]{new Pair(-1,0),
            new Pair(0,-1), new Pair(1,0), new Pair(0,1)};
        for (Pair m: moves_x) {
                int pos_x = x + m.x;
                int pos_y = y + m.y;
                if (0 <= pos_x && pos_x < W && 0 <= pos_y && pos_y < H)
                {
                    if (path[pos_x][pos_y] == false && (x != 0 || y != 0) )
                        neighbours.add(new Pair(pos_x, pos_y));
                }
        }
        while (!neighbours.isEmpty()) {
            Random rand = new Random();
            Pair random_neighbour = neighbours.get(rand.nextInt(neighbours.size()));
            if (path[random_neighbour.x][random_neighbour.y] == false)
                rand_dfs (path, random_neighbour.x, random_neighbour.y, x, y);
            neighbours.remove(random_neighbour);
        }



    }

    public void generate_maze(int x, int y) {
        boolean[][] path = new boolean[W][H];
        for (boolean[] p : path)
            Arrays.fill(p, false);
        rand_dfs(path, x, y, x, y);
    }

    public Maze(int x, int y) {
        maze = new Chamber[x][y];
        W = x;
        H = y;
        for (int i = 0; i < W; i++)
            for (int j = 0; j < H; j++)
                maze[i][j] = new Chamber();
        generate_maze(x - 1, y - 1);
    }
    public int[][] convert_maze()
    {
        int[][] maze_tmp = new int[2 * W + 1][2 * H + 1];
        for (int[] l : maze_tmp)
            Arrays.fill(l, 0);
        for (int i = 0; i < W; i++) {
            for (int j = 0; j < H; j++) {
                Chamber act = maze[i][j];
                int new_i = 2 * i + 1;
                int new_j = 2 * j + 1;
             maze_tmp[new_i][new_j] = 1;
                if (act.walls[0] == 1) {
                 maze_tmp[new_i - 1][new_j] = 1;
                }
                if (act.walls[1] == 1) {
                 maze_tmp[new_i][new_j - 1] = 1;
                }
                if (act.walls[2] == 1) {
                 maze_tmp[new_i + 1][new_j] = 1;
                }
                if (act.walls[3] == 1) {
                 maze_tmp[new_i][new_j + 1] = 1;
                }

            }
        }
        /*for (int z : maze[0][0].walls)
            System.out.print(z + "\n");
        for (int j = 0; j < 2*H + 1; j++) {
            for (int i = 0; i < 2*W + 1; i++) {
                System.out.print maze_tmp[i][j]);
            }
            System.out.println();
        }*/
        return maze_tmp;
    }
}