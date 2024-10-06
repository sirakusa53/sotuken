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
import java.util.List;

public class BitWidthDef {
    public static final String LABEL_INSTRUCTION = "Instruction";
    public static final String LABEL_JSVALUE = "JSValue";
    public static final String LABEL_ALIGN = "Align";

    public static class BitWidth {
        int insn;
        int jsv;
        int align;

        BitWidth(int insn, int jsv, int align) {
            if (insn != 32  && insn != 64)
                throw new Error("Unexpected " + LABEL_INSTRUCTION + " bit width : " + insn);
            if (jsv != 32  && jsv != 64)
                throw new Error("Unexpected " + LABEL_JSVALUE + " bit width : " + insn);
            if (align != 32  && align != 64)
                throw new Error("Unexpected " + LABEL_ALIGN + " bit width : " + insn);

            this.insn  = insn;
            this.jsv   = jsv;
            this.align = align;
        }

        public int getInsnWidth() { return insn; }
        public int getJSVWidth() { return jsv; }
        public int getAlignWidth() { return align; }
    }

    static public BitWidthDef generateFromValue(int insn, int jsv, int align) {
        return new BitWidthDef(new BitWidth(insn, jsv, align));
    }
    static public BitWidthDef loadFromFile(String fileName) throws IOException {
        List<String> lines = Files.readAllLines(Paths.get(fileName));
        return parse(lines, 0, lines.size());
    }
    static public BitWidthDef parse(List<String> lines, int start, int end) {
        int insn = 0;
        int jsv = 0;
        int align = 0;

        for (int lineNo = start; lineNo < end; lineNo++) {
            String line = lines.get(lineNo);
            line = line.replaceFirst("//.*", "");
            if (line.matches("\\s*"))
                continue;

            String[] fields = line.split("\\s+");
            if (fields.length != 2)
                continue;

            String name = fields[0];
            int value = Integer.parseInt(fields[1]);

            switch(name) {
                case LABEL_INSTRUCTION : insn = value; break;
                case LABEL_JSVALUE     : jsv = value; break;
                case LABEL_ALIGN       : align = value; break;
                default : throw new Error("Unknown bit width specifier : " + name);
            }
        }
        return new BitWidthDef(new BitWidth(insn, jsv, align));
    }

    private BitWidthDef(BitWidth bitWidth) {
        this.bitWidth = bitWidth;
    }
    private BitWidth bitWidth;

    public String unparse() {
        StringBuffer sb = new StringBuffer();
        unparse(sb);
        return sb.toString();
    }
    public void unparse(StringBuffer sb) {
        sb.append(LABEL_INSTRUCTION).append(" ").append(bitWidth.getInsnWidth()).append("\n");
        sb.append(LABEL_JSVALUE).append(" ").append(bitWidth.getJSVWidth()).append("\n");
        sb.append(LABEL_ALIGN).append(" ").append(bitWidth.getAlignWidth()).append("\n");
    }
    public BitWidth getBitWidth() {
        return bitWidth;
    }
}
