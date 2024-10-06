package type;

import java.util.HashMap;
import java.util.Map;

import type.AstType.AstBaseType;
import vmdlc.ErrorPrinter;

public enum FunctionAnnotation{
    vmInstruction(new Variable[]{
        new Variable("int", "border"), 
        new Variable("FunctionTable", "curfn"),
        new Variable("int", "pc"),
        new Variable("int", "fp"),
        new Variable("JSValue", "regbase").setArrayType(true) /* JSValue[] */
    }),
    needContext(new Variable[]{
        new Variable("Context", "context")
    }),
    triggerGC(),
    tailCall(),
    noIncPC(),
    makeInline(),
    builtinFunction(new Variable[]{
        new Variable("int", "fp"),
        new Variable("int", "na"),
        new Variable("JSValue", "rest").setArrayType(true),
        new Variable("int", "n_rest")
    }),
    calledFromC();

    Map<String, AstType> variableMap = null;
    Variable[] variables;

    private FunctionAnnotation(){}

    private FunctionAnnotation(Variable[] introduceVariables){
        this.variables = introduceVariables;
    }

    public boolean hasVariable(){
        return variables != null;
    }

    public Map<String, AstType> getVariables(){
        if(variableMap != null) return variableMap;
        if(variables == null) return null;
        int size = variables.length;
        variableMap = new HashMap<>(size);
        for(int i=0; i<size; i++){
            String typeName = variables[i].getTypeName();
            AstBaseType type = variables[i].getType();
            String variableName = variables[i].getVariableName();
            if(type == null){
                ErrorPrinter.error("Missing header file: Type \'"+typeName+"\' is not defined.\n"
                    +"NOTE: The variable \'"+variableName+"\' of type \'"+typeName+"\' is implicitly introduced by \'"+this.toString()+"\' annotation");
            }
            variableMap.put(variableName, type);
        }
        return getVariables();
    }

    static class Variable{
        private String typeName;
        private String variableName;
        private boolean isArray;

        /* 
         * ATTENTION: If you want to declare an array type (ex. T[]), DON'T wrtie it like 'new Variable("T[]", "v")'.
         *            Instead, use setArrayType() and write it like 'new Variable("T", "v").setArrayType(true)'
         */
        public Variable(String typeName, String variableName){
            this.typeName = typeName;
            this.variableName = variableName;
        }

        public Variable setArrayType(boolean flag){
            this.isArray = flag;
            return this;
        }

        public AstBaseType getType(){
            AstBaseType type = AstType.getBaseType(typeName);
            if(isArray)
                type = type.getArrayType(false, false);
            return type;
        }

        public String getTypeName(){
            return typeName;
        }

        public String getVariableName(){
            return variableName;
        }
    }
}