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
import java.util.ArrayList;
import java.util.List;

public class InsnRepresentationDef {
    public static class InsnType {
        String name;
        InsnType(String name) {
            this.name = name;
        }

        public String getName() { return name; }
        public boolean isSBC() { return name.equals("sbc"); }
        public boolean isOBC() { return name.equals("obc"); }
        public boolean isEI() { return name.equals("ei"); }
    }

    static public InsnRepresentationDef loadFromFile(String fileName) throws IOException {
        List<String> lines = Files.readAllLines(Paths.get(fileName));
        return parse(lines, 0, lines.size());
    }
    static public InsnRepresentationDef parse(List<String> lines, int start, int end) {
        InsnRepresentationDef def = new InsnRepresentationDef();

        for (int lineNo = start; lineNo < end; lineNo++) {
            String line = lines.get(lineNo);
            line = line.replaceFirst("//.*", "");
            if (line.matches("\\s*"))
                continue;

            String[] fields = line.split("\\s+");
            if (fields.length != 1)
                continue;

            String name = fields[0];
            def.addInsnType(name);
        }
        return def;
    }

    private List<InsnType> types = new ArrayList<InsnType>();

    public String unparse() {
        StringBuffer sb = new StringBuffer();
        unparse(sb);
        return sb.toString();
    }
    public void unparse(StringBuffer sb) {
        for (InsnType type: types) {
            sb.append(type.getName()).append("\n");
        }
    }

    public void addInsnType(String name) {
        switch(name) {
        case "sbc":
        case "obc":
        case "ei":
            break;
        default:
            throw new Error("Unknown instruction representation type : " + name);
        }
        types.add(new InsnType(name));
    }

    public List<InsnType> getInsnTypes() {
        return types;
    }
    public int numInsnTypes() {
        return types.size();
    }
    public InsnType getInsnType(String name) {
        for (InsnType type : types) {
            if(type.getName().equals(name)) {
                return type;
            }
        }
        return null;
    }
}
