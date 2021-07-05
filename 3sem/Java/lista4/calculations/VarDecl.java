package calculations;

public class VarDecl extends Instruction{
    private final String name;
    private final int value;
    private Integer old_value;
    public VarDecl(String n) throws IllegalArgumentException{
        if (n == null)
            throw new IllegalArgumentException("Null name of variable!");
        name = n;
        value = 0;
        old_value = null;
    }

    public VarDecl(String n, int val) throws IllegalArgumentException{
        if (n == null)
            throw new IllegalArgumentException("Null name of variable!");

        name = n;
        value = val;
        old_value = null;
    }

    public void execute() {
        if(Variable.exists(name)) {
            old_value  = (int) Variable.search(name).get_value();
        }
        Variable.update(name , value);
    }

    public void remove() {
        if (old_value != null) {
            Variable.update(name , old_value);
        }
        else {
        Variable.delete(name);
        }
    }
}
