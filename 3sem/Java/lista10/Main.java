import game.*;
public class Main {
    public static void main(String args[]) {
        Game g = new Game(Integer.parseInt(args[0]), Integer.parseInt(args[1]), Integer.parseInt(args[2]));
        for(int i = 0; i < g.c; i++) {
            try {
                g.board.kids[i].join();
            }

            catch(Exception e)
            {
                System.out.println(e.getMessage());
            }
        }
        new game.End(g, Integer.parseInt(args[0]), Integer.parseInt(args[1]), Integer.parseInt(args[2]));
    }
}
