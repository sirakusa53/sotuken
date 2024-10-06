/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package ejsc;
import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

import ejsc.CodeBuffer.SpecialValue;

interface CodeBuffer {
    public class SourceLocation {
        int line, column;
        SourceLocation(int line, int column) {
            this.line = line;
            this.column = column;
        }
    };

    enum SpecialValue {
        TRUE,
        FALSE,
        NULL,
        UNDEFINED
    }
    // fixnum
    void addFixnumSmallPrimitive(String insnName, boolean log, SourceLocation sloc, Register dst, int n);
    // number
    void addNumberBigPrimitive(String insnName, boolean log, SourceLocation sloc, Register dst, double n);
    // string
    void addStringBigPrimitive(String insnName, boolean log, SourceLocation sloc, Register dst, String s);
    // special
    void addSpecialSmallPrimitive(String insnName, boolean log, SourceLocation sloc, Register dst, SpecialValue v);
    // regexp
    void addRegexp(String insnName, boolean log, SourceLocation sloc, Register dst, int flag, String ptn);
    // threeop
    void addRXXThreeOp(String insnName, boolean log, SourceLocation sloc, Register dst, SrcOperand src1, SrcOperand src2);
    // threeop (setprop)
    void addXXXThreeOp(String insnName, boolean log, SourceLocation sloc, SrcOperand src1, SrcOperand src2, SrcOperand src3);
    // threeop (setarray)
    void addXIXThreeOp(String insnName, boolean log, SourceLocation sloc, SrcOperand src1, int index, SrcOperand src2);
    // twoop
    void addRXTwoOp(String insnName, boolean log, SourceLocation sloc, Register dst, SrcOperand src);
    // twoop (setglobal)
    void addXXTwoOp(String insnName, boolean log, SourceLocation sloc, SrcOperand src1, SrcOperand src2);
    // oneop
    void addROneOp(String insnName, boolean log, SourceLocation sloc, Register dst);
    // oneop (seta, throw)
    void addXOneOp(String insnName, boolean log, SourceLocation sloc, SrcOperand src);
    // oneop (setfl)
    void addIOneOp(String insnName, boolean log, SourceLocation sloc, int n);
    // zeroop
    void addZeroOp(String insnName, boolean log, SourceLocation sloc);
    // newframe
    void addNewFrameOp(String insnName, boolean log, SourceLocation sloc, int len, boolean mkargs);
    // getvar
    void addGetVar(String insnName, boolean log, SourceLocation sloc, Register dst, int link, int index);
    // setvar
    void addSetVar(String insnName, boolean log, SourceLocation sloc, int link, int inex, SrcOperand src);
    // makeclosure
    void addMakeClosureOp(String insnName, boolean log, SourceLocation sloc, Register dst, int index);
    // call
    void addXICall(String insnName, boolean log, SourceLocation sloc, SrcOperand fun, int nargs);
    // call (new)
    void addRXCall(String insnName, boolean log, SourceLocation sloc, Register dst, SrcOperand fun);
    // construct
    void addXXIConstruct(String insnName, boolean log, SourceLocation sloc, SrcOperand receiver, SrcOperand constructor, int nargs);
    // uncondjump
    void addUncondJump(String insnName, boolean log, SourceLocation sloc, int disp);
    // condjump
    void addCondJump(String insnName, boolean log, SourceLocation sloc, SrcOperand test, int disp);
}

public abstract class BCode {
    class SourceLocation {
        class Position {
            int line, column;
            Position(int line, int column) {
                this.line = line;
                this.column = column;
            }
        }
        String file;
        Position start, end;
        SourceLocation(String file, int startLine, int startColumn, int endLine, int endColumn) {
            this.file = file;
            this.start = new Position(startLine, startColumn);
            this.end = new Position(endLine, endColumn);
        }
    }
    String name;
    protected int address;
    protected Register dst;
    ArrayList<Label> labels = new ArrayList<Label>();
    boolean logging = false;
    boolean showSourceLocation = true;
    SourceLocation sloc;

    BCode(String name) {
        this.name = name;
    }

    BCode(String name, Register dst) {
        this(name);
        this.dst = dst;
    }

    BCode from(IASTNode node) {
        IASTNode.SourceLocation sloc = node.getSourceLocation();
        if (sloc != null)
            this.sloc = new SourceLocation(sloc.file, sloc.start.line, sloc.start.column, sloc.end.line, sloc.end.column);
        return this;
    }

    void addLabel(Label label) {
        label.replaceDestBCode(this);
        labels.add(label);
    }

    void addLabels(List<Label> labels) {
        for (Label l: labels)
            addLabel(l);
    }

    ArrayList<Label> getLabels() {
        return labels;
    }

    public boolean isFallThroughInstruction() {
        return true;
    }

    public BCode getBranchTarget() {
        return null;
    }

    public Register getDestRegister() {
        return dst;
    }

    public int getAddress() {
        return address;
    }

    public HashSet<Register> getSrcRegisters() {
        HashSet<Register> srcs = new HashSet<Register>();
        Class<? extends BCode> c = getClass();
        for (Field f: c.getDeclaredFields()) {
            if (f.getType() == SrcOperand.class) {
                try {
                    SrcOperand opx = (SrcOperand) f.get(this);
                    if (opx instanceof RegisterOperand)
                        srcs.add(((RegisterOperand) opx).get());
                } catch (Exception e) {
                    throw new Error(e);
                }
            }
        }

        return srcs;
    }

    public void logInsn() {
        this.logging = true;
    }

    String logStr() {
        if (logging) { return "_log"; }
        else { return ""; }
    }

    String slocStr() {
        if (showSourceLocation && sloc != null)
            return String.format("\t\t# %d:%d %s", sloc.start.line, sloc.start.column, sloc.file == null ? "" : sloc.file);
        else
            return "";
    }
    
    CodeBuffer.SourceLocation l() {
        if (sloc == null)
            return null;
        return new CodeBuffer.SourceLocation(sloc.start.line, sloc.start.column);
    }

    abstract void emit(CodeBuffer out);

    String toString(String opcode) {
        return opcode + logStr() + slocStr();
    }
    String toString(String opcode, Register op1) {
        return opcode + logStr() + " " + op1 + slocStr();
    }
    String toString(String opcode, SrcOperand op1) {
        return opcode + logStr() + " " + op1 + slocStr();
    }
    String toString(String opcode, Register op1, SrcOperand op2) {
        return opcode + logStr() + " " + op1 + " " + op2 + slocStr();
    }
    String toString(String opcode, SrcOperand op1, Register op2) {
        return opcode + logStr() + " " + op1 + " " + op2 + slocStr();
    }
    String toString(String opcode, Register op1, SrcOperand op2, SrcOperand op3) {
        return opcode + logStr() + " " + op1 + " " + op2 + " " + op3 + slocStr();
    }
    String toString(String opcode, SrcOperand op1, SrcOperand op2, SrcOperand op3) {
        return opcode + logStr() + " " + op1 + " " + op2 + " " + op3 + slocStr();
    }
    String toString(String opcode, SrcOperand src1, SrcOperand src2) {
        return opcode + logStr() + " " + src1 + " " + src2 + slocStr();
    }
    String toString(String opcode, Register op1, String op2) {
        return opcode + logStr() + " " + op1 + " " + op2 + slocStr();
    }
    String toString(String opcode, SrcOperand op1, int op2) {
        return opcode + logStr() + " " + op1 + " " + op2 + slocStr();
    }
    String toString(String opcode, Register op1, int op2) {
        return opcode + logStr() + " " + op1 + " " + op2 + slocStr();
    }
    String toString(String opcode, Register op1, double op2) {
        return opcode + logStr() + " " + op1 + " " + op2 + slocStr();
    }
    String toString(String opcode, Register op1, int op2, int op3) {
        return opcode + logStr() + " " + op1 + " " + op2 + " " + op3 + slocStr();
    }
    String toString(String opcode, SrcOperand op1, int op2, SrcOperand op3) {
        return opcode + logStr() + " " + op1 + " " + op2 + " " + op3 + slocStr();
    }
    String toString(String opcode, int op1, int op2, SrcOperand op3) {
        return opcode + logStr() + " " + op1 + " " + op2 + " " + op3 + slocStr();
    }
    String toString(String opcode, int op1) {
        return opcode + logStr() + " " + op1 + slocStr();
    }
    String toString(String opcode, int op1, int op2) {
        return opcode + logStr() + " " + op1 + " " + op2 + slocStr();
    }
    String toString(String opcode, SrcOperand op1, SrcOperand op2, int op3) {
        return opcode + logStr() + " " + op1 + " " + op2 + " " + op3 + slocStr();
    }
    String toString(String opcode, Register op1, int op2, String op3) {
        return opcode + logStr() + " " + op1 + " " + op2 + " " + op3 + slocStr();
    }
}

class Register {
    private int n;
    Register(int n) {
        this.n = n;
    }
    public int getRegisterNumber() {
        return n;
    }
    public void setRegisterNumber(int n) {
        this.n = n;
    }
    public String toString() {
        return Integer.toString(n);
    }
}

class Label {
    private BCode bcode;
    Label() {}
    Label(BCode bcode) {
        this.bcode = bcode;
    }
    public int dist(int number) {
        return bcode.address - number;
    }
    public int dist(int number, int argoffset) {
        return bcode.address - number - (argoffset + 1);
    }
    public BCode getDestBCode() {
        return bcode;
    }
    public void replaceDestBCode(BCode bcode) {
        this.bcode = bcode;
    }
}

/*
 * Normal src operand of an instruction.
 */
class SrcOperand {}

class RegisterOperand extends SrcOperand {
    Register x;
    RegisterOperand(Register x) {
        if (x == null)
            throw new Error("x == null");
        this.x = x;
    }
    Register get() {
        return x;
    }
    void set(Register x) {
        this.x = x;
    }
    @Override
    public String toString() {
        return "[reg "+x.toString()+"]";
    }
}

class FixnumOperand extends SrcOperand {
    long x; // Literal value in C code, and be contained in insn operand
    FixnumOperand(long x) {
        this.x = x;
    }
    long get() {
        return x;
    }
    @Override
    public String toString() {
        return "[fixnum "+String.valueOf(x)+"]";
    }
}

class FlonumOperand extends SrcOperand {
    double x; // flonum_cell value in C code, and this value cannot represent as Fixnum
    FlonumOperand(double x) {
        this.x = x;
    }
    double get() {
        return x;
    }
    @Override
    public String toString() {
        return "[flonum "+String.valueOf(x)+"]";
    }
}

class StringOperand extends SrcOperand {
    String x;
    StringOperand(String x) {
        this.x = x;
    }
    String get() {
        return x;
    }
    @Override
    public String toString() {
        return "[string "+x+"]";
    }
}

class SpecialOperand extends SrcOperand {
    SpecialValue x;
    SpecialOperand(SpecialValue x) {
        this.x = x;
    }
    SpecialValue get() {
        return x;
    }
    @Override
    public String toString() {
        switch (x) {
        case TRUE:
            return "[special true]";
        case FALSE:
            return "[special false]";
        case NULL:
            return "[special null]";
        case UNDEFINED:
            return "[special undefined]";
        default:
            throw new Error("unknown special value");
        }
    }
}

/*
 * BCode
 */
abstract class CauseExceptionBCode extends BCode {
    CauseExceptionBCode(String name, Label exceptionDest) {
        super(name);
        this.exceptionDest = exceptionDest;
    }
    CauseExceptionBCode(String name, Register dst, Label exceptionDest) {
        super(name, dst);
        this.exceptionDest = exceptionDest;
    }

    Label exceptionDest;
    final public BCode getBranchTarget() {
        if (exceptionDest == null)
            return null;
        return exceptionDest.getDestBCode();
    }
}

/* SMALLPRIMITIVE */
class IFixnum extends BCode {
    int n;
    IFixnum(Register dst, int n) {
        super("fixnum", dst);
        this.n = n;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addFixnumSmallPrimitive(name, logging, l(), dst, n);
    }
    public String toString() {
        return super.toString(name, dst, n);
    }
}
/* BIGPRIMITIVE */
class INumber extends BCode {
    double n;
    INumber(Register dst, double n) {
        super("bigprim", dst);
        this.n = n;
    }
    @Override
    public void emit(CodeBuffer buf) {
        // TODO: check range of n
        buf.addNumberBigPrimitive(name, logging, l(), dst, n);
    }
    public String toString() {
        return super.toString(name, dst, n);
    }
}
/* BIGPRIMITIVE */
class IString extends BCode {
    String str;
    IString(Register dst, String str) {
        super("bigprim", dst);
        this.str = str;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addStringBigPrimitive(name, logging, l(), dst, str);
    }
    public String toString() {
        return super.toString(name, dst, "\"" + str + "\"");
    }
}
/* SMALLPRIMITIVE */
class IBooleanconst extends BCode {
    boolean b;
    IBooleanconst(Register dst, boolean b) {
        super("specconst", dst);
        this.b = b;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addSpecialSmallPrimitive(name, logging, l(), dst, b ? CodeBuffer.SpecialValue.TRUE : CodeBuffer.SpecialValue.FALSE);
    }
    public String toString() {
        return super.toString(name, dst, b ? "true" : "false");
    }
}
/* SMALLPRIMITIVE */
class INullconst extends BCode {
    INullconst(Register dst) {
        super("specconst", dst);
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addSpecialSmallPrimitive(name, logging, l(), dst, CodeBuffer.SpecialValue.NULL);
    }
    public String toString() {
        return super.toString(name, dst, "null");
    }
}
/* SMALLPRIMITIVE */
class IUndefinedconst extends BCode {
    IUndefinedconst(Register dst) {
        super("specconst", dst);
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addSpecialSmallPrimitive(name, logging, l(), dst, CodeBuffer.SpecialValue.UNDEFINED);
    }
    public String toString() {
        return super.toString(name, dst, "undefined");
    }
}
/* BIGPRIMITIVE */
class IRegexp extends BCode {
    int idx;
    String ptn;
    IRegexp(Register dst, int idx, String ptn) {
        super("bigprim", dst);
        this.idx = idx;
        this.ptn = ptn;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRegexp(name, logging, l(), dst, idx, ptn);
    }
    public String toString() {
        return super.toString(name, dst, idx, "\"" + ptn + "\"");
    }
}
/* THREEOP */
class IAdd extends CauseExceptionBCode {
    SrcOperand src1, src2;
    IAdd(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    IAdd(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("add", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class ISub extends CauseExceptionBCode {
    SrcOperand src1, src2;
    ISub(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    ISub(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("sub", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class IMul extends CauseExceptionBCode {
    SrcOperand src1, src2;
    IMul(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    IMul(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("mul", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class IDiv extends CauseExceptionBCode {
    SrcOperand src1, src2;
    IDiv(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    IDiv(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("div", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class IMod extends CauseExceptionBCode {
    SrcOperand src1, src2;
    IMod(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    IMod(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("mod", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class IBitor extends CauseExceptionBCode {
    SrcOperand src1, src2;
    IBitor(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    IBitor(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("bitor", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class IBitand extends CauseExceptionBCode {
    SrcOperand src1, src2;
    IBitand(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    IBitand(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("bitand", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class ILeftshift extends CauseExceptionBCode {
    SrcOperand src1, src2;
    ILeftshift(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    ILeftshift(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("leftshift", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class IRightshift extends CauseExceptionBCode {
    SrcOperand src1, src2;
    IRightshift(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    IRightshift(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("rightshift", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class IUnsignedrightshift extends CauseExceptionBCode {
    SrcOperand src1, src2;
    IUnsignedrightshift(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    IUnsignedrightshift(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("unsignedrightshift", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class IEqual extends CauseExceptionBCode {
    SrcOperand src1, src2;
    IEqual(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    IEqual(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("equal", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class IEq extends BCode {
    SrcOperand src1, src2;
    IEq(Register dst, Register src1, Register src2) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2));
    }
    IEq(Register dst, SrcOperand src1, SrcOperand src2) {
        super("eq", dst);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class ILessthan extends CauseExceptionBCode {
    SrcOperand src1, src2;
    ILessthan(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    ILessthan(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("lessthan", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* THREEOP */
class ILessthanequal extends CauseExceptionBCode {
    SrcOperand src1, src2;
    ILessthanequal(Register dst, Register src1, Register src2, Label exceptionDest) {
        this(dst, new RegisterOperand(src1), new RegisterOperand(src2), exceptionDest);
    }
    ILessthanequal(Register dst, SrcOperand src1, SrcOperand src2, Label exceptionDest) {
        super("lessthanequal", dst, exceptionDest);
        this.src1 = src1;
        this.src2 = src2;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* TWOOP */
class INot extends CauseExceptionBCode {
    SrcOperand src;
    INot(Register dst, Register src, Label exceptionDest) {
        this(dst, new RegisterOperand(src), exceptionDest);
    }
    INot(Register dst, SrcOperand src, Label exceptionDest) {
        super("not", dst, exceptionDest);
        this.src = src;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXTwoOp(name, logging, l(), dst, src);
    }
    public String toString() {
        return super.toString(name, dst, src);
    }
}
/* ONEOP */
class IGetglobalobj extends BCode {
    IGetglobalobj(Register dst) {
        super("getglobalobj", dst);
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addROneOp(name, logging, l(), dst);
    }
    public String toString() {
        return super.toString(name, dst);
    }
}
/* ZEROOP */
class INewargs extends BCode {
    INewargs() {
        super("newargs");
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addZeroOp(name, logging, l());
    }
    public String toString() {
        return super.toString(name);
    }
}
/* NEWFRAMEOP */
class INewframe extends BCode {
    int len;
    boolean makeArguments;
    INewframe(int len, boolean makeArguments) {
        super("newframe");
        this.len = len;
        this.makeArguments = makeArguments;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addNewFrameOp(name, logging, l(), len, makeArguments);
    }
    public String toString() {
        return super.toString(name, len, makeArguments ? 1 : 0);
    }
}
/* ZEROOP */
class IExitframe extends BCode {
    IExitframe() {
        super("exitframe");
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addZeroOp(name, logging, l());
    }
    public String toString() {
        return super.toString(name);
    }
}
/* TWOOP */
class IGetglobal extends CauseExceptionBCode {
    SrcOperand varName;
    IGetglobal(Register dst, Register name, Label exceptionDest) {
        this(dst, new RegisterOperand(name), exceptionDest);
    }
    IGetglobal(Register dst, SrcOperand name, Label exceptionDest) {
        super("getglobal", dst, exceptionDest);
        this.varName = name;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXTwoOp(name, logging, l(), dst, varName);
    }
    public String toString() {
        return super.toString(name, dst, varName);
    }
}
/* TWOOP */
class ISetglobal extends CauseExceptionBCode {
    SrcOperand varName, src;
    ISetglobal(Register name, Register src, Label exceptionDest) {
        this(new RegisterOperand(name), new RegisterOperand(src), exceptionDest);
    }
    ISetglobal(SrcOperand name, SrcOperand src, Label exceptionDest) {
        super("setglobal", exceptionDest);
        this.varName = name;
        this.src = src;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addXXTwoOp(name, logging, l(), varName, src);
    }
    public String toString() {
        return super.toString(name, varName, src);
    }
}
/* GETVAR */
class IGetlocal extends BCode {
    int link, index;
    IGetlocal(Register dst, int depth, int index) {
        super("getlocal", dst);
        this.link = depth;
        this.index = index;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addGetVar(name, logging, l(), dst, link, index);
    }
    public String toString() {
        return super.toString(name, dst, link, index);
    }
}
/* SETVAR */
class ISetlocal extends BCode {
    int link, index;
    SrcOperand src;
    ISetlocal(int link, int index, Register src) {
        this(link, index, new RegisterOperand(src));
    }
    ISetlocal(int link, int index, SrcOperand src) {
        super("setlocal");
        this.link = link;
        this.index = index;
        this.src = src;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addSetVar(name, logging, l(), link, index, src);
    }
    public String toString() {
        return super.toString(name, link, index, src);
    }
}
/* GETVAR */
class IGetarg extends BCode {
    int link, index;
    IGetarg(Register dst, int link, int index) {
        super("getarg", dst);
        this.link = link;
        this.index = index;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addGetVar(name, logging, l(), dst, link, index);
    }
    public String toString() {
        return super.toString(name, dst, link, index);
    }
}
/* SETVAR */
class ISetarg extends BCode {
    int link, index;
    SrcOperand src;
    ISetarg(int link, int index, Register src) {
        this(link, index, new RegisterOperand(src));
    }
    ISetarg(int link, int index, SrcOperand src) {
        super("setarg");
        this.link = link;
        this.index = index;
        this.src = src;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addSetVar(name, logging, l(), link, index, src);
    }
    public String toString() {
        return super.toString(name, link, index, src);
    }
}
/* THREEOP */
class IGetprop extends BCode {
    SrcOperand obj, prop;
    IGetprop(Register dst, Register obj, Register prop) {
        this(dst, new RegisterOperand(obj), new RegisterOperand(prop));
    }
    IGetprop(Register dst, SrcOperand obj, SrcOperand prop) {
        super("getprop", dst);
        this.obj = obj;
        this.prop = prop;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, obj, prop);
    }
    public String toString() {
        return super.toString("getprop", dst, obj, prop);
    }
}
/* SETPROP */
class ISetprop extends BCode {
    SrcOperand obj, prop, src;
    ISetprop(Register obj, Register prop, Register src) {
        this(new RegisterOperand(obj), new RegisterOperand(prop), new RegisterOperand(src));
    }
    ISetprop(SrcOperand obj, SrcOperand prop, SrcOperand src) {
        super("setprop");
        this.obj = obj;
        this.prop = prop;
        this.src = src;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addXXXThreeOp(name, logging, l(), obj, prop, src);
    }
    public String toString() {
        return super.toString("setprop", obj, prop, src);
    }
}
/* MAKECLOSUREOP */
class IMakeclosure extends BCode {
    BCBuilder.FunctionBCBuilder function;
    IMakeclosure(Register dst, BCBuilder.FunctionBCBuilder function) {
        super("makeclosure", dst);
        this.function = function;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addMakeClosureOp(name, logging, l(), dst, function.getIndex());
    }
    public String toString() {
        return super.toString(name, dst, function.getIndex());
    }
}
/* ONEOP */
class IGeta extends BCode {
    IGeta(Register dst) {
        super("geta", dst);
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addROneOp(name, logging, l(), dst);
    }
    public String toString() {
        return super.toString(name, dst);
    }
}
/* ONEOP */
class IGetNewa extends BCode {
    SrcOperand dst;
    IGetNewa(Register dst) {
        this(new RegisterOperand(dst));
    }
    IGetNewa(RegisterOperand dst) {
        super("getnewa", dst.get());
        this.dst = dst;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addXOneOp(name, logging, l(), dst);
    }
    public String toString() {
        return super.toString(name, dst);
    }
}
/* ONEOP */
class ISeta extends BCode {
    SrcOperand src;
    ISeta(Register src) {
        this(new RegisterOperand(src));
    }
    ISeta(SrcOperand src) {
        super("seta");
        this.src = src;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addXOneOp(name, logging, l(), src);
    }
    public String toString() {
        return super.toString(name, src);
    }
}
/* RET */
class IRet extends BCode {
    IRet() {
        super("ret");
    }
    @Override
    public boolean isFallThroughInstruction() {
        return false;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addZeroOp(name, logging, l());
    }
    public String toString() {
        return super.toString(name);
    }
}
/* TWOOP */
class IMove extends BCode {
    SrcOperand src;
    IMove(Register dst, Register src) {
        super("move", dst);
        this.src = new RegisterOperand(src);
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXTwoOp(name, logging, l(), dst, src);
    }
    public String toString() {
        return super.toString(name, dst, src);
    }
}
/* TWOOP */
class IIsundef extends BCode {
    SrcOperand src;
    IIsundef(Register dst, Register src) {
        super("isundef", dst);
        this.src = new RegisterOperand(src);
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXTwoOp(name, logging, l(), dst, src);
    }
    public String toString() {
        return super.toString(name, dst, src);
    }
}
/* TWOOP */
class IIsobject extends BCode {
    SrcOperand src;
    IIsobject(Register dst, Register src) {
        super("isobject", dst);
        this.src = new RegisterOperand(src);
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXTwoOp(name, logging, l(), dst, src);
    }
    public String toString() {
        return super.toString(name, dst, src);
    }
}
/* THREEOP */
class IInstanceof extends BCode {
    SrcOperand src1, src2;
    IInstanceof(Register dst, Register src1, Register src2) {
        super("instanceof", dst);
        this.src1 = new RegisterOperand(src1);
        this.src2 = new RegisterOperand(src2);
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXXThreeOp(name, logging, l(), dst, src1, src2);
    }
    public String toString() {
        return super.toString(name, dst, src1, src2);
    }
}
/* CALLOP */
class ICall extends BCode {
    SrcOperand function;
    int numOfArgs;
    ICall(Register function, int numOfArgs) {
        super("call");
        this.function = new RegisterOperand(function);
        this.numOfArgs = numOfArgs;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addXICall(name, logging, l(), function, numOfArgs);
    }
    public String toString() {
        return super.toString(name, function, numOfArgs);
    }
}
/* CALL */
class ISend extends BCode {
    SrcOperand function;
    int numOfArgs;
    ISend(Register function, int numOfArgs) {
        super("send");
        this.function = new RegisterOperand(function);
        this.numOfArgs = numOfArgs;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addXICall(name, logging, l(), function, numOfArgs);
    }
    public String toString() {
        return super.toString(name, function, numOfArgs);
    }
}
/* THREEOP */
class IConstruct extends BCode {
    SrcOperand receiver;
    SrcOperand constructor;
    int numOfArgs;
    IConstruct(Register receiver, Register constructor, int numOfArgs) {
        super("construct");
        this.receiver = new RegisterOperand(receiver);
        this.constructor = new RegisterOperand(constructor);
        this.numOfArgs = numOfArgs;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addXXIConstruct(name, logging, l(), receiver, constructor, numOfArgs);
    }
    public String toString() {
        return super.toString(name, receiver, constructor, numOfArgs);
    }
}
/* TWOOP */
class IMakeiterator extends BCode {
    SrcOperand obj;
    IMakeiterator(Register obj, Register dst) {
        super("makeiterator", dst);
        this.obj = new RegisterOperand(obj);
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXTwoOp(name, logging, l(), dst, obj);
    }
    public String toString() {
        return super.toString(name, dst, obj);
    }
}
/* TWOOP */
class INextpropnameidx extends BCode {
    SrcOperand ite;
    INextpropnameidx(Register ite, Register dst) {
        super("nextpropnameidx", dst);
        this.ite = new RegisterOperand(ite);
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addRXTwoOp(name, logging, l(), dst, ite);
    }
    public String toString() {
        return super.toString(name, dst, ite);
    }
}
/* UNCONDJUMP */
class IJump extends BCode {
    Label label;
    IJump(Label label) {
        super("jump");
        this.label = label;
    }
    @Override
    public boolean isFallThroughInstruction() {
        return false;
    }
    @Override
    public BCode getBranchTarget() {
        return label.getDestBCode();
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addUncondJump(name, logging, l(), label.dist(address));
    }
    public String toString() {
        return super.toString(name, label.dist(address));
    }
}
/* CONDJUMP */
class IJumptrue extends BCode {
    SrcOperand test;
    Label label;
    IJumptrue(Label label, Register test) {
        super("jumptrue");
        this.label = label;
        this.test = new RegisterOperand(test);
    }
    @Override
    public BCode getBranchTarget() {
        return label.getDestBCode();
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addCondJump(name, logging, l(), test, label.dist(address));
    }
    public String toString() {
        return super.toString(name, test, label.dist(address));
    }
}
/* CONDJUMP */
class IJumpfalse extends BCode {
    SrcOperand test;
    Label label;
    IJumpfalse(Label label, Register test) {
        super("jumpfalse");
        this.label = label;
        this.test = new RegisterOperand(test);
    }
    @Override
    public BCode getBranchTarget() {
        return label.getDestBCode();
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addCondJump(name, logging, l(), test, label.dist(address));
    }
    public String toString() {
        return super.toString(name, test, label.dist(address));
    }
}
/* ONEOP */
class IThrow extends CauseExceptionBCode {
    SrcOperand reg;
    IThrow(Register reg, Label exceptionDest) {
        super("throw", exceptionDest);
        this.reg = new RegisterOperand(reg);
    }
    @Override
    public boolean isFallThroughInstruction()  {
        return false;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addXOneOp(name, logging, l(), reg);
    }
    public String toString() {
        return super.toString(name, reg);
    }
}
/* UNCONDJUMP */
class IPushhandler extends BCode {
    Label label;
    IPushhandler(Label label) {
        super("pushhandler");
        this.label = label;
    }
    public Label getHandlerLabel() {
        return label;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addUncondJump(name, logging, l(), label.dist(address));
    }
    public String toString() {
        return super.toString(name, label.dist(address));
    }
}
/* ZEROOP */
class IPophandler extends BCode {
    IPophandler() {
        super("pophandler");
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addZeroOp(name, logging, l());
    }
    public String toString() {
        return super.toString(name);
    }
}
/* UNCONDJUMP */
class ILocalcall extends BCode {
    Label label;
    ILocalcall(Label label) {
        super("localcall");
        this.label = label;
    }
    @Override
    public BCode getBranchTarget() {
        return label.getDestBCode();
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addUncondJump(name, logging, l(), label.dist(address));
    }
    public String toString() {
        return super.toString("localcall", label.dist(address));
    }
}
/* ZEROOP */
class ILocalret extends BCode {
    ILocalret() {
        super("localret");
    }
    @Override
    public boolean isFallThroughInstruction() {
        return false;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addZeroOp(name, logging, l());
    }
    public String toString() {
        return super.toString(name);
    }
}
/* ZEROOP */
class IPoplocal extends BCode {
    IPoplocal() {
        super("poplocal");
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addZeroOp(name, logging, l());
    }
    public String toString() {
        return super.toString("poplocal");
    }
}
/* ONEOP */
class ISetfl extends BCode {
    int fl;
    ISetfl(int fl) {
        super("setfl");
        this.fl = fl;
    }
    @Override
    public void emit(CodeBuffer buf) {
        buf.addIOneOp(name, logging, l(), fl);
    }
    public String toString() {
        return super.toString(name, fl);
    }
}
/* macro instruction */
class MSetfl extends BCode {
    MSetfl() {
        super("@Msetfl");
    }
    @Override
    public void emit(CodeBuffer buf) {
        throw new Error("attempt to emit a macro instruction MSetfl");
    }
    @Override
    public String toString() {
        return "@MACRO setfl";
    }
}

class MCall extends CauseExceptionBCode {
    SrcOperand receiver;
    SrcOperand function;
    SrcOperand[] args;
    boolean isTail;
    MCall(Register receiver, Register function, Register[] args, boolean isTail, Label exceptionDest) {
        super("@Mcall", exceptionDest);
        this.receiver = receiver == null ? null : new RegisterOperand(receiver);
        this.function = new RegisterOperand(function);
        this.args = new SrcOperand[args.length];
        for (int i = 0; i < args.length; i++)
            this.args[i] = new RegisterOperand(args[i]);
        this.isTail = isTail;
    }
    @Override
    public HashSet<Register> getSrcRegisters() {
        HashSet<Register> srcs = new HashSet<Register>();
        if (receiver != null && receiver instanceof RegisterOperand)
            srcs.add(((RegisterOperand) receiver).get());
        if (function instanceof RegisterOperand)
            srcs.add(((RegisterOperand) function).get());
        for (SrcOperand opx: args) {
            if (opx instanceof RegisterOperand)
                srcs.add(((RegisterOperand) opx).get());
        }
        return srcs;
    }
    @Override
    public void emit(CodeBuffer buf) {
        throw new Error("attempt to emit a macro instruction MCall");
    }
    @Override
    public String toString() {
        String s ="@MACRO ";

        if (isTail)
            s += "tail";
        else if (receiver == null)
            s += "call " + function;
        else
            s += "send " + receiver + " " + function;
        for (SrcOperand opx: args)
            s += " " + opx;
        return s;
    }
}

class MConstruct extends CauseExceptionBCode {
    SrcOperand constructor;
    SrcOperand[] args;
    MConstruct(Register dst, Register constructor, Register[] args, Label exceptionDest) {
        super("@MConstruct", dst, exceptionDest);
        this.constructor = new RegisterOperand(constructor);
        this.args = new SrcOperand[args.length];
        for (int i = 0; i < args.length; i++)
            this.args[i] = new RegisterOperand(args[i]);
    }
    @Override
    public HashSet<Register> getSrcRegisters() {
        HashSet<Register> srcs = new HashSet<Register>();
        srcs.add(dst);
        if (constructor instanceof RegisterOperand)
            srcs.add(((RegisterOperand) constructor).get());
        for (SrcOperand opx: args) {
            if (opx instanceof RegisterOperand)
                srcs.add(((RegisterOperand) opx).get());
        }
        return srcs;
    }
    @Override
    public void emit(CodeBuffer buf) {
        throw new Error("attempt to emit a macro instruction MConstruct");
    }
    @Override
    public String toString() {
        String s ="@MACRO " + "construct " + dst + " " + constructor;

        for (SrcOperand opx: args)
            s += " " + opx;
        return s;
    }
}

class MParameter extends BCode {
    MParameter(Register dst) {
        super("@Mparameter", dst);
    }
    @Override
    public void emit(CodeBuffer buf) {
        throw new Error("attempt to emit a macro instruction MParameter");
    }
    @Override
    public String toString() {
        return "@MACRO param "+dst;
    }
}
