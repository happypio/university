package calculations;

public class Assign extends Instruction{
    private final Expression expr;
    private final String var;

    public Assign(String var, Expression e) throws IllegalArgumentException {
        if (var == null)
            throw new IllegalArgumentException("Null name of variable");
        if (e == null)
            throw new IllegalArgumentException("Null expression");
        this.var = var;
        expr = e;
    }

    public void execute() {
        Variable.update(var, expr.calculate());
    }
}
