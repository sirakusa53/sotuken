package vmdlc;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

public class ErrorPrinter{
    private static List<String> codes = null;

    private static final Collection<String> recursivesList = Arrays.asList(new String[] {
        "TypeArray", "TypeProduct", "OrPattern", "AndPattern", "LeftHandIndex", "LeftHandField", "Trinary", "Or", "And",
        "BitwiseOr", "BitwiseXor", "BitwiseAnd", "NotEquals", "LessThanEquals", "GreaterThanEquals",
        "LessThan", "GreaterThan", "LeftShift", "RightShift", "Add", "Sub", "Mul", "Div", "Mod",
        "Plus", "Minus", "Compl", "Not", "FunctionCall", "ArrayIndex", "FieldAccess"
    });

    private static String getText(String title, String message, int line, long column, int length){
        StringBuilder builder = new StringBuilder();
        builder.append("[").append(title).append("] ");
        builder.append(message);
        builder.append(" (at line "+line+":"+column+")\n\n");
        if(codes != null){
            String code = codes.get(line-1);
            int lineLength = code.length();
            builder.append(code);
            if(length+column-1 >= lineLength) builder.append(" ...");
            builder.append('\n');
            for(int i=0; i<column; i++) builder.append(' ');
            for(int i=0; i<length && i+column<lineLength; i++) builder.append('^');
        }
        builder.append('\n');
        return builder.toString();
    }


    public static void error(String message){
        StringBuilder builder = new StringBuilder();
        builder.append("[error] ");
        builder.append(message);
        System.err.println(builder.toString());
        System.exit(-1);
    }

    public static void error(String message, SyntaxTree node){
        int textLength = 0;
        SyntaxTree n = node;
        for(; recursivesList.contains(n.getTag().toString()); n = n.get(0)){
            textLength += n.toText().length();
        }
        textLength += n.toText().length();
        int line = n.getLineNum();
        long column = n.getSourcePosition();
        for(int i=0; i<line-1; i++){
            column -= codes.get(i).length() + 1;
        }
        System.err.print(getText("error", message, line, column, textLength));
        System.exit(-1);
    }

    public static void warning(String message, SyntaxTree node){
        int textLength = 0;
        SyntaxTree n = node;
        for(; recursivesList.contains(n.getTag().toString()); n = n.get(0)){
            textLength += n.toText().length();
        }
        textLength += n.toText().length();
        int line = n.getLineNum();
        long column = n.getSourcePosition();
        for(int i=0; i<line-1; i++){
            column -= codes.get(i).length() + 1;
        }
        System.err.print(getText("warning", message, line, column, textLength));
    }

    public static void setSource(String path){
        try{
            codes = Files.readAllLines(Paths.get(path));
        }catch(IOException e){
            codes = null;
        }
    }
}