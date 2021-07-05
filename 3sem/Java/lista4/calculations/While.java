package calculations;

public class While extends Instruction{
    private final Expression cond;
    private final Instruction body;

    public While(Expression c, Instruction b) throws IllegalArgumentException {
        if (b == null)
            throw new IllegalArgumentException("Null instruction");
        if (c == null)
            throw new IllegalArgumentException("Null expression");
        cond = c;
        body = b;
    }

    public void execute() {
        while (cond.calculate() != 0)
            body.execute();
    }
}
