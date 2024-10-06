/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package vmdlc;

import nez.ast.Tree;
import nez.ast.TreeVisitorMap;
import nez.ast.Symbol;

import java.util.HashMap;
import java.util.Stack;
import java.util.Set;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.ArrayList;
import java.util.Collections;
import java.lang.Exception;
import java.lang.Integer;

import vmdlc.AstToCVisitor.DefaultVisitor;
import vmdlc.Option.CompileMode;
import dispatch.DispatchProcessor;
import dispatch.DispatchPlan;
import dispatch.RuleSet;
import type.AstType;
import type.CConstantTable;
import type.ExprTypeSet;
import type.FunctionAnnotation;
import type.FunctionTable;
import type.TypeMap;
import type.TypeMapSet;
import type.VMDataType;
import type.AstType.AstPrimitiveType;
import type.AstType.AstBaseType;
import type.AstType.AstComplexType;
import type.AstType.AstMappingType;
import type.AstType.AstPairType;
import type.AstType.AstProductType;
import type.AstType.JSValueType;
import type.AstType.JSValueVMType;
import vmdlc.OperandSpecifications.OperandSpecificationRecord.Behaviour;

public class AstToCVisitor extends TreeVisitorMap<DefaultVisitor> {
    static final boolean OUTPUT_DEBUG_INFO = false;
    static final boolean VM_INSTRUCTION = true;
    static class MatchRecord {
        static int next = 1;
        String name;
        String functionName;
        String matchLabel;
        String[] opNames;
        Option option;
        MatchRecord(String functionName, String matchLabel, int lineNum, String[] opNames, Option option) {
            this.matchLabel = matchLabel;
            this.functionName = functionName;
            this.option = option;
            if (matchLabel != null)
                name = matchLabel +"AT"+lineNum;
            else
                name = (next++)+"AT"+lineNum;
            this.opNames = opNames;
        }
        String getHeadLabel() {
            String labelPrefix = option.getXOption().getOption(XOption.AvailableOptions.GEN_LABEL_PREFIX, functionName);
            return "MATCH_HEAD_"+labelPrefix+"_"+name;
        }
        String getTailLabel() {
            String labelPrefix = option.getXOption().getOption(XOption.AvailableOptions.GEN_LABEL_PREFIX, functionName);
            return "MATCH_TAIL_"+labelPrefix+"_"+name;
        }
        boolean hasMatchLabelOf(String label) {
            return matchLabel != null && matchLabel.equals(label);
        }
        String getFunctionName(){
            return functionName;
        }
    }
    Stack<StringBuffer> outStack;
    Stack<MatchRecord> matchStack;
    String currentFunctionName;
    OperandSpecifications opSpec;
    OperandSpecifications caseSplittingSpec;
    CompileMode compileMode;
    Option option;

    public AstToCVisitor() {
        init(AstToCVisitor.class, new DefaultVisitor());
        outStack = new Stack<StringBuffer>();
        matchStack = new Stack<MatchRecord>();
    }

    public String start(Tree<?> node, OperandSpecifications opSpec, CompileMode compileMode, Option option) {
        this.opSpec = opSpec;
        this.compileMode = compileMode;
        this.option = option;
        if(option.isEnableCaseSplitting())
            caseSplittingSpec = option.getCaseSplittingSpec();
        try {
            outStack.push(new StringBuffer());
            for (Tree<?> chunk : node) {
                visit(chunk, 0);
            }
            StringBuffer sb = outStack.pop();
            if(!compileMode.isFunctionMode()) sb.append(getEpilogueLabel() + ": __attribute__((unused));\n");
            String program = sb.toString();
            return program;
        } catch (Exception e) {
            e.printStackTrace();
            throw new Error("visitor thrown an exception");
        }
    }

    private final void visit(Tree<?> node, int indent) throws Exception {
        find(node.getTag().toString()).accept(node, indent);
    }

    private final void visit(Tree<?> node, int indent, String extraHeadCode) throws Exception {
        if(extraHeadCode == null)
            find(node.getTag().toString()).accept(node, indent);
        else
            find(node.getTag().toString()).accept(node, indent, extraHeadCode);
    }

    private final void notifyICCProfCode(Tree<?> node, String code) throws Exception {
        find(node.getTag().toString()).setICCProfCode(node, code);
    }

    private final void notifyInsnName(Tree<?> node, String insnName) throws Exception {
        find(node.getTag().toString()).setInsnName(node, insnName);
    }

    private void print(Object o) {
        outStack.peek().append(o);
    }

    private void println(Object o) {
        outStack.peek().append(o + "\n");
    }

    private void printBinaryOperator(Tree<?> node, String s) throws Exception {
        Tree<?> leftNode = node.get(Symbol.unique("left"));
        Tree<?> rightNode = node.get(Symbol.unique("right"));
        print("(");
        visit(leftNode, 0);
        print(s);
        visit(rightNode, 0);
        print(")");
    }
    private void printUnaryOperator(Tree<?> node, String s) throws Exception {
        Tree<?> exprNode = node.get(Symbol.unique("expr"));
        print("(");
        print(s);
        visit(exprNode, 0);
        print(")");
    }
    private void printIndent(int indent, String s) {
        for (int i = 0; i < indent; i++) {
            print("  ");
        }
        print(s);
    }
    private void printIndentln(int indent, String s) {
        printIndent(indent, s);
        println("");
    }

    private String getEpilogueLabel() {
        String labelPrefix = option.getXOption().getOption(XOption.AvailableOptions.GEN_LABEL_PREFIX, currentFunctionName);
        return "L"+labelPrefix+"_EPILOGUE";
    }

    public class DefaultVisitor {
        public void accept(Tree<?> node, int indent) throws Exception {
            for (Tree<?> seq : node) {
                visit(seq, indent);
            }
        }
        public void accept(Tree<?> node, int indent, String extraHeadCode) throws Exception {
            for (Tree<?> seq : node) {
                visit(seq, indent, extraHeadCode);
            }
        }

        public void setICCProfCode(Tree<?> node, String code) throws Exception {
            for (Tree<?> seq : node) {
                notifyICCProfCode(seq, code);
            }
        }

        public void setInsnName(Tree<?> node, String insnName) throws Exception {
            for (Tree<?> seq : node) {
                notifyInsnName(seq, insnName);
            }
        }
    }

    public class UnionDefinition extends DefaultVisitor {
        public void accept(Tree<?> node, int indent) throws Exception {
        }
    }
    public class FunctionMeta extends DefaultVisitor {
        private final String generateExtraHeadCode(List<AstType> types, List<String> params){
            if(types.size() != params.size())
                throw new Error("InternalError: invalid data state");
            if(types.isEmpty()) return null;
            StringBuilder builder = new StringBuilder();
            builder.append("assert(");
            int length = types.size();
            List<String> conditions = new ArrayList<>(length);
            for(int i=0; i<length; i++){
                Set<AstType> detailed = types.get(i).getDetailedTypes();
                for(AstType t : detailed){
                    if(!(t instanceof JSValueVMType))
                        throw new Error("InternalError: getDetailedType() returns non-JSValueVMType value");
                    conditions.add("is_"+(((JSValueVMType)t).getVMDataType().toString())+"("+params.get(i)+")");
                }
            }
            builder.append(String.join("||", conditions.toArray(new String[0])));
            builder.append(");");
            return builder.toString();
        }
        private final String generateICCProfCode(String insnName, AstBaseType[] types, Tree<?> paramsNode){
            StringBuilder builder = new StringBuilder();
            int jsvSize = 0;
            for(AstBaseType type : types)
                if(AstType.getPrimitiveType("JSValue").isSuperOrEqual(type)) jsvSize++;
            if(jsvSize==0) return "";
            builder.append("#ifdef ICC_PROF\n");
            builder.append("icc_inc_record");
            builder.append(jsvSize);
            builder.append("(\"");
            builder.append(insnName);
            builder.append('\"');
            for(int i=0; i<jsvSize; i++){
                builder.append(", ");
                builder.append(paramsNode.get(i).toText());
            }
            builder.append(");\n");
            builder.append("#endif /* ICC_PROF */\n");
            return builder.toString();
        }
        private final String getTypeString(CompileMode mode, AstProductType functionType){
            if(mode.isBuiltinFunctionMode())
                return "void";
            AstType rangeType = functionType.getRange();
            if(rangeType instanceof AstPrimitiveType)
                return ((AstPrimitiveType)rangeType).getCCodeName();
            if(rangeType instanceof AstPairType){

            }
            throw new Error("InternalError: cannot generate range type C code: "+rangeType.toString());
        }
        private final String getParameterString(CompileMode mode, AstBaseType[] parameterTypes, SyntaxTree paramsNode, String functionName){
            if(mode.isBuiltinFunctionMode())
                return "Context* context, cint fp, cint na";
            List<String> parameters;
            int size = paramsNode.size();
            if(FunctionTable.hasAnnotations(functionName, FunctionAnnotation.needContext)){
                parameters = new ArrayList<>(size+1);
                parameters.add("Context* context");
            }else{
                parameters = new ArrayList<>(size);
            }
            for(int i=0; i<size; i++){
                String typeString = parameterTypes[i].getCCodeName();
                String nameString = paramsNode.get(i).toText();
                parameters.add(typeString+" "+nameString);
            }
            return String.join(", ", parameters.toArray(new String[0]));
        }

        public void accept(Tree<?> node, int indent) throws Exception {
            Tree<?> nameNode = node.get(Symbol.unique("name"));
            Tree<?> bodyNode = node.get(Symbol.unique("definition"));
            SyntaxTree typeNode = (SyntaxTree)node.get(Symbol.unique("type"));
            SyntaxTree paramsNode = ((SyntaxTree)bodyNode).get(Symbol.unique("params"));
            String extraHeadCode = null;
            AstType type = AstType.nodeToType(typeNode);
            if(!(type instanceof AstProductType)){
                throw new Error("Function is not function type");
            }
            AstProductType functionType = (AstProductType)type;
            AstBaseType[] varTypes = functionType.getDomainAsArray();
            String name = nameNode.toText();
            currentFunctionName = name;
            if(opSpec.isAllUnspecified(name) && name.indexOf("constr") == -1){
                /* 
                 * This function cannot be executed.
                 * (NOTE: XXX_constr cannot be eliminated. This is because those functions are referenced in 'ini.c'.)
                 */
                println("#define ELIMINATED_"+name.toUpperCase());
                return;
            }
            if(compileMode.isFunctionMode()){
                String typeString = getTypeString(compileMode, functionType);
                print(typeString+" "+name+" (");
                if(!FunctionTable.contains(name)){
                    throw new Error("InternalError: cannot find in FunctionTable: "+name);
                }
                print(getParameterString(compileMode, varTypes, paramsNode, name));
                println(")");
                if(FunctionTable.hasAnnotations(name, FunctionAnnotation.calledFromC)){
                    int paramSize = varTypes.length;
                    List<AstType> jsvVarTypes = new ArrayList<>(paramSize);
                    List<String> paramNames = new ArrayList<>(paramSize);
                    for(int i=0; i<paramSize; i++){
                        AstType t = varTypes[i];
                        if(!(t instanceof JSValueType)) continue;
                        jsvVarTypes.add(t);
                        paramNames.add(paramsNode.get(i).toText());
                    }
                    extraHeadCode = generateExtraHeadCode(jsvVarTypes, paramNames);
                }
            }
            if(!compileMode.isFunctionMode()){
                notifyICCProfCode(bodyNode, generateICCProfCode(name, varTypes, paramsNode));
                notifyInsnName(bodyNode, name);
            }
            visit(bodyNode, indent, extraHeadCode);
        }
    }
    public class FunctionDefinition extends DefaultVisitor {
        private SyntaxTree printIntro(Tree<?> node, int indent) throws Exception {
            Tree<?> paramsNode = node.get(Symbol.unique("params"));
            Tree<?> funNameNode = node.get(Symbol.unique("name"));
            if(!compileMode.isFunctionMode()){
                String[] jsvParams = new String[paramsNode.size()];
                int jsvNum = 0;

                for (int i = 0; i < paramsNode.size(); i++) {
                    String paramName = paramsNode.get(i).toText();
                    /* JSValue parameter's name starts with v as defined in InstructionDefinitions.java */
                    if (paramName.startsWith("v")) {
                        jsvParams[jsvNum++] = paramName;
                    }
                }
                println("DEFLABEL(HEAD): __attribute__((unused));");
                print("INSN_COUNT" + jsvNum + "(" + funNameNode.toText());
                for (int i = 0; i < jsvNum; i++) {
                    print("," + jsvParams[i]);
                }
                println(");");
            }
            SyntaxTree bodyNode = (SyntaxTree) node.get(Symbol.unique("body"));
            if(compileMode.isBuiltinFunctionMode()){
                int paramSize = paramsNode.size();
                while(bodyNode.hasExpandedTree()){
                    bodyNode = bodyNode.getExpandedTree();
                }
                SyntaxTree[] originalStmts = (SyntaxTree[])((SyntaxTree)bodyNode).getSubTree();
                SyntaxTree[] expandedStmts = new SyntaxTree[originalStmts.length + paramSize + 4];
                expandedStmts[0] = ASTHelper.generateExpressionStatement(ASTHelper.BUILTIN_PROLOGUE);
                StringBuilder builtinCountMacroBuilder = new StringBuilder();
                builtinCountMacroBuilder.append("BUILTIN_COUNT").append(paramSize).append('(').append(funNameNode.toText()).append(",na");
                for(int i=0; i<paramSize; i++){
                    expandedStmts[i+1] = ASTHelper.generateDeclaration("JSValue", paramsNode.get(i).toText() + " __attribute__((unused))", ASTHelper.generateArrayIndex("args", i));
                    builtinCountMacroBuilder.append(",args[").append(i).append("]");
                }
                builtinCountMacroBuilder.append(");\n");
                expandedStmts[paramSize+1] = ASTHelper.generateDeclaration(ASTHelper.generateArrayType("JSValue"), "rest __attribute__((unused))", ASTHelper.generateNativeCode("&args["+paramSize+"]"));
                expandedStmts[paramSize+2] = ASTHelper.generateDeclaration("int", "n_rest __attribute__((unused))",
                    ASTHelper.generateBinaryExpression("Sub", new SyntaxTree[]{ASTHelper.generateName("na"), ASTHelper.generateNativeCode("("+(paramSize-1)+")")}));
                expandedStmts[paramSize+3] = ASTHelper.generateNativeCode(builtinCountMacroBuilder.toString());
                int length = originalStmts.length;
                for(int i=0; i<length; i++){
                    expandedStmts[paramSize+4+i] = originalStmts[i];
                }
                bodyNode = ASTHelper.generateBlock(expandedStmts);
            }
            else if (compileMode.isFunctionMode()) {
                while(bodyNode.hasExpandedTree()){
                    bodyNode = bodyNode.getExpandedTree();
                }
                SyntaxTree[] originalStmts = (SyntaxTree[])((SyntaxTree)bodyNode).getSubTree();
                SyntaxTree[] expandedStmts = new SyntaxTree[originalStmts.length + 1];
                int length = originalStmts.length;
                for(int i=0; i<length; i++){
                    expandedStmts[i] = originalStmts[i];
                }
                expandedStmts[length] = ASTHelper.generateExpressionStatement(ASTHelper.FUNCTION_EPILOGUE);
                bodyNode = ASTHelper.generateBlock(expandedStmts);
            }
            return bodyNode;
        }
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            SyntaxTree bodyNode = printIntro(node, indent);
            String name = node.get(Symbol.unique("name")).toText();
            if(opSpec.isAllUnspecified(name) && name.indexOf("constr") >= 0){
                /* 
                 * This function cannot be executed.
                 * (NOTE: XXX_constr cannot be eliminated. This is because those functions are referenced in 'ini.c'.)
                 */
                println("{}");
                return;
            }
            visit(bodyNode, indent);
        }
        @Override
        public void accept(Tree<?> node, int indent, String extraHeadCode) throws Exception {
            SyntaxTree bodyNode = printIntro(node, indent);
            String name = node.get(Symbol.unique("name")).toText();
            if(opSpec.isAllUnspecified(name) && name.indexOf("constr") >= 0){
                /* 
                 * This function cannot be executed.
                 * (NOTE: XXX_constr cannot be eliminated. This is because those functions are referenced in 'ini.c'.)
                 */
                println("{}");
                return;
            }
            visit(bodyNode, indent, extraHeadCode);
        }
    }

    public class CFunction extends DefaultVisitor {
        public void accept(Tree<?> node, int indent) throws Exception {
        }
    }

    public class CConstantDef extends DefaultVisitor {
        public void accept(Tree<?> node, int indent) throws Exception {
        }
    }

    public class CTypeDef extends DefaultVisitor {
        public void accept(Tree<?> node, int indent) throws Exception {
        }
    }

    public class CObjectmapping extends DefaultVisitor {
        public void accept(Tree<?> node, int indent) throws Exception {
        }
    }

    public class CVariableDef extends DefaultVisitor {
        public void accept(Tree<?> node, int indent) throws Exception {
        }
    }

    public class Block extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            SyntaxTree expandedNode = ((SyntaxTree)node).getExpandedTree();
            if(expandedNode != null){
                visit(expandedNode, indent);
                return;
            }
            printIndentln(indent, "{");
            for (Tree<?> seq : node) {
                visit(seq, indent + 1);
            }
            printIndentln(indent, "}");
        }
        @Override
        public void accept(Tree<?> node, int indent, String extraHeadCode) throws Exception {
            SyntaxTree expandedNode = ((SyntaxTree)node).getExpandedTree();
            if(expandedNode != null){
                visit(expandedNode, indent, extraHeadCode);
                return;
            }
            printIndentln(indent, "{");
            printIndentln(indent+1, extraHeadCode);
            for (Tree<?> seq : node) {
                visit(seq, indent + 1);
            }
            printIndentln(indent, "}");
        }
    }

    private static Map<String, Integer> matchLabelGeneratedSizeMap = new HashMap<>();

    public class Match extends DefaultVisitor {
        private String iccprofCode = null;
        private String insnName;

        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            SyntaxTree expandedNode = ((SyntaxTree)node).getExpandedTree();
            if(expandedNode != null){
                visit(expandedNode, indent);
                return;
            }
            MatchProcessor mp = new MatchProcessor((SyntaxTree) node);
            String[] formalParams = mp.getFormalParams();
            String rawLabel = mp.getLabel();
            String label;
            if(compileMode.isFunctionMode()){
                Integer labelCount = matchLabelGeneratedSizeMap.get(rawLabel);
                if(labelCount == null){
                    labelCount = 0;
                }
                matchLabelGeneratedSizeMap.put(rawLabel, labelCount + 1);
                label = "_" + rawLabel + labelCount;
            }else{
                label = "";
            }

            TypeMapSet dict = ((SyntaxTree) node).getHeadDict();

            // printIndentln(indent, "/* "+dict.toString()+" */");
            printIndentln(indent, "/* [ormit] */");

            matchStack.add(new MatchRecord(currentFunctionName, rawLabel, node.getLineNum(), formalParams, option));
            printIndent(indent, matchStack.peek().getHeadLabel()+": __attribute__((unused));"+"\n");

            /* Insert code for ICCPROF (only top level match) */
            if(compileMode == CompileMode.Instruction && rawLabel != null && rawLabel.equals("top")){
                print(iccprofCode);
            }

            Set<RuleSet.Rule> rules = new HashSet<RuleSet.Rule>();
            Set<VMDataType[]> acceptInput = new HashSet<>();

            for (int i = 0; i < mp.size(); i++) {
                Set<VMDataType[]> vmtVecs = mp.getVmtVecCond(i);
                if (!option.getXOption().disableMatchOptimisation())
                    vmtVecs = dict.filterTypeVecs(formalParams, vmtVecs);
                if (vmtVecs.size() == 0)
                    continue;

                acceptInput.addAll(vmtVecs);

                /* action */
                outStack.push(new StringBuffer());
                Tree<?> stmt = mp.getBodyAst(i);
                visit(stmt, indent);
                String action = outStack.pop().toString();

                /* OperandDataTypes set */
                Set<RuleSet.OperandDataTypes> odts = new LinkedHashSet<RuleSet.OperandDataTypes>();
                if(caseSplittingSpec != null && mp.getFormalParams().length == caseSplittingSpec.getArity(insnName)){
                    /* Case split specified */
                    for (VMDataType[] vmtVec: vmtVecs) {
                        if(caseSplittingSpec.findSpecificationRecord(insnName, vmtVec).getBehavior() != Behaviour.ACCEPT) continue;
                        RuleSet.OperandDataTypes odt = new RuleSet.OperandDataTypes(vmtVec);
                        odts.add(odt);
                    }
                    /* Case split unspecified */
                    for (VMDataType[] vmtVec: vmtVecs) {
                        if(caseSplittingSpec.findSpecificationRecord(insnName, vmtVec).getBehavior() == Behaviour.ACCEPT) continue;
                        RuleSet.OperandDataTypes odt = new RuleSet.OperandDataTypes(vmtVec);
                        odts.add(odt);
                    }
                }else{
                    for (VMDataType[] vmtVec: vmtVecs) {
                        RuleSet.OperandDataTypes odt = new RuleSet.OperandDataTypes(vmtVec);
                        odts.add(odt);
                    }
                }

                /* debug */
                if (OUTPUT_DEBUG_INFO) {
                    StringBuffer sb = new StringBuffer();
                    for (VMDataType[] vmts: vmtVecs) {
                        sb.append("/*");
                        for(VMDataType vmt: vmts)
                            sb.append(" "+vmt);
                        sb.append(" */\n");
                    }
                    action = sb.toString() + action;
                }

                RuleSet.Rule r = new RuleSet.Rule(action, odts);
                rules.add(r);
            }

            /* print error types (NOT in accept types) */
            Set<VMDataType[]> errorInput = opSpec.getErrorOperands(currentFunctionName);
            if(errorInput == null) errorInput = Collections.emptySet();
            Set<RuleSet.OperandDataTypes> errorConditions = new HashSet<RuleSet.OperandDataTypes>();
            NEXT_DTS: for (VMDataType[] dts: errorInput) {
                int length = dts.length;
                NEXT_ARRAY: for (VMDataType[] accept: acceptInput) {
                    for(int i=0; i<length; i++){
                        if(!dts[i].equals(accept[i])) continue NEXT_ARRAY;
                    }
                    continue NEXT_DTS;
                }
                errorConditions.add(new RuleSet.OperandDataTypes(dts));
            }
            String errorAction = new String("LOG_EXIT(\"unexpected operand type\\n\");\n");
            if (errorConditions.size() > 0) {
                rules.add(new RuleSet.Rule(errorAction, errorConditions));
            }

            RuleSet rs = new RuleSet(formalParams, rules);

            DispatchPlan dp = new DispatchPlan(option.getXOption());
            DispatchProcessor dispatchProcessor = new DispatchProcessor();
            String labelPrefix =option.getXOption().getOption(XOption.AvailableOptions.GEN_LABEL_PREFIX, currentFunctionName);
            dispatchProcessor.setLabelPrefix(labelPrefix + "_"+ matchStack.peek().name + "_");
            String s = dispatchProcessor.translate(rs, dp, option.getXOption(), currentFunctionName, label);
            printIndentln(indent, s);

            println(matchStack.pop().getTailLabel()+": __attribute__((unused));");
        }

        @Override
        public void setICCProfCode(Tree<?> node, String code) throws Exception {
            iccprofCode = code;
        }
        
        @Override
        public void setInsnName(Tree<?> node, String insnName) throws Exception {
            this.insnName = insnName;
        }
    }

    public class Return extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            if(compileMode.isBuiltinFunctionMode()){
                printIndentln(indent, "{");
                printIndent(indent+1, "set_a(context, ");
                for (Tree<?> expr : node) {
                    visit(expr, 0);
                }
                println(");");
                printIndentln(indent+1, "return;");
                printIndentln(indent, "}");
            }else if (compileMode.isFunctionMode()) {
                printIndent(indent, "return ");
                for (Tree<?> expr : node) {
                    visit(expr, 0);
                }
                println(";");
            } else {
                printIndent(indent, "regbase[r0] = ");
                for (Tree<?> expr : node) {
                    visit(expr, 0);
                }
                println(";");
                println("goto "+getEpilogueLabel()+";");
            }
        }
    }

    public class Assignment extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            SyntaxTree expandedTree = ((SyntaxTree)node).getExpandedTree();
            if(expandedTree != null){
                visit(expandedTree, indent);
                return;
            }
            printIndent(indent, "");
            Tree<?> leftNode = node.get(Symbol.unique("left"));
            Tree<?> rightNode = node.get(Symbol.unique("right"));
            visit(leftNode, 0);
            print(" = ");
            visit(rightNode, 0);
            println(";");
        }
    }
    public class AssignmentPair extends DefaultVisitor {
        private final String getStructTypeName(String functionName){
            return functionName+"_rettype";
        }
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            SyntaxTree expandedTree = ((SyntaxTree)node).getExpandedTree();
            if(expandedTree != null){
                visit(expandedTree, indent);
                return;
            }
            printIndent(indent, "");
            Tree<?> leftNode = node.get(Symbol.unique("left"));
            Tree<?> rightNode = node.get(Symbol.unique("right"));
            Tree<?> fname = rightNode.get(Symbol.unique("recv"));
            Tree<?>[] pairs = new Tree<?>[leftNode.size()];
            int pairSize = leftNode.size();
            for(int i=0; i<pairSize; i++){
                pairs[i] = leftNode.get(i);
            }
            println("{");
            print("struct "+getStructTypeName(fname.toText())+" __assignment_pair_temp__ = ");
            visit(rightNode, indent);
            println(";");
            for(int i=0; i<pairSize; i++){
                println(pairs[i].toText()+" = __assignment_pair_temp__.r"+i+";");
            }
            println("}");
        }
    }

    public class ExpressionStatement extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            SyntaxTree expandedTree = ((SyntaxTree)node).getExpandedTree();
            if(expandedTree != null){
                visit(expandedTree, indent);
                return;
            }
            printIndent(indent, "");
            visit(node.get(0), indent);
            println(";");
        }
    }
    public class Declaration extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            SyntaxTree expandedTree = ((SyntaxTree)node).getExpandedTree();
            if(expandedTree != null){
                visit(expandedTree, indent);
                return;
            }
            Tree<?> typeNode = node.get(Symbol.unique("type"));
            Tree<?> varNode = node.get(Symbol.unique("var"));
            printIndent(indent, "");
            visit(typeNode, 0);
            print(" ");
            visit(varNode, 0);
            if(node.has(Symbol.unique("expr"))){
                Tree<?> exprNode = node.get(Symbol.unique("expr"));
                if(exprNode != SyntaxTree.PHANTOM_NODE){
                    print(" = ");
                    visit(exprNode, 0);
                }
            }
            println(";");
        }
    }
    public class If extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            Tree<?> condNode = node.get(Symbol.unique("cond"));
            Tree<?> thenNode = node.get(Symbol.unique("then"));
            printIndent(indent, "if (!!");
            visit(condNode, indent);
            if(thenNode.is(Symbol.unique("Block"))){
                println(")");
                visit(thenNode, indent);
            }else{
                println(") {");
                visit(thenNode, indent + 1);
                printIndentln(indent, "}");
            }
            if (node.has(Symbol.unique("else"))) {
                Tree<?> elseNode = node.get(Symbol.unique("else"));
                if(thenNode.is(Symbol.unique("Block"))){
                    printIndentln(indent, "else");
                    visit(elseNode, indent);
                }else{
                    printIndentln(indent, "else {");
                    visit(elseNode, indent + 1);
                    printIndentln(indent, "}");
                }
            }
        }
    }
    public class Do extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            Tree<?> initNode = node.get(Symbol.unique("init"));
            Tree<?> limitNode = node.get(Symbol.unique("limit"));
            Tree<?> stepNode = node.get(Symbol.unique("step"));
            Tree<?> blockNode = node.get(Symbol.unique("block"));
            printIndentln(indent, "{");
            for (int i = 0; i < indent+1; i++) {
                print("  ");
            }
            visit(initNode, 0);
            println("; ");
            printIndent(indent+1, "for (;");
            Tree<?> varNode = initNode.get(Symbol.unique("var"));
            visit(varNode, 0);
            print("<=");
            visit(limitNode, 0);
            print("; ");
            visit(varNode, 0);
            print("+=");
            visit(stepNode, 0);
            println(")");
            visit(blockNode, indent+1);
            printIndentln(indent, "}");
        }
    }
    public class DoInit extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            Tree<?> typeNode = node.get(Symbol.unique("type"));
            Tree<?> varNode = node.get(Symbol.unique("var"));
            Tree<?> exprNode = node.get(Symbol.unique("expr"));
            visit(typeNode, 0);
            print(" ");
            visit(varNode, 0);
            print("=");
            visit(exprNode, 0);
        }
    }
    public class While extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            Tree<?> condNode = node.get(Symbol.unique("cond"));
            Tree<?> blockNode = node.get(Symbol.unique("block"));
            printIndent(indent, "while (");
            visit(condNode, 0);
            println(")");
            visit(blockNode, indent);
        }
    }
    public class Rematch extends DefaultVisitor {
        private final boolean isDirectGotoEnabled(){
            return compileMode == CompileMode.Instruction &&
                   option.getXOption().getOption(XOption.AvailableOptions.GEN_ADD_TYPELABEL, false) &&
                   option.getXOption().getOption(XOption.AvailableOptions.GEN_DIRECT_GOTO, false);
        }
        private final VMDataType[] getUniqueVMDTVec(SyntaxTree node, String[] params){
            TypeMapSet headDict = node.getHeadDict().select(java.util.Arrays.asList(params));
            if(headDict == null) return null;
            Set<TypeMap> typeMaps = headDict.getTypeMapSet();
            if(typeMaps.isEmpty()) return null;
            int length = params.length;
            TypeMap typeMap = null;
            for(TypeMap t : typeMaps){
                if(typeMap == null){
                    typeMap = t;
                    continue;
                }
                typeMap = typeMap.lub(t);
            }
            VMDataType[] vec = new VMDataType[length];
            for(int i=0; i<length; i++){
                String param = params[i];
                AstType astType = typeMap.get(param);
                if(astType instanceof JSValueVMType)
                    vec[i] = ((JSValueVMType)astType).getVMDataType();
                else
                    vec[i] = null;
            }
            for(int i=0; i<length; i++){
                if(vec[i] != null) {
                    /* test code */
                    // System.err.println("Direct... : "+typeMaps.toString());
                    // System.err.println("Lubed TypeMap is... : "+typeMap.toString());
                    // System.err.println("vec is... : "+Arrays.toString(vec));
                    // System.err.println("params is... : "+Arrays.toString(params));
                    return vec;
                }
            }
            return null;
        }
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            Tree<?> targetNode = node.get(Symbol.unique("label"));
            String target = targetNode.toText();
            String[] rematchParams = new String[node.size()-1];
            for(int i=1; i<node.size(); i++)
                rematchParams[i-1] = node.get(i).toText();

            println("{");
            for (int i = matchStack.size() - 1; i >= 0; i--) {
                MatchRecord mr = matchStack.elementAt(i);
                if (mr.hasMatchLabelOf(target)) {
                    for (int j = 0; j < mr.opNames.length; j++) {
                        Tree<?> argNode = node.get(j + 1);
                        print("JSValue tmp"+j+" = ");
                        visit(argNode, 0);
                        println(";");
                    }
                    for (int j = 0; j < mr.opNames.length; j++)
                        println(mr.opNames[j]+" = "+"tmp"+j+";");
                    if(isDirectGotoEnabled()){
                        VMDataType[] uniqueVMDTVec = getUniqueVMDTVec((SyntaxTree)node, rematchParams);
                        if(uniqueVMDTVec != null){
                            println("/* DIRECT GOTO */");
                            print("goto TL"+mr.getFunctionName());
                            for(VMDataType vmt : uniqueVMDTVec){
                                print("_");
                                if(vmt == null)
                                    print("any");
                                else
                                    print(vmt.toString());
                            }
                            println(";");
                            println("}");
                            return;
                        }
                    }
                    println("goto "+mr.getHeadLabel()+";");
                    println("}");
                    return;
                }
            }
            throw new Error("no rematch target:"+ target);
        }
    }

    public class Trinary extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            Tree<?> condNode = node.get(Symbol.unique("cond"));
            Tree<?> thenNode = node.get(Symbol.unique("then"));
            Tree<?> elseNode = node.get(Symbol.unique("else"));
            visit(condNode, 0);
            print(" ? ");
            visit(thenNode, 0);
            print(" : ");
            visit(elseNode, 0);
        }
    }
    public class Or extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "||");
        }
    }
    public class And extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "&&");
        }
    }
    public class BitwiseOr extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "|");
        }
    }
    public class BitwiseXor extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "^");
        }
    }
    public class BitwiseAnd extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "&");
        }
    }
    public class Equals extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "==");
        }
    }
    public class NotEquals extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "!=");
        }
    }
    public class LessThanEquals extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "<=");
        }
    }
    public class GreaterThanEquals extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, ">=");
        }
    }
    public class LessThan extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "<");
        }
    }
    public class GreaterThan extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, ">");
        }
    }
    public class LeftShift extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "<<");
        }
    }
    public class RightShift extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, ">>");
        }
    }
    public class Add extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "+");
        }
    }
    public class Sub extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "-");
        }
    }
    public class Mul extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "*");
        }
    }
    public class Div extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "/");
        }
    }
    public class Mod extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printBinaryOperator(node, "%");
        }
    }
    public class Plus extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printUnaryOperator(node, "+");
        }
    }
    public class Minus extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printUnaryOperator(node, "-");
        }
    }
    public class Compl extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printUnaryOperator(node, "~");
        }
    }
    public class Not extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            printUnaryOperator(node, "!");
        }
    }
    public class FunctionCall extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            SyntaxTree expandedNode = ((SyntaxTree)node).getExpandedTree();
            if(expandedNode != null){
                // INLINE EXPANSION PRINT ******************************************
                /*
                System.err.println("Function-Inline-Expand:");
                System.err.println("Original:"+node.toString());
                System.err.println("Expanded:"+expandedNode.toString());
                */
                visit(expandedNode, indent);
                return;
            }
            String functionName = node.get(0).toText();
            visit(node.get(0), 0);
            print("(");
            if(!FunctionTable.contains(functionName)){
                throw new Error("FunctionTable is broken: not has "+functionName);
            }
            Tree<?> argsNode = node.get(1);
            if(FunctionTable.hasAnnotations(functionName, FunctionAnnotation.needContext)){
                print("context");
                if(argsNode.size() != 0){
                    print(", ");
                }
            }
            visit(argsNode, 0);
            print(")");
        }
    }
    public class ArgList extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            int i;
            for (i = 0; i < node.size() - 1; i++) {
                visit(node.get(i), 0);
                print(", ");
            }
            if (node.size() != 0) {
                visit(node.get(node.size() - 1), 0);
            }
        }
    }

//    public class FieldAccess extends DefaultVisitor {
//        private void pointerPrint(Tree<?> recvNode, Tree<?> fieldNode) throws Exception {
//            print("*(");
//            valuePrint(recvNode, fieldNode);
//            print(")");
//        }
//        private void valuePrint(Tree<?> recvNode, Tree<?> fieldNode) throws Exception {
//            visit(recvNode, 0);
//            print(".");
//            visit(fieldNode, 0);
//        }
//        @Override
//        public void accept(Tree<?> node, int indent) throws Exception {
//            SyntaxTree recvNode = (SyntaxTree) node.get(Symbol.unique("recv"));
//            SyntaxTree fieldNode = (SyntaxTree) node.get(Symbol.unique("field"));
//            ExprTypeSet exprTypeSet = recvNode.getExprTypeSet();
//            if(exprTypeSet.getTypeSet().size() != 1){
//                throw new Error("Illigal field access");
//            }
//            AstType type = exprTypeSet.getOne();
//            if(!(type instanceof AstMappingType)){
//                throw new Error("Illigal field access");
//            }
//            AstMappingType mtype = (AstMappingType)type;
//            String fieldName = fieldNode.toText();
//            Set<String> annotaions = mtype.getFieldAnnotations(fieldName);
//            if(annotaions != null){
//                if(annotaions.contains("val")){
//                    valuePrint(recvNode, fieldNode);
//                    return;
//                }
//            }
//            pointerPrint(recvNode, fieldNode);
//        }
//    }

    public class FieldAccess extends DefaultVisitor {
        // private void printPointerFieldAccess(Tree<?> recvNode, Tree<?> fieldNode, AstMappingType mappingType, AstBaseType fieldType) throws Exception{
        //     print("*(");
        //     printFieldAccess(recvNode, fieldNode, mappingType, fieldType);
        //     print(")");
        // }
        // private void printFieldAccess(Tree<?> recvNode, Tree<?> fieldNode, AstMappingType mappingType, AstBaseType fieldType) throws Exception{
        //     visit(recvNode, 0);
        //     print(mappingType.getAccessOperator());
        //     visit(fieldNode, 0);
        // }
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            SyntaxTree recvNode = (SyntaxTree) node.get(Symbol.unique("recv"));
            SyntaxTree fieldNode = (SyntaxTree) node.get(Symbol.unique("field"));
            ExprTypeSet exprTypeSet = recvNode.getExprTypeSet();
            if(exprTypeSet.getTypeSet().size() != 1)
                throw new Error("Illigal field access");
            AstType type = exprTypeSet.getOne();
            if(!(type instanceof AstMappingType))
                throw new Error("Illigal field access");
            AstMappingType mappingType = (AstMappingType)type;
            // AstBaseType fieldType = mappingType.getFieldType(fieldNode.toText());
            // boolean isPointerAccess = false; //fieldType instanceof AstComplexType && !(((AstComplexType)fieldType).hasValAnnotation());
            // if(isPointerAccess)
            // printPointerFieldAccess(recvNode, fieldNode, mappingType, fieldType);
            // else
            // printFieldAccess(recvNode, fieldNode, mappingType, fieldType);
            visit(recvNode, 0);
            print(mappingType.getAccessOperator());
            visit(fieldNode, 0);
        }
    }

    public class LeftHandField extends FieldAccess{
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            super.accept(node, indent);
        }
    }

    public class _Float extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            print(node.toText());
        }
    }
    public class _Integer extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            print(node.toText());
        }
    }
    public class _String extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            print("\"");
            print(node.toText());
            print("\"");
        }
    }
    public class _Character extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            print("\'");
            print(node.toText());
            print("\'");
        }
    }
    public class _True extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            print("1");
        }
    }
    public class _False extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            print("0");
        }
    }

    public class Name extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            String name = node.toText();
            if(CConstantTable.contains(name)){
                print(CConstantTable.get(name));
            }else{
                print(name);
            }
        }
    }
    public class JSValueTypeName extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            print("JSValue");
        }
    }
    public class UserTypeName extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            AstBaseType type = (AstBaseType)AstType.nodeToType((SyntaxTree)node);
            print(type.getCCodeName());
            if(type instanceof AstComplexType && !((AstComplexType)type).hasValAnnotation())
                print("*");
        }
    }
    public class Ctype extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            print(((AstPrimitiveType)AstType.getPrimitiveType(node.toText())).getCCodeName());
        }
    }
    public class CValue extends DefaultVisitor {
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            print("\"");
            print(node.toText());
            print("\"");
        }
    }
    public class TypeArray extends DefaultVisitor{
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            visit(node.get(Symbol.unique("type")), indent);
            boolean valFlag = false;
            if(node.has(Symbol.unique("arraymodifier"))){
                Tree<?> modifiersNode = node.get(Symbol.unique("arraymodifier"));
                for(Tree<?> modifierNode : modifiersNode){
                    if(modifierNode.toText().equals("val")){
                        valFlag = true;
                        break;
                    }
                }
            }
            if(valFlag)
                print("[]");
            else
                print("*");
        }
    }
    public class ArrayIndex extends DefaultVisitor{
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            visit(node.get(Symbol.unique("recv")), indent);
            print("[");
            visit(node.get(Symbol.unique("index")), indent);
            print("]");
        }
    }

    public class LeftHandIndex extends ArrayIndex{
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            super.accept(node, indent);
        }
    }

    public class NativeCode extends ArrayIndex{
        @Override
        public void accept(Tree<?> node, int indent) throws Exception {
            print(node.getValue());
        }
    }
}
