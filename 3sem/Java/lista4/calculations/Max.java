 package calculations;

public class Max extends Operator2Arg {
    
    public Max(Expression arg1, Expression arg2) {
        super( arg1 , arg2 );
    }

    @Override
    public int calculate() {
        int a = arg1.calculate();
        int b = arg2.calculate();
        if (a < b)
            return b;
        return a;
    }

    @Override
    public String toString() {
        return "max( " + arg1.toString() + " , " + arg2.toString() + " )";
    }  
}