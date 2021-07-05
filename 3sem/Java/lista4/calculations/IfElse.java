package calculations;

public class IfElse extends Instruction{
    private final Expression if_expr;
    private final Instruction if_body;

    public IfElse(Expression if_e, Instruction if_b) throws IllegalArgumentException {
        if (if_b == null)
            throw new IllegalArgumentException("Null instruction");
        if (if_e == null)
            throw new IllegalArgumentException("Null expression");
        if_expr = if_e;
        if_body = if_b;
    }

    public void execute() {
        if (if_expr.calculate() == 0)
            if_body.execute();
    }
}
