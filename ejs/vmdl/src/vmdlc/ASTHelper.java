package vmdlc;

import nez.ast.Symbol;
import type.AstType;

public class ASTHelper {

    //*********************************
    // Types
    //*********************************

    public static SyntaxTree generateTopTypeName(){
        return new SyntaxTree(Symbol.unique("TopTypeName"), null, null, "Top");
    }
    public static SyntaxTree generateVoidTypeName(){
        return new SyntaxTree(Symbol.unique("VoidTypeName"), null, null, "void");
    }
    public static SyntaxTree generateCType(String name){
        return new SyntaxTree(Symbol.unique("Ctype"), null, null, name);
    }
    public static SyntaxTree generateJSValueType(String name){
        return new SyntaxTree(Symbol.unique("JSValueTypeName"), null, null, name);
    }
    public static SyntaxTree generateUserTypeName(String name){
        // type に紐づける
        return new SyntaxTree(Symbol.unique("UserTypeName"), new Symbol[]{Symbol.unique("type")}, new SyntaxTree[]{new SyntaxTree(null, null, null, name)}, null);
    }
    public static SyntaxTree generateType(String name){
        AstType t = AstType.getPrimitiveType(name);
        if(t == null)
            t = AstType.getMappingType(name);
        if(t == null){
            System.err.println("InternalWarning: Unexpected type name : "+name);
            return null;
        }
        if(name.equals("void")){
            return generateVoidTypeName();
        }
        if(name.equals("Top")){
            return generateTopTypeName();
        }
        if(t instanceof AstType.JSValueType){
            return generateJSValueType(name);
        }
        if(t instanceof AstType.AstPrimitiveType){
            return generateCType(name);
        }
        /* really? */
        return generateUserTypeName(name);
    }
    public static SyntaxTree generateType(AstType t){
        return generateType(t.toString());
    }
    public static SyntaxTree generateArrayType(String name){
        return new SyntaxTree(Symbol.unique("TypeArray"), new Symbol[]{Symbol.unique("type")}, new SyntaxTree[]{generateType(name)}, null);
    }

    //*********************************
    // TypePatterns
    //*********************************

    // TypePattern

    public static SyntaxTree generateTypePattern(String type, String var){
        return new SyntaxTree(Symbol.unique("TypePattern"),
            new Symbol[]{Symbol.unique("type"), Symbol.unique("var")}, 
            new SyntaxTree[]{generateType(type), generateName(var)}, null);
    }

    // AndPattern

    public static SyntaxTree generateAndPattern(SyntaxTree pattern1, SyntaxTree pattern2){
        return new SyntaxTree(Symbol.unique("AndPattern"), null, new SyntaxTree[]{pattern1, pattern2}, null);
    }

    // OrPattern

    public static SyntaxTree generateOrPattern(SyntaxTree pattern1, SyntaxTree pattern2){
        return new SyntaxTree(Symbol.unique("OrPattern"), null, new SyntaxTree[]{pattern1, pattern2}, null);
    }

    //*********************************
    // Statements
    //*********************************

    // Declaration

    public static SyntaxTree generateDeclaration(SyntaxTree type, SyntaxTree var, SyntaxTree expr){
        return new SyntaxTree(Symbol.unique("Declaration"),
            new Symbol[]{Symbol.unique("type"), Symbol.unique("var"), Symbol.unique("expr")},
            new SyntaxTree[]{type, var, expr}, null);
    }
    public static SyntaxTree generateDeclaration(SyntaxTree type, String var, SyntaxTree expr){
        return generateDeclaration(type, generateName(var), expr);
    }
    public static SyntaxTree generateDeclaration(String type, String var, SyntaxTree expr){
        return generateDeclaration(generateType(type), generateName(var), expr);
    }
    public static SyntaxTree generateDeclaration(AstType type, String var, SyntaxTree expr){
        return generateDeclaration(generateType(type), generateName(var), expr);
    }
    public static SyntaxTree generateDeclaration(SyntaxTree type, SyntaxTree var){
        return new SyntaxTree(Symbol.unique("Declaration"),
            new Symbol[]{Symbol.unique("type"), Symbol.unique("var")},
            new SyntaxTree[]{type, var}, null);
    }

    //Assignment

    public static SyntaxTree generateAssignment(SyntaxTree left, SyntaxTree right){
        return new SyntaxTree(Symbol.unique("Assignment"),
            new Symbol[]{Symbol.unique("left"), Symbol.unique("right")},
            new SyntaxTree[]{left, right}, null);
    }


    // ExpressionStatement

    public static SyntaxTree generateExpressionStatement(SyntaxTree expr){
        return new SyntaxTree(Symbol.unique("ExpressionStatement"), null, new SyntaxTree[]{expr}, null);
    }

    // Block

    public static SyntaxTree generateBlock(SyntaxTree[] args){
        return new SyntaxTree(Symbol.unique("Block"), null, args, null);
    }

    //*********************************
    // Expressions
    //*********************************

    public static SyntaxTree generateFunctionCall(String name, SyntaxTree args){
        return new SyntaxTree(Symbol.unique("FunctionCall"),
            new Symbol[]{Symbol.unique("recv"), Symbol.unique("args")},
            new SyntaxTree[]{generateName(name), args}, null);
    }
    public static SyntaxTree generateFunctionCall(String name, SyntaxTree[] args){
        return new SyntaxTree(Symbol.unique("FunctionCall"),
            new Symbol[]{Symbol.unique("recv"), Symbol.unique("args")},
            new SyntaxTree[]{generateName(name), generateArgList(args)}, null);
    }
    public static SyntaxTree generateFunctionCall(String name, String[] args){
        SyntaxTree[] argNodes = new SyntaxTree[args.length];
        for(int i=0; i<args.length; i++){
            argNodes[i] = generateName(args[i]);
        }
        return new SyntaxTree(Symbol.unique("FunctionCall"),
            new Symbol[]{Symbol.unique("recv"), Symbol.unique("args")},
            new SyntaxTree[]{generateName(name), generateArgList(argNodes)}, null);
    }
    public static SyntaxTree generateBinaryExpression(String operator, SyntaxTree[] args){
        return new SyntaxTree(Symbol.unique(operator),
            new Symbol[]{Symbol.unique("left"), Symbol.unique("right")},
            args, null);
    }

    //*********************************
    // Others
    //*********************************

    // Name
    public static SyntaxTree generateName(String name){
        return new SyntaxTree(Symbol.unique("Name"), null, null, name);
    }

    // ArgList
    public static SyntaxTree generateArgList(SyntaxTree[] args){
        return new SyntaxTree(Symbol.unique("ArgList"), null, args, null);
    }

    // Case
    public static SyntaxTree generateCase(SyntaxTree condition, SyntaxTree body){
        return new SyntaxTree(Symbol.unique("Case"),
            new Symbol[]{Symbol.unique("pattern"), Symbol.unique("body")}, 
            new SyntaxTree[]{condition, body}, null);
    }

    // Cases
    public static SyntaxTree generateCases(SyntaxTree[] cases){
        return new SyntaxTree(Symbol.unique("Cases"), null, cases, null);
    }

    // ArrayIndex
    public static SyntaxTree generateArrayIndex(String varName, SyntaxTree index){
        return new SyntaxTree(Symbol.unique("ArrayIndex"),
            new Symbol[]{Symbol.unique("recv"), Symbol.unique("index")},
            new SyntaxTree[]{generateName(varName), index}, null);
    }
    public static SyntaxTree generateArrayIndex(String varName, int index){
        return generateArrayIndex(varName, generateInteger(index));
    }

    // Constants
    public static SyntaxTree generateInteger(int interger){
        return new SyntaxTree(Symbol.unique("Integer"), null, null, Integer.toString(interger));
    }

    //*********************************
    // Transforms
    //*********************************

    public static SyntaxTree removeInitializer(SyntaxTree node){
        if(!node.is(Symbol.unique("Declaration"))){
            System.err.println("InternalWarning: ASTHelper.removeInitializer expects Declarations");
            return node;
        }
        SyntaxTree type = node.get(Symbol.unique("type"));
        SyntaxTree var = node.get(Symbol.unique("var"));
        return ASTHelper.generateDeclaration(type, var);
    }
    public static SyntaxTree clipAssignment(SyntaxTree node){
        if(!node.is(Symbol.unique("Declaration"))){
            System.err.println("InternalWarning: ASTHelper.clipAssignment expects Declarations");
            return node;
        }
        SyntaxTree var = node.get(Symbol.unique("var"));
        SyntaxTree expr = node.get(Symbol.unique("expr"));
        return ASTHelper.generateAssignment(var, expr);
    }

    //*********************************
    // Specials
    //*********************************

    static SyntaxTree EMPTY_ARGLIST = generateArgList(null);
    static SyntaxTree BUILTIN_PROLOGUE = generateFunctionCall("builtin_prologue", EMPTY_ARGLIST);
    static SyntaxTree FUNCTION_EPILOGUE = generateFunctionCall("__builtin_unreachable", EMPTY_ARGLIST);

    static {
        EMPTY_ARGLIST.setValue("()");
    }

    // Special Expression
    /* NOTE: Special Expression is used to wrap expressions which like a condition node of if statement, etc. */
    public static SyntaxTree generateSpecialExpression(SyntaxTree expression){
        return new SyntaxTree(Symbol.unique("SpecialExpression"), null, new SyntaxTree[]{ expression }, null);
    }

    /* NOTE: NativeCode is used to print C code directly which like a initialize expression that contains address operator. */
    public static SyntaxTree generateNativeCode(String code){
        return new SyntaxTree(Symbol.unique("NativeCode"), null, null, code);
    }

}
