package validator;
import calculations.*;
import calculations.Number;

public class TestInstructions {
    public TestInstructions() {
        System.out.println("==========TEST===========");
        System.out.println("Algorithm checks if the number in input is prime number.");
        System.out.println("RESULTS: 1 - prime number, 0 - composite number.");
        System.out.println("Enter the number: ");
        is_prime.execute();
    }

    Instruction is_prime = new Block(
        new VarDecl("n"),
        new Read("n"),

        new IfExpr(
            new Less(
                new Variable("n"),
                new Number(2)
            ),
            new Write(new Number(0))
        ),
        new IfElse(
            new Less(
                new Variable("n"),
                new Number(2)
            ),
            new Block(
                new VarDecl("p"),
                new Assign("p", new Number(2)),
                new VarDecl("res"),
                new While(
                    new Leq(
                        new Multiply(
                            new Variable("p"),
                            new Variable("p")
                        ),
                        new Variable("n")
                    ),
                    new Block(
                        new IfExpr(
                            new Equal(
                                new Mod(
                                    new Variable("n"),
                                    new Variable("p")
                                ),
                                new Number(0)
                            ),
                            new Block(
                                new Assign("res", new Variable("p")),
                                new Assign("p", new Variable("n"))
                            )
                        ),
                        new Assign(
                            "p",
                             new Add (
                                 new Variable("p"),
                                 new Number(1)
                             )
                        )
                    )
                ),
                new IfExpr(
                    new Greater(
                        new Variable("res"),
                        new Number(0)
                    ),
                    new Write(new Number(0))
                ),
                new IfElse(
                    new Greater(
                        new Variable("res"),
                        new Number(0)
                    ),
                    new Write(new Number(1))
                )
            )
         )
        );

}