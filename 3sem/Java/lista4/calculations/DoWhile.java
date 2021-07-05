package calculations;

public class DoWhile extends Instruction{
    private final Expression cond;
    private final Instruction body;

    public DoWhile(Instruction b, Expression c ) throws IllegalArgumentException {
        if (b == null)
            throw new IllegalArgumentException("Null instruction");
        if (c == null)
            throw new IllegalArgumentException("Null expression");
        cond = c;
        body = b;
    }

    public void execute() {
        do
            body.execute();
        while (cond.calculate() != 0);
    }
}
