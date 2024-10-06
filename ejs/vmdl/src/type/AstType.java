/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package type;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.HashSet;
import java.util.Set;

import vmdlc.ErrorPrinter;
import vmdlc.SyntaxTree;
import nez.ast.Symbol;

import java.lang.Error;

/* 
 * === AstType ===
 * AstType
 *  |- AstBaseType
 *  |   |- AstPrimitiveType
 *  |   |   |- JSValueType
 *  |   |   |   |- JSValueVMType
 *  |   |   |- AstAliasType
 *  |   |- AstComplexType
 *  |       |- AstArrayType
 *  |       |- AstMappingType
 *  |- AstPairType
 *  |- AstProductType
 * 
 * === AstPrimitiveType Hierarchy ===
 * Top
 *  |- void
 *  |- CValue
 *  |   |- (User-defined alias types)
 *  |- int
 *  |- uint
 *  |- int32_t
 *  |- uint32_t
 *  |- double
 *  |- cstring
 *  |- InstructionDisplacement
 *  |- ConstantDisplacement
 *  |- StackDisplacement
 *  |- Subscript
 *  |- JSValue
 *      |- Fixnum
 *      |- Flonum
 *      |- String
 *      |- Special
 *      |- SimpleObject
 *      |- Array
 *      |- Function
 *      |- Builtin
 *      |- Iterator
 *      |- Regexp
 *      |- StringObject
 *      |- NumberObject
 *      |- BooleanObject
 *      |- (User-defined union types)
 */

public class AstType {
    static Map<String, AstPrimitiveType> definedTypes = new HashMap<>();
    static Map<String, AstMappingType> definedMappingTypes = new HashMap<>();
    static Map<VMDataType, JSValueVMType> vmtToTypes = new HashMap<>();
    static Map<Integer, JSValueType> unionBitsToTypes = new HashMap<>();
    static int definedVMDataTypeSize = 0;

    static AstPrimitiveType defineType(String name){
        return defineType(name, null);
    }
    static AstPrimitiveType defineType(String name, AstPrimitiveType parent){
        AstPrimitiveType t = new AstPrimitiveType(name, parent);
        definedTypes.put(name, t);
        return t;
    }
    public static JSValueType defineJSValueType(String name, int unionBits, AstPrimitiveType parent){
        JSValueType t = new JSValueType(name, unionBits, parent);
        putJSValueType(t);
        return t;
    }
    public static JSValueType defineJSValueType(String name, int unionBits){
        return defineJSValueType(name, unionBits, (AstPrimitiveType)getPrimitiveType("JSValue"));
    }
    static JSValueVMType defineJSValueVMType(String name, AstPrimitiveType parent, VMDataType vmt){
        JSValueVMType t = new JSValueVMType(name, parent, vmt);
        vmtToTypes.put(vmt, t);
        putJSValueType(t);
        return t;
    }
    public static AstMappingType defineMappingType(String name, boolean heapAnnotation){
        AstMappingType type = new AstMappingType(name, heapAnnotation);
        definedMappingTypes.put(name, type);
        return type;
    }
    public static AstMappingType defineMappingType(String name, String cCodeName, boolean heapAnnotation){
        AstMappingType type = new AstMappingType(name, cCodeName, heapAnnotation);
        definedMappingTypes.put(name, type);
        return type;
    }
    public static void addCValueTypeAlias(String typeName){
        AstAliasType t = new AstAliasType(typeName);
        definedTypes.put(typeName, t);
    }
    public static void addCValueTypeAlias(String typeName, String cCodeName){
        AstAliasType t = new AstAliasType(typeName, cCodeName);
        definedTypes.put(typeName, t);
    }
    public static AstMappingType getMappingType(String name){
        return definedMappingTypes.get(name);
    }
    public static AstPrimitiveType getPrimitiveType(String name) {
        if(name.endsWith("[]")){
            ErrorPrinter.error("ArrayType is not expected");
        }
        return definedTypes.get(name);
    }
    public static AstBaseType getBaseType(String name){
        AstBaseType ret = getPrimitiveType(name);
        if(ret != null)
            return ret;
        return getMappingType(name);
    }
    public static JSValueVMType get(VMDataType vmt) {
        return vmt.toJSValueVMType();
        //return vmtToTypes.get(vmt);
    }
    public static void putJSValueType(JSValueType jst){
        String name = jst.getName();
        int unionBits = jst.getUnionBits();
        if(name == null)
            System.err.println("InternalWarning: An unnamed JSValueType is registered.");
        if(unionBits == 0)
            System.err.println("InternalWarning: An empty JSValueType is registered.");
        definedTypes.put(name, jst);
        unionBitsToTypes.put(unionBits, jst);
    }

    // public static final Args ARGS;
    // static final AstProductType BUILTINFUNCTION_TYPE;

    // public static boolean isBuiltinFunctionType(AstType type){
    //     return BUILTINFUNCTION_TYPE.equals(type);
    // }

    static {
        AstPrimitiveType top = defineType("Top");
        defineType("void", top);
        defineType("CValue", top).setCCodeName("cint"); /* CCodeName have to be "int64_t" in 64-bit mode, "int32_t" in 32-bit mode */
        defineType("int", top).setCCodeName("cint");
        defineType("uint", top).setCCodeName("cuint");
        defineType("int32_t", top);
        defineType("uint32_t", top);
        defineType("intjsv_t", top);
        defineType("uintjsv_t", top);
        defineType("double", top);
        defineType("cstring", top).setCCodeName("char*");
        defineType("ConstantDisplacement", top);
        defineType("InstructionDisplacement", top);
        defineType("StackDisplacement", top);
        defineType("Subscript", top);
        JSValueType jsValueType = new JSValueType("JSValue", top);
        definedTypes.put("JSValue", jsValueType);
        defineJSValueVMType("String", jsValueType, VMDataType.get("string"));
        defineJSValueVMType("Fixnum", jsValueType, VMDataType.get("fixnum"));
        defineJSValueVMType("Flonum", jsValueType, VMDataType.get("flonum"));
        defineJSValueVMType("Special", jsValueType, VMDataType.get("special"));
        defineJSValueVMType("SimpleObject", jsValueType, VMDataType.get("simple_object"));
        defineJSValueVMType("Array", jsValueType, VMDataType.get("array"));
        defineJSValueVMType("Function", jsValueType, VMDataType.get("function"));
        defineJSValueVMType("Builtin", jsValueType, VMDataType.get("builtin"));
        defineJSValueVMType("Iterator", jsValueType, VMDataType.get("iterator"));
        defineJSValueVMType("Regexp", jsValueType, VMDataType.get("regexp"));
        defineJSValueVMType("StringObject", jsValueType, VMDataType.get("string_object"));
        defineJSValueVMType("NumberObject", jsValueType, VMDataType.get("number_object"));
        defineJSValueVMType("BooleanObject", jsValueType, VMDataType.get("boolean_object"));
        jsValueType.setUnionBits((1 << definedVMDataTypeSize) - 1);
        putJSValueType(jsValueType);
    }

    String name;

    public static AstType nodeToType(SyntaxTree node) {
        if (node.is(Symbol.unique("TypeProduct"))) {
            return new AstProductType(nodeToType(node.get(0)), nodeToType(node.get(1)));
        } else if (node.is(Symbol.unique("TypePair"))) {
            int size = node.size();
            AstBaseType[] al = new AstBaseType[size];
            for (int i = 0; i < size; i++) {
                AstType elementType = nodeToType(node.get(i));
                if(!(elementType instanceof AstBaseType))
                    ErrorPrinter.error("Non-BaseType cannot be an element of PairTe: "+elementType.toString(), node);
                al[i] = (AstBaseType)elementType;
            }
            return new AstPairType(al);
        } else if(node.is(Symbol.unique("TypeArray"))) {
            AstType elementType = nodeToType(node.get(Symbol.unique("type")));
            if(!(elementType instanceof AstBaseType))
                ErrorPrinter.error("Non-BaseType cannot be an element of ArrayType: "+elementType.toString(), node);
            AstArrayType ret;
            if(node.has(Symbol.unique("arraymodifier"))){
                try{
                    ret = AstArrayType.newAstArrayType((AstBaseType)elementType, node.get(Symbol.unique("arraymodifier")));
                }catch(Error e){
                    ErrorPrinter.error(e.getMessage(), node);
                    ret = null;
                }
            }else{
                ret = new AstArrayType((AstBaseType)elementType, false, false);
            }
            return ret;
        }else if (node.is(Symbol.unique("JSValueTypeName")) || node.is(Symbol.unique("Ctype"))){
            if(node.has(Symbol.unique("typemodifier")) && !node.get(Symbol.unique("typemodifier")).isEmpty())
                ErrorPrinter.error(node.toText()+" cannot be specified modifiers");
            AstType ret = AstType.getPrimitiveType(node.toText());
            if(ret == null)
                ErrorPrinter.error("Unkwon type: \""+node.toText()+'\"', node);
            return ret;
        }else if (node.is(Symbol.unique("UserTypeName"))) {
            String typeName = node.get(Symbol.unique("type")).toText();
            AstBaseType type = getPrimitiveType(typeName);
            if(type != null){
                if(node.has(Symbol.unique("typemodifier")) && !node.get(Symbol.unique("typemodifier")).isEmpty())
                    ErrorPrinter.error(node.toText()+" cannot be specified modifiers", node);
                return type;
            }
            AstMappingType ctype = getMappingType(typeName);
            if(ctype == null)
                ErrorPrinter.error("Unkwon type: \""+typeName+'\"', node);
            if(ctype instanceof AstMappingType){
                if(node.has(Symbol.unique("typemodifier"))){
                    SyntaxTree typeModifierNode = node.get(Symbol.unique("typemodifier"));
                    for(SyntaxTree modifier : typeModifierNode){
                        switch(modifier.toText()){
                            case "heap":
                                ErrorPrinter.error("MappingTypes cannot be specified the heap modifier except at externC");
                                break;
                            case "val":
                                try{
                                    ctype = ctype.getValAnnotated();
                                }catch(Error e){
                                    ErrorPrinter.error(e.getMessage(), node);
                                }
                                break;
                            default:
                                ErrorPrinter.error("Unknown modifier : \""+modifier.toText()+'\"');
                                break;
                        }
                    }
                }
            }
            return ctype;
        } else if (node.is(Symbol.unique("TopTypeName")))
            return AstType.getPrimitiveType("Top");
        else if (node.is(Symbol.unique("VoidTypeName")))
            return AstType.getPrimitiveType("void");
        throw new Error("Unknown type: "+node.toText());
    }

    static int tempTypeCounter = 0;
    public static JSValueType nodeToUnionType(SyntaxTree node, String name) {
        if(node.is(Symbol.unique("TypeUnion"))){
            AstType t = getPrimitiveType(node.get(Symbol.unique("type")).toText());
            if(!(t instanceof JSValueType))
                throw new Error("Internal Error: non-JSValueType: \""+node.toText()+'\"');
            return (JSValueType)t;
        }
        if(node.is(Symbol.unique("NotUnion"))){
            JSValueType t = nodeToUnionType(node, "TEMP@"+(tempTypeCounter++));
            if(!(t instanceof JSValueType))
                throw new Error("InternalError: A non-UnionType is specified in UnionType");
            JSValueType jst = (JSValueType) t;
            int bits = jst.getUnionBits();
            int reverse = bits ^ ((1 << definedVMDataTypeSize) - 1);
            return new JSValueType(name, reverse);
        }
        if(node.is(Symbol.unique("OrUnion"))){
            SyntaxTree[] subTree = (SyntaxTree[]) node.getSubTree();
            int unionBits = 0;
            for(SyntaxTree child : subTree){
                JSValueType t = nodeToUnionType(child, "TEMP@"+(tempTypeCounter++));
                unionBits = unionBits | t.getUnionBits();
            }
            return new JSValueType(name, unionBits);
        }
        if(node.is(Symbol.unique("AndUnion"))){
            SyntaxTree[] subTree = (SyntaxTree[]) node.getSubTree();
            int unionBits = 0;
            for(SyntaxTree child : subTree){
                JSValueType t = nodeToUnionType(child, "TEMP@"+(tempTypeCounter++));
                unionBits = unionBits & t.getUnionBits();
            }
            return new JSValueType(name, unionBits);
        }
        throw new Error("InternalError: Invalid syntaxTree: "+node.getTag());
    }

    static int lubGeneratedSize = 0;
    public AstType lub(AstType that) {
        if(!(this instanceof AstPrimitiveType) || !(that instanceof AstPrimitiveType)) {
            /* non-AstPrimitiveType lub */
            if(this.equals(that)) return this;
            if(this == BOT) return that;
            if(that == BOT) return this;
            if(this == getPrimitiveType("Top")) return this;
            if(that == getPrimitiveType("Top")) return that;
            throw new Error("InternalError: AstType lub type error "+this.toString()+", "+that.toString());
        }
        if(!(this instanceof JSValueType) || !(that instanceof JSValueType)) {
            /* non-JSValueType lub */
            AstPrimitiveType a = (AstPrimitiveType)that;
            AstPrimitiveType b = (AstPrimitiveType)this;
            if(a == BOT) return b;
            if(b == BOT) return a;
            while(a.depth > b.depth)
                a = a.parent;
            while(a.depth < b.depth)
                b = b.parent;
            while(a != b) {
                a = a.parent;
                b = b.parent;
            }
            return a;
        }
        /* JSValueType lub */
        JSValueType a = (JSValueType)that;
        JSValueType b = (JSValueType)this;
        int lubBits = a.getUnionBits() | b.getUnionBits();
        JSValueType lubed = unionBitsToTypes.get(lubBits);
        if(lubed == null)
            lubed = defineJSValueType("LUB@"+(lubGeneratedSize++), lubBits, (AstPrimitiveType)getPrimitiveType("JSValue"));
        /* For test print */
        // System.err.println("> Lub info");
        // System.err.println("> a="+a.toString()+", "+Integer.toBinaryString(a.getUnionBits()));
        // System.err.println("> b="+b.toString()+", "+Integer.toBinaryString(b.getUnionBits()));
        // System.err.println("> lubed="+lubed.toString()+", "+lubed.getUnionBits());
        // System.err.println("> lubBits="+Integer.toBinaryString(lubBits)+", lubed.unionBits="+Integer.toBinaryString(lubed.getUnionBits()));
        return lubed;
    }

    // Use the fact that JSValueType forms a tree rather than a lattice
    // TODO: update
    public AstType glb(AstType that) {
        if (!(this instanceof AstPrimitiveType) || !(that instanceof AstPrimitiveType)) {
            throw new Error("InternalError: AstType glb type error: "+this+" vs "+that);
        }
        AstPrimitiveType a = (AstPrimitiveType)this;
        AstPrimitiveType b = (AstPrimitiveType)that;
        if (a == BOT)
            return BOT;
        if (b == BOT)
            return BOT;
        while (a.depth > b.depth)
            a = a.parent;
        while (a.depth < b.depth)
            b = b.parent;
        if (a != b)
            return AstPrimitiveType.BOT;
        else if (a == this)
            return that;
        else if (b == that)
            return this;
        throw new Error("InternalError: glb is wrong algorithm!");
    }

    public Set<AstType> getDetailedTypes(){
        Set<AstType> ret = new HashSet<>(1);
        ret.add(this);
        return ret;
    }

    public boolean isSuperOrEqual(AstType t) {
        if(this == getPrimitiveType("Top")) return true; /* The Top type is the top of type hierarchy (EVEN ARRAY TYPE) */
        if(t == AstType.BOT) return true;
        if(!(t instanceof AstPrimitiveType) || !(this instanceof AstPrimitiveType))
            return t.equals(this);
        if(t instanceof JSValueType && this instanceof JSValueType){
            int thisUnion = ((JSValueType)this).getUnionBits();
            int thatUnion = ((JSValueType)t).getUnionBits();
            return ((~thisUnion) & thatUnion) == 0; /* Is thisUnion contains all of thatUnion */
        }
        AstPrimitiveType thisType = (AstPrimitiveType)this;
        AstPrimitiveType type = (AstPrimitiveType)t;
        while(type != null){
            if (type == thisType) return true;
            type = type.parent;
        }
        return false;
    }
    @Override
    public boolean equals(Object obj){
        if(obj == null) return false;
        if(!(obj instanceof AstType)) return false;
        return this==obj;
    }

    boolean requireGCPushPopFlag;

    public boolean isRequiredGCPushPop(){
        return requireGCPushPopFlag;
    }
    public void setRequireGCPushPop(boolean flag){
        requireGCPushPopFlag = flag;
    }

    public static class AstBaseType extends AstType {
        String cCodeName;

        private AstBaseType(String name){
            this.name = name;
            setRequireGCPushPop(false);
            setCCodeName(name);
        }
        public void setCCodeName(String name){
            cCodeName = name;
        }
        public String getCCodeName(){
            return cCodeName;
        }
        public AstArrayType getArrayType(boolean heapAnnotation, boolean valAnnotation){
            return new AstArrayType(this, heapAnnotation, valAnnotation);
        }
        @Override
        public String toString() {
            return name;
        }
    }
    public static class AstPrimitiveType extends AstBaseType {
        AstPrimitiveType parent;
        int depth;

        private AstPrimitiveType(String _name) {
            super(_name);
        }
        private AstPrimitiveType(String _name, AstPrimitiveType _parent) {
            super(_name);
            parent = _parent;
            depth = 0;
            for (AstPrimitiveType t = parent; t != null; t = t.parent)
                depth++;
        }
    }

    public static final JSValueVMType BOT = defineJSValueVMType("$bot", null, VMDataType.get("none"));
    public static class JSValueType extends AstPrimitiveType {
        int unionBits;
        Set<JSValueVMType> union;
    
        private JSValueType(String name, AstPrimitiveType parent) {
            super(name, parent);
            setRequireGCPushPop(true);
        }
        private JSValueType(String name, int unionBits, AstPrimitiveType parent) {
            super(name, parent);
            this.unionBits = unionBits;
            setRequireGCPushPop(true);
        }
        private JSValueType(String name) {
            this(name, (AstPrimitiveType)getPrimitiveType("JSValue"));
        }
        private JSValueType(String name, int unionBits) {
            this(name, (AstPrimitiveType)getPrimitiveType("JSValue"));
            setUnionBits(unionBits);
        }
        public void setUnionBits(int bits){
            this.unionBits = bits;
            union = null;
        }
        public void setName(String name){
             this.name = name;
        }
        public int getUnionBits(){
            return unionBits;
        }
        public String getName(){
            return name;
        }
        public Set<JSValueVMType> getUnion(){
            if(union == null){
                union = new HashSet<>(definedVMDataTypeSize);
                for(int i=0; i<definedVMDataTypeSize; i++){
                    int uniqueNumber = unionBits & (1 << i);
                    if(uniqueNumber == 0) continue;
                    JSValueType vmType = unionBitsToTypes.get(uniqueNumber);
                    if(vmType == null || !(vmType instanceof JSValueVMType))
                        throw new Error("InternalError: bitsToJSValueTypes is broken");
                    union.add((JSValueVMType)vmType);
                }
            }
            return union;
        }
        @Override
        public String getCCodeName(){
            return "JSValue";
        }
        @Override
        public Set<AstType> getDetailedTypes(){
            return new HashSet<>(getUnion());
        }
        public Set<VMDataType> getVMDataTypes(){
            Set<JSValueVMType> union = getUnion();
            Set<VMDataType> result = new HashSet<>(union.size());
            for(JSValueVMType jsvmt : union){
                result.add(jsvmt.getVMDataType());
            }
            return result;
        }
        @Override
        public boolean isSuperOrEqual(AstType that){
            if(!(that instanceof JSValueType))
                return false;
            int thatUnionBit = ((JSValueType)that).getUnionBits();
            return (thatUnionBit & unionBits) == thatUnionBit;
        }
    }

    public static class JSValueVMType extends JSValueType {
        VMDataType vmt;

        private JSValueVMType(String name, AstPrimitiveType type, VMDataType vmt) {
            super(name, type);
            this.vmt = vmt;
            vmt.setJSValueVMType(this);
            setUnionBits(1 << definedVMDataTypeSize++);
            union = new HashSet<>(1);
            union.add(this);
        }
        public VMDataType getVMDataType(){
            return vmt;
        }
        @Override
        public boolean isSuperOrEqual(AstType that){
            return this == that;
        }
    }
    public static class AstAliasType extends AstPrimitiveType{
        private AstAliasType(String name) {
            super(name, (AstPrimitiveType)getPrimitiveType("CValue"));
        }
        private AstAliasType(String name, String cCodeName) {
            super(name, (AstPrimitiveType)getPrimitiveType("CValue"));
            setCCodeName(cCodeName);
        }
    }

    public static class AstComplexType extends AstBaseType{
       boolean isAnnotatedHeap;
       boolean isAnnotatedVal;
       
        private AstComplexType(String name){
            super(name);
            setHasHeapAnnotation(false);
            setHasValAnnotation(false);
        }
        private AstComplexType(String name, boolean hasHeapAnnotation, boolean hasValAnnotation) throws Error{
            super(name);
            setHasHeapAnnotation(hasHeapAnnotation);
            setHasValAnnotation(hasValAnnotation);
        }
        public void setHasHeapAnnotation(boolean flag) throws Error{
            isAnnotatedHeap = flag;
            if(isAnnotatedHeap && isAnnotatedVal)
                throw new Error("conflict 'heap' and 'val' modifiers");
            setRequireGCPushPop(flag);
        }
        public void setHasValAnnotation(boolean flag) throws Error{
            isAnnotatedVal = flag;
            if(isAnnotatedHeap && isAnnotatedVal)
                throw new Error("conflict 'heap' and 'val' modifiers");
        }
        public boolean hasHeapAnnotation(){
            return isAnnotatedHeap;
        }
        public boolean hasValAnnotation(){
            return isAnnotatedVal;
        }
    }

    public static class AstArrayType extends AstComplexType {
        AstBaseType elementType;

        public AstArrayType(AstBaseType elementType, boolean hasHeapAnnotation, boolean hasValAnnotation){
            super(elementType.toString()+"[]", hasHeapAnnotation, hasValAnnotation);
            this.elementType = elementType;
            setCCodeName(elementType.toString()+"*");
        }
        private static AstArrayType newAstArrayType(AstBaseType elementType, SyntaxTree modifierNode) throws Error{
            boolean hasHeapAnnotation = false;
            boolean hasValAnnotation = false;
            for(SyntaxTree modifier : modifierNode){
                switch(modifier.toText()){
                    case "heap":
                        hasHeapAnnotation = true;
                        break;
                    case "val":
                        hasValAnnotation = true;
                        break;
                    default:
                        ErrorPrinter.error("Unknown modifier : \""+modifier.toText()+'\"');
                        break;
                }
            }
            return new AstArrayType(elementType, hasHeapAnnotation, hasValAnnotation);
        }
        public AstBaseType getElementType(){
            return elementType;
        }
        @Override
        public int hashCode(){
            return elementType.hashCode();
        }
        @Override
        public boolean equals(Object obj){
            if(obj == null) return false;
            if(!(obj instanceof AstArrayType)) return false;
            return elementType.equals(((AstArrayType)obj).elementType);
        }
    }

    public static class AstMappingType extends AstComplexType{
        Map<String, Field> fieldMap;
        AstMappingType valAnnotated;

        public AstMappingType(String name, String cCodeName, boolean hasHeapAnnotation){
            super(name, hasHeapAnnotation, false);
            fieldMap = new HashMap<>();
            setCCodeName(cCodeName);
        }
        public AstMappingType(String name, boolean heapAnnotation){
            this(name, name, heapAnnotation);
        }
        private AstMappingType(AstMappingType original){
            super(original.name, original.isAnnotatedHeap, original.isAnnotatedVal);
            this.fieldMap = new HashMap<>(original.fieldMap);
            this.setCCodeName(original.cCodeName);
        }
        public AstBaseType getFieldType(String name){
            Field field = fieldMap.get(name);
            if(field != null)
                return field.type;
            return null;
        }
        public void addField(AstBaseType type, String name){
            fieldMap.put(name, new Field(type, name));
        }
        public AstMappingType getValAnnotated() throws Error{
            if(valAnnotated == null){
                valAnnotated = new AstMappingType(this);
                valAnnotated.setHasValAnnotation(true);
            }
            return valAnnotated;
        }
        public String getAccessOperator(){
            return isAnnotatedVal ? "." : "->";
        }
        @Override
        public int hashCode(){
            return name.hashCode();
        }
        @Override
        public boolean equals(Object obj){
            if(obj == null) return false;
            if(!(obj instanceof AstMappingType)) return false;
            AstMappingType that = (AstMappingType)obj;
            return (name.equals(that.name) && fieldMap.equals(that.fieldMap));
        }

        private class Field{
            private AstBaseType type;
            private String name;

            private Field(AstBaseType _type, String _name){
                name = _name;
                type = _type;
            }
            @Override
            public int hashCode(){
                return name.hashCode();
            }
            @Override
            public boolean equals(Object obj){
                if(obj == null) return false;
                if(!(obj instanceof Field)) return false;
                Field that = (Field)obj;
                return (name.equals(that.name) && type.equals(that.type));
            }
        }
    }

    public static class AstPairType extends AstType {
        AstBaseType[] types;

        public AstPairType(AstBaseType[] _types) {
            types = _types;
        }
        public String toString() {
            int size = types.length;
            StringBuffer sb = new StringBuffer();
            sb.append("(");
            if (size > 0)
                sb.append(types[0].toString());
            for (int i = 1; i < size; i++) {
                sb.append(",");
                sb.append(types[i].toString());
            }
            sb.append(")");
            return sb.toString();
        }
        public AstBaseType[] getTypes() {
            return types;
        }
        public int size() {
            return types.length;
        }
        @Override
        public int hashCode(){
            return types.hashCode();
        }
        @Override
        public boolean equals(Object obj){
            if(obj == null) return false;
            if(!(obj instanceof AstPairType)) return false;
            return Arrays.deepEquals(types, ((AstPairType)obj).types);
        }
    }

    public static class AstProductType extends AstType {
        AstType domain;
        AstType range;
        AstBaseType[] domainArray;

        public AstProductType(AstType _domain, AstType _range) {
            domain = _domain;
            range = _range;
        }
        public String toString() {
            StringBuffer sb = new StringBuffer();
            sb.append(domain.toString());
            sb.append("->");
            sb.append(range.toString());
            return sb.toString();
        }
        public AstType getDomain() {
            return domain;
        }
        public AstType getRange() {
            return range;
        }
        public int parameterSize(){
            if(domain instanceof AstBaseType)
                return 1;
            if(domain instanceof AstPairType)
                return ((AstPairType)domain).size();
            throw new Error("Domain type of AstProductType is illigal state: "+domain.toString());
        }
        public AstBaseType[] getDomainAsArray(){
            if(domainArray == null){
                if(domain instanceof AstPairType)
                    domainArray = ((AstPairType)domain).getTypes();
                else if(domain instanceof AstBaseType)
                    domainArray = new AstBaseType[]{ (AstBaseType)domain };
                else
                    ErrorPrinter.error("ProductTypes domain is expected PairType or BaseType: "+domain.getClass().toString());
            }
            return domainArray;
        }
        @Override
        public int hashCode(){
            return domain.hashCode()*range.hashCode();
        }
        @Override
        public boolean equals(Object obj){
            if(obj == null) return false;
            if(!(obj instanceof AstProductType)) return false;
            return (domain.equals(((AstProductType)obj).domain)
                 && range.equals(((AstProductType)obj).range));
        }
    }

    // public static class Args extends AstArrayType{
    //     public Args(){
    //         super(get("JSValue"));
    //     }
    //     @Override
    //     public String toString(){
    //         return "Args";
    //     }
    //     @Override
    //     public String getCCodeName(){
    //         return "JSValue[]";
    //     }
    // }
}
