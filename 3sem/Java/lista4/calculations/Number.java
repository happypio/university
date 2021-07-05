package calculations;

public class Number extends Expression{
    private final int number;

    public Number(int n) {
        number = n;
    }

    @Override
    public int calculate() {
        return number;
    }
    
    @Override
    public String toString() {
        return Integer.toString(number);
    }
}
