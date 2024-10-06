/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package ejsc;

import java.io.FileWriter;

import java.io.IOException;
import java.io.Writer;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.nio.charset.StandardCharsets;

import ejsc.CodeBuffer.SourceLocation;
import ejsc.CodeBuffer.SpecialValue;
import ejsc.VMImplementation;
import ejsc.VMImplementation.InstructionRepresentation;
import ejsc.VMImplementation.JSValueRepresentation;

import specfile.SpecFile;

public class EIFileComposer extends OutputFileComposer {
    static final boolean DEBUG = false;

    static final boolean BIG_ENDIAN = true;

    static class EIInstruction {
        enum Format {
            ABC,
            AB
        }

        static EIInstruction createAB(String insnName, int opcode, int a, int b) {
            return new EIInstruction(insnName, opcode, Format.AB, a, b, 0);
        }

        static EIInstruction createABC(String insnName, int opcode, int a, int b, int c) {
            return new EIInstruction(insnName, opcode, Format.ABC, a, b, c);
        }

        String insnName;  /* debug */
        int opcode;
        Format format;
        int a, b, c;

        EIInstruction(String insnName, int opcode, Format format, int a, int b, int c) {
            this.insnName = insnName;
            this.opcode = opcode;
            this.format = format;
            this.a = a;
            this.b = b;
            this.c = c;
        }

        /**
         * Returns label of the instruction.
         * 
         * @return label of this instruction as String.
         */
        String getLabel() {
            return "I_" + insnName.toUpperCase();
        }

        /**
         * Returns byte code of the instruction.
         * 
         * @return byte code of this instruction as long.
         */
        long getCode(InstructionRepresentation insnRep) {
            long insn = ((long) opcode) << insnRep.opcodeOffset();
            switch (format) {
            case ABC:
                insn |= (((long) a) << insnRep.aOffset()) & insnRep.aMask();
                insn |= (((long) b) << insnRep.bOffset()) & insnRep.bMask();
                insn |= (((long) c) << insnRep.cOffset()) & insnRep.cMask();
                break;
            case AB:
                insn |= (((long) a) << insnRep.aOffset()) & insnRep.aMask();
                insn |= (((long) b) << insnRep.bbOffset()) & insnRep.bbMask();
                break;
            default:
                throw new Error("Unknown instruction format");
            }

            return insn;
        }
    }

    static class EIConstant {
        enum Type {
            Fixnum, Double, String
        }

        static EIConstant CreateFixnumConstant(VMImplementation vmImpl, long val, int index) {
            return new EIConstant(vmImpl, Type.Fixnum, val, 0.0, null, index);
        }
        static EIConstant CreateDoubleConstant(VMImplementation vmImpl, double val, int index) {
            return new EIConstant(vmImpl, Type.Double, 0, val, null, index);
        }
        static EIConstant CreateStringConstant(VMImplementation vmImpl, String val, int index) {
            return new EIConstant(vmImpl, Type.String, 0, 0.0, val, index);
        }

        EIConstant(VMImplementation vmImpl, Type type, long fix, double dbl, String str, int index) {
            this.type = type;
            this.bytePerWord = vmImpl.getSpec().getBitWidthDef().getBitWidth().getAlignWidth() / 8;
            this.fix = fix;
            this.dbl = dbl;
            this.rawstr = str;
            this.index = index;

            if (str == null)
                this.str = null;
            else {
                int expect = (((str.length() + 1) + (bytePerWord - 1)) / bytePerWord) * bytePerWord;
                int toAppend = expect - (str.length() + 1);
                String tmp = str + "\0";
                while (toAppend > 0) {
                    tmp += "\0";
                    --toAppend;
                }
                this.str = tmp;
            }
        }

        Type type;
        int bytePerWord;
        long fix;
        double dbl;
        String rawstr, str;
        int index;

        boolean isFixnum() {
            return type == Type.Fixnum;
        }
        boolean isDouble() {
            return type == Type.Double;
        }
        boolean isString() {
            return type == Type.String;
        }

        long rawFixnum() {
            return fix;
        }
        double rawDouble() {
            return dbl;
        }
        String rawString() {
            return rawstr;
        }

        String varname() {
            return "eiconstant_" + String.format("%04d", index);
        }
        String sectionname() {
            return ".ejs_constant_" + String.format("%04d", index);
        }
        String symbolname() {
            return "__" + varname() + "_JSValue";
        }
        String typename() {
            if (type == Type.Fixnum)
                return "Fixnum";
            else if (type == Type.Double)
                return "Double";
            else
                return "String";
        }
        /* This method return only size of payload in JSValue words.  */
        int size() {
            if (type == Type.Fixnum)
                return 0;
            else if (type == Type.Double)
                return 8 / bytePerWord;
            else
                return (4 * 2 + str.length()) / bytePerWord;
        }
        String ptag() {
            if (type == Type.Fixnum)
                return "PTAGV_FIXNUM";
            else if (type == Type.Double)
                return "PTAGV_FLONUM";
            else
                return "PTAGV_STRING";
        }
        String htag() {
            if (type == Type.Fixnum)
                throw new Error("Fixnum dose not have htag.");
            else if (type == Type.Double)
                return "HTAGV_FLONUM";
            else
                return "HTAGV_STRING";
        }
        String val() {
            if (type == Type.Fixnum)
                return "" + fix;
            else if (type == Type.Double)
                return "" + dbl;
            else
                return str;
        }
    }

    static class EIConstantPool {
        int count = 0;
        Map<Object, Integer> table = new HashMap<Object, Integer>();
        List<EIConstant> array = new ArrayList<EIConstant>();

        EIConstant doLookup(VMImplementation vmImpl, Object x) {
            if (table.containsKey(x))
                return array.get(table.get(x));

            EIConstant constant;
            if (x instanceof Double) {
                if (vmImpl.getJSVRep().inFixnumRange((Double) x))
                    constant = EIConstant.CreateFixnumConstant(vmImpl, (long) ((double) (Double) x), count);
                 else
                    constant = EIConstant.CreateDoubleConstant(vmImpl, (Double) x, count);
            }
            else if (x instanceof String)
                constant = EIConstant.CreateStringConstant(vmImpl, (String) x, count);
            else
                throw new Error("Unknown constant type");

            table.put(x, count++);
            array.add(constant);

            return constant;
        }

        List<EIConstant> getConstants() {
            return array;
        }

        int size() {
            return array.size();
        }
    }

    static class EIConstantTable {
        static EIConstantPool pool = new EIConstantPool();

        int count = 0;
        Map<Object, Integer> table = new HashMap<Object, Integer>();
        List<EIConstant> array = new ArrayList<EIConstant>();

        private int doLookup(VMImplementation vmImpl, Object x) {
            if (table.containsKey(x))
                return table.get(x);
            table.put(x, count);

            EIConstant constant = pool.doLookup(vmImpl, x);
            array.add(constant);

            return count++;
        }

        int lookup(VMImplementation vmImpl, double n) {
            return doLookup(vmImpl, n);
        }

        int lookup(VMImplementation vmImpl, String n) {
            return doLookup(vmImpl, n);
        }

        List<EIConstant> getConstants() {
            return array;
        }

        int size() {
            return array.size();
        }
    }

    class EIFunction implements CodeBuffer {
        /* function header */
        int callEntry;
        int sendEntry;
        int numberOfLocals;

        VMImplementation vmImpl;
        int index;

        EIConstantTable constants = new EIConstantTable();
        List<EIInstruction> instructions;

        EIFunction(VMImplementation vmImpl, BCBuilder.FunctionBCBuilder fb, int index) {
            List<BCode> bcodes = fb.getInstructions();
            this.callEntry = fb.callEntry.dist(0);
            this.sendEntry = fb.sendEntry.dist(0);
            this.numberOfLocals = fb.numberOfLocals;

            this.vmImpl = vmImpl;
            this.index = index;

            instructions = new ArrayList<EIInstruction>(bcodes.size());
            for (BCode bc : bcodes)
                bc.emit(this);
        }

        String decorateInsnName(String insnName, SrcOperand... srcs) {
            String decorated = EIFileComposer.decorateInsnName(insnName, srcs);
            if (decorated != null)
                insnName = decorated;
            return insnName;
        }

        int getOpcode(String decoratedInsnName, SrcOperand... srcs) {
            return spec.getOpcodeIndex(decoratedInsnName);
        }

        int fieldBitsOf(SrcOperand src) {
            if (src instanceof RegisterOperand) {
                Register r = ((RegisterOperand) src).get();
                int n = r.getRegisterNumber();
                return n;
            } else if (src instanceof FixnumOperand) {
                long n = ((FixnumOperand) src).get();
                return (int) n;
            } else if (src instanceof FlonumOperand) {
                double n = ((FlonumOperand) src).get();
                int index = constants.lookup(vmImpl, n);
                return index;
            } else if (src instanceof StringOperand) {
                String s = ((StringOperand) src).get();
                int index = constants.lookup(vmImpl, s);
                return index;
            } else if (src instanceof SpecialOperand) {
                SpecialValue v = ((SpecialOperand) src).get();
                return jsvRep.specialFieldValue(v);
            } else
                throw new Error("Unknown source operand");
        }

        @Override
        public void addFixnumSmallPrimitive(String insnName, boolean log, SourceLocation sloc, Register dst, int n) {
            if (insnRep.inSmallPrimitiveRange(n)) {
                insnName = decorateInsnName(insnName);
                int opcode = getOpcode(insnName);
                int a = dst.getRegisterNumber();
                int b = n;
                EIInstruction insn = EIInstruction.createAB(insnName, opcode, a, b);
                instructions.add(insn);
            } else
                addNumberBigPrimitive("bigprim", log, sloc, dst, (double) n);
        }
        @Override
        public void addNumberBigPrimitive(String insnName, boolean log, SourceLocation sloc, Register dst, double n) {
            insnName = decorateInsnName(insnName);
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            int b = constants.lookup(vmImpl, n);
            EIInstruction insn = EIInstruction.createAB(insnName, opcode, a, b);
            instructions.add(insn);

        }
        @Override
        public void addStringBigPrimitive(String insnName, boolean log, SourceLocation sloc, Register dst, String s) {
            insnName = decorateInsnName(insnName);
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            int b = constants.lookup(vmImpl, s);
            EIInstruction insn = EIInstruction.createAB(insnName, opcode, a, b);
            instructions.add(insn);
        }
        @Override
        public void addSpecialSmallPrimitive(String insnName, boolean log, SourceLocation sloc, Register dst, SpecialValue v) {
            insnName = decorateInsnName(insnName);
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            int b = jsvRep.specialFieldValue(v);
            EIInstruction insn = EIInstruction.createAB(insnName, opcode, a, b);
            instructions.add(insn);
        }
        @Override
        public void addRegexp(String insnName, boolean log, SourceLocation sloc, Register dst, int flag, String ptn) {
            throw new Error("not supported RegExp literal in EmbeddedInstruction");
/*
            insnName = decorateInsnName(insnName);
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            int c = constants.lookup(vmImpl, ptn);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, flag, c);
            instructions.add(insn);
*/
        }
        @Override
        public void addRXXThreeOp(String insnName, boolean log, SourceLocation sloc, Register dst, SrcOperand src1, SrcOperand src2) {
            insnName = decorateInsnName(insnName, src1, src2);
            int opcode = getOpcode(insnName, src1, src2);
            int a = dst.getRegisterNumber();
            int b = fieldBitsOf(src1);
            int c = fieldBitsOf(src2);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, b, c);
            instructions.add(insn);
        }
        @Override
        public void addXXXThreeOp(String insnName, boolean log, SourceLocation sloc, SrcOperand src1, SrcOperand src2, SrcOperand src3) {
            insnName = decorateInsnName(insnName, src1, src2, src3);
            int opcode = getOpcode(insnName, src1, src2, src3);
            int a = fieldBitsOf(src1);
            int b = fieldBitsOf(src2);
            int c = fieldBitsOf(src3);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, b, c);
            instructions.add(insn);
        }
        @Override
        public void addXIXThreeOp(String insnName, boolean log, SourceLocation sloc, SrcOperand src1, int index, SrcOperand src2) {
            insnName = decorateInsnName(insnName, src1, src2);
            int opcode = getOpcode(insnName, src1, src2);
            int a = fieldBitsOf(src1);
            int c = fieldBitsOf(src2);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, index, c);
            instructions.add(insn);
        }
        @Override
        public void addRXTwoOp(String insnName, boolean log, SourceLocation sloc, Register dst, SrcOperand src) {
            insnName = decorateInsnName(insnName, src);
            int opcode = getOpcode(insnName, src);
            int a = dst.getRegisterNumber();
            int b = fieldBitsOf(src);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, b, 0);
            instructions.add(insn);
        }
        @Override
        public void addXXTwoOp(String insnName, boolean log, SourceLocation sloc, SrcOperand src1, SrcOperand src2) {
            insnName = decorateInsnName(insnName, src1, src2);
            int opcode = getOpcode(insnName, src1, src2);
            int a = fieldBitsOf(src1);
            int b = fieldBitsOf(src2);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, b, 0);
            instructions.add(insn);
        }
        @Override
        public void addROneOp(String insnName, boolean log, SourceLocation sloc, Register dst) {
            insnName = decorateInsnName(insnName);
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, 0, 0);
            instructions.add(insn);
        }
        @Override
        public void addXOneOp(String insnName, boolean log, SourceLocation sloc, SrcOperand src) {
            insnName = decorateInsnName(insnName, src);
            int opcode = getOpcode(insnName, src);
            int a = fieldBitsOf(src);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, 0, 0);
            instructions.add(insn);
        }
        @Override
        public void addIOneOp(String insnName, boolean log, SourceLocation sloc, int n) {
            insnName = decorateInsnName(insnName);
            int opcode = getOpcode(insnName);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, n, 0, 0);
            instructions.add(insn);
        }
        @Override
        public void addZeroOp(String insnName, boolean log, SourceLocation sloc) {
            insnName = decorateInsnName(insnName);
            int opcode = getOpcode(insnName);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, 0, 0, 0);
            instructions.add(insn);
        }
        @Override
        public void addNewFrameOp(String insnName, boolean log, SourceLocation sloc, int len, boolean mkargs) {
            insnName = decorateInsnName(insnName);
            int opcode = getOpcode(insnName);
            int b = mkargs ? 1 : 0;
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, len, b, 0);
            instructions.add(insn);
        }
        @Override
        public void addGetVar(String insnName, boolean log, SourceLocation sloc, Register dst, int link, int index) {
            insnName = decorateInsnName(insnName);
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, link, index);
            instructions.add(insn);
        }
        @Override
        public void addSetVar(String insnName, boolean log, SourceLocation sloc, int link, int index, SrcOperand src) {
            insnName = decorateInsnName(insnName, src);
            int opcode = getOpcode(insnName, src);
            int c = fieldBitsOf(src);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, link, index, c);
            instructions.add(insn);
        }
        @Override
        public void addMakeClosureOp(String insnName, boolean log, SourceLocation sloc, Register dst, int index) {
            insnName = decorateInsnName(insnName);
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            // int b = index + functionNumberOffset;
            int b = index;
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, b, 0);
            instructions.add(insn);
        }
        @Override
        public void addXICall(String insnName, boolean log, SourceLocation sloc, SrcOperand fun, int nargs) {
            insnName = decorateInsnName(insnName, fun);
            int opcode = getOpcode(insnName, fun);
            int a = fieldBitsOf(fun);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, nargs, 0);
            instructions.add(insn);
        }
        @Override
        public void addRXCall(String insnName, boolean log, SourceLocation sloc, Register dst, SrcOperand fun) {
            insnName = decorateInsnName(insnName, fun);
            int opcode = getOpcode(insnName, fun);
            int a = dst.getRegisterNumber();
            int b = fieldBitsOf(fun);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, b, 0);
            instructions.add(insn);
        }
        @Override
        public void addXXIConstruct(String insnName, boolean log, SourceLocation sloc, SrcOperand receiver, SrcOperand constructor, int nargs) {
            int opcode = getOpcode(insnName, receiver, constructor);
            int a = fieldBitsOf(receiver);
            int b = fieldBitsOf(constructor);
            EIInstruction insn = EIInstruction.createABC(insnName, opcode, a, b, nargs);
            instructions.add(insn);
        }
        @Override
        public void addUncondJump(String insnName, boolean log, SourceLocation sloc, int disp) {
            insnName = decorateInsnName(insnName);
            int opcode = getOpcode(insnName);
            EIInstruction insn = EIInstruction.createAB(insnName, opcode, 0, disp);
            instructions.add(insn);
        }
        @Override
        public void addCondJump(String insnName, boolean log, SourceLocation sloc, SrcOperand test, int disp) {
            insnName = decorateInsnName(insnName, test);
            int opcode = getOpcode(insnName, test);
            int a = fieldBitsOf(test);
            EIInstruction insn = EIInstruction.createAB(insnName, opcode, a, disp);
            instructions.add(insn);
        }
    }

    List<EIFunction> EIFunctions;

    EIFileComposer(BCBuilder compiledFunctions, VMImplementation vmImpl) {
        super(vmImpl);
        List<BCBuilder.FunctionBCBuilder> fbs = compiledFunctions.getFunctionBCBuilders();
        EIFunctions = new ArrayList<EIFunction>(fbs.size());

        int index = 0;
        for (BCBuilder.FunctionBCBuilder fb : fbs) {
            EIFunction out = new EIFunction(vmImpl, fb, index);
            EIFunctions.add(out);
            ++index;
        }
    }

    private void outputPrologueTypedef(Writer out) throws IOException {
        out.write("/* Embedded Instructions */\n");
        out.write("union tmp_JSValue {\n");
        out.write("  struct {\n");
        out.write("    unsigned int tag : TAGOFFSET;\n");
        out.write("    uintptr_t ptr : (8 * (1 << LOG_BYTES_IN_JSVALUE)) - TAGOFFSET;\n");
        out.write("  };\n");
        out.write("  uintptr_t value;\n");
        out.write("};\n");
        out.write("struct tmp_JSDouble {\n");
        out.write("  header_t hdr /* __attribute__ ((packed)) */;\n");
        out.write("  double value __attribute__ ((packed));\n");
        out.write("};\n");
        out.write("struct tmp_JSString {\n");
        out.write("  header_t hdr /* __attribute__ ((packed)) */;\n");
        out.write("#ifdef STROBJ_HAS_HASH\n");
        out.write("  uint32_t hash /* __attribute__ ((packed)) */;\n");
        out.write("  uint32_t length /* __attribute__ ((packed)) */;\n");
        out.write("#endif /* STROBJ_HAS_HASH */\n");
        out.write("  const char value /* __attribute__ ((packed)) */ [];\n");
        out.write("};\n");
        out.write("union tmp_JSConstant {\n");
        out.write("  const struct tmp_JSString *pString;\n");
        out.write("  const struct tmp_JSDouble *pDouble;\n");
        out.write("};\n");
        out.write("\n");
    }

    private void outputPrologueMacro(Writer out) throws IOException {
        out.write("/* Embedded Instructions */\n");
        out.write("#define PTAGV_FIXNUM TV_FIXNUM\n");
        out.write("#ifdef TV_FLONUM\n");
        out.write("#define PTAGV_FLONUM TV_FLONUM\n");
        out.write("#else /* TV_FLONUM */\n");
        out.write("#define PTAGV_FLONUM TV_GENERIC\n");
        out.write("#endif /* TV_FLONUM */\n");
        out.write("#ifdef TV_STRING\n");
        out.write("#define PTAGV_STRING TV_STRING\n");
        out.write("#else /* TV_STRING */\n");
        out.write("#define PTAGV_STRING TV_GENERIC\n");
        out.write("#endif /* TV_STRING */\n");
        out.write("\n");
    }

    private void outputPrologue(Writer out) throws IOException {
        outputPrologueTypedef(out);
        outputPrologueMacro(out);
    }

    private void outputInstruction(Writer out, EIInstruction insn) throws IOException {
        out.write("  { .ilabel = &&" + insn.getLabel() + ", .code = (Bytecode) " + insn.getCode(insnRep) + " },\n");
    }

    private void outputInstructions(Writer out, List<EIInstruction> insns, int index) throws IOException {
        out.write("static const struct instruction eicode" + index + "[] __attribute__ ((section (\".ejs_instruction\"))) = {\n");
        for (EIInstruction insn : insns)
            outputInstruction(out, insn);
        out.write("};\n");
    }

    private void outputObjectHeader(Writer out, int size, String htag) throws IOException {
        out.write("  .hdr = {\n");

	// Mark-Sweep
        out.write("#ifdef MARKSWEEP\n");
        out.write("    .type = " + htag + ",\n");
        out.write("    .extra = 0,\n");
        out.write("    .markbit = 1,\n");
        out.write("#if HEADER_MAGIC_BITS > 0\n");
        out.write("    .magic = HEADER_MAGIC,\n");
        out.write("#endif /* HEADER_MAGIC_BITS > 0 */\n");
        out.write("#if HEADER_GEN_BITS > 0\n");
        out.write("    .gen = 0,\n");
        out.write("#endif /* HEADER_GEN_BITS > 0 */\n");
        out.write("    .size = HEADER_GRANULES + " + size + "\n");
        out.write("#endif /* MARKSWEEP */\n");

	// Threaded
        out.write("#ifdef THREADED\n");
        out.write("    .type = " + htag + ",\n");
        out.write("    .markbit = 1,\n");
        out.write("#if HEADER_MAGIC_BITS > 0\n");
        out.write("    .magic = HEADER_MAGIC,\n");
        out.write("#endif /* HEADER_MAGIC_BITS > 0 */\n");
        out.write("#if HEADER_GEN_BITS > 0\n");
        out.write("    .gen = 0,\n");
        out.write("#endif /* HEADER_GEN_BITS > 0 */\n");
        out.write("    .size = HEADER_GRANULES + " + size + ",\n");
        out.write("    .identifier = 1\n");
        out.write("#endif /* THREADED */\n");

	// Copy
        out.write("#ifdef COPY\n");
        out.write("    .size = HEADER_GRANULES + " + size + ",\n");
        out.write("    .type = " + htag + ",\n");
        out.write("    .forwarded = 0\n");
        out.write("#endif /* COPY */\n");

	// Lisp2
        out.write("#ifdef LISP2\n");
        out.write("    .type = " + htag + ",\n");
        out.write("    .markbit = 1,\n");
        out.write("#if HEADER_MAGIC_BITS > 0\n");
        out.write("    .magic = HEADER_MAGIC,\n");
        out.write("#endif /* HEADER_MAGIC_BITS > 0 */\n");
        out.write("#if HEADER_GEN_BITS > 0\n");
        out.write("    .gen = 0,\n");
        out.write("#endif /* HEADER_GEN_BITS > 0 */\n");
        out.write("    .size = HEADER_GRANULES + " + size + "\n");
        out.write("#endif /* LISP2 */\n");

        out.write("  },\n");
    }

    private int update_hash(int hash, String s) {
        for (int i = 0; i < s.length(); i++) {
            hash += (int)s.charAt(i);
            hash += (hash << 10);
            hash ^= hash >>> 6;
        }
        return hash;
    }

    private int finalise_hash(int hash) {
        hash += hash << 3;
        hash ^= hash >>> 11;
        hash += hash << 15;
        return hash;
    }

    private int makeHash(String s) {
        return finalise_hash(update_hash(0, s));
    }

    private void outputConstant(Writer out, EIConstant constant) throws IOException {
        if (constant.isFixnum())
            return;

        String typename  = "tmp_JS" + constant.typename();
        String varname   = constant.varname();
        String attribute = "__attribute__ ((section (\"" + constant.sectionname() + "\"), used))";
        out.write("static const struct " + typename + " " + varname + " " + attribute + " = {\n");
        outputObjectHeader(out, constant.size(), constant.htag());
        if (constant.isString()) {
            String rawStr = constant.rawString();
            byte str[] = constant.val().getBytes(StandardCharsets.UTF_8);
            int count = -1;

            out.write("#ifdef STROBJ_HAS_HASH\n");
            out.write("  .hash = " + makeHash(rawStr) + ",\n");
            out.write("  .length = " + rawStr.length() + ",\n");
            out.write("#endif /* STROBJ_HAS_HASH */\n");
            out.write("  /* " + rawStr + " */\n");
            out.write("  .value = {");
            for (byte b: str) {
                count = (count + 1) % 4;
                if (count == 0)
                    out.write("\n   ");

                int i = ((int) b) & 0x000000FF;
                out.write(" " + i + ",");
            }
            out.write("\n  }\n");
        }
        else
            out.write("  .value = " + constant.val() + "\n");
        out.write("};\n");
    }

    private void outputConstantAsJSValue(Writer out, EIConstant constant) throws IOException {
        if (constant.isFixnum())
            out.write("  { .ptr = " + constant.rawFixnum() + ", .tag = " + constant.ptag() + " },\n");
        else
            out.write("  { .value = (JSValue) &" + constant.symbolname() + " },\n");
    }

    private void outputConstants(Writer out, EIConstantTable consts, int funcindex) throws IOException {
        for (EIConstant constant : consts.getConstants()) {
            if (constant.isFixnum())
                continue;
            out.write("extern const uintptr_t " + constant.symbolname() + ";\n");
        }

        out.write("static const union tmp_JSValue eiconsts" + funcindex + "[] __attribute__ ((section (\".ejs_function\"))) = {\n");
        for (EIConstant constant : consts.getConstants()) {
            outputConstantAsJSValue(out, constant);
        }
        out.write("};\n");
    }

    private void outputConstantsLinkerScriptCode(Writer out, EIConstantPool pool) throws IOException {
        for (EIConstant constant : pool.getConstants()) {
            if (constant.isFixnum())
                continue;

            out.write("    " + constant.symbolname() + " = (. + (HEADER_GRANULES * BYTES_IN_GRANULE)) + " + constant.ptag() + ";\n");
            out.write("    KEEP(*(" + constant.sectionname() + "))\n");
        }
    }

    private void outputFunction(Writer out, EIFunction fun) throws IOException {
        out.write("  {\n");
        out.write("    .insns = (Instruction *) eicode" + fun.index + ",\n");
        out.write("    .constants = (JSValue *) eiconsts" + fun.index + ",\n");
        out.write("    .index = " + fun.index + ",\n");
        out.write("    .call_entry = " + fun.callEntry + ",\n");
        out.write("    .send_entry = " + fun.sendEntry + ",\n");
        out.write("    .n_locals = " + fun.numberOfLocals + ",\n");
        out.write("    .n_insns = " + fun.instructions.size() + ",\n");
        out.write("    .n_constants = " + fun.constants.size() + "\n");
        out.write("  },\n");
    }
    private void outputDummyFunction(Writer out) throws IOException {
        out.write("  {\n");
        out.write("    .insns = (Instruction *) NULL,\n");
        out.write("    .constants = (JSValue *) NULL,\n");
        out.write("    .index = -1,\n");
        out.write("    .call_entry = 0,\n");
        out.write("    .send_entry = 0,\n");
        out.write("    .n_locals = 0,\n");
        out.write("    .n_insns = 0,\n");
        out.write("    .n_constants = 0\n");
        out.write("  },\n");
    }

    private void outputFunctions(Writer out, List<EIFunction> funcs) throws IOException {
        out.write("static const struct function_table fitable[] __attribute__ ((section (\".ejs_function_table\"), used)) = {\n");
        for (EIFunction fun : funcs) {
            outputFunction(out, fun);
        }
        outputDummyFunction(out);
        out.write("};\n");
    }

    private void outputContents(Writer out, List<EIFunction> funcs) throws IOException {
        for (EIFunction fun : funcs) {
            outputInstructions(out, fun.instructions, fun.index);
            outputConstants(out, fun.constants, fun.index);
        }
        for (EIConstant constant : EIConstantTable.pool.getConstants()) {
            outputConstant(out, constant);
        }

        outputFunctions(out, funcs);
    }

    private void outputEpilogue(Writer out) throws IOException {
        out.write("\n");
    }

   /**
     * Output instruction to the file.
     * 
     * @param fileName
     *            file name to be output to.
     */
    void output(String fileName) {
        try {
            FileWriter out = new FileWriter(fileName);

            outputPrologue(out);
            outputContents(out, EIFunctions);
            outputEpilogue(out);

            out.close();

            out = new FileWriter(fileName + ".ld");
            outputPrologueMacro(out);
            outputConstantsLinkerScriptCode(out, EIConstantTable.pool);
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
