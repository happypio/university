package calculations;

public abstract class Operator1Arg extends Expression{
    
    protected final Expression arg1;

    public Operator1Arg(Expression arg1) {
        this.arg1 = arg1;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null)
			return false;
		if(obj.getClass() != this.getClass())
			return false;
		Operator1Arg other = (Operator1Arg) obj;
		if(!arg1.equals(other.arg1))
			return false;
		return true;
    }
}
