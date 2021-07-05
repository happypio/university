package game;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Controler implements KeyListener{
    public int pos_x, pos_y;
    public void keyPressed(KeyEvent evt) {
    }

    @Override
    public void keyReleased(KeyEvent evt) {
        int key = evt.getKeyCode();
        switch (key) {
            case 37: //left
                pos_x = -1;
                pos_y = 0;
                break;
            case 38: //up
                pos_y = -1;
                pos_x = 0;
                break;
            case 39: //right
                pos_x = 1;
                pos_y = 0;
                break;
            case 40: //down
                pos_y = 1;
                pos_x = 0;
                break;
        }
    }

    @Override
    public void keyTyped(KeyEvent evt) {
    }
}
