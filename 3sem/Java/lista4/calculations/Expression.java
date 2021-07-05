package calculations;

public abstract class Expression implements Calculable{
    
    // .../** metoda sumująca wyrażenia */
    public static double sum (Expression... expr) {
        double res = 0;
        for(int i = 0; i < expr.length; i++){
            res += expr[i].calculate();
        }
        return res;
    }
    /** metoda mnożąca wyrażenia */
    public static double product (Expression... expr) {
        double res = 1;
        for(int i = 0; i < expr.length; i++){
            res *= expr[i].calculate();
        }
        return res;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null)
			return false;
		if(obj.getClass() != this.getClass())
			return false;
		Expression other = (Expression) obj;
		if(this.calculate() != other.calculate() )
			return false;
		return true;
    }
}
