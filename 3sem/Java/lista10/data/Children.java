package data;
import java.util.Random;
public class Children extends Thread {
    Random rand = new Random();
    volatile boolean stop = false;
    int def_sleep = 100;
    public volatile int x, y, id, r = 0;
    public volatile boolean sleeping = false;
    Board b;
    public Children(int x, int y, Board b, int id) {
        this.x = x;
        this.y = y;
        this.b = b;
        this.id = id;
    }
    public void run() {
        while (!b.end(x, y) && !stop) {
            // 2 moves and sleep
            if (r < 2)
            {
                move();
                r ++;
            }
            else
            {
                rest();
                r = 0;
            }
        }
    }
    public void interrupt() {
        System.out.println("STOPPED");
        stop = true;
    }

    public void move() {
        //System.out.println(id + " child is moving...");
        sleeping = false;
        Pair n = b.do_move(x, y, id, sleeping);
        x = n.x;
        y = n.y;
    }

    public void rest() {
        //System.out.println(id + " child is resting...");
        try {
            sleeping = true;
            sleep(rand.nextInt(25) * def_sleep + 10 * def_sleep);
        }
        catch (InterruptedException e) {
            return;
        }
    }
} 