package graphics;

import java.awt.*;
import javax.swing.*;

public class AboutApp extends JFrame {
    private static final long serialVersionUID = 1L;
    public AboutApp() {
        super("About Application");
        setSize(1000,400);
        JLabel txt = new JLabel();
        String message = "<html>  Copyright (c) November 2020 by Piotr Piesiak<br>" + 
        "  This is an easy application for playing the solitaire.<br>" + 
        "  Version 1.0";
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
