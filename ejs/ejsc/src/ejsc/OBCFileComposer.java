/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package ejsc;

import java.io.FileOutputStream;

import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

import ejsc.CodeBuffer.SourceLocation;
import ejsc.CodeBuffer.SpecialValue;
import ejsc.VMImplementation;
import ejsc.VMImplementation.InstructionRepresentation;
import ejsc.VMImplementation.JSValueRepresentation;

import specfile.SpecFile;

public class OBCFileComposer extends OutputFileComposer {
    static final boolean DEBUG = false;

    static final boolean BIG_ENDIAN = true;

    static final byte OBC_FILE_MAGIC = (byte) 0xec;

    static class OBCInstruction {
        enum Format {
            ABC,
            AB
        }

        static OBCInstruction createAB(String insnName, int opcode, int a, int b) {
            return new OBCInstruction(insnName, opcode, Format.AB, a, b, 0);
        }

        static OBCInstruction createABC(String insnName, int opcode, int a, int b, int c) {
            return new OBCInstruction(insnName, opcode, Format.ABC, a, b, c);
        }

        String insnName;  /* debug */
        int opcode;
        Format format;
        int a, b, c;

        OBCInstruction(String insnName, int opcode, Format format, int a, int b, int c) {
            this.insnName = insnName;
            this.opcode = opcode;
            this.format = format;
            this.a = a;
            this.b = b;
            this.c = c;
        }

        /**
         * Returns binary representation of the instruction.
         * 
         * @return binary representation of this instruction.
         */
        byte[] getBytes(InstructionRepresentation insnRep) {
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

            if (DEBUG)
                System.out.print("insn: ");
            if (BIG_ENDIAN) {
                insn = Long.reverseBytes(insn);
                insn >>>= 8 * (8 - insnRep.instructionBytes());
            }
            byte[] bytes = new byte[insnRep.instructionBytes()];
            for (int i = 0; i < insnRep.instructionBytes(); i++) {
                bytes[i] = (byte) (insn >> (8 * i));
                if (DEBUG)
                System.out.print(String.format(" %02x", bytes[i]));
            }
            if (DEBUG)
                System.out.println(String.format(" %s", insnName));
            return bytes;
        }
    }

    class OBCFunction implements CodeBuffer {
        int functionNumberOffset;

        /* function header */
        int callEntry;
        int sendEntry;
        int numberOfLocals;

        ConstantTable constants;
        List<OBCInstruction> instructions;

        OBCFunction(BCBuilder.FunctionBCBuilder fb, int functionNumberOffset) {
            this.functionNumberOffset = functionNumberOffset;

            List<BCode> bcodes = fb.getInstructions();
            this.callEntry = fb.callEntry.dist(0);
            this.sendEntry = fb.sendEntry.dist(0);
            this.numberOfLocals = fb.numberOfLocals;

            constants = new ConstantTable();
            instructions = new ArrayList<OBCInstruction>(bcodes.size());
            for (BCode bc : bcodes)
                bc.emit(this);
        }

        int getOpcode(String insnName, SrcOperand... srcs) {
            String decorated = OBCFileComposer.decorateInsnName(insnName, srcs);
            if (decorated == null)
                return spec.getOpcodeIndex(insnName);
            else
                return spec.getOpcodeIndex(decorated);
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
                int index = constants.lookup(n);
                return index;
            } else if (src instanceof StringOperand) {
                String s = ((StringOperand) src).get();
                int index = constants.lookup(s);
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
                int opcode = getOpcode(insnName);
                int a = dst.getRegisterNumber();
                int b = n;
                OBCInstruction insn = OBCInstruction.createAB(insnName, opcode, a, b);
                instructions.add(insn);
            } else
                addNumberBigPrimitive("bigprim", log, sloc, dst, (double) n);
        }
        @Override
        public void addNumberBigPrimitive(String insnName, boolean log, SourceLocation sloc, Register dst, double n) {
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            int b = constants.lookup(n);
            OBCInstruction insn = OBCInstruction.createAB(insnName, opcode, a, b);
            instructions.add(insn);

        }
        @Override
        public void addStringBigPrimitive(String insnName, boolean log, SourceLocation sloc, Register dst, String s) {
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            int b = constants.lookup(s);
            OBCInstruction insn = OBCInstruction.createAB(insnName, opcode, a, b);
            instructions.add(insn);
        }
        @Override
        public void addSpecialSmallPrimitive(String insnName, boolean log, SourceLocation sloc, Register dst, SpecialValue v) {
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            int b = jsvRep.specialFieldValue(v);
            OBCInstruction insn = OBCInstruction.createAB(insnName, opcode, a, b);
            instructions.add(insn);
        }
        @Override
        public void addRegexp(String insnName, boolean log, SourceLocation sloc, Register dst, int flag, String ptn) {
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            int b = constants.lookup(new RegExp(ptn, flag));
            OBCInstruction insn = OBCInstruction.createAB(insnName, opcode, a, b);
            instructions.add(insn);
        }
        @Override
        public void addRXXThreeOp(String insnName, boolean log, SourceLocation sloc, Register dst, SrcOperand src1, SrcOperand src2) {
            int opcode = getOpcode(insnName, src1, src2);
            int a = dst.getRegisterNumber();
            int b = fieldBitsOf(src1);
            int c = fieldBitsOf(src2);
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, a, b, c);
            instructions.add(insn);
        }
        @Override
        public void addXXXThreeOp(String insnName, boolean log, SourceLocation sloc, SrcOperand src1, SrcOperand src2, SrcOperand src3) {
            int opcode = getOpcode(insnName, src1, src2, src3);
            int a = fieldBitsOf(src1);
            int b = fieldBitsOf(src2);
            int c = fieldBitsOf(src3);
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, a, b, c);
            instructions.add(insn);
        }
        @Override
        public void addXIXThreeOp(String insnName, boolean log, SourceLocation sloc, SrcOperand src1, int index, SrcOperand src2) {
            int opcode = getOpcode(insnName, src1, src2);
            int a = fieldBitsOf(src1);
            int c = fieldBitsOf(src2);
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, a, index, c);
            instructions.add(insn);
        }
        @Override
        public void addRXTwoOp(String insnName, boolean log, SourceLocation sloc, Register dst, SrcOperand src) {
            int opcode = getOpcode(insnName, src);
            int a = dst.getRegisterNumber();
            int b = fieldBitsOf(src);
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, a, b, 0);
            instructions.add(insn);
        }
        @Override
        public void addXXTwoOp(String insnName, boolean log, SourceLocation sloc, SrcOperand src1, SrcOperand src2) {
            int opcode = getOpcode(insnName, src1, src2);
            int a = fieldBitsOf(src1);
            int b = fieldBitsOf(src2);
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, a, b, 0);
            instructions.add(insn);
        }
        @Override
        public void addROneOp(String insnName, boolean log, SourceLocation sloc, Register dst) {
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, a, 0, 0);
            instructions.add(insn);
        }
        @Override
        public void addXOneOp(String insnName, boolean log, SourceLocation sloc, SrcOperand src) {
            int opcode = getOpcode(insnName, src);
            int a = fieldBitsOf(src);
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, a, 0, 0);
            instructions.add(insn);
        }
        @Override
        public void addIOneOp(String insnName, boolean log, SourceLocation sloc, int n) {
            int opcode = getOpcode(insnName);
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, n, 0, 0);
            instructions.add(insn);
        }
        @Override
        public void addZeroOp(String insnName, boolean log, SourceLocation sloc) {
            int opcode = getOpcode(insnName);
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, 0, 0, 0);
            instructions.add(insn);
        }
        @Override
        public void addNewFrameOp(String insnName, boolean log, SourceLocation sloc, int len, boolean mkargs) {
            int opcode = getOpcode(insnName);
            int b = mkargs ? 1 : 0;
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, len, b, 0);
            instructions.add(insn);
        }
        @Override
        public void addGetVar(String insnName, boolean log, SourceLocation sloc, Register dst, int link, int index) {
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, a, link, index);
            instructions.add(insn);
        }
        @Override
        public void addSetVar(String insnName, boolean log, SourceLocation sloc, int link, int index, SrcOperand src) {
            int opcode = getOpcode(insnName, src);
            int c = fieldBitsOf(src);
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, link, index, c);
            instructions.add(insn);
        }
        @Override
        public void addMakeClosureOp(String insnName, boolean log, SourceLocation sloc, Register dst, int index) {
            int opcode = getOpcode(insnName);
            int a = dst.getRegisterNumber();
            // int b = index + functionNumberOffset;
            int b = index;
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, a, b, 0);
            instructions.add(insn);
        }
        @Override
        public void addXICall(String insnName, boolean log, SourceLocation sloc, SrcOperand fun, int nargs) {
            int opcode = getOpcode(insnName, fun);
            int a = fieldBitsOf(fun);
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, a, nargs, 0);
            instructions.add(insn);
        }
        @Override
        public void addRXCall(String insnName, boolean log, SourceLocation sloc, Register dst, SrcOperand fun) {
            int opcode = getOpcode(insnName, fun);
            int a = dst.getRegisterNumber();
            int b = fieldBitsOf(fun);
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, a, b, 0);
            instructions.add(insn);
        }
        @Override
        public void addXXIConstruct(String insnName, boolean log, SourceLocation sloc, SrcOperand receiver, SrcOperand constructor, int nargs) {
            int opcode = getOpcode(insnName, receiver, constructor);
            int a = fieldBitsOf(receiver);
            int b = fieldBitsOf(constructor);
            OBCInstruction insn = OBCInstruction.createABC(insnName, opcode, a, b, nargs);
            instructions.add(insn);
        }
        @Override
        public void addUncondJump(String insnName, boolean log, SourceLocation sloc, int disp) {
            int opcode = getOpcode(insnName);
            OBCInstruction insn = OBCInstruction.createAB(insnName, opcode, 0, disp);
            instructions.add(insn);
        }
        @Override
        public void addCondJump(String insnName, boolean log, SourceLocation sloc, SrcOperand test, int disp) {
            int opcode = getOpcode(insnName, test);
            int a = fieldBitsOf(test);
            OBCInstruction insn = OBCInstruction.createAB(insnName, opcode, a, disp);
            instructions.add(insn);
        }
    }

    List<OBCFunction> obcFunctions;

    OBCFileComposer(BCBuilder compiledFunctions, int functionNumberOffset, VMImplementation vmImpl) {
        super(vmImpl);
        List<BCBuilder.FunctionBCBuilder> fbs = compiledFunctions.getFunctionBCBuilders();
        obcFunctions = new ArrayList<OBCFunction>(fbs.size());
        for (BCBuilder.FunctionBCBuilder fb : fbs) {
            OBCFunction out = new OBCFunction(fb, functionNumberOffset);
            obcFunctions.add(out);
        }
    }

    private void outputByte(OutputStream out, byte v) throws IOException {
        if (DEBUG)
            System.out.println(String.format("byte: %02x", v));
        out.write(v);
    }

    private void outputShort(OutputStream out, int v) throws IOException {
        if (DEBUG)
            System.out.println(String.format("short: %04x", v));
        if (BIG_ENDIAN)
            v = Integer.reverseBytes(v << 16);
        out.write((byte) (v & 0xff));
        out.write((byte) ((v >> 8) & 0xff));
    }

    private void outputLong(OutputStream out, long v) throws IOException {
        if (DEBUG)
            System.out.println(String.format("short: %016x", v));
        if (BIG_ENDIAN)
            v = Long.reverseBytes(v);
        for (int i = 0; i < 8; i++)
            out.write((byte) ((v >> (8 * i)) & 0xff));
    }

    /**
     * Output instruction to the file.
     * 
     * @param fileName
     *            file name to be output to.
     */
    void output(String fileName) {
        try {
            FileOutputStream out = new FileOutputStream(fileName);

            outputByte(out, OBC_FILE_MAGIC);
            outputByte(out, spec.getFingerprint());

            /* File header */
            outputShort(out, obcFunctions.size());

            /* Function */
            for (OBCFunction fun : obcFunctions) {
                /* Function header */
                outputShort(out, fun.callEntry);
                outputShort(out, fun.sendEntry);
                outputShort(out, fun.numberOfLocals);
                outputShort(out, fun.instructions.size());
                outputShort(out, fun.constants.size());

                /* Instructions */
                for (OBCInstruction insn : fun.instructions)
                    out.write(insn.getBytes(insnRep));

                /* Constant pool */
                for (Object v : fun.constants.getConstants()) {
                    if (v instanceof Double) {
                        long bits = Double.doubleToLongBits((Double) v);
                        outputShort(out, 8); // size
                        outputShort(out, 4); // InsnOperandType::NUM
                        outputLong(out, bits);
                    } else if (v instanceof String) {
                        String s = (String) v;
                        outputShort(out, s.length() + 1); // size
                        outputShort(out, 3); // InsnOperandType::STR
                        if (DEBUG)
                            System.out.println("string: "+s);
                        out.write(s.getBytes());
                        out.write('\0');
                    } else if (v instanceof RegExp) {
                        RegExp regexp = (RegExp) v;
                        String ptn = regexp.pattern;
                        int flag = regexp.flag;
                        outputShort(out, ptn.length() + 1); // size
                        outputShort(out, 5); // InsnOperandType::REGEXP
                        outputShort(out, flag); // flag
                        if (DEBUG)
                            System.out.println("pattern: "+ptn);
                        out.write(ptn.getBytes());
                        out.write('\0');
                    } else
                        throw new Error("Unknown constant");
                }
            }
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}
