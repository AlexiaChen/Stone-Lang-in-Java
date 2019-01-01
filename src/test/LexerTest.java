package test;

import stone.*;

import java.io.FileNotFoundException;
import java.io.FileReader;

public class LexerTest {
    public static void main(String[] args) throws ParseException {

        Lexer lexer = null;

        try{
            lexer = new Lexer(new FileReader("src/test/stone-test.st"));
        }catch (FileNotFoundException e){
            System.out.println(e.toString());
        }

        for (Token token; (token = lexer.read()) != Token.EOF; ){
            System.out.println("( " + token.getLineNumber() + ", " + token.getText() + " )");

        }
    }
}
