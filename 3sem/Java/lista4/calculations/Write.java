package calculations;

public class Write extends Instruction {
    private Expression message;
    public Write(Expression e) {
        message = e;
    }
    public void execute() {
        System.out.println(message.calculate());
    }
}
