package prosteokno;

/*
    Copyright (c) November 2016 by Paweł Rzechonek
    Prosta aplikacja okienkowa AWT - okno z etykietą, przyciskiem
    i polem tekstowym.
*/

import java.awt.*;
import java.awt.event.*;

class MojeOkno extends Frame {
    // słuchacz zdarzeń okienkowych
    private class SluchaczOkienkowy extends WindowAdapter
    {
        @Override
        // reakcja na zamknięcie okna
        public void windowClosing (WindowEvent ev)
        {
            MojeOkno.this.dispose();
        }
    };
    // elementy GUI
    private Label etyk = new Label("liść róży");
    private Button przyc = new Button("weź");
    private TextField pole = new TextField("weź prędko liść róży w swoją dłoń");

    public MojeOkno()
    {
        super("proste okno");
        setSize(700,300);
        setLocation(300,300);
        add(etyk, BorderLayout.NORTH);
        add(przyc, BorderLayout.CENTER);
        add(pole, BorderLayout.SOUTH);
        etyk.setAlignment(Label.RIGHT);
        addWindowListener(new SluchaczOkienkowy());
        setResizable(false);
        setVisible(true);
    }
}

public class ProsteOkno {
    public static void main(String[] args) {
        new MojeOkno();
    }
}
