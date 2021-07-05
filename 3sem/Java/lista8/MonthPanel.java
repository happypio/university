import java.util.Calendar;
import java.util.*;
import java.awt.*;
import javax.swing.*;


public class MonthPanel extends JPanel{
    private static final long serialVersionUID = 1L;
    public JLabel txt;
    public static int[] m_days = 
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    public static String[] m_names = {"Januray", "February", "March", "April", "May",
    "June", "July", "August", "September", "October", "November", "December"};


    public MonthPanel(int year, int month) {
        JPanel grid = new JPanel();
        grid.setLayout(new GridLayout(0,7,10,10));
        if (year == 1582 && month == 9) {
            for (int i = 1; i <= 4; i ++) {
                
                JLabel l = new JLabel(String.valueOf(i));
                l.setFont(new Font("sansserif", 10, 12));
                l.setHorizontalAlignment(SwingConstants.CENTER); 
                grid.add(l);
            }
            for (int i = 15; i <= 37; i ++) {
                JLabel l;
				if (i > 31)
                     l = new JLabel("");
                else
                {
                    l = new JLabel(String.valueOf(i));
                    l.setFont(new Font("sansserif", 10, 12));
                    if (i == 17 || i == 24 || i == 31) 
                        l.setForeground(Color.RED);
                    l.setHorizontalAlignment(SwingConstants.CENTER);
                }
                grid.add(l);
            }
        }
        else {
            GregorianCalendar c = new GregorianCalendar(year, month, 1);
            if (year < 0) {
                //year = -year;
                year += 1;
                c.set(Calendar.ERA, GregorianCalendar.BC);
                c = new GregorianCalendar(year,month,1);

            }
            int daysinmon = m_days[month];
            if (year > 1582 || (year >= 1582 && month >= 10)) {
                if (year % 4 == 0 && month == 1 && (!(year % 100 == 0)
                || year % 400 == 0 )) {
                    daysinmon = 29;
                }
            }
            else {
                if (year > 0 && year % 4 == 0 && month == 1)
                    daysinmon = 29;
            	if (year <= 0 && (year - 1) % 4 == 0 && month == 1)
            		daysinmon = 29;
            }
            boolean was = false;
            int day = 0;
            for (int i = 1; i <= daysinmon; i++) {
                JLabel l;
                if (day == (((c.get(Calendar.DAY_OF_WEEK)) + 5) % 7))
                    was = true;
                if(was) {
                    l = new JLabel(String.valueOf(i));
                    l.setFont(new Font("sansserif", 10, 12));
                    l.setHorizontalAlignment(SwingConstants.CENTER);
                    if (day == 6) {
                        l.setForeground(Color.RED);
                        day = -1;
                    }
                }
                else {
                    l = new JLabel("");
                    i--;
                }
                day++;
                grid.add(l);
            }

        }
        txt = new JLabel();
        txt.setText(m_names[month]);
        txt.setFont(new Font ("sansserif", 20, 15));
        txt.setHorizontalAlignment(SwingConstants.CENTER);
        setLayout(new GridLayout(1,0,20,20));
        add(txt,BorderLayout.NORTH);
        add(grid, BorderLayout.CENTER);
    }
}
