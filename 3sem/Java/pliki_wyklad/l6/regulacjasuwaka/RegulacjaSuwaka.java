package regulacjasuwaka;

/*
    Copyright (c) November 2013 by Paweł Rzechonek
    Prosta aplikacja okienkowa AWT - wyświetla kąt skrętu określony za pomocą suwaka.
    Aktualizacja kąta dokonuje się w metodzie obsługującej zdarzenie regulacji.
*/

import java.awt.*;
import java.awt.event.*;

class MojeOkno extends Frame
{
    // obiekt implementujący interfejs WindowListener dla zdarzeń okienkowych
    private WindowListener sluchaczOkienkowy = new WindowAdapter()
    {
        @Override
        public void windowClosing (WindowEvent ev)
        {
            MojeOkno.this.dispose();
        }
    };
    // obiekt implementujący interfejs AdjustmentListener dla zdarzeń regulacji
    private AdjustmentListener sluchaczSuwaka = new AdjustmentListener()
    {
        @Override
        public void adjustmentValueChanged (AdjustmentEvent e)
        {
            et.setText(
                "obecny kąt to " + suw.getValue() + 
                " z zakresu {" + suw.getMinimum() + "..." +
                (suw.getMaximum() - suw.getVisibleAmount()) + "}"
            );
        }
    };

    private Label et = new Label("Jaki jest kierunek skrętu?");
    private Scrollbar suw = new Scrollbar(Scrollbar.HORIZONTAL, 0, 15, -180, 195);

    public MojeOkno ()
    {
        super("kierunek skrętu");
        setSize(1000,300);
        setLocation(100,100);
        add(et, BorderLayout.NORTH);
        add(suw, BorderLayout.SOUTH);
        // źródło zdarzenia Scrollbal deleguje słuchacza zdarzeń regulacji AdjustmentListener
        // do przechwytywania i obsługi zdarzeń regulacji pochodzących od tego komponentu
        suw.addAdjustmentListener(sluchaczSuwaka);
        // okno aplikacji Frame deleguje słuchacza zdarzeń okienkowych WindowListener
        // do przechwytywania i obsługi zdarzeń okienkowych związanych z tym oknem
        addWindowListener(sluchaczOkienkowy);
        setResizable(false);
        setVisible(true);
    }
}

public class RegulacjaSuwaka {
    public static void main(String[] args) {
        new MojeOkno();
    }
}
