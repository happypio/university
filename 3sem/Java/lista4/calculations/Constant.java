package calculations;

public class Constant extends Expression{
    private final int value;
    private final String name;

    public Constant(int val, String name) {
        value = val;
        this.name = name;
    }

    @Override
    public int calculate() {
        return value;
    }
    
    @Override
    public String toString() {
        return name;
    }
}
