/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package ejsc;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import ejsc.IASTNode.ParameterVarDecl;
import ejsc.IASTNode.VarDecl;
import ejsc.VMImplementation;

public class CodeGenerator extends IASTBaseVisitor {
    static final int THIS_OBJECT_REGISTER = 1;

    static class Continuation {
        Continuation k;
        public void emitBreak(String labelName) {
            k.emitBreak(labelName);
        }
        public void emitContinue(String labelName) {
            k.emitContinue(labelName);
        }
        public void emitReturn(Register r) {
            k.emitReturn(r);
        }
        public void emitThrow(Register r) {
            k.emitThrow(r);
        }
        public void emitEndFunction(Register r) {
            emitReturn(r);
        }
        public void setPrev(Continuation k) {
            this.k = k;
        }
        public Label getExceptionDest() {
            return k.getExceptionDest();
        }
        public Continuation getPrev() {
            return k;
        }
    }

    class LoopContinuation extends Continuation {
        private Label breakLabel, continueLabel;
        private String labelName;
        public LoopContinuation(String labelName, Label breakLabel, Label continueLabel) {
            this.labelName = labelName;
            this.breakLabel = breakLabel;
            this.continueLabel = continueLabel;
        }
        @Override
        public void emitBreak(String name) {
            if (name != null && !labelName.equals(name))
                super.emitBreak(name);
            bcBuilder.push(new IJump(breakLabel));
        }
        @Override
        public void emitContinue(String name) {
            if (name != null && !labelName.equals(name))
                super.emitContinue(name);
            bcBuilder.push(new IJump(continueLabel));
        }
    }

    class SwitchContinuation extends Continuation {
        private Label breakLabel;
        public SwitchContinuation(Label breakLabel) {
            this.breakLabel = breakLabel;
        }
        @Override
        public void emitBreak(String name) {
            if (name != null)
                super.emitBreak(name);
            bcBuilder.push(new IJump(breakLabel));
        }
    }

    class FunctionContinuation extends Continuation {
        boolean topLevel;
        FunctionContinuation(boolean topLevel) {
            this.topLevel = topLevel;
        }
        @Override
        public void emitBreak(String name) {
            throw new Error("No enclosing loop/switch for `break'");
        }
        @Override
        public void emitContinue(String name) {
            throw new Error("No enclosing loop for `continue'");
        }
        @Override
        public void emitReturn(Register r) {
            if (topLevel)
                throw new Error("Top level function cannot return");
            if (r != null)
                bcBuilder.push(new ISeta(r));
            bcBuilder.push(new IRet());
        }
        @Override
        public void emitEndFunction(Register r) {
            if (topLevel)
                bcBuilder.push(new ISeta(r));
            else {
                Register retReg = env.freshRegister();
                bcBuilder.push(new IUndefinedconst(retReg));
                emitReturn(retReg);
            }
        }
        @Override
        public Label getExceptionDest() {
            return null;
        }
        @Override
        public void emitThrow(Register r) {
            bcBuilder.push(new IThrow(r, exLabel()));
        }
    }

    class TryCatchContinuation extends Continuation {
        Label handlerLabel;
        public TryCatchContinuation(Label handlerLabel) {
            this.handlerLabel = handlerLabel;
        }
        @Override
        public void emitBreak(String name) {
            bcBuilder.push(new IPophandler());
            super.emitBreak(name);
        }
        @Override
        public void emitContinue(String name) {
            bcBuilder.push(new IPophandler());
            super.emitContinue(name);
        }
        @Override
        public void emitReturn(Register r) {
            bcBuilder.push(new IPophandler());
            super.emitReturn(r);
        }
        @Override
        public Label getExceptionDest() {
            return handlerLabel;
        }
    }

    class CatchContinuation extends Continuation {
        @Override
        public void emitBreak(String name) {
            bcBuilder.push(new IExitframe());
            super.emitBreak(name);
        }
        @Override
        public void emitContinue(String name) {
            bcBuilder.push(new IExitframe());
            super.emitContinue(name);
        }
    }

    class TryFinallyContinuation extends Continuation {
        Label finallyLabel;
        public TryFinallyContinuation(Label finallyLabel) {
            this.finallyLabel = finallyLabel;
        }
        private void localCall() {
            bcBuilder.push(new IPophandler());
            bcBuilder.push(new ILocalcall(finallyLabel));
        }
        @Override
        public void emitBreak(String name) {
            localCall();
            super.emitBreak(name);
        }
        @Override
        public void emitContinue(String name) {
            localCall();
            super.emitContinue(name);
        }
        @Override
        public void emitReturn(Register r) {
            localCall();
            super.emitReturn(r);
        }
        @Override
        public void emitThrow(Register r) {
            localCall();
            super.emitThrow(r);
        }
        @Override
        public Label getExceptionDest() {
            return finallyLabel;
        }
    }

    class FinallyContinuation extends Continuation {
        @Override
        public void emitBreak(String name) {
            bcBuilder.push(new IPoplocal());
            super.emitBreak(name);
        }
        @Override
        public void emitContinue(String name) {
            bcBuilder.push(new IPoplocal());
            super.emitContinue(name);
        }
        @Override
        public void emitReturn(Register r) {
            bcBuilder.push(new IPoplocal());
            super.emitReturn(r);
        }
        @Override
        public void emitThrow(Register r) {
            bcBuilder.push(new IPoplocal());
            super.emitThrow(r);
        }
    }

    class RegisterManager {
        /* map of register number to interned Register */
        private ArrayList<Register> registers = new ArrayList<Register>();
        private List<Register> argumentRegisters = new ArrayList<Register>();

        private Register allocateRegister(int regNo) {
            int index = regNo - 1;  // register number is 1-origin
            if (registers.size() <= index) {
                registers.ensureCapacity(index + 1);
                for (int i = registers.size(); i <= index; i++)
                    registers.add(new Register(i + 1));
            }
            return registers.get(index);
        }

        public Register getRegister(int regNo) {
            return registers.get(regNo - 1);
        }

        public Register freshRegister() {
            Register r = new Register(registers.size() + 1);
            registers.add(r);
            return r;
        }

        public RegisterManager(IASTFunctionExpression func) {
            /* create input registers */
            allocateRegister(THIS_OBJECT_REGISTER);
            for (ParameterVarDecl decl: func.params)
                allocateRegister(THIS_OBJECT_REGISTER + 1 + decl.getParameterIndex());

            /* allocate registers to not escaping variables */
            for (ParameterVarDecl decl: func.params) {
                IASTNode.VarLoc locx = decl.getLocation();
                if (locx instanceof IASTNode.RegisterVarLoc) {
                    IASTNode.RegisterVarLoc loc = (IASTNode.RegisterVarLoc) locx;
                    loc.setRegisterNo(THIS_OBJECT_REGISTER + 1 + decl.getParameterIndex());
                }
            }
            for (VarDecl decl: func.locals) {
                IASTNode.VarLoc locx = decl.getLocation();
                if (locx instanceof IASTNode.RegisterVarLoc) {
                    IASTNode.RegisterVarLoc loc = (IASTNode.RegisterVarLoc) locx;
                    loc.setRegisterNo(freshRegister().getRegisterNumber());
                }
            }
        }

        public void close() {
            int top = registers.size() + argumentRegisters.size();
            for (int i = 0; i < argumentRegisters.size(); i++)
                argumentRegisters.get(i).setRegisterNumber(top - i);
        }

        public int getNumberOfGPRegisters() {
            return registers.size();
        }
    }

    public static BCBuilder compile(IASTProgram program, VMImplementation vmImpl) {
        BCBuilder bcb = new BCBuilder();
        for (IASTFunctionExpression node: program.programs) {
            CodeGenerator g = new CodeGenerator(bcb, vmImpl);
            g.compileFunction(node);
        }
        return bcb;
    }

    private BCBuilder bcBuilder;
    private VMImplementation vmImpl;
    private Register dstReg;
    private RegisterManager env;
    private Continuation continuation;

    private CodeGenerator(BCBuilder bcb, VMImplementation vmi) {
        this.bcBuilder = bcb;
        this.vmImpl = vmi;
    }

    private void pushContinuation(Continuation k) {
        k.setPrev(continuation);
        continuation = k;
    }

    private void popContinuation() {
        continuation = continuation.getPrev();
    }

    private Continuation getContinuation() {
        return continuation;
    }

    private Label exLabel() {
        return continuation.getExceptionDest();
    }

    public void printByteCode(List<BCode> bcodes) {
        for (BCode bcode : bcodes) {
            System.out.println(bcode);
        }
    }

    private void compileNode(IASTNode node, Register reg) {
        Register tmp = this.dstReg;
        this.dstReg = reg;
        node.accept(this);
        this.dstReg = tmp;
    }

    private BCBuilder.FunctionBCBuilder compileFunction(IASTFunctionExpression node) {
        BCBuilder.FunctionBCBuilder compiledFunction = bcBuilder.openFunctionBCBuilder();
        if (node.topLevel)
            bcBuilder.setTopLevel();
        bcBuilder.setLogging(node.logging);
        pushContinuation(new FunctionContinuation(node.topLevel));
        env = new RegisterManager(node);

        /*
         * Pseudo instruction to mark input registers
         */
        bcBuilder.push(new MParameter(env.getRegister(THIS_OBJECT_REGISTER)));
        for (ParameterVarDecl decl: node.params)
            bcBuilder.push(new MParameter(env.getRegister(THIS_OBJECT_REGISTER + 1 + decl.getParameterIndex())));

        /*
         * Create entry point
         */
        bcBuilder.setLogging(node.logging);
        Label callEntry = new Label();
        Label sendEntry = new Label();
        bcBuilder.setEntry(callEntry, sendEntry);
        bcBuilder.push(callEntry);
        bcBuilder.pushMsetfl();
        bcBuilder.push(new IGetglobalobj(env.getRegister(THIS_OBJECT_REGISTER)).from(node));
        bcBuilder.push(sendEntry);
        if (node.frameSize() > 0)
            bcBuilder.push(new INewframe(node.frameSize(), node.needArguments()).from(node));
        bcBuilder.pushMsetfl();

        /*
         * move argument on stack to frame
         */
        for (ParameterVarDecl decl: node.params) {
            IASTNode.VarLoc locx = decl.getLocation();
            if (locx instanceof IASTNode.FrameVarLoc) {
                IASTNode.FrameVarLoc loc = (IASTNode.FrameVarLoc) locx;
                Register inputReg = env.getRegister(THIS_OBJECT_REGISTER + 1 + decl.getParameterIndex());
                bcBuilder.push(new ISetlocal(0, loc.getIndex(), inputReg).from(node));
            }
        } 

        /*
         * Compile body
         */
        Register retReg = env.freshRegister();
        if (node.topLevel)
            bcBuilder.push(new IUndefinedconst(retReg).from(node)); // default value
        compileNode(node.body, retReg);
        getContinuation().emitEndFunction(retReg);

        bcBuilder.setNumberOfLocals(node.frameSize());
        bcBuilder.setNumberOfGPRegisters(env.getNumberOfGPRegisters());

        // Don't change the order.
        popContinuation();
        env.close();
        bcBuilder.closeFuncBCBuilder();

        return compiledFunction;
    }

    @Override
    public Object visitProgram(IASTProgram node) {
        throw new Error("unexpected node IASTProgram");
    }

    @Override
    public Object visitStringLiteral(IASTStringLiteral node) {
        bcBuilder.push(new IString(dstReg, node.value).from(node));
        return null;
    }

    @Override
    public Object visitNumericLiteral(IASTNumericLiteral node) {
        boolean isSmallPrimitive = vmImpl.getInsnRep().inSmallPrimitiveRange(node.value);
        if (isSmallPrimitive) {
            bcBuilder.push(new IFixnum(dstReg, (int) node.value).from(node));
        } else {
            bcBuilder.push(new INumber(dstReg, node.value).from(node));
        }
        return null;
    }

    @Override
    public Object visitBooleanLiteral(IASTBooleanLiteral node) {
        bcBuilder.push(new IBooleanconst(dstReg, node.value).from(node));
        return null;
    }

    @Override
    public Object visitNullLiteral(IASTNullLiteral node) {
        bcBuilder.push(new INullconst(dstReg).from(node));
        return null;
    }

    @Override
    public Object visitRegExpLiteral(IASTRegExpLiteral node) {
        String flags = node.flag;
        int flagValue = 0;
        for(int i = 0; i < flags.length(); i++) {
            switch(flags.charAt(i)) {
                case 'g': flagValue += 1; break;
                case 'i': flagValue += 2; break;
                case 'm': flagValue += 4; break;
                default: throw new Error("Unknown regexp flag : " + flags);
            }
        }
        bcBuilder.push(new IRegexp(dstReg, flagValue, node.pattern).from(node));
        return null;
    }

    @Override
    public Object visitBlockStatement(IASTBlockStatement node) {
        bcBuilder.push(new IUndefinedconst(dstReg).from(node));
        for (IASTStatement stmt : node.stmts)
            compileNode(stmt, dstReg);
        return null;
    }

    @Override
    public Object visitReturnStatement(IASTReturnStatement node) {
        if (node.value == null) {
            bcBuilder.push(new IUndefinedconst(dstReg).from(node));
        } else {
            compileNode(node.value, dstReg);
        }
        getContinuation().emitReturn(dstReg);
        return null;
    }

    @Override
    public Object visitWithStatement(IASTWithStatement node) {
        throw new UnsupportedOperationException("WithStatement has not been implemented yet.");

    }

    @Override
    public Object visitEmptyStatement(IASTEmptyStatement node) {
        return null;
    }

    @Override
    public Object visitIfStatement(IASTIfStatement node) {
        Label l1 = new Label();
        compileNode(node.test, dstReg);
        bcBuilder.push(new IJumpfalse(l1, dstReg).from(node.test));
        compileNode(node.consequent, dstReg);
        if (node.alternate == null) {
            bcBuilder.push(l1);
        } else {
            Label l2 = new Label();
            bcBuilder.push(new IJump(l2).from(node.alternate));
            bcBuilder.push(l1);
            compileNode(node.alternate, dstReg);
            bcBuilder.push(l2);
        }
        return null;
    }

    @Override
    public Object visitSwitchStatement(IASTSwitchStatement node) {
        Register discReg = env.freshRegister();
        compileNode(node.discriminant, discReg);
        LinkedList<Label> caseLabels = new LinkedList<Label>();
        Register testReg = env.freshRegister();
        for (IASTSwitchStatement.CaseClause caseClause : node.cases) {
            if (caseClause.test != null) {
                Label caseLabel = new Label();
                compileNode(caseClause.test, testReg);
                bcBuilder.push(new IEq(dstReg, discReg, testReg).from(caseClause.test));
                bcBuilder.push(new IJumptrue(caseLabel, dstReg).from(caseClause.test));
                caseLabels.add(caseLabel);
            } else {
                Label caseLabel = new Label();
                bcBuilder.push(new IJump(caseLabel).from(node));
                caseLabels.add(caseLabel);
                break;
            }
        }
        Label breakLabel = new Label();
        pushContinuation(new SwitchContinuation(breakLabel));
        for (IASTSwitchStatement.CaseClause caseClause : node.cases) {
            Label caseLabel = caseLabels.pollFirst();
            if (caseLabel != null) {
                bcBuilder.push(caseLabel);
            }
            compileNode(caseClause.consequent, testReg);
        }
        popContinuation();
        bcBuilder.push(breakLabel);
        return null;
    }

    @Override
    public Object visitExpressionStatement(IASTExpressionStatement node) {
        compileNode(node.exp, dstReg);
        return null;
    }

    @Override
    public Object visitThrowStatement(IASTThrowStatement node) {
        Register r = env.freshRegister();
        compileNode(node.value, r);
        getContinuation().emitThrow(r);
        return null;
    }

    @Override
    public Object visitTryCatchStatement(IASTTryCatchStatement node) {
        Label l1 = new Label();
        Label l2 = new Label();
        bcBuilder.push(new IPushhandler(l1).from(node));
        pushContinuation(new TryCatchContinuation(l1));
        compileNode(node.body, dstReg);
        popContinuation();
        bcBuilder.push(new IPophandler().from(node.body));
        bcBuilder.push(new IJump(l2).from(node.body));

        bcBuilder.push(l1);
        bcBuilder.pushMsetfl();
        IASTNode.VarLoc locx = node.var.getLocation();
        if (locx instanceof IASTNode.FrameVarLoc) {
            IASTNode.FrameVarLoc loc = (IASTNode.FrameVarLoc) locx;
            Register r = env.freshRegister();
            pushContinuation(new CatchContinuation());
            bcBuilder.push(new INewframe(1, false).from(node.handler));
            bcBuilder.push(new IGeta(r).from(node.handler));
            bcBuilder.push(new ISetlocal(0, loc.getIndex(), r).from(node.handler));
            compileNode(node.handler, dstReg);
            popContinuation();
            bcBuilder.push(new IExitframe().from(node.handler));
            bcBuilder.push(l2);
        } else if (locx instanceof IASTNode.RegisterVarLoc) {
            IASTNode.RegisterVarLoc loc = (IASTNode.RegisterVarLoc) locx;
            Register r = env.freshRegister();
            loc.setRegisterNo(r.getRegisterNumber());
            bcBuilder.push(new IGeta(r).from(node.handler));
            compileNode(node.handler, dstReg);
            bcBuilder.push(l2);
        } else
            throw new Error("Unexpected VarLoc");
        return null;
    }

    @Override
    public Object visitTryFinallyStatement(IASTTryFinallyStatement node) {
        Label lByException = new Label();
        Label lFinally = new Label();
        Label lExit = new Label();
        Register rException = env.freshRegister();
        bcBuilder.push(new IPushhandler(lByException).from(node));
        pushContinuation(new TryFinallyContinuation(lFinally));
        compileNode(node.body, dstReg);
        popContinuation();
        bcBuilder.push(new IPophandler().from(node.body));
        bcBuilder.push(new ILocalcall(lFinally).from(node.finaliser));
        bcBuilder.push(new IJump(lExit).from(node.finaliser));

        bcBuilder.push(lByException);
        bcBuilder.pushMsetfl();
        bcBuilder.push(new IGeta(rException).from(node.finaliser));
        bcBuilder.push(new ILocalcall(lFinally).from(node.finaliser));
        getContinuation().emitThrow(rException);

        bcBuilder.push(lFinally);
        pushContinuation(new FinallyContinuation());
        compileNode(node.finaliser, dstReg);
        popContinuation();
        bcBuilder.push(new ILocalret().from(node.finaliser));

        bcBuilder.push(lExit);
        return null;
    }

    @Override
    public Object visitForStatement(IASTForStatement node) {
        if (node.init != null)
            compileNode(node.init, env.freshRegister());
        Label l1 = new Label();
        Label l2 = new Label();
        Label continueLabel = new Label();
        Label breakLabel = new Label();
        bcBuilder.push(new IJump(l1).from(node));
        bcBuilder.push(l2);
        if (node.body != null) {
            pushContinuation(new LoopContinuation(node.label, breakLabel, continueLabel));
            compileNode(node.body, dstReg);
            popContinuation();
        }
        bcBuilder.push(continueLabel);
        if (node.update != null)
            compileNode(node.update, env.freshRegister());
        bcBuilder.push(l1);
        Register testReg = env.freshRegister();
        if (node.test != null) {
            compileNode(node.test, testReg);
            bcBuilder.push(new IJumptrue(l2, testReg).from(node.test));
        } else {
            bcBuilder.push(new IJump(l2).from(node));
        }
        bcBuilder.push(breakLabel);
        return null;
    }

    @Override
    public Object visitWhileStatement(IASTWhileStatement node) {
        Label l1 = new Label();
        Label l2 = new Label();
        Label breakLabel = new Label();
        Label continueLabel = new Label();
        bcBuilder.push(new IJump(l1).from(node));
        bcBuilder.push(l2);
        if (node.body != null) {
            pushContinuation(new LoopContinuation(node.label, breakLabel, continueLabel));
            compileNode(node.body, dstReg);
            popContinuation();
        }
        bcBuilder.push(continueLabel);
        bcBuilder.push(l1);
        Register testReg = env.freshRegister();
        compileNode(node.test, testReg);
        bcBuilder.push(new IJumptrue(l2, testReg).from(node.test));
        bcBuilder.push(breakLabel);
        return null;
    }

    @Override
    public Object visitDoWhileStatement(IASTDoWhileStatement node) {
        Label l1 = new Label();
        Label breakLabel = new Label();
        Label continueLabel = new Label();
        bcBuilder.push(continueLabel);
        bcBuilder.push(l1);
        if (node.body != null) {
            pushContinuation(new LoopContinuation(node.label, breakLabel, continueLabel));
            compileNode(node.body, dstReg);
            popContinuation();
        }
        Register testReg = env.freshRegister();
        compileNode(node.test, testReg);
        bcBuilder.push(new IJumptrue(l1, testReg).from(node.test));
        bcBuilder.push(breakLabel);
        return null;
    }

    @Override
    public Object visitForInStatement(IASTForInStatement node) {
        Register objReg = env.freshRegister();
        Register iteReg = env.freshRegister();
        Register propReg = env.freshRegister();
        Register testReg = env.freshRegister();
        Label breakLabel = new Label();
        Label continueLabel = new Label();
        Label l1 = new Label();
        Label l2 = new Label();
        compileNode(node.object, objReg);
        bcBuilder.push(new IMakeiterator(objReg, iteReg).from(node));
        bcBuilder.push(l1);
        bcBuilder.push(new INextpropnameidx(iteReg, propReg).from(node));
        compileSetVariable(node.var, propReg);
        bcBuilder.push(new IIsundef(testReg, propReg).from(node));
        bcBuilder.push(new IJumptrue(l2, testReg).from(node));
        bcBuilder.push(continueLabel);
        pushContinuation(new LoopContinuation(node.label, breakLabel, continueLabel));
        compileNode(node.body, dstReg);
        popContinuation();
        bcBuilder.push(new IJump(l1).from(node.body));
        bcBuilder.push(breakLabel);
        bcBuilder.push(l2);
        return null;
    }

    @Override
    public Object visitBreakStatement(IASTBreakStatement node) {
        getContinuation().emitBreak(node.label);
        return null;
    }

    @Override
    public Object visitContinueStatement(IASTContinueStatement node) {
        getContinuation().emitContinue(node.label);
        return null;
    }

    // precondition: node.params and node.locals are disjoint
    @Override
    public Object visitFunctionExpression(IASTFunctionExpression node) {
        CodeGenerator g = new CodeGenerator(bcBuilder, vmImpl);
        BCBuilder.FunctionBCBuilder compiledFunction = g.compileFunction(node);
        bcBuilder.push(new IMakeclosure(dstReg, compiledFunction).from(node));
        return null;
    }

    @Override
    public Object visitThisExpression(IASTThisExpression node) {
        bcBuilder.push(new IMove(dstReg, env.getRegister(THIS_OBJECT_REGISTER)).from(node));
        return null;
    }

    @Override
    public Object visitArrayExpression(IASTArrayExpression node) {
        Register r1 = env.freshRegister();
        Register constructorReg = env.freshRegister();
        Register[] tmpRegs = new Register[1];
        tmpRegs[0] = env.freshRegister();
        bcBuilder.push(new IString(r1, "Array").from(node));
        bcBuilder.push(new IGetglobal(constructorReg, r1, exLabel()).from(node));
        bcBuilder.push(new IFixnum(tmpRegs[0], node.elements.size()).from(node)); // TODO: Check size is not to be overflow
        bcBuilder.pushMConstruct(dstReg, constructorReg, tmpRegs, exLabel());
        bcBuilder.pushMsetfl();
        bcBuilder.push(new IGetNewa(dstReg).from(node));
        int i = 0;
        for (IASTExpression element : node.elements) {
            if (element != null) {
                compileNode(element, r1);
                bcBuilder.push(new IFixnum(constructorReg, i).from(element)); // TODO: Check size is not to be overflow
                bcBuilder.push(new ISetprop(dstReg, constructorReg, r1).from(element));
            }
            i++;
        }
        return null;
    }

    @Override
    public Object visitObjectExpression(IASTObjectExpression node) {
        Register r1 = env.freshRegister();
        Register constructorReg = env.freshRegister();
        Register[] tmpRegs = new Register[0];
        bcBuilder.push(new IString(r1, "Object").from(node));
        bcBuilder.push(new IGetglobal(constructorReg, r1, exLabel()).from(node));
        bcBuilder.pushMConstruct(dstReg, constructorReg, tmpRegs, exLabel());
        bcBuilder.pushMsetfl();
        bcBuilder.push(new IGetNewa(dstReg).from(node));
        for (IASTObjectExpression.Property prop : node.properties) {
            compileNode(prop.value, r1);
            compileNode(prop.key, constructorReg);
            bcBuilder.push(new ISetprop(dstReg, constructorReg, r1).from(prop.value));
        }
        return null;
    }

    @Override
    public Object visitUnaryExpression(IASTUnaryExpression node) {
        switch (node.operator) {
        case PLUS: {
            compileNode(node.operands[0], dstReg);
        }
        break;
        case MINUS: {
            Register r1 = env.freshRegister();
            Register r2 = env.freshRegister();
            compileNode(node.operands[0], r1);
            bcBuilder.push(new IFixnum(r2, -1).from(node));
            bcBuilder.push(new IMul(dstReg, r1, r2, exLabel()).from(node));
        }
        break;
        case NOT: {
            Register r1 = env.freshRegister();
            compileNode(node.operands[0], r1);
            bcBuilder.push(new INot(dstReg, r1, exLabel()).from(node));
        }
        break;
        case INC:
        case DEC: {
            if (node.prefix) {
                Register r1 = env.freshRegister();
                Register r2 = env.freshRegister();
                compileNode(node.operands[0], r1);
                bcBuilder.push(new IFixnum(r2, 1).from(node));
                if (node.operator == IASTUnaryExpression.Operator.INC) {
                    bcBuilder.push(new IAdd(dstReg, r1, r2, exLabel()).from(node));
                } else if (node.operator == IASTUnaryExpression.Operator.DEC) {
                    bcBuilder.push(new ISub(dstReg, r1, r2, exLabel()).from(node));
                }
                compileAssignment(node.operands[0], dstReg);
            } else {
                Register r1 = env.freshRegister();
                Register r2 = env.freshRegister();
                compileNode(node.operands[0], dstReg);
                bcBuilder.push(new IFixnum(r1, 1).from(node));
                if (node.operator == IASTUnaryExpression.Operator.INC) {
                    bcBuilder.push(new IAdd(r2, dstReg, r1, exLabel()).from(node));
                } else if (node.operator == IASTUnaryExpression.Operator.DEC) {
                    bcBuilder.push(new ISub(r2, dstReg, r1, exLabel()).from(node));
                }
                compileAssignment(node.operands[0], r2);
            }
        }
        break;
        case BNOT: {
            Register r1 = env.freshRegister();
            compileNode(node.operands[0], dstReg);
            bcBuilder.push(new IFixnum(r1, 0).from(node));
            bcBuilder.push(new ISub(dstReg, r1, dstReg, exLabel()).from(node));
            bcBuilder.push(new IFixnum(r1, 1).from(node));
            bcBuilder.push(new ISub(dstReg, dstReg, r1, exLabel()).from(node));
        }
        break;
        case TYPEOF:
            throw new UnsupportedOperationException("Unary operator not implemented : typeof");
        case VOID: {
            Register r1 = env.freshRegister();
            compileNode(node.operands[0], dstReg);
            bcBuilder.push(new IString(r1, "\"undefined\"").from(node));
            bcBuilder.push(new IGetglobal(dstReg, r1, exLabel()).from(node));
        }
        break;
        case DELETE:
            throw new UnsupportedOperationException("Unary operator not implemented : delete");
        default:
            throw new UnsupportedOperationException("Unary operator not implemented : unknown");
        }
        return null;
    }
    @Override
    public Object visitBinaryExpression(IASTBinaryExpression node) {
        // TODO: refactoring
        Register r1 = null, r2 = null;
        switch (node.operator) {
        case ADD: case SUB: case MUL: case DIV: case MOD:
        case SHL: case SHR: case UNSIGNED_SHR:
        case BAND: case BOR: case BXOR:
        case EQUAL: case NOT_EQUAL: case EQ: case NOT_EQ: case LT: case LTE: case GT: case GTE:
        case ASSIGN_ADD: case ASSIGN_SUB: case ASSIGN_MUL: case ASSIGN_DIV: case ASSIGN_MOD:
        case ASSIGN_SHL: case ASSIGN_SHR: case ASSIGN_UNSIGNED_SHR:
        case ASSIGN_BAND: case ASSIGN_BOR: case ASSIGN_BXOR:
            r1 = env.freshRegister();
            compileNode(node.operands[0], r1);
            r2 = env.freshRegister();
            compileNode(node.operands[1], r2);
            break;
        default:
            /* do nothing */
            break;
        }


        switch (node.operator) {
        // arithmetic
        case ADD: case ASSIGN_ADD: {
            bcBuilder.push(new IAdd(dstReg, r1, r2, exLabel()).from(node));
        } break;
        case SUB: case ASSIGN_SUB: {
            bcBuilder.push(new ISub(dstReg, r1, r2, exLabel()).from(node));
        } break;
        case MUL: case ASSIGN_MUL: {
            bcBuilder.push(new IMul(dstReg, r1, r2, exLabel()).from(node));
        } break;
        case DIV: case ASSIGN_DIV: {
            bcBuilder.push(new IDiv(dstReg, r1, r2, exLabel()).from(node));
        } break;
        case MOD: case ASSIGN_MOD: {
            bcBuilder.push(new IMod(dstReg, r1, r2, exLabel()).from(node));
        } break;

        // shift
        case SHL: case ASSIGN_SHL: {
            bcBuilder.push(new ILeftshift(dstReg, r1, r2, exLabel()).from(node));
        } break;
        case SHR: case ASSIGN_SHR: {
            bcBuilder.push(new IRightshift(dstReg, r1, r2, exLabel()).from(node));
        } break;
        case UNSIGNED_SHR: case ASSIGN_UNSIGNED_SHR: {
            bcBuilder.push(new IUnsignedrightshift(dstReg, r1, r2, exLabel()).from(node));
        } break;

        // bit
        case BOR: case ASSIGN_BOR: {
            bcBuilder.push(new IBitor(dstReg, r1, r2, exLabel()).from(node));
        } break;
        case BAND: case ASSIGN_BAND: {
            bcBuilder.push(new IBitand(dstReg, r1, r2, exLabel()).from(node));
        } break;
        case BXOR: case ASSIGN_BXOR: {
            Register r3 = env.freshRegister();
            bcBuilder.push(new IBitor(r3, r1, r2, exLabel()).from(node));  // r3 = a | b
            bcBuilder.push(new IBitand(r1, r1, r2, exLabel()).from(node));  // r1 = a & b
            bcBuilder.push(new IFixnum(r2, 0).from(node));
            bcBuilder.push(new ISub(r1, r2, r1, exLabel()).from(node));    // r1 = -(a & b)
            bcBuilder.push(new IFixnum(r2, 1).from(node));
            bcBuilder.push(new ISub(r1, r1, r2, exLabel()).from(node));    // r1 = ~(a & b)
            bcBuilder.push(new IBitand(dstReg, r1, r3, exLabel()).from(node)); // reg = ~(a & b) & (a | b)
        } break;

        // logical
        case OR: {
            Label l1 = new Label();
            compileNode(node.operands[0], dstReg);
            bcBuilder.push(new IJumptrue(l1, dstReg).from(node));
            compileNode(node.operands[1], dstReg);
            bcBuilder.push(l1);
        }
        break;
        case AND: {
            Label l1 = new Label();
            compileNode(node.operands[0], dstReg);
            bcBuilder.push(new IJumpfalse(l1, dstReg).from(node));
            compileNode(node.operands[1], dstReg);
            bcBuilder.push(l1);
        }
        break;

        // relational
        case EQUAL: case NOT_EQUAL: {
            Register r3 = (node.operator == IASTBinaryExpression.Operator.EQUAL) ? dstReg : env.freshRegister();
            Register r4 = env.freshRegister();
            Register r5 = env.freshRegister();
            Register r6 = env.freshRegister();
            Register r7 = env.freshRegister();
            Register r8 = env.freshRegister();
            Register r9 = env.freshRegister();
            Register r10 = env.freshRegister();
            // Register r10 = node.operator == IASTBinaryExpression.Operator.EQUAL ? reg : env.freshRegister();
            Label l1 = new Label();
            Label l2 = new Label();
            Label l3 = new Label();
            Label l4 = new Label();
            bcBuilder.push(new IEqual(r3, r1, r2, exLabel()).from(node));
            bcBuilder.push(new IIsundef(r4, r3).from(node));
            bcBuilder.push(new IJumpfalse(l1, r4).from(node));
            bcBuilder.push(new IString(r5, "valueOf").from(node));
            bcBuilder.push(new IIsobject(r6, r1).from(node));
            bcBuilder.push(new IJumpfalse(l2, r6).from(node));

            bcBuilder.push(new IGetprop(r7, r1, r5).from(node));
            bcBuilder.push(new MCall(r1, r7, new Register[] {}, false, exLabel()).from(node));
            bcBuilder.push(new IGeta(r8).from(node));
            bcBuilder.push(new IMove(r9, r2).from(node));

            bcBuilder.push(new IJump(l3).from(node));

            bcBuilder.push(l2);
            bcBuilder.push(new IGetprop(r7, r2, r5).from(node));
            bcBuilder.push(new MCall(r2, r7, new Register[] {}, false, exLabel()).from(node));
            bcBuilder.push(new IGeta(r9).from(node));
            bcBuilder.push(new IMove(r8, r1).from(node));

            bcBuilder.push(l3);
            bcBuilder.push(new IEqual(r3, r8, r9, exLabel()).from(node));
            bcBuilder.push(new IIsundef(r5, r3).from(node));
            bcBuilder.push(new IJumpfalse(l4, r5).from(node));
            bcBuilder.push(new IString(r10, "EQUAL_GETTOPRIMITIVE").from(node));
            bcBuilder.push(new IThrow(r10, exLabel()).from(node));
            bcBuilder.push(l1);
            bcBuilder.push(l4);
            if (node.operator == IASTBinaryExpression.Operator.NOT_EQUAL)
                bcBuilder.push(new INot(dstReg, r3, exLabel()).from(node));
        } break;
        case EQ: {
            bcBuilder.push(new IEq(dstReg, r1, r2).from(node));
        } break;
        case NOT_EQ: {
            Register r3 = env.freshRegister();
            bcBuilder.push(new IEq(r3, r1, r2).from(node));
            bcBuilder.push(new INot(dstReg, r3, exLabel()).from(node));
        } break;
        case LT: {
            bcBuilder.push(new ILessthan(dstReg, r1, r2, exLabel()).from(node));
        } break;
        case LTE: {
            bcBuilder.push(new ILessthanequal(dstReg, r1, r2, exLabel()).from(node));
        } break;
        case GT: {
            bcBuilder.push(new ILessthan(dstReg, r2, r1, exLabel()).from(node));
        } break;
        case GTE: {
            bcBuilder.push(new ILessthanequal(dstReg, r2, r1, exLabel()).from(node));
        } break;
        case IN:
            throw new UnsupportedOperationException("Binary operator not implemented : in");
        case INSTANCE_OF: {
            bcBuilder.push(new IInstanceof(dstReg, r2, r1).from(node));
        } break;

        // assignment
        case ASSIGN: {
            compileNode(node.operands[1], dstReg);
        } break;
        }


        switch (node.operator) {
        case ASSIGN_ADD: case ASSIGN_SUB: case ASSIGN_MUL: case ASSIGN_DIV: case ASSIGN_MOD:
        case ASSIGN_SHL: case ASSIGN_SHR: case ASSIGN_UNSIGNED_SHR:
        case ASSIGN_BAND: case ASSIGN_BOR: case ASSIGN_BXOR:
        case ASSIGN:
            compileAssignment(node.operands[0], dstReg);
            break;
        default:
            break;
        }
        return null;
    }
    void compileAssignment(IASTExpression dst, Register srcReg) {
        if (dst instanceof IASTIdentifier) {
            IASTIdentifier dstVar = (IASTIdentifier) dst;
            compileSetVariable(dstVar, srcReg);
        } else if (dst instanceof IASTMemberExpression) {
            IASTMemberExpression memExp = (IASTMemberExpression) dst;
            Register objReg = env.freshRegister();
            compileNode(memExp.object, objReg);
            Register propReg = env.freshRegister();
            compileNode(memExp.property, propReg);
            bcBuilder.push(new ISetprop(objReg, propReg, srcReg).from(memExp));
        }
    }

    void compileSetVariable(IASTIdentifier node, Register srcReg) {
        IASTNode.VarLoc locx = node.getDeclaration().getLocation();
        if (locx instanceof IASTNode.GlobalVarLoc) {
            Register r1 = env.freshRegister();
            bcBuilder.push(new IString(r1, node.id).from(node));
            bcBuilder.push(new ISetglobal(r1, srcReg, exLabel()).from(node));
        } else if (locx instanceof IASTNode.RegisterVarLoc) {
            IASTNode.RegisterVarLoc loc = (IASTNode.RegisterVarLoc) locx;
            Register varReg = env.getRegister(loc.getRegisterNo());
            bcBuilder.push(new IMove(varReg, srcReg).from(node));
        } else if (locx instanceof IASTNode.FrameVarLoc) {
            IASTNode.FrameVarLoc loc = (IASTNode.FrameVarLoc) locx;
            int slink = loc.countStaticLink(node.getScope());
            bcBuilder.push(new ISetlocal(slink, loc.getIndex(), srcReg).from(node));
        } else if (locx instanceof IASTNode.ArgumentsVarLoc) {
            IASTNode.ArgumentsVarLoc loc = (IASTNode.ArgumentsVarLoc) locx;
            int slink = loc.countStaticLink(node.getScope());
            bcBuilder.push(new ISetarg(slink, loc.getIndex(), srcReg).from(node));
        } else
            throw new Error("unknown VarLoc");
    }

    void compileGetVariable(IASTIdentifier node, Register dstReg) {
        IASTNode.VarLoc locx = node.getDeclaration().getLocation();
        if (locx instanceof IASTNode.GlobalVarLoc) {
            Register r1 = env.freshRegister();
            bcBuilder.push(new IString(r1, node.id).from(node));
            bcBuilder.push(new IGetglobal(dstReg, r1, exLabel()).from(node));
        } else if (locx instanceof IASTNode.RegisterVarLoc) {
            IASTNode.RegisterVarLoc loc = (IASTNode.RegisterVarLoc) locx;
            Register varReg = env.getRegister(loc.getRegisterNo());
            bcBuilder.push(new IMove(dstReg, varReg).from(node));
        } else if (locx instanceof IASTNode.FrameVarLoc) {
            IASTNode.FrameVarLoc loc = (IASTNode.FrameVarLoc) locx;
            int slink = loc.countStaticLink(node.getScope());
            bcBuilder.push(new IGetlocal(dstReg, slink, loc.getIndex()).from(node));
        } else if (locx instanceof IASTNode.ArgumentsVarLoc) {
            IASTNode.ArgumentsVarLoc loc = (IASTNode.ArgumentsVarLoc) locx;
            int slink = loc.countStaticLink(node.getScope());
            bcBuilder.push(new IGetarg(dstReg, slink, loc.getIndex()).from(node));
        } else
            throw new Error("unknown VarLoc");
    }

    @Override
    public Object visitTernaryExpression(IASTTernaryExpression node) {
        switch (node.operator) {
        case COND: {
            Register testReg = env.freshRegister();
            compileNode(node.operands[0], testReg);
            Label l1 = new Label();
            Label l2 = new Label();
            bcBuilder.push(new IJumpfalse(l1, testReg).from(node.operands[0]));
            compileNode(node.operands[1], dstReg);
            bcBuilder.push(new IJump(l2).from(node.operands[1]));
            bcBuilder.push(l1);
            compileNode(node.operands[2], dstReg);
            bcBuilder.push(l2);
        }
        break;
        default:
            throw new Error("Unreachable code.");
        }
        return null;
    }

    @Override
    public Object visitCallExpression(IASTCallExpression node) {
        Register[] tmpRegs = new Register[node.arguments.size()];
        for (int i = 0; i < tmpRegs.length; i++)
            tmpRegs[i] = env.freshRegister();

        if (node.callee instanceof IASTMemberExpression) {
            IASTNode object = ((IASTMemberExpression) node.callee).object;
            IASTNode property = ((IASTMemberExpression) node.callee).property;
            Register objReg      = env.freshRegister();
            Register propNameReg = env.freshRegister();
            Register propValReg   = env.freshRegister();

            compileNode(object,   objReg);
            compileNode(property, propNameReg);
            bcBuilder.push(new IGetprop(propValReg, objReg, propNameReg).from(node.callee));
            for (int i = 0; i < node.arguments.size(); i++) {
                IASTNode argument = node.arguments.get(i);
                compileNode(argument, tmpRegs[i]);
            }
            bcBuilder.pushMCall(objReg, propValReg, tmpRegs, false, exLabel());
        } else {
            Register calleeReg = env.freshRegister();
            compileNode(node.callee, calleeReg);
            for (int i = 0; i < node.arguments.size(); i++) {
                IASTNode argument = node.arguments.get(i);
                compileNode(argument, tmpRegs[i]);
            }            
            bcBuilder.pushMCall(null, calleeReg, tmpRegs, false, exLabel());
        }
        bcBuilder.pushMsetfl();
        bcBuilder.push(new IGeta(dstReg).from(node));
        return null;
    }

    @Override
    public Object visitNewExpression(IASTNewExpression node) {
        Register[] tmpRegs = new Register[node.arguments.size()];
        for (int i = 0; i < tmpRegs.length; i++)
            tmpRegs[i] = env.freshRegister();
        Register constructorReg = env.freshRegister();
        compileNode(node.constructor, constructorReg);
        for (int i = 0; i < node.arguments.size(); i++) {
            IASTNode argument = node.arguments.get(i);
            compileNode(argument, tmpRegs[i]);
        }
        bcBuilder.pushMConstruct(dstReg, constructorReg, tmpRegs, exLabel());
        bcBuilder.pushMsetfl();
        bcBuilder.push(new IGetNewa(dstReg).from(node.constructor));
        return null;
    }

    @Override
    public Object visitMemberExpression(IASTMemberExpression node) {
        Register objReg = env.freshRegister();
        compileNode(node.object, objReg);
        Register expReg = env.freshRegister();
        compileNode(node.property, expReg);
        bcBuilder.push(new IGetprop(dstReg, objReg, expReg).from(node.property));
        return null;
    }

    @Override
    public Object visitIdentifier(IASTIdentifier node) {
        compileGetVariable(node, dstReg);
        return null;
    }
}
