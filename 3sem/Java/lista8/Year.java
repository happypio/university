import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Year extends JPanel {
    private static final long serialVersionUID = 1L;
    public Calendar parent;
    public int y;
    public class Listener implements MouseListener {
        int m;
        public Listener(int i) {
            this.m = i;
        }
        public void mouseClicked(MouseEvent arg0) {}
        public void mouseEntered(MouseEvent arg0) {}
        public void mouseExited(MouseEvent arg0) {}
        public void mousePressed(MouseEvent arg0) {}
        @Override
        public void mouseReleased(MouseEvent arg0) {
            parent.tp.remove(parent.p2);
            parent.month = m;
            parent.p2 = new Month(m, y);
            parent.tp.add(parent.p2);
            parent.tp.setTitleAt(1, "MONTH: " + MonthPanel.m_names[m]);
        }
        
    }

    public Year(int year, Calendar p) {
        parent = p;
        y = year;
        setLayout(new GridLayout(3,4,20,20));
        for (int i = 0; i < 12; i ++) {

            MonthPanel m = new MonthPanel(year, i);
            m.setBorder(BorderFactory.createLineBorder(Color.BLACK));
            m.addMouseListener(new Listener(i));
            add(m);
        }
    }
}
