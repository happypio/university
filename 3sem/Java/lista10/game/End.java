package game;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class End extends Frame {
    private static final long serialVersionUID = 1L;
    private Label l = new Label("It's the end!\n Do you want to play again?");
    private Label l2;
    public Button yes = new Button("YES");
    public Button nope = new Button("NO");
    private Panel center = new Panel(new GridLayout(1, 2));
    private Game game;
    private final int c,n,m;
    private End act;
    private ActionListener y_listen = new ActionListener()
    {
        @Override
        public void actionPerformed(ActionEvent e) {
            for(int i = 0; i < c; i++) {
                game.board.kids[i].interrupt();

            }
            game.board.timer.stop();
            new Game(c,n,m);
            game.dispose();
            act.dispose();
        }
    };
    private ActionListener n_listen = new ActionListener()
    {
        @Override
        public void actionPerformed(ActionEvent e) {
            for(int i = 0; i < c; i++) {
                game.board.kids[i].interrupt();

            }
            game.board.timer.stop();
            game.dispose();
            act.dispose();

        }
    };

    public End(Game g, int c, int n, int m) {
        super("THE END!");
        act = this;
        game = g;
        this.n = n;
        this.m = m;
        this.c =c;
        l2 = new Label();
        int children = game.board.b.children;
        l2.setText(children + " children left!");
        setSize(500, 200);
        setLocationRelativeTo(null);
        yes.setFont(new Font("Arial", Font.PLAIN, 40));
        nope.setFont(new Font("Arial", Font.PLAIN, 40));
        yes.addActionListener(y_listen);
        nope.addActionListener(n_listen);
        l.setFont(new Font("Arial", Font.PLAIN, 20));
        l2.setFont(new Font("Arial", Font.PLAIN, 20));
        center.add(yes);
        center.add(nope);
        add(l, BorderLayout.SOUTH);
        add(l2, BorderLayout.NORTH);
        add(center, BorderLayout.CENTER);
        setResizable(true);
        setUndecorated(true);
        setVisible(true);
    }
}
