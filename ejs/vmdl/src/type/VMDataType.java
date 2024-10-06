/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package type;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import type.AstType.JSValueVMType;

public class VMDataType implements Comparable<VMDataType> {
    static final boolean DEBUG_WITH_SMALL = false;

    static Map<String, VMDataType> definedVMDataTypes = new HashMap<String, VMDataType>();

    static VMDataType NONE;

    static VMDataType defineVMDataType(String name, boolean isObject) {
        VMDataType t = new VMDataType(name, isObject);
        definedVMDataTypes.put(name, t);
        return t;
    }

    public static VMDataType get(String name) {
        return get(name, false);
    }

    public static int size() {
        return definedVMDataTypes.size();
    }

    static VMDataType get(String name, boolean permitNull) {
        VMDataType dt = definedVMDataTypes.get(name);
        if (dt == null && !permitNull)
            throw new Error("unknown data type; "+ name);
        return dt;
    }

    private VMDataType(String name, boolean isObject) {
        this.name = name;
        this.mIsObject = isObject;
        this.id = definedVMDataTypes.size();
        reptypes = new ArrayList<VMRepType>();
    }

    static {
        if (DEBUG_WITH_SMALL) {
            defineVMDataType("string", false);
            defineVMDataType("fixnum", false);
            defineVMDataType("array", true);
        } else {
            defineVMDataType("string", false);
            defineVMDataType("fixnum", false);
            defineVMDataType("flonum", false);
            defineVMDataType("special", false); 
            defineVMDataType("simple_object", true);
            defineVMDataType("array", true);
            defineVMDataType("function", true);
            defineVMDataType("builtin", true);
            defineVMDataType("iterator", true);
            defineVMDataType("regexp", true);
            defineVMDataType("string_object", true);
            defineVMDataType("number_object", true);
            defineVMDataType("boolean_object", true);
            NONE = defineVMDataType("none", true); /* A pseudo-type representing the BOT type */
        }
    }

    public static List<VMDataType> all() {
        List<VMDataType> lst = new ArrayList<VMDataType>(definedVMDataTypes.values());
        lst.remove(NONE);
        Collections.sort(lst);
        return lst;
    }

    public static List<VMDataType> allContainsNone() {
        List<VMDataType> lst = new ArrayList<VMDataType>(definedVMDataTypes.values());
        Collections.sort(lst);
        return lst;
    }

    /*
     * data type instance
     */

    String name;
    String struct;
    boolean mIsObject;
    ArrayList<VMRepType> reptypes;
    JSValueVMType asttype;
    private int id;

    public String getName() {
        return name;
    }

    public ArrayList<VMRepType> getVMRepTypes() {
        return reptypes;
    }

    void addVMRepType(VMRepType r) {
        reptypes.add(r);
    }

    void setDataStructure(String struct) {
        this.struct = struct;
    }

    public boolean isObject() {
        return mIsObject;
    }

    public int getID() {
        return id;
    }

    public void setJSValueVMType(JSValueVMType t){
        asttype = t;
    }

    public JSValueVMType toJSValueVMType(){
        return asttype;
    }

    @Override
    public String toString() {
        return name;
        /*
        String s = name + " =";
        for (VMRepType r : reptypes) {
            s += " " + r;
        }
        return s;
         */
    }

    @Override
    public int compareTo(VMDataType that) {
        return this.id - that.id;
    }
}
