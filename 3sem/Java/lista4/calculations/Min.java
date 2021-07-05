package calculations;

public class Min extends Operator2Arg {
    
    public Min(Expression arg1, Expression arg2) {
        super( arg1 , arg2 );
    }

    @Override
    public int calculate() {
        int a = arg1.calculate();
        int b = arg2.calculate();
        if (a > b)
            return b;
        return a;
    }

    @Override
    public String toString() {
        return "min( " + arg1.toString() + " , " + arg2.toString() + " )";
    }  
}