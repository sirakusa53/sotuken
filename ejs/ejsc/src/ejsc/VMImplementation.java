/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package ejsc;

import ejsc.CodeBuffer.SpecialValue;

import specfile.SpecFile;
import specfile.BitWidthDef.BitWidth;
import specfile.DatatypeDef.Datatype;

public class VMImplementation {
    public static abstract class JSValueRepresentation {
        static final int FIELD_VALUE_TRUE = 0x3;
        static final int FIELD_VALUE_FALSE = 0x1;
        static final int FIELD_VALUE_NULL = 0x0;
        static final int FIELD_VALUE_UNDEFINED = 0x2;

        static class Bit32 extends JSValueRepresentation {
            Bit32(SpecFile spec, int ptagBits) { super(spec, ptagBits); }

            @Override
            public long minFixnum() { return - maxFixnum() - 1; }
            @Override
            public long maxFixnum() { return 0x7fffffffL >> ptagBits; /* PTAG k bit and signed 1 bit */ }
        }
        static class Bit64 extends JSValueRepresentation {
            Bit64(SpecFile spec, int ptagBits) { super(spec, ptagBits); }

            @Override
            public long minFixnum() { return - maxFixnum() - 1; }
            @Override
            public long maxFixnum() { return 0x7fffffffffffffffL >> ptagBits; /* PTAG k bit and signed 1 bit */ }
        }

        int ptagBits;
        int specPTag;

        JSValueRepresentation(SpecFile spec, int ptagBits) {
            this.ptagBits = ptagBits;

            Datatype special = spec.getDatatypeDef().getDatatype("special");
            if (special == null) {
                throw new Error("SpecFile does not contain datatype definiton of special.");
            }

            this.specPTag = special.getPtag();
        }

        public abstract long minFixnum();
        public abstract long maxFixnum();

        public boolean inFixnumRange(long n) {
            return minFixnum() <= n && n <= maxFixnum();
        }
        public boolean inFixnumRange(double d) {
            long n = (long) d;
            return ((double) n == d) && inFixnumRange(n);
        }

        public int specialFieldValue(SpecialValue v) {
            switch (v) {
            case TRUE:
                return (FIELD_VALUE_TRUE << ptagBits) | specPTag;
            case FALSE:
                return (FIELD_VALUE_FALSE << ptagBits) | specPTag;
            case NULL:
                return (FIELD_VALUE_NULL << ptagBits) | specPTag;
            case UNDEFINED:
                return (FIELD_VALUE_UNDEFINED << ptagBits) | specPTag;
            default:
                throw new Error("Unknown special");
            }
        }

    }

    public static abstract class InstructionRepresentation {
        static class Bit32 extends InstructionRepresentation {
            @Override public int instructionBytes() { return 4; }

            @Override public int opcodeBits() { return 8; }
            @Override public int aBits()      { return 8; }
            @Override public int bBits()      { return 8; }
            @Override public int cBits()      { return 8; }
        }

        static class Bit64 extends InstructionRepresentation {
            @Override public int instructionBytes() { return 8; }

            @Override public int opcodeBits() { return 16; }
            @Override public int aBits()      { return 16; }
            @Override public int bBits()      { return 16; }
            @Override public int cBits()      { return 16; }
        }

        abstract public int instructionBytes();

        abstract public int opcodeBits();
        abstract public int aBits();
        abstract public int bBits();
        abstract public int cBits();
        public int bbBits() { return bBits() + cBits(); }

        public int opcodeOffset() { return aOffset() + aBits(); }
        public int aOffset()      { return bOffset() + bBits(); }
        public int bOffset()      { return cOffset() + cBits(); }
        public int bbOffset()     { return 0; }
        public int cOffset()      { return 0; }

        public long opcodeMask() { return ((1L << opcodeBits()) - 1) << opcodeOffset(); }
        public long aMask()      { return ((1L << aBits()) - 1) << aOffset(); }
        public long bMask()      { return ((1L << bBits()) - 1) << bOffset(); }
        public long bbMask()     { return ((1L << bbBits()) - 1) << bbOffset(); }
        public long cMask()      { return ((1L << cBits()) - 1) << cOffset(); }

        public boolean inSmallPrimitiveRange(long n) {
            long max = (1L << (bbBits() - 1)) - 1;
            long min = - max - 1;
            return min <= n && n <= max;
        }
        public boolean inSmallPrimitiveRange(double d) {
            long n = (long) d;
            return ((double) n == d) && inSmallPrimitiveRange(n);
        }

        public boolean inFixnumOperandRange(long n) {
            long max = (1L << (cBits() - 1)) - 1;
            long min = - max - 1;
            return min <= n && n <= max;
        }
        public boolean inFixnumOperandRange(double d) {
            long n = (long) d;
            return ((double) n == d) && inFixnumOperandRange(n);
        }
    }

    SpecFile spec;
    JSValueRepresentation jsvRep;
    InstructionRepresentation insnRep;

    VMImplementation(SpecFile spec) {
        this.spec = spec;

        BitWidth bitWidth = spec.getBitWidthDef().getBitWidth();

        boolean isInsn32  = (bitWidth.getInsnWidth() == 32);
        boolean isJSV32   = (bitWidth.getJSVWidth() == 32);
        boolean isAlign32 = (bitWidth.getAlignWidth() == 32);

        int ptagBits = (isAlign32) ? 2 : 3;
        if (isJSV32)
            jsvRep = new JSValueRepresentation.Bit32(spec, ptagBits);
        else
            jsvRep = new JSValueRepresentation.Bit64(spec, ptagBits);

        if (isInsn32)
            insnRep = new InstructionRepresentation.Bit32();
        else
            insnRep = new InstructionRepresentation.Bit64();
    }

    SpecFile getSpec() { return spec; }
    JSValueRepresentation getJSVRep() { return jsvRep; }
    InstructionRepresentation getInsnRep() { return insnRep; }
}
