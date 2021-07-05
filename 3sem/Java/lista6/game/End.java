package game;
import graphics.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class End extends Frame {
    private static final long serialVersionUID = 1L;
    private Label l = new Label("CONGRATULATIONS!\n Do you want to play again?");
    public Button yes = new Button("YES");
    public Button nope = new Button("NO");
    private Panel center = new Panel(new GridLayout(1, 2));
    private GameWindow window;
    private final int x,y;
    private final boolean do_rand;
    private End act;
    private ActionListener y_listen = new ActionListener()
    {
        @Override
        public void actionPerformed(ActionEvent e) {
            new GameWindow(x,y,do_rand);
            window.dispose();
            act.dispose();
        }
    };
    private ActionListener n_listen = new ActionListener()
    {
        @Override
        public void actionPerformed(ActionEvent e) {
            window.dispose();
            act.dispose();

        }
    };

    public End(GameWindow g, int x, int y, boolean do_rand) {
        super("THE END!");
        act = this;
        window = g;
        this.x = x;
        this.y = y;
        this.do_rand = do_rand;
        setSize(500, 200);
        setLocationRelativeTo(null);
        yes.setFont(new Font("Arial", Font.PLAIN, 40));
        nope.setFont(new Font("Arial", Font.PLAIN, 40));
        yes.addActionListener(y_listen);
        nope.addActionListener(n_listen);
        l.setFont(new Font("Arial", Font.PLAIN, 20));
        center.add(yes);
        center.add(nope);
        add(l, BorderLayout.NORTH);
        add(center, BorderLayout.CENTER);
        setResizable(true);
        setUndecorated(true);
        setVisible(true);
    }
}
