/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package vmdlc;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.Map.Entry;
import java.util.regex.MatchResult;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import type.AstType;
import type.VMDataType;
import type.VMDataTypeVecSet;
import vmdlc.OperandSpecifications.OperandSpecificationRecord.Behaviour;


public class OperandSpecifications {
    static final boolean DEBUG = false;
    static class OperandSpecificationRecord {
        String insnName;
        String[] operandTypes;
        enum Behaviour {
            ACCEPT,
            UNSPECIFIED,
            ERROR
        };
        Behaviour behaviour;
        OperandSpecificationRecord(String insnName, String[] operandTypes, Behaviour behaviour) {
            this.insnName = insnName;
            this.operandTypes = operandTypes;
            this.behaviour = behaviour;
        }

        @Override
        public String toString(){
            StringBuilder builder = new StringBuilder();
            builder.append(insnName);
            builder.append(" (");
            builder.append(String.join(",", operandTypes));
            builder.append(") ");
            builder.append(behaviour.toString().toLowerCase());
            return builder.toString();
        }

        @Override
        public OperandSpecificationRecord clone(){
            return new OperandSpecificationRecord(insnName, operandTypes.clone(), behaviour);
        }

        public Behaviour getBehavior(){
            return behaviour;
        }

        @Override
        public int hashCode(){
            return insnName.hashCode() + operandTypes.hashCode() + behaviour.hashCode();
        }

        @Override
        public boolean equals(Object obj){
            if(!(obj instanceof OperandSpecificationRecord)) return false;
            OperandSpecificationRecord that = (OperandSpecificationRecord) obj;
            return this.insnName.equals(that.insnName) &&
                Arrays.equals(this.operandTypes, that.operandTypes) &&
                this.behaviour == that.behaviour;
        }
    }
    List<OperandSpecificationRecord> spec;
    Map<String, Integer> arities;

    public OperandSpecifications(){
    }

    public OperandSpecifications(List<OperandSpecificationRecord> spec, Map<String, Integer> arities){
        this.spec = spec;
        this.arities = arities;
    }

    void load(Scanner sc) {
        final String P_SYMBOL = "[a-zA-Z_][a-zA-Z0-9_]*";
        final String P_OPERANDS = "\\(\\s*([^)]*)\\s*\\)";
        final String P_BEHAVIOUR = "accept|error|unspecified";
        final Pattern splitter = Pattern.compile("("+P_SYMBOL+")\\s*"+P_OPERANDS+"\\s*("+P_BEHAVIOUR+")\\s*$");

        spec = new ArrayList<OperandSpecificationRecord>();
        arities = new HashMap<String, Integer>();
        while (sc.hasNextLine()) {
            String line = sc.nextLine();
            if(line.isBlank()) continue;
            if (line.startsWith("#"))
                continue;
            Matcher matcher = splitter.matcher(line);
            if (matcher.matches()) {
                MatchResult m = matcher.toMatchResult();
                String insnName = m.group(1);
                String[] operandTypes = null;

                if (!m.group(2).equals("")) {
                    int n = 0;
                    String[] allOps = m.group(2).split("\\s*,\\s*");
                    for (String s: allOps)
                        if (!s.equals("-"))
                            n++;
                    operandTypes = new String[n];
                    int i = 0;
                    for (String s: allOps)
                        if (!s.equals("-"))
                            operandTypes[i++] = s;

                    Integer arity = arities.get(insnName);
                    if (arity == null)
                        arities.put(insnName, n);
                    else {
                        if (arity != n)
                            throw new Error("operand specification file error");
                    }
                } else {
                    operandTypes = new String[0];
                    arities.put(insnName, 0);
                }

                OperandSpecificationRecord.Behaviour behaviour;
                if (m.group(3).equals("accept"))
                    behaviour = OperandSpecificationRecord.Behaviour.ACCEPT;
                else if (m.group(3).equals("error"))
                    behaviour = OperandSpecificationRecord.Behaviour.ERROR;
                else if (m.group(3).equals("unspecified"))
                    behaviour = OperandSpecificationRecord.Behaviour.UNSPECIFIED;
                else
                    throw new Error("operand specification syntax error:"+ m.group());

                OperandSpecificationRecord r = new OperandSpecificationRecord(insnName, operandTypes, behaviour);
                spec.add(r);
            } else
                throw new Error("operand specification syntax error:"+ line);
        }
    }

    public void load(String file) throws FileNotFoundException {
        Scanner sc = new Scanner(new FileInputStream(file));
        try {
            load(sc);
        } finally {
            sc.close();
        }
    }

    boolean matchOperandTypes(String[] specTypes, VMDataType[] types, String insnName) {
        if (specTypes.length != types.length)
            throw new Error("number of operands mismatch: "+insnName+" insndef:"+types.length+", opspec: "+specTypes.length);
        for (int i = 0; i < specTypes.length; i++) {
            if (specTypes[i].equals("_"))
                continue; // next operand
            if (specTypes[i].startsWith("!") &&
                    specTypes[i].substring(1).equals("object") &&
                    !types[i].isObject())
                continue; // next operand;
            if (specTypes[i].startsWith("!") &&
                    !specTypes[i].substring(1).equals(types[i].getName()))
                continue; // next operand;
            if (specTypes[i].equals("object") && types[i].isObject())
                continue; // next operand
            if (specTypes[i].equals(types[i].getName()))
                continue; // next operand
            return false;
        }
        return true;
    }

    OperandSpecificationRecord findSpecificationRecord(String insnName, VMDataType[] types) {
        for (OperandSpecificationRecord rec: spec) {
            if (insnName.equals(rec.insnName) &&
                    matchOperandTypes(rec.operandTypes, types, insnName))
                return rec;
        }
        /* construct error message */
        StringBuilder sb = new StringBuilder();
        sb.append("unexhaustive type specification for : ");
        sb.append(insnName);
        sb.append("(");
        for (int i = 0; i < types.length; i++) {
            if (i >= 1)
                sb.append(",");
            sb.append(types[i].getName());
        }
        sb.append(")");
        throw new Error(sb.toString());
    }

    public Set<VMDataType[]> getOperands(String insnName, OperandSpecificationRecord.Behaviour behaviour) {
        if (arities == null)
            return null;
        Integer xarity = arities.get(insnName);
        if (xarity == null)
            return null;
        int arity = xarity.intValue();
        Set<VMDataType[]> typess = new HashSet<VMDataType[]>();
        int total = 1;
        for (int i = 0; i < arity; i++)
            total *= VMDataType.allContainsNone().size();
        for (int i = 0; i < total; i++) {
            VMDataType[] types = new VMDataType[arity];
            int a = i;
            for (int j = 0; j < arity; j++) {
                types[j] = VMDataType.allContainsNone().get(a % VMDataType.allContainsNone().size());
                a /= VMDataType.allContainsNone().size();
            }
            if (spec == null)
                typess.add(types);
            else {
                OperandSpecificationRecord rec = findSpecificationRecord(insnName, types);
                if (rec.behaviour == behaviour)
                    typess.add(types);
            }
        }
        return typess;
    }


    private Set<VMDataType[]> getAcceptOperands(String insnName) {
        return getOperands(insnName, OperandSpecificationRecord.Behaviour.ACCEPT);
    }

    public Set<VMDataType[]> getUnspecifiedOperands(String insnName) {
        return getOperands(insnName, OperandSpecificationRecord.Behaviour.UNSPECIFIED);
    }

    public Set<VMDataType[]> getErrorOperands(String insnName) {
        return getOperands(insnName, OperandSpecificationRecord.Behaviour.ERROR);
    }

    public boolean isAllUnspecified(String insnName){
        Collection<VMDataType[]> accepts = getAcceptOperands(insnName);
        Collection<VMDataType[]> errors = getErrorOperands(insnName);
        return (accepts == null || accepts.isEmpty()) && (errors == null || errors.isEmpty());
    }

    static class OperandVMDataTypeVecSet extends VMDataTypeVecSet {
        OperandSpecifications opSpec;
        String insnName;
        OperandVMDataTypeVecSet(String[] paramNames, OperandSpecifications opSpec, String insnName) {
            super(paramNames);
            this.opSpec = opSpec;
            this.insnName = insnName;
        }

        @Override
        public AstType getMostSpecificType(String vn) {
            Set<VMDataType[]> dtss = opSpec.getAcceptOperands(insnName);
            return getMostSpecificTypeFromSet(dtss, vn);
        }

        @Override
        public Set<VMDataType[]> getTuples() {
            return opSpec.getAcceptOperands(insnName);
        }
    }

    public VMDataTypeVecSet getAccept(String insnName, String[] paramNames) {
        return new OperandVMDataTypeVecSet(paramNames, this, insnName);
    }

    public void insertRecord(String insnName, String[] operandTypes, OperandSpecificationRecord.Behaviour behaviour){
        spec.add(0, new OperandSpecificationRecord(insnName, operandTypes, behaviour));
    }

    public void insertRecord(String insnName, VMDataType[] operandTypes, OperandSpecificationRecord.Behaviour behaviour){
        String[] typeNames = new String[operandTypes.length];
        for(int i=0; i<operandTypes.length; i++){
            typeNames[i] = operandTypes[i].toString();
        }
        insertRecord(insnName, typeNames, behaviour);
    }

    public void insertRecord(OperandSpecificationRecord record){
        spec.add(0, record);
    }

    public void write(FileWriter writer) throws IOException{
        StringBuilder builder = new StringBuilder();
        for(OperandSpecificationRecord record : spec){
            builder.append(record.toString());
            builder.append('\n');
        }
        writer.write(builder.toString());
    }

    public void write(String fileName) throws IOException{
        try{
            FileWriter writer = new FileWriter(new File(fileName));
            write(writer);
            writer.close();
        }catch(Exception e){
            e.printStackTrace();
        }
    }

    public void print(PrintStream stream){
        StringBuilder builder = new StringBuilder();
        for(OperandSpecificationRecord record : spec){
            builder.append(record.toString());
            builder.append('\n');
        }
        stream.print(builder.toString());
    }

    public boolean hasName(String name){
        return (arities.get(name) != null);
    }

    public int getArity(String name){
        if(!hasName(name)){
            System.err.println("InternalWarning: cannot find instruction name: "+name);
            return 0;
        }
        return arities.get(name);
    }

    public Map<String, Set<VMDataType[]>> getAllAccpetSpecifications(){
        Map<String, Set<VMDataType[]>> result = new HashMap<>();
        for(OperandSpecificationRecord record : spec){
            String name = record.insnName;
            Set<VMDataType[]> acceptTypess = getAcceptOperands(name);
            result.put(name, acceptTypess);
        }
        return result;
    }

    public List<OperandSpecificationRecord> getOperandSpecificationRecord(){
        return spec;
    }

    @Override
    public OperandSpecifications clone(){
        List<OperandSpecificationRecord> cloneRecord = new ArrayList<>(spec.size());
        for(OperandSpecificationRecord rec : spec){
            cloneRecord.add(rec.clone());
        }
        Map<String, Integer> cloneArities = new HashMap<>(arities.size());
        for(Entry<String, Integer> entry : arities.entrySet()){
            cloneArities.put(entry.getKey(), entry.getValue());
        }
        return new OperandSpecifications(cloneRecord, cloneArities);
    }

    @Override
    public String toString(){
        StringBuilder builder = new StringBuilder();
        builder.append("[");
        for(OperandSpecificationRecord r : spec){
            builder.append(r.toString());
            builder.append(",");
        }
        builder.append("]");
        return builder.toString();
    }

    public static OperandSpecifications merge(List<OperandSpecifications> opSpecs){
        if(opSpecs.isEmpty()) return new OperandSpecifications();
        OperandSpecifications merged = opSpecs.get(0).clone();
        List<OperandSpecifications> cdr = opSpecs.subList(1, opSpecs.size());
        for(OperandSpecifications target : cdr){
            List<OperandSpecificationRecord> mergedRecords = merged.getOperandSpecificationRecord();
            List<OperandSpecificationRecord> targetRecords = target.getOperandSpecificationRecord();
            for(OperandSpecificationRecord record : targetRecords){
                boolean isAccept = record.getBehavior() == Behaviour.ACCEPT;
                boolean isRecordMerged = mergedRecords.contains(record);
                if(!isAccept|| isRecordMerged) continue;
                merged.insertRecord(record);
            }
        }
        return merged;
    }
    //Never used
    /*
    private Set<String[]> getErrorOperandsString(String insnName) {
        Set<String[]> result = new HashSet<String[]>();
        for (OperandSpecificationRecord rec : spec) {
            if (insnName.equals(rec.insnName) &&
                    rec.behaviour == OperandSpecificationRecord.Behaviour.ERROR) {
                result.add(rec.operandTypes);
            }
        }
        return result;
    }
    */
}
