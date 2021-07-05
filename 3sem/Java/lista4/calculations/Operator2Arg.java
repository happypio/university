package calculations;

public abstract class Operator2Arg extends Operator1Arg{
    protected final Expression arg2;

    public Operator2Arg (Expression arg1, Expression arg2) {
        super(arg1);
        this.arg2 = arg2;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null)
			return false;
		if(obj.getClass() != this.getClass())
			return false;
		Operator2Arg other = (Operator2Arg) obj;
		if(!arg1.equals(other.arg1) || !arg2.equals(other.arg2))
			return false;
		return true;
    }
}
