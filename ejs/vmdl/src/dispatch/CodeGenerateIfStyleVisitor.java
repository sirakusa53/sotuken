/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package dispatch;

import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

import dispatch.DecisionDiagram.HTNode;
import dispatch.DecisionDiagram.Leaf;
import dispatch.DecisionDiagram.Node;
import dispatch.DecisionDiagram.PTNode;
import dispatch.DecisionDiagram.TagPairNode;
import type.VMRepType;
import type.VMRepType.HT;
import type.VMRepType.PT;
import vmdlc.XOption;

class CodeGenerateIfStyleVisitor extends CodeGenerateVisitor {
    static boolean USE_GOTO = true;
    static boolean PAD_CASES = true;
    static boolean USE_DEFAULT = false;  // add default by the same strategy as -old (exclusive to PAD_CASES)
    static boolean DEBUG_COMMENT = true;

    static class CCodeHelper {
        static String getPTDeclaration(String var) {
            return "unsigned int ptag_of_"+var+" = "+"get_ptag("+var+").v;\n";
        }
        static String getHTDeclaration(String var) {
            return "unsigned int htag_of_"+var+" = "+"get_htag("+var+").v;\n";
        }
        static String getPTConditionalExpression(String var, PT tag){
            return "ptag_of_"+var+"=="+tag.getValueName();
        }
        static String getHTConditionalExpression(String var, HT tag){
            return "htag_of_"+var+"=="+tag.getValueName();
        }
    }

    XOption option;
    StringBuffer sb = new StringBuffer();
    Macro tagMacro;
    String[] varNames;
    Map<Node, String> gotoLabels = new TreeMap<Node, String>();
    Map<Node, Set<String>> typeLabels;
    String labelPrefix;

    public CodeGenerateIfStyleVisitor(String[] varNames, Macro tagMacro, XOption option, Map<Node, Set<String>> typeLabels, String labelPrefix) {
        super(varNames, tagMacro, option, typeLabels, labelPrefix);
        this.varNames = varNames;
        this.tagMacro = tagMacro;
        this.typeLabels = typeLabels;
        this.option = option;
        USE_GOTO = option.getOption(XOption.AvailableOptions.GEN_USE_GOTO, USE_GOTO);
        PAD_CASES = option.getOption(XOption.AvailableOptions.GEN_PAD_CASES, PAD_CASES);
        USE_DEFAULT = option.getOption(XOption.AvailableOptions.GEN_USE_DEFAULT, USE_DEFAULT);
        DEBUG_COMMENT = option.getOption(XOption.AvailableOptions.GEN_DEBUG_COMMENT, DEBUG_COMMENT);
        this.labelPrefix = labelPrefix;
    }

    @Override
    public String toString() {
        if (option.getOption(XOption.AvailableOptions.GEN_MAGIC_COMMENT, false)) {
            return sb.toString() +
                    "/* Local Variables: */\n" +
                    "/* mode: c */\n" +
                    "/* c-basic-offset: 4 */\n" +
                    "/* End: */\n";
        } else
            return sb.toString();
    }

    boolean processSharedNode(Node node) {
        if (USE_GOTO) {
            String label = gotoLabels.get(node);
            if (label != null) {
                sb.append("goto ").append(label).append(";\n");
                return true;
            }
            label = tagMacro.getLabel();
            gotoLabels.put(node, label);
            sb.append(label).append(": __attribute__((unused));\n");
        }
        return false;
    }

    private void addTypeLabels(Node node) {
        if (typeLabels != null) {
            Set<String> labels = typeLabels.get(node);
            if (labels == null)
                return;
            sb.append("\n");
            for (String label: labels)
                sb.append("TL").append(labelPrefix).append(label).append(": __attribute__((unused));\n");
        }
    }

    @Override
    Void visitLeaf(Leaf node) {
        sb.append("{");
        if (DEBUG_COMMENT) {
            sb.append(" //");
            for (VMRepType rt: node.getRule().getVMRepTypes())
                sb.append(" ").append(rt.getName());
            sb.append(" ").append(node);
        }
        sb.append('\n');
        if (processSharedNode(node)){
            sb.append("}\n");
            return null;
        }
        addTypeLabels(node);
        sb.append(node.getRule().getHLRule().action).append("}\n");
        return null;
    }
    @Override
    Void visitTagPairNode(TagPairNode node) {
        throw new Error("InternalError: The TagPairNode have not been supported in Xgen:if_style mode.");
    }
    @Override
    Void visitPTNode(PTNode node) {
        TreeMap<Node, TreeSet<PT>> childToTags = node.getChildToTagsMap();
        sb.append("{");
        if (DEBUG_COMMENT)
            sb.append(" // "+node+"("+childToTags.size()+")");
        sb.append('\n');
        if (processSharedNode(node)){
            sb.append("}\n");
            return null;
        }
        addTypeLabels(node);
        sb.append("{\n");
        
        String varName = varNames[node.getOpIndex()];
        sb.append(CCodeHelper.getPTDeclaration(varNames[node.getOpIndex()]));

        Node defaultChild = null;
        int defaultChildCases = 0;
        for (Node child: childToTags.keySet()) {
            TreeSet<?> tags = childToTags.get(child);
            if (tags.size() > defaultChildCases) {
                defaultChild = child;
                defaultChildCases = tags.size();
            }
        }
        boolean isFirstNode = true;
        for (Node child: childToTags.keySet()) {
            if(child == defaultChild) continue;
            if(isFirstNode)
                isFirstNode = false;
            else
                sb.append("else ");
            TreeSet<PT> tags = childToTags.get(child);
            int tagSize = tags.size();
            String[] conds = new String[tagSize];
            int i = 0;
            for (PT tag: childToTags.get(child))
                conds[i++] = CCodeHelper.getPTConditionalExpression(varName, tag);
            sb.append("if("+String.join("||", conds)+")");
            sb.append("\n");
            child.accept(this);
        }
        if(defaultChild != null){
            if(!isFirstNode)
                sb.append("else ");
            defaultChild.accept(this);
        }
        sb.append("}}");
        if (DEBUG_COMMENT)
            sb.append(" // "+node);
        sb.append('\n');
        return null;
    }
    @Override
    Void visitHTNode(HTNode node) {
        TreeMap<Node, TreeSet<HT>> childToTags = node.getChildToTagsMap();
        sb.append("{");
        if (DEBUG_COMMENT)
            sb.append(" // "+node+"("+childToTags.size()+")");
        sb.append('\n');
        if (processSharedNode(node)){
            sb.append("}\n");
            return null;
        }
        addTypeLabels(node);
        sb.append("{\n");
        if (node.isNoHT()) {
            node.getChild().accept(this);
            return null;
        }
        String varName = varNames[node.getOpIndex()];
        sb.append(CCodeHelper.getHTDeclaration(varNames[node.getOpIndex()]));

        Node defaultChild = null;
        int defaultChildCases = 0;
        for (Node child: childToTags.keySet()) {
            TreeSet<?> tags = childToTags.get(child);
            if (tags.size() > defaultChildCases) {
                defaultChild = child;
                defaultChildCases = tags.size();
            }
        }
        boolean isFirstNode = true;
        for (Node child: childToTags.keySet()) {
            if(child == defaultChild) continue;
            if(isFirstNode)
                isFirstNode = false;
            else
                sb.append("else ");
            TreeSet<HT> tags = childToTags.get(child);
            int tagSize = tags.size();
            String[] conds = new String[tagSize];
            int i = 0;
            for (HT tag: childToTags.get(child))
                conds[i++] = CCodeHelper.getHTConditionalExpression(varName, tag);
            sb.append("if("+String.join("||", conds)+")");
            sb.append("\n");
            child.accept(this);
        }
        if(defaultChild != null){
            if(!isFirstNode)
                sb.append("else ");
            defaultChild.accept(this);
        }
        sb.append("}}");
        if (DEBUG_COMMENT)
            sb.append(" // "+node);
        sb.append('\n');
        return null;
    }
}