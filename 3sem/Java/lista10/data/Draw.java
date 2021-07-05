package data;
import java.awt.event.*;
public class Draw implements ActionListener {
    graphics.Board b;

    public Draw(graphics.Board b) {
        this.b = b;
    }

    @Override
    public void actionPerformed(ActionEvent arg0) {
        b.repaint();

    }

}