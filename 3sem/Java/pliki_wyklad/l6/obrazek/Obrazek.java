package obrazek;

/*
    Copyright (c) November 2016 by Paweł Rzechonek
    Aplikacja okienkowa AWT - prezentuje możliwości klasy Canvas
    w wyświetlaniu obrazków zapisanych na dysku w postaci plików graficznych.
*/

import java.awt.*;
import java.awt.image.*;
import java.awt.event.*;
import java.io.*;
import javax.imageio.*;

class MojeOkno extends Frame
{
    private WindowListener frameList = new WindowAdapter()
    {
        @Override
        public void windowClosing (WindowEvent ev)
        {
            MojeOkno.this.dispose();
        }
    };

    private BufferedImage img = null;
    {
        try { img = ImageIO.read(new File("fig.jpg")); }
        catch (IOException e) { }
    }
    private Canvas plotno = new Canvas() {
        @Override
        public void paint(Graphics gr) {
            super.paint(gr);
            gr.setColor(new Color(192, 192, 192));
            gr.fillOval(64-16, 64-16, 255+32, 204+32);
            gr.setColor(Color.black);
            gr.drawRect(64-4, 64-4, 255+8, 204+8);
            if (img != null) gr.drawImage(img, 64, 64, this);
        }
    };

    public MojeOkno()
    {
        super("obraz na płótnie");
        setSize(2000, 1000);
        setLocation(100, 100);
        add(plotno, BorderLayout.CENTER);
        addWindowListener(frameList);
        setResizable(false);
        setVisible(true);
    }
}

public class Obrazek {
    public static void main(String[] args) {
        new MojeOkno();
    }
}
