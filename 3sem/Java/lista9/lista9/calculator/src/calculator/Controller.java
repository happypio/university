package calculator;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextField;

import java.io.IOException;
import java.math.BigInteger;

public class Controller {

    @FXML
    private TextField argument;
    @FXML
    private Label op_lab;
    @FXML
    private Label last_res;
    @FXML
    private TextField result;
    private  String arg1 = "",arg2= "";
    private String op = "";
    public int type = 10;

    @FXML
    void Number(ActionEvent event) {
        String no = ((Button)event.getSource()).getText();
        argument.setText(argument.getText() + no);
    }

    @FXML
    void Operation(ActionEvent event) {
        String operation = ((Button)event.getSource()).getText();
        if (operation.equals("=")) {
            if (op.equals("")) {
                arg1 = argument.getText();
                last_res.setText(arg1);
                argument.setText("");
                result.setText(arg1);
                return;
            }
            else {
                arg2 = argument.getText();
                if (arg1.equals("") || arg2.equals("") ) {
                    return;
                }
                BigInteger x = new BigInteger(arg1,type);
                BigInteger y = new BigInteger(arg2,type);
                try {
                    BigInteger res = calculate(x, y);
                    arg1 = res.toString(type);
                    last_res.setText(arg1);
                    result.setText(arg1);
                }
                catch (Exception e) {
                    arg1 = "";
                    last_res.setText(arg1);
                    result.setText("error");
                    System.out.println(e.getMessage());
                }
                argument.setText("");
                op = "";
                op_lab.setText(op);
            }
            return;
        }
        if(operation.equals("!")) {
            op = "";
            op_lab.setText(op);
            arg1 = argument.getText();
            if (arg1.equals(""))
                return;
            BigInteger res = factorial(new BigInteger(arg1,type));
            arg1 = res.toString(type);
            last_res.setText(arg1);
            argument.setText("");
            result.setText(arg1);
            return;
        }
        if(operation.equals("+/-")) {
            op = "";
            op_lab.setText(op);
            arg1 = argument.getText();
            if (arg1.equals(""))
                return;
            BigInteger res = new BigInteger(arg1, type);
            res = res.multiply(new BigInteger("-1",type));
            arg1 = res.toString(type);
            last_res.setText(arg1);
            argument.setText("");
            result.setText(arg1);
            return;
        }
        op = operation;
        op_lab.setText(op);
        String tmp = argument.getText();
        if (tmp.equals(""))
            return;
        arg1 = tmp;
        last_res.setText(arg1);
        argument.setText("");

    }

    BigInteger calculate(BigInteger x, BigInteger y) throws Exception {
        BigInteger res;
        switch (op) {
            case "+": res = x.add(y);break;
            case "-": res = x.subtract(y);break;
            case "/":
                if(y.equals(new BigInteger("0")))
                    throw new Exception("Dividing by zero "+ x.toString() + " " + y.toString());
                res = x.divide(y);break;
            case "*" : res = x.multiply(y);break;
            case "^": res = x.pow(y.intValue());break;
            case "%": res = x.mod(y);break;
            default:
                if(x.compareTo(y) < 0 || y.compareTo(new BigInteger("0", type)) < 0)
                    throw new Exception("Wrong args in newton " + x.toString() + " " + y.toString());
                res = newton(x,y);break;

        }
        return res;
    }
    BigInteger factorial(BigInteger x) {
        //operations in decimal, but returning in "type"
        String dec = x.toString();
        if (dec.equals("0")) {
            return new BigInteger("1", type);
        }
        BigInteger d = new BigInteger(dec);
        BigInteger res = d;
        while (d.compareTo(new BigInteger("1")) > 0) {
            d = d.subtract(new BigInteger("1"));
            res = res.multiply(d);
        }
        String r = res.toString(type);
        return new BigInteger(r, type);
    }
    BigInteger newton(BigInteger x, BigInteger y) {
        BigInteger n = factorial(x);
        BigInteger denom = factorial(y).multiply(factorial(x.subtract(y)));
        return n.divide(denom);
    }

    @FXML
    void Reset() {
        arg1 = "";arg2= "";op = "";
        argument.setText("");
        last_res.setText(arg1);
        op_lab.setText(op);
        result.setText("");
    }

    @FXML
    void Undo() {
        String tmp = argument.getText();
        if (!tmp.equals("")) {
            tmp = tmp.substring(0, tmp.length() - 1);
        }
        argument.setText(tmp);
    }
    @FXML
    public void initialize() {
        System.out.println("STARTED");
        result.setEditable(false);
    }
    @FXML
    public void Type(ActionEvent event) throws IOException {
        String t = ((MenuItem)event.getSource()).getText();
        FXMLLoader loader;
        switch (t) {
            case "Binary":
                this.type = 2;
                loader = new FXMLLoader(getClass().getResource("Binary.fxml")); break;
            case "Decimal":
                this.type = 10;
                loader = new FXMLLoader(getClass().getResource("Decimal.fxml")); break;
            default:
                this.type = 16;
                loader = new FXMLLoader(getClass().getResource("Hexadecimal.fxml")); break;
        }
        Reset();
        Parent root = (Parent)loader.load();
        Controller controller = loader.<Controller>getController();
        controller.type = this.type;
        Scene scene = argument.getScene();
        scene.setRoot(root);

    }

}
