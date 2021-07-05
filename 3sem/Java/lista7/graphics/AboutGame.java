package graphics;

import java.awt.*;
import javax.swing.*;

public class AboutGame extends JFrame {
    private static final long serialVersionUID = 1L;
    public AboutGame() {
        super("About Game");
        setSize(1000,800);
        JLabel txt = new JLabel();
        String message = "<html>Peg solitaire (or Solo Noble) is a board game <br> for one player involving movement of pegs on a board with holes.<br>" +
        "The standard game fills the entire board <br> with pegs except for the central hole." + 
        "The objective is, making valid moves, <br> to empty the entire board except for <br> a solitary peg in the central hole.<br>" +
        "~WIKIPEDIA";
        txt.setText(message);
        txt.setFont(new Font("sansserif", 20, 40));
        txt.setHorizontalAlignment(JLabel.CENTER);
        txt.setVerticalAlignment(JLabel.CENTER);
        add(txt);
        setLocationRelativeTo(null);
        setResizable(false);
        setVisible(true);
    }
    
}
