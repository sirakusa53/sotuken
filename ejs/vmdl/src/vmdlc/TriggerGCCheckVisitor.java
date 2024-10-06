package vmdlc;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Stack;

import nez.ast.Symbol;
import nez.ast.TreeVisitorMap;
import type.AstType;
import type.CConstantTable;
import type.FunctionAnnotation;
import type.FunctionTable;
import type.TypeMap;
import type.TypeMapSet;
import vmdlc.Option.CompileMode;
import vmdlc.TriggerGCCheckVisitor.DefaultVisitor;
import vmdlc.TriggerGCCheckVisitor.BlockExpansionMap.BlockExpansionRequsets;
import vmdlc.TriggerGCCheckVisitor.BlockExpansionMap.Entry;

public class TriggerGCCheckVisitor extends TreeVisitorMap<DefaultVisitor> {
    static class StrictUniqueList<E> extends ArrayList<E>{
        public StrictUniqueList(int initialCapacity){
            super(initialCapacity);
        }
        @Override
        public boolean contains(Object o){
            for(E e : this){
                if(e == o) return true;
            }
            return false;
        }
        @Override
        public boolean add(E e){
            if(!contains(e))
                super.add(e);
            return true;
        }
        @Override
        public boolean addAll(Collection<? extends E> c){
            for(E e : c)
                add(e);
            return true;
        }
    }
    static class StrictMap<K,V> {
        private List<K> keyList;
        private List<V> valueList;

        public StrictMap(int initialCapacity){
            this.keyList = new ArrayList<K>(initialCapacity);
            this.valueList = new ArrayList<V>(initialCapacity);
        }
        public StrictMap(){
            this.keyList = new ArrayList<K>();
            this.valueList = new ArrayList<V>();
        }
        public int size(){
            return keyList.size();
        }
        private int keyIndexOf(K o){
            int size = this.size();
            for(int i=0; i<size; i++){
                if(o == keyList.get(i)) return i;
            }
            return -1;
        }
        public void put(K key, V value){
            int index = this.keyIndexOf(key);
            if(index == -1){
                keyList.add(key);
                valueList.add(value);
            }else{
                keyList.remove(index);
                valueList.remove(index);
                keyList.add(index, key);
                valueList.add(index, value);
            }
        }
        public V get(K key){
            int index = keyIndexOf(key);
            if(index == -1 || index >= valueList.size()) return null;
            return valueList.get(index);
        }
        public Collection<V> values(){
            return valueList;
        }
        public Collection<K> keys(){
            return keyList;
        }
    }

    static class GCFunctionGenerator{
        public SyntaxTree genFunctionCall(String functionName, String arg){
            return ASTHelper.generateExpressionStatement(ASTHelper.generateFunctionCall(functionName, new SyntaxTree[]{ASTHelper.generateName(arg)}));
        }
        public SyntaxTree genFunctionCall(String functionName, String[] args){
            return ASTHelper.generateExpressionStatement(ASTHelper.generateFunctionCall(functionName, args));
        }
        public SyntaxTree getGCPushExprStmt(List<String> names, int start, int length){
            String functionName = (length == 1) ? "GC_PUSH" : ("GC_PUSH"+length);
            SyntaxTree exprStmt = genFunctionCall(functionName, names.subList(start, start+length).toArray(new String[0]));
            return exprStmt;
        }
        public SyntaxTree getGCPopExprStmt(List<String> names, int start, int length){
            String functionName = (length == 1) ? "GC_POP" : ("GC_POP"+length);
            SyntaxTree exprStmt = genFunctionCall(functionName, names.subList(start, start+length).toArray(new String[0]));
            return exprStmt;
        }
    }

    static class BlockExpansionMap{
        /* 
         * Entry is a pair of block statements specified in key and BlockExpansionRequests for the statements it has.
         * Note that target statements in BlockExpansionRequests is expected to belonging to the key block statement.
         */
        static class Entry{
            private SyntaxTree key;
            private BlockExpansionRequsets value;

            public Entry(SyntaxTree key, BlockExpansionRequsets value){
                this.key = key;
                this.value = value;
            }
            public SyntaxTree getKey(){
                return key;
            }
            public BlockExpansionRequsets getValue(){
                return value;
            }
        }
        /* 
         * BlockExpansionRequests expresses requests to expand a statement in a block into a sequence of other statements.
         * NOTE: It is mainly intended to be used to insert GC_PUSH/POP before and after a statement.
         * 
         *                        ..(prev)..
         *   ..(prev)..           stmts[0];
         *   target;       --->   stmts[1];
         *   ..(next)..             ...
         *                        stmts[n];
         *                        ..(next)..
         */
        static class BlockExpansionRequsets{
            StrictMap<SyntaxTree, SyntaxTree[]> requests = new StrictMap<>();

            public void put(SyntaxTree target, SyntaxTree[] stmts){
                requests.put(target, stmts);
            }
            public SyntaxTree[] get(SyntaxTree target){
                return requests.get(target);
            }
            public int size(){
                return requests.size();
            }
            public int requestSize(){
                Collection<SyntaxTree[]> values = requests.values();
                int sum = 0;
                for(SyntaxTree[] stmts : values){
                    sum += stmts.length;
                }
                return sum;
            }
            public int size(SyntaxTree[] targets){
                int sum = 0;
                for(SyntaxTree stmt : targets){
                    SyntaxTree[] to = requests.get(stmt);
                    if(to == null) continue;
                    sum++;
                }
                return sum;
            }
            public int requestSize(SyntaxTree[] targets){
                int sum = 0;
                for(SyntaxTree stmt : targets){
                    SyntaxTree[] to = get(stmt);
                    if(to == null) continue;
                    sum += to.length;
                }
                return sum;
            }
            public Collection<SyntaxTree> keys(){
                return requests.keys();
            }
        }

        List<Entry> list = new ArrayList<>();

        public void put(SyntaxTree key, BlockExpansionRequsets value){
            list.add(new Entry(key, value));
        }
        public BlockExpansionRequsets get(SyntaxTree key){
            for(Entry entry : list){
                if(key == entry.getKey())
                    return entry.getValue();
            }
            return null;
        }
        public Collection<Entry> entryCollection(){
            return list;
        }
        private static SyntaxTree[] generateExpandedBlockInner(SyntaxTree[] original, BlockExpansionRequsets requests, Collection<SyntaxTree> expanded){
            int originalSize = original.length;
            int additionalSize = requests.requestSize(original) - requests.size(original);
            int expandedSize = originalSize + additionalSize;
            SyntaxTree[] expandedStmts = new SyntaxTree[expandedSize];
            int j = 0;
            for(int i=0; i<originalSize; i++){
                SyntaxTree[] stmts = requests.get(original[i]);
                if(stmts == null || expanded.contains(original[i])){
                    expandedStmts[j++] = original[i];
                    continue;
                }
                expanded.add(original[i]);
                for(SyntaxTree stmt : stmts){
                    expandedStmts[j++] = stmt;
                }
            }
            if(j == originalSize)
                return original;
            return generateExpandedBlockInner(expandedStmts, requests, expanded);
        }
        public static SyntaxTree generateExpandedBlock(SyntaxTree original, BlockExpansionRequsets requests){
            if(original == null || original.size() == 0) return original;
            SyntaxTree[] originalStmts = (SyntaxTree[]) original.getSubTree();
            return ASTHelper.generateBlock(generateExpandedBlockInner(originalStmts, requests, new StrictUniqueList<SyntaxTree>(requests.requestSize())));
        }
    }

    Map<String, String[]> matchParams;
    GCFunctionGenerator gcFunctionGenerator = new GCFunctionGenerator();
    BlockExpansionMap blockExpansionMap = new BlockExpansionMap();
    BlockExpansionRequsets currentRequests;
    CompileMode compileMode;
    Collection<AstType> exceptType;
    List<SyntaxTree> triggerGCStmtList;
    Map<ControlFlowGraphNode, List<SyntaxTree>> triggerGCStmtListMap = new HashMap<>();

    public TriggerGCCheckVisitor() {
        init(TriggerGCCheckVisitor.class, new DefaultVisitor());
    }

    public void start(ControlFlowGraphNode node, CompileMode compileMode, Map<String, String[]> matchParams) {
        this.compileMode = compileMode;
        this.matchParams = matchParams;
        exceptType = new HashSet<>(3);
        exceptType.add(AstType.getPrimitiveType("Fixnum"));
        exceptType.add(AstType.getPrimitiveType("Special"));
        exceptType.add(AstType.BOT);
        try {
            /* Compute live variables at head and tail for all CFG nodes. */
            Queue<ControlFlowGraphNode> queue = new ArrayDeque<>();
            queue.add(node);
            while(!queue.isEmpty()){
                ControlFlowGraphNode target = queue.remove();
                List<String> newTailLive = new ArrayList<>();
                Collection<ControlFlowGraphNode> nexts = target.getNext();
                for(ControlFlowGraphNode cfgn : nexts){
                    Collection<String> cfgnHeadLive = cfgn.getHeadLive();
                    if(cfgnHeadLive == null) continue;
                    for(String name : cfgnHeadLive){
                        if(newTailLive.contains(name)) continue;
                        newTailLive.add(name);
                    }
                }
                if(target.hasTailLive()){
                    Collection<String> prevTailLiveSet = new HashSet<>(target.getTailLive());
                    Collection<String> newTailLiveSet = new HashSet<>(newTailLive);
                    if(prevTailLiveSet.equals(newTailLiveSet)) continue;
                }
                target.setTailLive(new ArrayList<>(newTailLive));
                currentRequests = new BlockExpansionRequsets();
                SyntaxTree belongingBlock = target.getBelongingBlock();
                if(belongingBlock != null){
                    BlockExpansionRequsets recorded = blockExpansionMap.get(belongingBlock);
                    if(recorded != null)
                        currentRequests = recorded;
                    blockExpansionMap.put(target.getBelongingBlock(), currentRequests);
                }
                triggerGCStmtList = new ArrayList<>(target.size());
                List<SyntaxTree> stmts = target.getStatementList();
                int size = stmts.size();
                for(int i=size-1; i>=0; i--){
                    SyntaxTree stmt = stmts.get(i);
                    if(hasTriggerGC(stmt)){
                        updateWithTriggerGC(stmt, newTailLive);
                    }
                    else
                        update(stmt, newTailLive);
                }
                target.setHeadLive(newTailLive);
                
                /* Update triggerGCStmtListMap */
                List<SyntaxTree> oldTriggerGCStmtList = triggerGCStmtListMap.get(target);
                if(oldTriggerGCStmtList == null){
                    oldTriggerGCStmtList = new StrictUniqueList<>(triggerGCStmtList.size());
                }
                oldTriggerGCStmtList.addAll(triggerGCStmtList);
                triggerGCStmtListMap.put(target, oldTriggerGCStmtList);

                Collection<ControlFlowGraphNode> prevs = target.getPrev();
                for(ControlFlowGraphNode prev : prevs){
                    if(prev == ControlFlowGraphNode.enter) continue;
                    queue.add(prev);
                }
            }

            for(java.util.Map.Entry<ControlFlowGraphNode, List<SyntaxTree>> entry : triggerGCStmtListMap.entrySet()){
                ControlFlowGraphNode target = entry.getKey();
                currentRequests = new BlockExpansionRequsets();
                SyntaxTree belongingBlock = target.getBelongingBlock();
                if(belongingBlock != null){
                    BlockExpansionRequsets recorded = blockExpansionMap.get(belongingBlock);
                    if(recorded != null)
                        currentRequests = recorded;
                    blockExpansionMap.put(target.getBelongingBlock(), currentRequests);
                }
                List<SyntaxTree> triggerGCStmtList = entry.getValue();
                Collections.reverse(triggerGCStmtList);
                insertGCoperation(target, triggerGCStmtList);
            }

            /* Expand block */
            for(Entry entry : blockExpansionMap.entryCollection()){
                SyntaxTree originalBlock = entry.getKey();
                SyntaxTree expandedBlock = BlockExpansionMap.generateExpandedBlock(originalBlock, entry.getValue());
                if(originalBlock == expandedBlock) continue;
                // Expect originalBlock has no expand candidate
                originalBlock.addExpandedTreeCandidate(expandedBlock);
            }
        }catch(Exception e) {
            e.printStackTrace();
            throw new Error("visitor thrown an exception");
        }
    }

    public void pushPopGenerate(SyntaxTree node, List<String> gcPushList, List<String> gcPopList){
        int pushListSize = gcPushList.size();
        int popListSize = gcPopList.size();
        int pushStmtSize = (pushListSize == 0) ? 0 : (pushListSize - 1) / 7 + 1;
        int popStmtSize = (popListSize == 0) ? 0 : (popListSize - 1) / 7 + 1;
        int stmtsSize = pushStmtSize+popStmtSize+1;
        SyntaxTree[] stmts = new SyntaxTree[stmtsSize];
        int i = 0;
        for(int j=0; j<pushListSize; j+=7){
            stmts[i] = gcFunctionGenerator.getGCPushExprStmt(gcPushList, j, (j+7 <= pushListSize) ? 7 : pushListSize-j);
            i++;
        }
        SyntaxTree[] nestSolved = new NestGCTransformVisitor().start(node.dup());
        SyntaxTree transformed = (nestSolved.length == 1) ? nestSolved[0] : ASTHelper.generateBlock(nestSolved);
        stmts[i] = transformed;
        i++;
        for(int j=0; j<popListSize; j+=7){
            stmts[i] = gcFunctionGenerator.getGCPopExprStmt(gcPopList, j, (j+7 <= popListSize) ? 7 : popListSize-j);
            i++;
        }
        currentRequests.put(node, stmts);
    }

    private final List<String> tryGCPop(Stack<String> gcStack, Collection<String> popTarget){
        List<String> poped = new ArrayList<>(popTarget.size());
        while(!popTarget.isEmpty()){
            String peek = gcStack.peek();
            if(popTarget.contains(peek)){
                poped.add(peek);
                gcStack.pop();
                if(gcStack.isEmpty()) break;
                continue;
            }
            break;
        }
        return poped;
    }

    private final void insertGCoperation(ControlFlowGraphNode node, List<SyntaxTree> triggerGCStmtList){
        int size = triggerGCStmtList.size();
        if(size == 0) return;

        /* Construct gcStack at the head of the CFG node */
        Stack<String> gcStack = new Stack<>();
        Collection<String> headLive = node.getHeadLive();
        Collection<String> tailLive = node.getTailLive();
        Collection<String> active = new ArrayList<>(headLive);
        active.retainAll(node.getTailLive());
        headLive.removeAll(tailLive);
        // for(String v : active){
        //     gcStack.push(v);
        // }
        // for(String v : headLive){
        //     gcStack.push(v);
        // }

        /* Compute GC_PUSH/POP for the first statement */
        SyntaxTree stmt0 = triggerGCStmtList.get(0);
        List<String> push0 = new ArrayList<>(triggerGCStmtList.get(0).getGCRootRequireList());
        active.retainAll(push0);
        headLive.retainAll(push0);
        headLive.removeAll(active);
        List<String> others = new ArrayList<>(push0);
        others.removeAll(active);
        others.removeAll(headLive);
        for(String v : active)
            gcStack.push(v);
        for(String v : headLive)
            gcStack.push(v);
        for(String v : others)
            gcStack.push(v);
        List<String> pop0;
        if(size == 1){
            pushPopGenerate(stmt0, push0, push0);
            // System.err.println("0:");
            // System.err.println("stmt:"+stmt0.toText()+" (at line "+stmt0.getLineNum()+")");
            // System.err.println("live:"+stmt0.getGCRootRequireList());
            // System.err.println("gcStack:"+gcStack.toString()+"\n---");
            return;
        }else{
            pop0 = new ArrayList<>(push0);
            pop0.removeAll(triggerGCStmtList.get(1).getGCRootRequireList());
            pushPopGenerate(stmt0, push0, tryGCPop(gcStack, pop0));
        }

        /* Compute GC_PUSH/POP for intermediate statements */
        SyntaxTree stmt = stmt0;
        SyntaxTree next = triggerGCStmtList.get(1);
        // System.err.println("0:");
        // System.err.println("stmt:"+stmt.toText()+" (at line "+stmt.getLineNum()+")");
        // System.err.println("live:"+stmt.getGCRootRequireList());
        // System.err.println("gcStack:"+gcStack.toString());
        for(int i=1; i<size-1; i++){
            stmt = next;
            next = triggerGCStmtList.get(i+1);
            // System.err.println(i+":");
            // System.err.println("stmt:"+stmt.toText()+" (at line "+stmt.getLineNum()+")");
            // System.err.println("live:"+stmt.getGCRootRequireList());
            // System.err.println("gcStack:"+gcStack.toString());
            List<String> gcTargets = stmt.getGCRootRequireList();
            List<String> nextTargets = next.getGCRootRequireList();
            List<String> gcPushList = new ArrayList<>(gcTargets);
            gcPushList.removeAll(gcStack);
            for(String v : gcPushList){
                gcStack.push(v);
            }
            List<String> gcPopList = new ArrayList<>(gcTargets);
            gcPopList.removeAll(nextTargets);
            Collections.reverse(gcPopList);
            gcPopList = tryGCPop(gcStack, gcPopList);
            pushPopGenerate(stmt, gcPushList, gcPopList);
        }

        /* Compute GC_PUSH/POP for the last statement */
        stmt = next;
        next = triggerGCStmtList.get(size-1);
        // System.err.println((size-1)+":");
        // System.err.println("stmt:"+stmt.toText()+" (at line "+stmt.getLineNum()+")");
        // System.err.println("live:"+stmt.getGCRootRequireList());
        // System.err.println("gcStack:"+gcStack.toString()+"\n---");
        List<String> gcTargets = stmt.getGCRootRequireList();
        List<String> gcPushList = new ArrayList<>(gcTargets);
        gcPushList.removeAll(gcStack);
        for(String v : gcPushList){
            gcStack.push(v);
        }
        List<String> gcPopList = new ArrayList<>(gcStack);
        Collections.reverse(gcPopList);
        pushPopGenerate(stmt, gcPushList, gcPopList);
    }

    private final void updateWithTriggerGC(SyntaxTree node, Collection<String> live) throws Exception{
        find(node.getTag().toString()).updateLiveWithTriggerGC(node, live);
    }

    private final boolean hasTriggerGC(SyntaxTree node) throws Exception{
        return find(node.getTag().toString()).findTriggerGC(node);
    }

    private final void update(SyntaxTree node, Collection<String> live) throws Exception{
        find(node.getTag().toString()).updateLive(node, live);
    }

    /* Updates live variables set and returns variable set which is added to live variables set. */
    private final void update(SyntaxTree node, Collection<String> live, TypeMapSet dict) throws Exception{
        find(node.getTag().toString()).updateLive(node, live, dict);
    }

    public class DefaultVisitor{
        public void updateLiveWithTriggerGC(SyntaxTree node, Collection<String> live) throws Exception{
            updateLive(node, live);
        }
        public void updateLive(SyntaxTree node, Collection<String> live) throws Exception{
            for(SyntaxTree chunk : node){
                update(chunk, live);
            }
        }
        public void updateLive(SyntaxTree node, Collection<String> live, TypeMapSet dict) throws Exception{
            for(SyntaxTree chunk : node){
                update(chunk, live, dict);
            }
        }
        public boolean findTriggerGC(SyntaxTree node) throws Exception{
            for(SyntaxTree chunk : node){
                if(hasTriggerGC(chunk)) return true;
            }
            return false;
        }
    }

    public class Statements extends DefaultVisitor{
        protected void registerGCRequire(SyntaxTree target, List<String> live){
            //target.setGCRootRequireList(new ArrayList<>(live));
            target.setGCRootRequireList(live);
            triggerGCStmtList.add(target);
        }
    }

    public class Declaration extends Statements{
        private final SyntaxTree nestGCTransform(SyntaxTree node, Collection<String> live){
            SyntaxTree[] nestSolved = new NestGCTransformVisitor().start(ASTHelper.clipAssignment(node));
            if(nestSolved.length == 1) return node;
            SyntaxTree[] transformed = {
                ASTHelper.removeInitializer(node),
                ASTHelper.generateBlock(nestSolved)
            };
            currentRequests.put(node, transformed);
            return transformed[1];
        }
        private final void removeLive(SyntaxTree node, Collection<String> live) throws Exception{
            SyntaxTree var = node.get(Symbol.unique("var"));
            String varName = var.toText();
            if(!node.has(Symbol.unique("expr")) && live.contains(varName))
                throw new Error("Illigal live variable analysis status");
            live.remove(varName);
        }
        @Override
        public void updateLiveWithTriggerGC(SyntaxTree node, Collection<String> live) throws Exception{
            List<String> gcRequires = new ArrayList<>(live);
            removeLive(node, gcRequires);
            updateLive(node, live);
            /* Nested GCPUSH/POP transform */
            if(!node.has(Symbol.unique("expr")))
                throw new Error("Illigal live variable analysis status");
            SyntaxTree expr = node.get(Symbol.unique("expr"));
            if(expr == SyntaxTree.PHANTOM_NODE) return;
            SyntaxTree nestSolved = nestGCTransform(node, live);
            registerGCRequire(nestSolved, gcRequires);
        }
        @Override
        public void updateLive(SyntaxTree node, Collection<String> live) throws Exception{
            removeLive(node, live);
            if(!node.has(Symbol.unique("expr"))) return;
            SyntaxTree expr = node.get(Symbol.unique("expr"));
            update(expr, live, node.getTailDict());
        }
    }

    public class Assignment extends Statements{
        /* 
         * JSValue type Variables are not permitted to be reassigned, 
         * so they become non-live variables before the assignment statement.
         */
        private final void removeLive(SyntaxTree node, Collection<String> live) throws Exception{
            SyntaxTree var = node.get(Symbol.unique("left"));
            String varName = var.toText();
            live.remove(varName);
        }
        @Override
        public void updateLiveWithTriggerGC(SyntaxTree node, Collection<String> live) throws Exception{
            List<String> gcRequires = new ArrayList<>(live);
            removeLive(node, gcRequires);
            updateLive(node, live);
            registerGCRequire(node, gcRequires);
        }
        @Override
        public void updateLive(SyntaxTree node, Collection<String> live) throws Exception{
            removeLive(node, live);
            SyntaxTree expr = node.get(Symbol.unique("right"));
            update(expr, live, node.getTailDict());
        }
    }

    public class AssignmentPair extends Statements{
        private final void removeLive(SyntaxTree node, Collection<String> live) throws Exception{
            SyntaxTree pair = node.get(Symbol.unique("left"));
            for(SyntaxTree var : pair){
                String varName = var.toText();
                live.remove(varName);
            }
        }
        @Override
        public void updateLiveWithTriggerGC(SyntaxTree node, Collection<String> live) throws Exception{
            List<String> gcRequires = new ArrayList<>(live);
            removeLive(node, gcRequires);
            updateLive(node, live);
            registerGCRequire(node, gcRequires);
        }
        @Override
        public void updateLive(SyntaxTree node, Collection<String> live) throws Exception{
            removeLive(node, live);
            SyntaxTree expr = node.get(Symbol.unique("right"));
            update(expr, live, node.getTailDict());
        }
    }

    public class ExpressionStatement extends Statements{
        @Override
        public void updateLiveWithTriggerGC(SyntaxTree node, Collection<String> live) throws Exception{
            List<String> gcRequires = new ArrayList<>(live);
            updateLive(node, live);
            registerGCRequire(node, gcRequires);
        }
        @Override
        public void updateLive(SyntaxTree node, Collection<String> live) throws Exception{
            SyntaxTree expr = node.get(0);
            update(expr, live, node.getTailDict());
        }
    }

    public class SpecialExpression extends Statements{
        @Override
        public void updateLiveWithTriggerGC(SyntaxTree node, Collection<String> live) throws Exception{
        }
        @Override
        public void updateLive(SyntaxTree node, Collection<String> live) throws Exception{
            SyntaxTree expr = node.get(0);
            update(expr, live, node.getTailDict());
        }
    }

    private static class DataLocation{
        private static enum Location{
            VMHeap(true), ExemptedVMHeap(false), NonVMHeap(false);

            private boolean requireGCPushPopFlag;

            private Location(boolean requireGCPushPop){
                requireGCPushPopFlag = requireGCPushPop;
            }
            public boolean isRequiredGCPushPop(){
                return requireGCPushPopFlag;
            }
        }

        private Location location = Location.ExemptedVMHeap;

        public void setLocationToVMHeap(){
            if(location == Location.NonVMHeap)
                throw new Error("Illigal data location specification: cannot set to VMHeap");
            location = Location.VMHeap;
        }
        public void setLocationToNonVMHeap(){
            if(location == Location.VMHeap)
                throw new Error("Illigal data location specification: cannot set to Non-VMHeap");
            location = Location.NonVMHeap;
        }
        public boolean isRequiredGCPushPop(){
            return location.isRequiredGCPushPop();
        }
        @Override
        public String toString(){
            return location.toString();
        }
    }

    public class Return extends DefaultVisitor{
        @Override
        public void updateLive(SyntaxTree node, Collection<String> live) throws Exception{
            if(node.size() == 0) return;
            SyntaxTree expr = node.get(0);
            update(expr, live, node.getHeadDict());
        }
    }

    public class Rematch extends DefaultVisitor{
        @Override
        public void updateLive(SyntaxTree node, Collection<String> live) throws Exception{
            int size = node.size();
            String[] formalParams = matchParams.get(node.get(Symbol.unique("label")).toText());
            live.removeAll(Arrays.asList(formalParams));
            for(int i=1; i<size; i++)
                update(node.get(i), live, node.getHeadDict());
        }
    }

    public class Name extends DefaultVisitor{
        private boolean isCConstant(String name){
            return CConstantTable.contains(name);
        }
        private boolean isRequiredGCPushPop(String name, TypeMapSet dict){
            DataLocation dataLocation = new DataLocation();
            for(TypeMap typeMap : dict){
                AstType type = typeMap.get(name);
                if(exceptType.contains(type)) continue;
                if(type.isRequiredGCPushPop())
                    dataLocation.setLocationToVMHeap();
                else
                    dataLocation.setLocationToNonVMHeap();
            }
            return dataLocation.isRequiredGCPushPop();
        }
        @Override
        public void updateLive(SyntaxTree node, Collection<String> live, TypeMapSet dict) throws Exception{
            String name = node.toText();
            if(!isCConstant(name) && isRequiredGCPushPop(name, dict) && !live.contains(name)){
                live.add(name);
            }
        }
        @Override
        public boolean findTriggerGC(SyntaxTree node) throws Exception{
            return false;
        }
    }

    public class FieldAccess extends DefaultVisitor{
        @Override
        public void updateLive(SyntaxTree node, Collection<String> live, TypeMapSet dict) throws Exception{
        }
    }

    public class FunctionCall extends DefaultVisitor{
        @Override
        public void updateLive(SyntaxTree node, Collection<String> live, TypeMapSet dict) throws Exception{
            SyntaxTree args = node.get(Symbol.unique("args"));
            update(args, live, dict);
        }
        @Override
        public boolean findTriggerGC(SyntaxTree node) throws Exception{
            SyntaxTree expandedNode = node.getExpandedTree();
            if(expandedNode != null)
                return hasTriggerGC(expandedNode);
            String functionName = node.get(Symbol.unique("recv")).toText();
            if(!FunctionTable.contains(functionName)){
                ErrorPrinter.error("Cannot find function: "+functionName, node);
            }
            return FunctionTable.hasAnnotations(functionName, FunctionAnnotation.triggerGC) || hasTriggerGC(node.get(Symbol.unique("args")));
        }
    }
}
