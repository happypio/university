package calculations;

public class Factorial extends Operator1Arg{
    
    public Factorial(Expression arg1) {
        super(arg1);
    }



    @Override
    public int calculate() {
        int res = 1;
        int n = arg1.calculate();
        for(int i = 2; i <= n; i++) {
            res *= i;
        }
        return res;
    }

    @Override
    public String toString() {
        return "!" + arg1.toString();
    }
    
}
