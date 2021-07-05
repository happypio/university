package przegladelemawt;

/*
    Copyright (c) November 2010 by Paweł Rzechonek
    Aplikacja okienkowa AWT - prezentuje wszystkie komponenty (za wyjątkiem Canvas)
    dostępne w pakiecie java.awt (bez obsługi zdarzeń sla tych komponentów).
    Dodatkowo, trzy obiekty klasy Panel pełnią rolę kontenerów z innymi komponentami.
*/

import java.awt.*;
import java.awt.event.*;

class MyFrame extends Frame
{
    private WindowListener frameList = new WindowAdapter()
    {
        @Override
        public void windowClosing (WindowEvent ev)
        {
            MyFrame.this.dispose();
        }
    };

    private Label lab = new Label("enter an integer");
    private Button but = new Button("calculate");
    private TextField tex = new TextField(10);
    private Panel north = new Panel();

    private CheckboxGroup cbg = new CheckboxGroup();
    private Checkbox man = new Checkbox("man",cbg,false);
    private Checkbox wom = new Checkbox("woman",cbg,true);
    private Checkbox tall = new Checkbox("tall");
    private Checkbox fat = new Checkbox("fat");
    private Checkbox veg = new Checkbox("vegetarian",true);
    private Panel west = new Panel(new GridLayout(5,1));

    private List age = new List(3,false);
    private Choice hair = new Choice();
    private Panel east = new Panel(new GridLayout(5,1));

    public MyFrame ()
    {
        super("the frame with panels");
        setSize(900,450);
        setLocation(200,200);

        north.add(lab);
        north.add(tex);
        north.add(but);
        add(north,BorderLayout.NORTH);    // Panel with FlowLayout

        west.add(man);
        west.add(wom);
        west.add(tall);
        west.add(fat);
        west.add(veg);
        add(west,BorderLayout.WEST);    // Panel with GridLayout

        east.add(new Label("age:"));
        east.add(age);
        age.add("babby");
        age.add("child");
        age.add("teenage");
        age.add("adult");
        age.add("old man/woman");
        east.add(new Label(" "));
        east.add(new Label("hair"));
        east.add(hair);
        hair.add("black");
        hair.add("brown");
        hair.add("blond");
        hair.add("gray");
        hair.add("bald");
        add(east,BorderLayout.EAST);    // Panel with GridLayout

        add(new TextArea(),BorderLayout.CENTER);

        add(new Scrollbar(Scrollbar.HORIZONTAL,0,16,-128,127),BorderLayout.SOUTH);

        addWindowListener(frameList);
        setVisible(true);
    }
}

public class PrzegladElemAWT {
    public static void main(String[] args) {
        new MyFrame();
    }
}
