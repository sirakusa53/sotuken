package vmdlc;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;

public class ControlFlowGraphNode implements Iterable<SyntaxTree>{
    public static ControlFlowGraphNode enter = new ControlFlowGraphNode(new HashSet<>(0)).setLiveEmpty();
    public static ControlFlowGraphNode exit = new ControlFlowGraphNode(new HashSet<>(0)).setLiveEmpty();

    private Collection<ControlFlowGraphNode> next = new HashSet<>();
    private Collection<ControlFlowGraphNode> prev = new HashSet<>();
    private List<SyntaxTree> statementList = new ArrayList<>();
    private Collection<String> headLocals;
    private Collection<String> tailLocals;

    private Collection<String> initialized = null;
    private List<String> headLive = null;
    private List<String> tailLive = null;

    private SyntaxTree belongingBlock;

    public ControlFlowGraphNode(Collection<String> headLocals){
        this.headLocals = headLocals;
        this.tailLocals = headLocals;
    }
    private ControlFlowGraphNode setLiveEmpty(){
        this.headLive = new ArrayList<>(0);
        return this;
    }
    public void makeEdgeTo(ControlFlowGraphNode node){
        this.addNext(node);
        node.addPrev(this);
    }
    public void makeEdgeFrom(ControlFlowGraphNode[] nodes){
        for(ControlFlowGraphNode node: nodes){
            node.makeEdgeTo(this);
        }
    }
    public void addNext(ControlFlowGraphNode node){
        this.next.add(node);
    }
    public void addPrev(ControlFlowGraphNode node){
        this.prev.add(node);
    }
    public Collection<ControlFlowGraphNode> getNext(){
        return next;
    }
    public Collection<ControlFlowGraphNode> getPrev(){
        return prev;
    }
    public void addStatement(SyntaxTree node){
        statementList.add(node);
    }
    public void addLocals(String name){
        if(tailLocals == headLocals){
            tailLocals = new HashSet<>(headLocals);
        }
        tailLocals.add(name);
    }
    public void setInitialized(Collection<String> c){
        this.initialized = c;
    }
    public boolean isSetInitialized(){
        return initialized != null;
    }
    public Collection<String> getInitialized(){
        return initialized;
    }
    public void setHeadLive(List<String> l){
        this.headLive = l;
    }
    public void setTailLive(List<String> l){
        this.tailLive = l;
    }
    public boolean hasHeadLive(){
        return headLive != null;
    }
    public boolean hasTailLive(){
        return tailLive != null;
    }
    public List<String> getHeadLive(){
        return headLive;
    }
    public List<String> getTailLive(){
        return tailLive;
    }
    public Collection<String> selectValidAtHead(Collection<String> c){
        Collection<String> ret = new HashSet<>();
        for(String s : c){
            if(headLocals.contains(s)){
                ret.add(s);
            }
        }
        return ret;
    }
    public SyntaxTree getHeadStatement(){
        if(statementList.isEmpty()) return null;
        return statementList.get(0);
    }
    public boolean isSetBelongingBlock(){
        return belongingBlock != null;
    }
    public SyntaxTree getBelongingBlock(){
        return belongingBlock;
    }
    public void setBelongingBlock(SyntaxTree node){
        belongingBlock = node;
    }
    public int size(){
        return statementList.size();
    }
    @Override
    public Iterator<SyntaxTree> iterator(){
        return statementList.iterator();
    }
    public List<SyntaxTree> getStatementList(){
        return statementList;
    }
}
