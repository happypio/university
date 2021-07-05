package pusteokno;

/*
    Copyright (c) November 2016 by Paweł Rzechonek
    Prosta aplikacja okienkowa AWT - puste okno.
*/

import java.awt.*;
import java.awt.event.*;

class MojeOkno extends Frame {
    // słuchacz zdarzeń okienkowych
    // jako klasa wewnętrzna dziedzicząca po adapterze
    private class SluchaczOkienkowy extends WindowAdapter
    {
        @Override
        // reakcja na zamknięcie okna
        public void windowClosing(WindowEvent ev)
        {
            MojeOkno.this.dispose();
        }
    };
    
    public MojeOkno()
    {
        super("puste okno");
        setSize(300,240);
        setLocation(100,100);
        addWindowListener(new SluchaczOkienkowy());
        setVisible(true);
    }
}

public class PusteOkno {
    public static void main(String[] args) {
        new MojeOkno();
    }
}
