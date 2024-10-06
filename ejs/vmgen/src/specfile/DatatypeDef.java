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

import vmgen.type.VMDataType;
import vmgen.type.VMRepType;

public class DatatypeDef {
    public static class Datatype {
        String name;
        int ptag, htag;
        Datatype(String name, int ptag, int htag) {
            this.name = name;
            this.ptag = ptag;
            this.htag = htag;
        }

        public String getName() { return name; }
        public boolean hasPtag() { return ptag >= 0; }
        public boolean hasHtag() { return htag >= 0; }
        public int getPtag() { return ptag; }
        public int getHtag() { return htag; }
    }

    static public DatatypeDef generateFromVMDataType(List<VMDataType> dtList) {
        List<Datatype> datatypeDef = new ArrayList<Datatype>();
        for (VMDataType dt : dtList) {
            String dtName = dt.getName();
            List<VMRepType> rtList = dt.getVMRepTypes();
            for (VMRepType rt : rtList) {
                VMRepType.PT ptag = rt.getPT();
                VMRepType.HT htag = rt.getHT();

                int ptValue = ptag.getValue();
                int htValue = (htag == null) ? -1 : htag.getValue();

                datatypeDef.add(new Datatype(dtName, ptValue, htValue));
            }
        }
        return new DatatypeDef(datatypeDef);
    }

    static public DatatypeDef loadFromFile(String fileName) throws IOException {
        List<String> lines = Files.readAllLines(Paths.get(fileName));
        return parse(lines, 0, lines.size());
    }
    static public DatatypeDef parse(List<String> lines, int start, int end) {
        List<Datatype> datatypeDef = new ArrayList<Datatype>();
        for (int lineNo = start; lineNo < end; lineNo++) {
            String line = lines.get(lineNo);
            line = line.replaceFirst("//.*", "");
            if (line.matches("\\s*"))
                continue;

            String[] fields = line.split("\\s+");
            if (fields.length != 3)
                continue;

            String name = fields[0];
            int ptag = Integer.parseInt(fields[1]);
            int htag = Integer.parseInt(fields[2]);
            Datatype dt = new Datatype(name, ptag, htag);
            datatypeDef.add(dt);
        }
        return new DatatypeDef(datatypeDef);
    }

    private DatatypeDef(List<Datatype> list) {
        this.list = list;
    }
    private List<Datatype> list;

    public String unparse() {
        StringBuffer sb = new StringBuffer();
        unparse(sb);
        return sb.toString();
    }
    public void unparse(StringBuffer sb) {
        for (Datatype dt: list) {
            sb.append(dt.name).append(" ");
            sb.append(dt.ptag).append(" ");
            sb.append(dt.htag).append("\n");
        }
    }
    public List<Datatype> getList() {
        return list;
    }
    public int numDatatypes() {
        return list.size();
    }
    public Datatype getDatatype(String name) {
        for (Datatype dt : list) {
            if(dt.getName().equals(name)) {
                return dt;
            }
        }
        return null;
    }
}
