package calculations;

public class Greater extends Operator2Arg {
    
    public Greater(Expression arg1, Expression arg2) {
        super( arg1 , arg2 );
    }

    @Override
    public int calculate() {
        int a = arg1.calculate();
        int b = arg2.calculate();
        if (a > b)
            return 1;
        return 0;
    }

    @Override
    public String toString() {
        return "( " + arg1.toString() + " > " + arg2.toString() + " )";
    }  
}