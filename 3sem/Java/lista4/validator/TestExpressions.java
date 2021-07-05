package validator;
import calculations.*;
import calculations.Number;

public class TestExpressions {
    
    public TestExpressions() {
        Variable.update("x", 2); 
        Variable.update("y", 8);
        System.out.println("Variables set: x = " + (new Variable("x").calculate())
        + " , y = " + (new Variable("y").calculate()));
        System.out.println("==============TESTING==============");
        System.out.println("Expression 1:");
        System.out.println(w1.toString());
        System.out.println("Value of expr. is: " + w1.calculate());
        System.out.println("OK!");
        System.out.println("============================");
        System.out.println("Expression 2:");
        System.out.println(w2.toString());
        System.out.println("Value of expr. is: " + w2.calculate());
        System.out.println("OK!");
        System.out.println("============================");
        System.out.println("Expression 3:");
        System.out.println(w3.toString());
        System.out.println("Value of expr. is: " + w3.calculate());
        System.out.println("OK!");
        System.out.println("============================");
        System.out.println("Expression 4:");
        System.out.println(w4.toString());
        System.out.println("Value of expr. is: " + w4.calculate());
        System.out.println("OK!");
        System.out.println("============================");
        System.out.println("Expression 5:");
        System.out.println(w5.toString());
        System.out.println("Value of expr. is: " + w5.calculate());
        System.out.println("OK!");
        System.out.println("============================");
        System.out.println("Expression 6:");
        System.out.println(w6.toString());
        System.out.println("Value of expr. is: " + w6.calculate());
        System.out.println("OK!");
        System.out.println("Variables set: x = " + (new Variable("x").calculate()));

    }
    public Expression w1 = new Add (
        new Number(3),
        new Number(5)
    );

    public Expression w2 = new Multiply(
        new AddInv(
            new Subtract(
                new Number (2),
                new Variable("x")
            )
        ),
        new Number(7)
    );

    public Expression w3 = new Divide(
        new Subtract (
            new Multiply(
                new Number(3),
                new Number(11)
            ),
            new Number(1)
        ),
        new Add(
            new Number(7),
            new Number(5)
        )
    );

    public Expression w4 = new Min(
        new Multiply(
            new Add(
                new Variable("x"),
                new Number(13)
            ),
            new Variable("x")
        ),
        new Mod(
            new Subtract(
                new Number(1),
                new Variable("x")
            ),
            new Number(2)
        )
    );

    public Expression w5 = new Less(
        new Add(
            new Power(
                new Number(2),
                new Number(5)
            ),
            new LogDis(
                new Number(2),
                new Variable("y")
            )
        ),
        new Number(20)
    );

    public Expression w6 = new Add(
        new Number(7),
        new Multiply(
            new Variable("x") , 
            new Number(5)
        )
    ); 
    
}
