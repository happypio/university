import java.awt.*;
import java.util.*;
import javax.swing.*;
public class Month extends JPanel{
    private static final long serialVersionUID = 1L;
    public static String[] week_day = { "Sunday", "Monday", "Tuesday",
            "Wednesday", "Thursday", "Friday", "Saturday" };
    
    JList <String> lb;
    JList <String> ln;
    JList <String> la;
    MonthList mb;
    MonthList mn;
    MonthList ma;
    public Month(int month,int year) {
        setLayout(new GridLayout(1,3,20,20));
        int m_before = month - 1;
        int m_after = (month + 1) % 12;
        if (year < 0)
            year+=1;
        int y_before = year, y_after = year;
        if (month == 0)
        {
            y_before -= 1;
            m_before = 11;
        }
        if (month == 11)
            y_after += 1;
        //System.out.println(y_before+" "+year+" "+y_after);
        mb = new MonthList(y_before, m_before);
        lb =new JList<>(mb);
        mn = new MonthList(year, month);
        ln = new JList<>(mn);
        ma = new MonthList(y_after, m_after);
        la = new JList<>(ma);
        lb.setFont(new Font("Arial",Font.BOLD,25));
        ln.setFont(new Font("Arial",Font.BOLD,25));
        la.setFont(new Font("Arial",Font.BOLD,25));
        lb.setCellRenderer(new MonthRender());
        ln.setCellRenderer(new MonthRender());
        la.setCellRenderer(new MonthRender());
        
        JScrollPane pa = new JScrollPane(la);
        JScrollPane pb = new JScrollPane(lb);
        JScrollPane pn = new JScrollPane(ln);
        add(pb);
        add(pn);
        add(pa);
    }
    public void update() {
        mb.update();
        mn.update();
        ma.update();
    }

    public class MonthList extends AbstractListModel<String> {
        private static final long serialVersionUID = 1L;
        private int year;
        private int month;

        private GregorianCalendar c = new GregorianCalendar();
        public MonthList(int year, int month) {
            this.year = year;
            if (year <= 0)
                c.set(java.util.Calendar.ERA, GregorianCalendar.BC);
            this.month = month;
        }

        public void update() {
            fireContentsChanged(this,0,getSize() - 1);
        }

        @Override
        public String getElementAt(int i) {
            if (year <= 0) {
                c.set(year,month,i+1);

            }
            else {
                c.set(year,month,i+1);
            }
            int w_d = c.get(java.util.Calendar.DAY_OF_WEEK) - 1;
            if (year == 1582 && month == 9 & i > 3)
            {
                c.set(year,month,i+11);
                w_d = c.get(java.util.Calendar.DAY_OF_WEEK) - 1;
                return Month.week_day[w_d] +" "+ (i+11) +" "+ MonthPanel.m_names[month];
            }
            return Month.week_day[w_d] +" "+ (i+1) +" "+ MonthPanel.m_names[month];  
        }

        @Override
        public int getSize() {
            int daysinmon = MonthPanel.m_days[month];
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
            if (year == 1582 && month == 9)
                daysinmon = 21;
            return daysinmon;
        }
        
    }
    public class MonthRender extends JLabel implements ListCellRenderer<String> {
        private static final long serialVersionUID = 1L;

        @Override
        public Component getListCellRendererComponent(JList<? extends String> arg0, String arg1, int arg2, boolean arg3,
                boolean arg4) {
            String day = arg1;
            setText(day);
            setFont(new Font("Arial",Font.BOLD,18));
            if (day.substring(0,2).equals("Su")){
                setForeground(Color.RED);
            }
            else {
                setForeground(Color.BLACK);
            }
            return this;
        }

    }
    
}
