package vmdlc;

import java.util.HashMap;
import java.util.Map;

import nez.ast.Symbol;
import nez.ast.Tree;
import nez.ast.TreeVisitorMap;
import vmdlc.MatchParamsConstructVisitor.DefaultVisitor;

public class MatchParamsConstructVisitor extends TreeVisitorMap<DefaultVisitor>{
    Map<String, String[]> matchParams = new HashMap<>();
    public MatchParamsConstructVisitor(){
        init(MatchParamsConstructVisitor.class, new DefaultVisitor());
    }

    public Map<String, String[]> start(Tree<?> node){
        try{
            for (Tree<?> chunk : node){
                visit(chunk);
            }
            return matchParams;
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

    public class Match extends DefaultVisitor{
        @Override
        public void accept(Tree<?> node) throws Exception{
            MatchProcessor mp = new MatchProcessor((SyntaxTree)node);
            SyntaxTree labelNode = (SyntaxTree)node.get(Symbol.unique("label"), null);
            if(labelNode != null)
                matchParams.put(labelNode.toText(), mp.getFormalParams());
            super.accept(node);
        }
    }
}