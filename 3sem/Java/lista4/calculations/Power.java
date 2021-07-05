package calculations;
import java.lang.Math; 

public class Power extends Operator2Arg {
    
    public Power(Expression arg1, Expression arg2) {
        super( arg1 , arg2 );
    }

    @Override
    public int calculate() {
        return (int) Math.pow( arg1.calculate() , arg2.calculate() );
    }

    @Override
    public String toString() {
        return "( " + arg1.toString() + " ^ " + arg2.toString() + " )";
    }  
}