package calculations;

public class Multiply extends Operator2Arg {
    
    public Multiply(Expression arg1, Expression arg2) {
        super( arg1 , arg2 );
    }

    @Override
    public int calculate() {
        return arg1.calculate() * arg2.calculate();
    }

    @Override
    public String toString() {
        return "( " + arg1.toString() + " * " + arg2.toString() + " )";
    }  
}