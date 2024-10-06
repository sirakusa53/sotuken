/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package specfile;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class SpecFile {
    static final Map<String, InstructionFormat> instructionFormatTable =
            new HashMap<String, InstructionFormat>();
    public static class InstructionFormat {
        private InstructionFormat(String name, int arity) {
            this.name = name;
            this.arity = arity;
            instructionFormatTable.put(name,  this);
        }
        private String name;
        int arity;
        public String getName() {
            return name;
        }
        public int getArity() {
            return arity;
        }
    }
    static {
        new InstructionFormat("SMALLPRIMITIVE", 2);
        new InstructionFormat("BIGPRIMITIVE", 2);
        new InstructionFormat("ZEROOP", 0);
        new InstructionFormat("ONEOP", 1);
        new InstructionFormat("TWOOP", 2);
        new InstructionFormat("THREEOP", 3);
        new InstructionFormat("UNCONDJUMP", 1);
        new InstructionFormat("CONDJUMP", 2);
        new InstructionFormat("GETVAR", 3);
        new InstructionFormat("SETVAR", 3);
        new InstructionFormat("MAKECLOSUREOP", 2);
        new InstructionFormat("CALLOP", 2);
        new InstructionFormat("UNKNOWNOP", 0);
    }

    static Map<String, OperandType> operandTypeTable =
            new HashMap<String, OperandType>();
    public static class OperandType {
        private OperandType(String name) {
            this.name = name;
            operandTypeTable.put(name,  this);
        }
        private String name;
        public String getName() {
            return name;
        }
    }
    static {
        new OperandType("JSValue");
        new OperandType("Register");
        new OperandType("int");
        new OperandType("InstructionDisplacement");
        new OperandType("ConstantDisplacement");
        new OperandType("Subscript");
    }

    static final Map<String, DataType> dataTypeTable = new HashMap<String, DataType>();
    public static class DataType {
        private DataType(String name) {
            this.name = name;
            dataTypeTable.put(name, this);
        }
        private String name;
        public String getName() {
            return name;
        }
    }
    static {
        new DataType("fixnum");
        new DataType("flonum");
        new DataType("string");
        new DataType("special");
        new DataType("_");
        new DataType("-");
    }

    private static final String SECTION_PREFIX = "%% ";
    private static final String SECTION_BIT_WIDTH_DEF = "%% bit width def";
    private static final String SECTION_INSN_REPRESENTATION_DEF = "%% insn representation def";
    private static final String SECTION_DATATYPE_DEF = "%% datatype def";
    private static final String SECTION_INSTRUCTION_DEF = "%% instruction def";
    private static final String SECTION_SUPERINSTRUCTION_SPEC = "%% superinstruction spec";

    private static int findEnd(List<String> lines, int lineNo) {
        while (lineNo < lines.size()) {
            if (lines.get(lineNo).startsWith(SECTION_PREFIX))
                return lineNo;
            lineNo++;
        }
        return lineNo;
    }
    public static SpecFile loadFromFile(String fileName) throws IOException {
        List<String> lines = Files.readAllLines(Paths.get(fileName));
        return parse(lines);
    }
    public static SpecFile parse(List<String> lines) {
        int lineNo = 0;
        BitWidthDef bitWidthDef = null;
        InsnRepresentationDef insnReplesentationDef = null;
        DatatypeDef datatypeDef = null;
        InstructionDef instructionDef = null;
        SuperinstructionSpec superinstructionSpec = null;
        while (lineNo < lines.size()) {
            String line = lines.get(lineNo);
            if (line.startsWith(SECTION_PREFIX)) {
                int start = lineNo + 1;
                int end = findEnd(lines, lineNo + 1);
                switch (line) {
                case SECTION_BIT_WIDTH_DEF:
                    bitWidthDef = BitWidthDef.parse(lines, start, end);
                    break;
                case SECTION_INSN_REPRESENTATION_DEF:
                    insnReplesentationDef = InsnRepresentationDef.parse(lines, start, end);
                    break;
                case SECTION_DATATYPE_DEF:
                    datatypeDef = DatatypeDef.parse(lines, start, end);
                    break;
                case SECTION_INSTRUCTION_DEF:
                    instructionDef = InstructionDef.parse(lines, start, end);
                    break;
                case SECTION_SUPERINSTRUCTION_SPEC:
                    superinstructionSpec = SuperinstructionSpec.parse(lines, start, end);
                    break;
                default:
                    throw new Error("Unkonw section in spec file: "+lineNo+": "+line);
                }
                lineNo = end;
            } else if (line.matches("\\s*(//.*)?"))
                lineNo++;
            else
                throw new Error("Spec file parse error: "+lineNo+": "+line);
        }
        if (bitWidthDef == null)
            throw new Error("No bit width def in spec file");
        if (insnReplesentationDef == null)
            throw new Error("No insn representation def in spec file");
        if (datatypeDef == null)
            throw new Error("No datatype def in spec file");
        if (instructionDef == null)
            throw new Error("No instruction def in spec file");
        if (superinstructionSpec == null)
            throw new Error("No superinstruction spec in spec file");
        SpecFile spec = new SpecFile();
        spec.setBitWidthDef(bitWidthDef);
        spec.setInsnRepresentationDef(insnReplesentationDef);
        spec.setDatatypeDef(datatypeDef);
        spec.setInstructionDef(instructionDef);
        spec.setSuperinstructionSpec(superinstructionSpec);
        return spec;
    }

    private BitWidthDef bitWidthDef;
    private InsnRepresentationDef insnReplesentationDef;
    private DatatypeDef datatypeDef;
    private InstructionDef instructionDef;
    private SuperinstructionSpec superinstructionSpec;
    public void setBitWidthDef(BitWidthDef bitWidthDef) {
        this.bitWidthDef = bitWidthDef;
    }
    public void setInsnRepresentationDef(InsnRepresentationDef insnReplesentationDef) {
        this.insnReplesentationDef = insnReplesentationDef;
    }
    public void setDatatypeDef(DatatypeDef datatypeDef) {
        this.datatypeDef = datatypeDef;
    }
    public void setInstructionDef(InstructionDef instructionDef) {
        this.instructionDef = instructionDef;
    }
    public void setSuperinstructionSpec(SuperinstructionSpec superinstructionSpec) {
        this.superinstructionSpec = superinstructionSpec;
    }
    public BitWidthDef getBitWidthDef() {
        return bitWidthDef;
    }
    public InsnRepresentationDef getInsnRepresentationDef() {
        return insnReplesentationDef;
    }
    public DatatypeDef getDatatypeDef() {
        return datatypeDef;
    }
    public InstructionDef getInstructionDef() {
        return instructionDef;
    }
    public SuperinstructionSpec getSuperinstructionSpec() {
        return superinstructionSpec;
    }
    public int getOpcodeIndex(String name) {
        int index;
        index = instructionDef.getOpcodeIndex(name);
        if (index != -1)
            return index;
        index = superinstructionSpec.getOpcodeIndex(name);
        if (index != -1)
            return index + instructionDef.numInstructions();
        return -1;
    }
    // specfile fingerprint: lower 7 bits of the first byte of MD5 hash (0xff is a wildcard)
    public byte getFingerprint() {
        try {
            MessageDigest md = MessageDigest.getInstance("MD5");
            md.update(unparse().getBytes());
            byte[] digest = md.digest();
            return (byte) (digest[0] & 0x7f);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
            throw new Error("cannot compute hashcode for specfile");
        }
    }
    public String unparse() {
        StringBuffer sb = new StringBuffer();
        unparse(sb);
        return sb.toString();
    }
    private void unparse(StringBuffer sb) {
        sb.append(SECTION_BIT_WIDTH_DEF).append("\n");
        if (bitWidthDef != null)
            bitWidthDef.unparse(sb);
        sb.append(SECTION_INSN_REPRESENTATION_DEF).append("\n");
        if (insnReplesentationDef != null)
            insnReplesentationDef.unparse(sb);
        sb.append(SECTION_DATATYPE_DEF).append("\n");
        if (datatypeDef != null)
            datatypeDef.unparse(sb);
        sb.append(SECTION_INSTRUCTION_DEF).append("\n");
        if (instructionDef != null)
            instructionDef.unparse(sb);
        sb.append(SECTION_SUPERINSTRUCTION_SPEC).append("\n");
        if (superinstructionSpec != null)
            superinstructionSpec.unparse(sb);
    }
}
