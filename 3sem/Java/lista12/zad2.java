import java.io.*;
import java.util.regex.*;
import java.util.*;
class Triangle {
    public double a,b,c;
    public Triangle (double a, double b, double c) {
        if (a + b <= c || a + c <= b || c + b <= a)
            System.out.println("Wrong input!" + a + " " + b + " " + c);
        this.a = a;
        this.b = b;
        this.c = c;
    }
    public double getCircut() {
        return a + b + c;
    }
    public String toString() {
        return "Triangle: " + a + " " + b + " " + c;
    }
    public boolean equilateral() {
        if (a == b || b == c || a == c) return true;
        return false;
    }
    public boolean rect() {
        if (a*a + b*b == c*c || a*a + c*c == b*b || c*c + b*b == a*a)
            return true;
        return false; 
    }
}
public class zad2 {
    static double convert(String line) {
        double ans = 0;
        boolean com = false, dot = false;
        int id_dot = 1;
        for (int i = 0; i < line.length(); i++) {
            if (line.charAt(i) == '/')
                com = true;
            if (line.charAt(i) == '.')
                dot = true;
            if (Character.isDigit(line.charAt(i)) && !com)
            {
                if (dot)
                    id_dot *= 10;
                ans *= 10;
                ans += Character.getNumericValue(line.charAt(i));
            }
        }
        return ans / Double.valueOf(id_dot);
    }

    public static void main(String[] args) {
        String number = "[\\s]*((\\d+\\.\\d+)|(\\d+))[\\s]+((\\d+\\.\\d+)|(\\d+))[\\s]+((\\d+\\.\\d+)|(\\d+))(\\s*)(//(.*))*";
        String empty_com = "|(\\s*)(//(.*))*"; // starting with | - alternative
        Pattern pattern = Pattern.compile(number + empty_com);
        ArrayList<Double> list = new ArrayList<Double>();
        try(BufferedReader br = new BufferedReader(new FileReader("dane2.txt"))) {
            for (String ln = br.readLine(); ln != null; ln = br.readLine()) {
                System.out.println(ln);
                Matcher m = pattern.matcher(ln);
                System.out.println(m.matches());
                if (!pattern.matcher(ln).matches()) {
                    //throw new Exception("Wrong format!");
                } else {
                    boolean com = false;
                    boolean space = true;
                    int start = 0;
                    int end = 0;
                    for (int i = 0; i < ln.length(); i++) {
                        char c = ln.charAt(i);
                        if (c == '/')
                            com = true;
                        if (Character.isWhitespace(c) && !com) {
                            if (!space) {
                                end = i;
                                double n = convert(ln.substring(start, end));
                                if (n != 0)
                                    list.add(n);
                                //System.out.println(n);
                            }
                            space = true;
                        } else {
                            if (space)
                                start = i;
                            space = false;
                        }
                        if (Character.isDefined(c) && i == ln.length() - 1 && !com) {
                            double n = convert(ln.substring(start, i + 1));
                                if (n != 0)
                                    list.add(n);
                                //System.out.println(n);
                        }
                    }
                }

            }
            int s = 1;
            LinkedList<Triangle> data = new LinkedList<Triangle>();
            for (int i = 0; i < list.size(); i++) {
                if (s % 3 == 0)
                    data.add(new Triangle(list.get(i-2),list.get(i-1),list.get(i)));
               s++; 
            }
        data.stream().sorted(Comparator.comparingDouble(Triangle::getCircut)).forEach(System.out::println);
        System.out.println();
        data.stream().filter(t -> t.rect()).forEach(System.out::println);
        System.out.println();  
        data.stream().filter(t -> t.equilateral()).forEach(System.out::println);
        System.out.println();
        Triangle mini = data.stream().min(Comparator.comparingDouble(Triangle::getCircut)).orElseThrow(NoSuchElementException::new);;
        Triangle maxi = data.stream().max(Comparator.comparingDouble(Triangle::getCircut)).orElseThrow(NoSuchElementException::new);;
        System.out.println(mini + " " + maxi);
        System.out.println();

        } catch (Exception e) {
            System.out.println("Error during reading a file: " + e.getMessage());
        }
}
}