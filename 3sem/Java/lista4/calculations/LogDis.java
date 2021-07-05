package calculations;

public class LogDis extends Operator2Arg {
    
    public LogDis(Expression arg1, Expression arg2) {
        super( arg1 , arg2 );
    }

    @Override
    public int calculate() {
        int res = 0;
        int element = arg2.calculate();
        int base = arg1.calculate();
        int tmp = base;
        while (tmp <= element) {
            res ++;
            tmp *= base;
        }
        return res;
    }

    @Override
    public String toString() {
        return "( log_dis (" + arg1.toString() + ") " + arg2.toString() + " )";
    }  
}