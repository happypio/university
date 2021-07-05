package calculations;

public class AddInv extends Operator1Arg{
    
    public AddInv(Expression arg1) {
        super(arg1);
    }

    @Override
    public int calculate() {
        return -arg1.calculate();
    }

    @Override
    public String toString() {
        return "-" + arg1.toString();
    }
    
}
