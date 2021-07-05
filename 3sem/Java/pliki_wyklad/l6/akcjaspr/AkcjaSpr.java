package akcjaspr;

/*
    Copyright (c) November 2013 by Paweł Rzechonek
    Prosta aplikacja okienkowa AWT - sprawdza czy wprowadzony do pola tekstowego
    napis jest poprawnym zapisem liczby całkowitej (poprawność danych sprawdzana
    jest za pomocą dopasowania do wzorca).
    Sprawdzanie to odbywa się w metodzie obsługującej zdarzenie akcji.
*/

import java.awt.*;
import java.awt.event.*;

class MojeOkno extends Frame {
    // obiekt implementujący interfejs WindowListener dla zdarzeń okienkowych
    private WindowListener sluchaczOkienkowy = new WindowAdapter()
    {
        @Override
        public void windowClosing (WindowEvent ev)
        {
            MojeOkno.this.dispose();
        }
    };
    // obiekt implementujący interfejs ActionListener dla zdarzeń akcji
    private ActionListener sluchaczAkcji = new ActionListener()
    {
        @Override
        public void actionPerformed (ActionEvent ev)
        {
            String napis = pole.getText().trim();
            pole.setText(napis);
            if (napis.matches("([-]?[1-9]\\d*)|0"))
                etyk.setText(napis + " jest liczbą całkowitą");
            else
                etyk.setText(napis + " nie jest liczbą całkowitą");
            pole.requestFocus();
            pole.selectAll();
        }
    };
    // elementy GUI
    private Label etyk = new Label("Czy to jest liczba całkowita?");
    private Button przyc = new Button("sprawdź");
    private TextField pole = new TextField();

    public MojeOkno()
    {
        super("sprawdzanie poprawności danych");
        setSize(900,300);
        setLocation(100,100);
        add(etyk, BorderLayout.NORTH);
        add(przyc, BorderLayout.CENTER);
        add(pole, BorderLayout.SOUTH);
        // źródło zdarzenia Button deleguje słuchacza zdarzeń akcji ActionListener
        // do przechwytywania i obsługi zdarzeń akcji pochodzących od tego komponentu
        przyc.addActionListener(sluchaczAkcji);
        // okno aplikacji Frame deleguje słuchacza zdarzeń okienkowych WindowListener
        // do przechwytywania i obsługi zdarzeń okienkowych związanych z tym oknem
        this.addWindowListener(sluchaczOkienkowy);
        setResizable(false);
        setVisible(true);
    }
}

public class AkcjaSpr {
    public static void main(String[] args) {
        new MojeOkno();
    }
}
