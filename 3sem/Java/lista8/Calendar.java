
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;



public class Calendar extends JFrame {

    private static final long serialVersionUID = 1L;
    public JTabbedPane tp;
    public Year p1;
    public Month p2;
    public int year;
    public int month;
    public JSpinner s;
    public boolean bc = false;
    public int before = 0;
    public class ButtonListener implements ActionListener {
        int i;
        public ButtonListener(int i) {
            this.i = i;
        }
        @Override
        public void actionPerformed(ActionEvent arg0) {
            if (i < 0) {
                year--;
                if (year == 0){
                    year = -1;
                    bc = true;
                }
                update();
            }
            else {
                year++;
                if (year == 0) {
                    year = 1;
                    bc = false;
                }
                update();
            }
            before = year;
            s.setValue(year);
        }

    }
    public Calendar() {
         
        super("Calendar");
        //setSize(1300,1050);
        java.util.Calendar c = java.util.Calendar.getInstance(); 
        year = c.get(java.util.Calendar.YEAR);
        month = c.get(java.util.Calendar.MONTH);
        p1 = new Year(year, this);
        p2 = new Month(month, year);

        JToolBar tool = new JToolBar();
        JPanel p = new JPanel();
        JButton b1 = new JButton("Before");
        b1.setFont(new Font("Arial", Font.PLAIN, 20));
        b1.addActionListener(new ButtonListener(-1));
        JButton b2 = new JButton("Next");
        b2.setFont(new Font("Arial", Font.PLAIN, 20));
        b2.addActionListener(new ButtonListener(1));
        p.add(b1);
        p.add(b2);
        /*SpinnerModel spinnerModel = new SpinnerNumberModel(year, //initial value
         0, //min
         100, //max
         1);//step*/
        s = new JSpinner();
        Component se = s.getEditor();
        JFormattedTextField jftf = ((JSpinner.DefaultEditor) se).getTextField();
        jftf.setColumns(7);
        s.setValue(year);
        s.addChangeListener(new ChangeListener() {
            public void stateChanged(ChangeEvent e) {
                year = (int)((JSpinner)e.getSource()).getValue();
                if (year == 0) {
                    if(before > 0){
                        year = -1;
                        bc = true;
                    }
                    else{
                        year = 1;
                        bc = false;
                    }
                before = year;
                }
                update();
            }
        });
        p.add(s);
        
        
        tool.add(p);
        tp = new JTabbedPane();  
        //tp.setBounds(50,50,getSize().width - 100, getSize().height - 200);  
        tp.setFont( new Font( "Dialog", Font.BOLD|Font.ITALIC, 24 ) );
        tp.add("YEAR: " + year,p1);  
        tp.add("MONTH: " + MonthPanel.m_names[month],p2);

        Container cp = getContentPane(); 
        cp.add(tp, "Center");
        tool.setBorder(BorderFactory.createTitledBorder("Tools"));
        //add(tp,BorderLayout.CENTER);
        //add(tool, BorderLayout.SOUTH);
        cp.add(tool, "South");
        pack();
        //setSize(1300,1050);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setLayout(null);  
        setLocationRelativeTo(null);
        setVisible(true);
    }
    public void update() {
        tp.remove(p1);
        tp.remove(p2);
        int tmp = year;
        if (tmp < 0)
            tmp *= -1;
        p2 = new Month(month,year);
        p1 = new Year(year, this);
        if (bc)
            tp.add("YEAR: " + tmp + " B.C.",p1);
        else
            tp.add("YEAR: " + tmp,p1);  
        tp.add("MONTH: " + MonthPanel.m_names[month],p2);
        s.setValue(year);
    }
    public static void main(String args[]) {
        //System.out.println("START");
        new Calendar();
    }
}