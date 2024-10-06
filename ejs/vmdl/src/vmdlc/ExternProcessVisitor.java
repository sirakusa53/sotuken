package vmdlc;

import java.util.Collections;
import java.util.HashSet;
import java.util.Set;

import nez.ast.Symbol;
import nez.ast.Tree;
import nez.ast.TreeVisitorMap;
import type.AstType;
import type.CConstantTable;
import type.CVariableTable;
import type.FunctionAnnotation;
import type.FunctionTable;
import type.TypeMap;
import type.AstType.AstBaseType;
import type.AstType.AstMappingType;
import type.AstType.AstProductType;
import type.AstType.JSValueType;
import vmdlc.ExternProcessVisitor.DefaultVisitor;

public class ExternProcessVisitor extends TreeVisitorMap<DefaultVisitor>{
    String currentFunctionName;
    public ExternProcessVisitor(){
        init(ExternProcessVisitor.class, new DefaultVisitor());
    }

    public String start(Tree<?> node){
        try{
            for (Tree<?> chunk : node){
                visit(chunk);
            }
            return currentFunctionName;
        }catch(Exception e) {
            e.printStackTrace();
            throw new Error("visitor thrown an exception");
        }
    }

    private final void visit(Tree<?> node) throws Exception{
        find(node.getTag().toString()).accept(node);
    }

    public class DefaultVisitor{
        public void accept(Tree<?> node) throws Exception{
            for(Tree<?> seq : node){
                visit(seq);
            }
        }
    }

    public class FunctionMeta extends DefaultVisitor{
        private Set<FunctionAnnotation> nodeToAnnotations(Tree<?> annotationsNode){
            if(annotationsNode.countSubNodes() == 0){
                return Collections.emptySet();
            }
            Set<FunctionAnnotation> annotations = new HashSet<>();
            for(Tree<?> annotation : annotationsNode){
                FunctionAnnotation annotationEnum = FunctionAnnotation.valueOf(annotation.toText());
                annotations.add(annotationEnum);
            }
            return annotations;
        }
        @Override
        public void accept(Tree<?> node) throws Exception{
            Tree<?> nameNode = node.get(Symbol.unique("name"));
            Tree<?> typeNode = node.get(Symbol.unique("type"));
            Tree<?> annotationsNode = node.get(Symbol.unique("annotations"));
            Set<FunctionAnnotation> annotations = nodeToAnnotations(annotationsNode);
            if(annotations.contains(FunctionAnnotation.vmInstruction) && annotations.contains(FunctionAnnotation.makeInline)){
                ErrorPrinter.error("Function has annotations of \"vmInstruction\" and \"makeInline\"", (SyntaxTree)node);
            }
            if(annotations.contains(FunctionAnnotation.builtinFunction) && !annotations.contains(FunctionAnnotation.needContext)){
                ErrorPrinter.error("BuiltinFunction requires \"needContext\" annotation", (SyntaxTree)annotationsNode);
            }
            String name = nameNode.toText();
            currentFunctionName = name;
            AstType type = AstType.nodeToType((SyntaxTree)typeNode);
            if(!(type instanceof AstProductType)){
                ErrorPrinter.error("Function is not function type", (SyntaxTree)typeNode);
            }
            if(!FunctionTable.contains(name)){
                FunctionTable.put(name, (AstProductType)type, annotations);
            }else if(!type.equals(FunctionTable.getType(name))){
                ErrorPrinter.error("The function is already defined, and conflicted (Maybe externC): "+name, (SyntaxTree)nameNode);
            }else if(!FunctionTable.equalsAnnotation(name, annotations)){
                ErrorPrinter.error("Conflicting annotations with before definition (Maybe externC): "+name, (SyntaxTree)nameNode);
            }
        }
    }

    public class CFunction extends DefaultVisitor{
        private Set<FunctionAnnotation> nodeToAnnotations(Tree<?> annotationsNode){
            if(annotationsNode.countSubNodes() == 0){
                return Collections.emptySet();
            }
            Set<FunctionAnnotation> annotations = new HashSet<>();
            for(Tree<?> annotation : annotationsNode){
                FunctionAnnotation annotationEnum = FunctionAnnotation.valueOf(annotation.toText());
                annotations.add(annotationEnum);
            }
            return annotations;
        }
        @Override
        public void accept(Tree<?> node) throws Exception{
            Tree<?> nameNode = node.get(Symbol.unique("name"));
            Tree<?> typeNode = node.get(Symbol.unique("type"));
            Tree<?> annotationsNode = node.get(Symbol.unique("annotations"));
            Set<FunctionAnnotation> annotations = nodeToAnnotations(annotationsNode);
            if(annotations.contains(FunctionAnnotation.vmInstruction) && annotations.contains(FunctionAnnotation.makeInline)){
                ErrorPrinter.error("Function has annotations of \"vmInstruction\" and \"makeInline\"", (SyntaxTree)node);
            }
            String name = nameNode.toText();
            AstType type = AstType.nodeToType((SyntaxTree)typeNode);
            if(!(type instanceof AstProductType)){
                ErrorPrinter.error("Function is not function type", (SyntaxTree)typeNode);
            }
            if(FunctionTable.contains(name)){
                ErrorPrinter.error("The function is already defined: "+name, (SyntaxTree)node);
            }
            FunctionTable.put(name, (AstProductType)type, annotations);
        }
    }

    public class CTypeDef extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node) throws Exception {
            Tree<?> varNode = node.get(Symbol.unique("var"));
            String typeName = varNode.toText();
            if(node.has(Symbol.unique("cvalue"))){
                String cCodeName = node.get(Symbol.unique("cvalue")).toText();
                AstType.addCValueTypeAlias(typeName, cCodeName);
            }else{
                AstType.addCValueTypeAlias(typeName);
            }
        }
    }

    public class CObjectmapping extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node) throws Exception {
            Tree<?> typeNode = node.get(Symbol.unique("type"));
            Tree<?> membersNode = node.get(Symbol.unique("members"));
            boolean heapAnnotationFlag = node.has(Symbol.unique("heapannotation"));
            String typeName = typeNode.toText();
            AstMappingType mappingType;
            if(node.has(Symbol.unique("cCodeName"))){
                Tree<?> cCodeNameNode = node.get(Symbol.unique("cCodeName"));
                String cCodeName = cCodeNameNode.toText();
                mappingType = AstType.defineMappingType(typeName, cCodeName, heapAnnotationFlag);
            }else{
                mappingType = AstType.defineMappingType(typeName, heapAnnotationFlag);
            }
            for(Tree<?> memberNode : membersNode){
                Tree<?> memberTypeNode = memberNode.get(Symbol.unique("type"));
                Tree<?> memberVarNode = memberNode.get(Symbol.unique("var"));
                AstType type = AstType.nodeToType((SyntaxTree)memberTypeNode);
                String name = memberVarNode.toText();
                if(!(type instanceof AstBaseType))
                    ErrorPrinter.error("Mapping fields are expected BaseType : "+name, (SyntaxTree)memberNode);
                mappingType.addField((AstBaseType)type, name);
            }
        }
    }

    public class CConstantDef extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node) throws Exception {
            Tree<?> typeNode = node.get(Symbol.unique("type"));
            Tree<?> varNode = node.get(Symbol.unique("var"));
            Tree<?> valueNode = node.get(Symbol.unique("value"));
            AstType type = AstType.nodeToType((SyntaxTree)typeNode);
            String varName = varNode.toText();
            String cValue = valueNode.toText().replace("\\\"", "\"").replace("\\\\", "\\");
            boolean isAdded = TypeMap.addGlobal(varName, type);
            if(!isAdded){
                ErrorPrinter.error("Duplicate define: "+varName, (SyntaxTree)node);
            }
            CConstantTable.put(varName, cValue);
        }
    }

    public class CVariableDef extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node) throws Exception {
            Tree<?> typeNode = node.get(Symbol.unique("type"));
            Tree<?> varNode = node.get(Symbol.unique("var"));
            AstType type = AstType.nodeToType((SyntaxTree)typeNode);
            String varName = varNode.toText();
            boolean isAdded = TypeMap.addGlobal(varName, type);
            if(!isAdded){
                ErrorPrinter.error("Duplicate define: "+varName, (SyntaxTree)node);
            }
            CVariableTable.put(varName, type);
        }
    }
    
    public class UnionDefinition extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node) throws Exception {
            Tree<?> nameNode = node.get(Symbol.unique("name"));
            Tree<?> unionNode = node.get(Symbol.unique("union"));
            String name = nameNode.toText();
            JSValueType unionType = AstType.nodeToUnionType((SyntaxTree)unionNode, name);
            AstType.putJSValueType(unionType);
        }
    }
}