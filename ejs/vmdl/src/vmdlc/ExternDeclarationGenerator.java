package vmdlc;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import nez.ast.Symbol;
import nez.ast.Tree;
import type.AstType;
import type.FunctionTable;
import type.FunctionAnnotation;
import type.AstType.AstBaseType;
import type.AstType.AstProductType;
import type.AstType.JSValueType;

public class ExternDeclarationGenerator {
    private static SyntaxTree getFunctionMeta(SyntaxTree node){
        if(!node.is(Symbol.unique("FunctionMeta"))){
            Tree<SyntaxTree>[] subTree = node.getSubTree();
            if(subTree == null) return null;
            for(Tree<SyntaxTree> tree : subTree){
                SyntaxTree result = getFunctionMeta((SyntaxTree)tree);
                if(result != null) return result;
            }
            return null;
        }
        return node;
    }
    private static void getFunctionMetas(SyntaxTree node, List<SyntaxTree> functions){
        if(node.is(Symbol.unique("FunctionMeta"))){
            functions.add(node);
            return;
        }
        Tree<SyntaxTree>[] subTree = node.getSubTree();
        if(subTree == null) return;
        for(Tree<SyntaxTree> tree : subTree)
            getFunctionMetas((SyntaxTree)tree, functions);
    }
    private static SyntaxTree[] getFunctionMetas(SyntaxTree node){
        List<SyntaxTree> functions = new ArrayList<>();
        getFunctionMetas(node, functions);
        return functions.toArray(new SyntaxTree[0]);
    }
    public static String generate(SyntaxTree node){
        if(!node.is(Symbol.unique("FunctionMeta"))) return "";
        StringBuilder builder = new StringBuilder();
        Tree<?> nameNode = node.get(Symbol.unique("name"));
        Tree<?> typeNode = node.get(Symbol.unique("type"));
        Tree<?> paramsNode = node.get(Symbol.unique("definition")).get(Symbol.unique("params"));
        String name = nameNode.toText();
        AstType type = AstType.nodeToType((SyntaxTree)typeNode);
        if(!(type instanceof AstProductType)){
            throw new Error("Function is not function type");
        }
        AstProductType funType = (AstProductType)type;
        AstType rangeType = funType.getRange();
        AstBaseType[] varTypes = funType.getDomainAsArray();
        builder.append("extern ");
        if(!(rangeType instanceof AstBaseType))
            throw new Error("Expect the function range types BaseType");

        String typeString = ((AstBaseType)rangeType).getCCodeName();
        builder.append(typeString+" "+name+"(");
        int size = varTypes.length;
        if(!FunctionTable.contains(name)){
            throw new Error("FunctionTable is broken: not has "+name);
        }
        if(paramsNode.size() != size)
            ErrorPrinter.error("Invalid declaration", (SyntaxTree)paramsNode);
        List<String> paramNames = new ArrayList<>(size);
        for(Tree<?> param : paramsNode){
            paramNames.add(param.toText());
        }
        if(FunctionTable.hasAnnotations(name, FunctionAnnotation.needContext)){
            builder.append("Context *context");
            if(size != 0){
                builder.append(", ");
            }
        }
        int i=0;
        while(true){
            AstBaseType varType = varTypes[i];
            String param = paramNames.get(i);
            String typeName = varType.getCCodeName();
            builder.append(typeName).append(' ').append(param);
            i++;
            if(i>=size) break;
            builder.append(", ");
        }
        builder.append(");");
        builder.append("\n");
        return builder.toString();
    }
    private static void addArgumentDescription(StringBuilder builder, String name, AstBaseType[] types, List<String> params){
        if(FunctionTable.hasAnnotations(name, FunctionAnnotation.needContext))
            builder.append(" * @param[in] context The context when this function is called\n");
        if(types == null || types.length == 0) return;
        int size = types.length;
        for(int i=0; i<size; i++){
            builder.append(" * @param[in] ").append(params.get(i)).append(" Expected type : ");
            /* Full print */
            // Set<AstType> detailedTypes = types.get(i).getDetailedTypes();
            // int setSize = detailedTypes.size();
            // String[] detailedTypeNames = new String[setSize];
            // int j=0;
            // for(AstType t : detailedTypes)
            //     detailedTypeNames[j++] = t.toString();
            // builder.append(String.join(" | ", detailedTypeNames)).append('\n');
            /* Simple print */
            builder.append(types[i].toString()).append('\n');
        }
        return;
    }
    private static void addReturnDescription(StringBuilder builder, AstType type){
        if(type == null) return;
        builder.append(" * @return Returns type : ");
        /* Full print */
        // Set<AstType> detailedTypes = type.getDetailedTypes();
        // int setSize = detailedTypes.size();
        // String[] detailedTypeNames = new String[setSize];
        // int i=0;
        // for(AstType t : detailedTypes)
        //     detailedTypeNames[i++] = t.toString();
        // builder.append(String.join(" | ", detailedTypeNames)).append('\n');
        /* Simple print */
        builder.append(type).append('\n');
        return;
    }
    private static String generateDescription(SyntaxTree node){
        if(!node.is(Symbol.unique("FunctionMeta"))) return "";
        StringBuilder builder = new StringBuilder();
        Tree<?> nameNode = node.get(Symbol.unique("name"));
        Tree<?> typeNode = node.get(Symbol.unique("type"));
        Tree<?> paramsNode = node.get(Symbol.unique("definition")).get(Symbol.unique("params"));
        String name = nameNode.toText();
        builder.append("/**\n * @note generated by VMDLC\n");
        AstType type = AstType.nodeToType((SyntaxTree)typeNode);
        if(!(type instanceof AstProductType)){
            throw new Error("Function is not function type");
        }
        AstProductType funType = (AstProductType)type;
        AstBaseType[] varTypes = funType.getDomainAsArray();
        int size = varTypes.length;
        if(paramsNode.size() != size)
            ErrorPrinter.error("Invalid declaration", (SyntaxTree)paramsNode);
        List<String> paramNames = new ArrayList<>(size);
        for(Tree<?> param : paramsNode){
            paramNames.add(param.toText());
        }
        addArgumentDescription(builder, name, varTypes, paramNames);
        addReturnDescription(builder, funType.getRange());
        builder.append(" */\n");
        return builder.toString();
    }
    private static boolean isCalledFromCFunction(SyntaxTree node){
        if(!node.is(Symbol.unique("FunctionMeta"))) return false;
        String functionName = node.get(Symbol.unique("name")).toText();
        return FunctionTable.hasAnnotations(functionName, FunctionAnnotation.calledFromC);
    }
    private static void writeForC(SyntaxTree node, FileWriter writer) throws IOException{
        writer.write(generateDescription(node));
        writer.write(generate(node));
    }
    private static void writeForVMDL(SyntaxTree node, FileWriter writer) throws IOException{
        writer.write(generate(node));
    }
    public static void writeExternDeclaration(SyntaxTree node, String externCFile, String externVMDLFile) throws IOException{
        SyntaxTree[] functions = getFunctionMetas(node);
        FileWriter externCWriter = new FileWriter(externCFile, true);
        FileWriter externVMDLWriter = new FileWriter(externVMDLFile, true);
        for(SyntaxTree function : functions){
            boolean calledFromCFlag = isCalledFromCFunction(function);
            if(calledFromCFlag)
                writeForC(function, externCWriter);
            else
                writeForVMDL(function, externVMDLWriter);
        }
        externCWriter.close();
        externVMDLWriter.close();
    }
    public static String genereteOperandSpecCRequire(SyntaxTree node){
        node = getFunctionMeta(node);
        if(!node.is(Symbol.unique("FunctionMeta"))){
            return "";
        }
        Tree<?> nameNode = node.get(Symbol.unique("name"));
        Tree<?> typeNode = node.get(Symbol.unique("type"));
        String name = nameNode.toText();
        AstType type = AstType.nodeToType((SyntaxTree)typeNode);
        if(!(type instanceof AstProductType)){
            throw new Error("Function is not function type");
        }
        AstType[] funDomainTypes = ((AstProductType)type).getDomainAsArray();
        int length = funDomainTypes.length;
        StringBuilder builder = new StringBuilder();
        builder.append(name);
        builder.append(" (");
        String[] specifyChars = new String[length];
        for(int i=0; i<length; i++){
            if(funDomainTypes[i] instanceof JSValueType)
                specifyChars[i] = "_";
            else
                specifyChars[i] = "-";
        }
        builder.append(String.join(",", specifyChars));
        builder.append(") ");
        if(FunctionTable.hasAnnotations(name, FunctionAnnotation.calledFromC))
            builder.append("accept\n");
        else
            builder.append("unspecified\n");
        return builder.toString();
    }
}
