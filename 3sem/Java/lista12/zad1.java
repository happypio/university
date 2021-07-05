import java.io.*;
import java.util.regex.*;
import java.util.*;
public class zad1 {
    static int convert(String line) {
        int ans = 0;
        boolean com = false;
        for (int i = 0; i < line.length(); i++) {
            if (line.charAt(i) == '/')
                com = true;
            if (Character.isDigit(line.charAt(i)) && !com)
            {
                ans *= 10;
                ans += Character.getNumericValue(line.charAt(i));
            }
        }
        return ans;
    }
    static boolean prime(int n) {
        if (n == 1)
            return false;
        if (n == 2)
            return true;
        if (n % 2 == 0)
            return false;
        for (int i = 3; i*i <= n; i+=2) {
            if (n % i == 0) 
                return false;
        }
        return true;
    }
    public static void main(String[] args) {
        String number_first = "(\\s*[1-9])(\\s*[0-9]){0,8}(\\s*)(//(.*))*";
        String empty_com = "|(\\s*)(//(.*))*"; // starting with | - alternative
        Pattern pattern = Pattern.compile(number_first + empty_com);
        ArrayList<Integer> list = new ArrayList<Integer>();
        try(BufferedReader br = new BufferedReader(new FileReader("dane1.txt"))) {
            for (String ln = br.readLine(); ln != null; ln = br.readLine()) {
                System.out.println(ln);
                System.out.println(pattern.matcher(ln).matches());
                if (!pattern.matcher(ln).matches()) {
                    //throw new Exception("Wrong format!");
                } else {
                    int n = convert(ln);
                    if (n != 0)
                        list.add(n);
                    //System.out.println(n);
                }

            }
            System.out.println();
            list.stream().sorted(Comparator.reverseOrder()).forEach(System.out::println);
            System.out.println();
            list.stream().filter(s-> prime(s)).forEach(System.out::println);
            System.out.println();
            long p = list.stream().filter(n-> n < 1000).mapToInt(Integer::intValue).sum();
            System.out.println(p);
            System.out.println();
            p = list.stream().filter(s -> s % 13 == 0).count();
            System.out.println(p);
            System.out.println();
        } catch (Exception e) {
            System.out.println("Error during reading a file: " + e.getMessage());
        }
}
}