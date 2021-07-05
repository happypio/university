package calculations;

public class Mod extends Operator2Arg {
    
    public Mod(Expression arg1, Expression arg2) {
        super( arg1 , arg2 );
    }

    @Override
    public int calculate() {
        return arg1.calculate() % arg2.calculate();
    }

    @Override
    public String toString() {
        return "( " + arg1.toString() + " % " + arg2.toString() + " )";
    }  
}