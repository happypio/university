package calculations;
import java.util.Scanner;

public class Read extends Instruction{
    private String var;
    public Read(String v) throws IllegalArgumentException {
        if (v == null)
            throw new IllegalArgumentException("Name of variable is null!");
        var = v;
    } 
    public void execute() {
        Scanner s = new Scanner(System.in);
        int input = s.nextInt();
        (new Assign(var, new Number(input))).execute();
        s.close();
    }
}
