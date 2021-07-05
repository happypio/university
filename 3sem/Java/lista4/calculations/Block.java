package calculations;

public class Block extends Instruction {
    public Instruction[] instructions;
    public Block(Instruction... instr) throws IllegalArgumentException{
        instructions = instr;
        for (int i = 0; i < instructions.length; i++)
            if (instructions[i] == null)
                throw new IllegalArgumentException("Null instruction");
    }

    public void execute() {
        for (int i = 0; i < instructions.length; i++)
            instructions[i].execute();
        for (int i = 0; i < instructions.length; i++) {
            if (instructions[i].getClass() == (new VarDecl(" ")).getClass() )
            {
                VarDecl tmp = (VarDecl) instructions[i];
                tmp.remove();
            }
        }

    }   
}
