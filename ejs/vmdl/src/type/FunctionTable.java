package type;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import type.AstType.AstProductType;
import type.AstType.AstPairType;
import type.AstType.AstBaseType;

public class FunctionTable{
    private static Map<String, FunctionInfo> functionMap = new HashMap<>();

    static{
        AstProductType topToVoidType = new AstProductType(AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("void"));
        AstProductType ttToVoidType = new AstProductType(
            new AstPairType(new AstBaseType[]{AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top")}), AstType.getPrimitiveType("void"));
        AstProductType tttToVoidType = new AstProductType(
            new AstPairType(new AstBaseType[]{AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top")}),
            AstType.getPrimitiveType("void"));
        AstProductType ttttToVoidType = new AstProductType(
            new AstPairType(new AstBaseType[]{AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top"),
            AstType.getPrimitiveType("Top")}), AstType.getPrimitiveType("void"));
        AstProductType tttttToVoidType = new AstProductType(
            new AstPairType(new AstBaseType[]{AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top"),
            AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top")}), AstType.getPrimitiveType("void"));
        AstProductType ttttttToVoidType = new AstProductType(
            new AstPairType(new AstBaseType[]{AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top"),
            AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top")}), AstType.getPrimitiveType("void"));
        AstProductType tttttttToVoidType = new AstProductType(
            new AstPairType(new AstBaseType[]{AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top"),
            AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top"), AstType.getPrimitiveType("Top")}),
            AstType.getPrimitiveType("void"));
        AstProductType voidToVoidType = new AstProductType(AstType.getPrimitiveType("void"), AstType.getPrimitiveType("void"));
        put("GC_PUSH",  topToVoidType, Collections.emptySet());
        put("GC_PUSH2", ttToVoidType, Collections.emptySet());
        put("GC_PUSH3", tttToVoidType, Collections.emptySet());
        put("GC_PUSH4", ttttToVoidType, Collections.emptySet());
        put("GC_PUSH5", tttttToVoidType, Collections.emptySet());
        put("GC_PUSH6", ttttttToVoidType, Collections.emptySet());
        put("GC_PUSH7", tttttttToVoidType, Collections.emptySet());
        put("GC_POP", topToVoidType, Collections.emptySet());
        put("GC_POP2", ttToVoidType, Collections.emptySet());
        put("GC_POP3", tttToVoidType, Collections.emptySet());
        put("GC_POP4", ttttToVoidType, Collections.emptySet());
        put("GC_POP5", tttttToVoidType, Collections.emptySet());
        put("GC_POP6", ttttttToVoidType, Collections.emptySet());
        put("GC_POP7", tttttttToVoidType, Collections.emptySet());
        put("builtin_prologue", voidToVoidType, Collections.emptySet());
        put("__builtin_unreachable", voidToVoidType, Collections.emptySet());
    }

    public static void put(String name, AstProductType type, Set<FunctionAnnotation> annotations){
        if(functionMap.get(name) != null){
            System.err.println("InternalWarning: Duplicate Function define: "+name);
        }
        functionMap.put(name, new FunctionInfo(type, annotations));
    }

    public static boolean contains(String name){
        return functionMap.containsKey(name);
    }

    public static AstProductType getType(String name){
        FunctionInfo info = functionMap.get(name);
        if(info == null){
            throw new Error("Cannot find function: "+name);
        }
        return info.type;
    }

    public static boolean hasAnnotations(String name, FunctionAnnotation annotation){
        FunctionInfo info = functionMap.get(name);
        if(info == null){
            throw new Error("Cannot find function: "+name);
        }
        return info.annotations.contains(annotation);
    }

    public static boolean equalsAnnotation(String name, Set<FunctionAnnotation> annotations){
        if(!contains(name)) return false;
        Set<FunctionAnnotation> targetsAnnotations = functionMap.get(name).annotations;
        return targetsAnnotations.equals(annotations);
    }

    public static Set<FunctionAnnotation> getAnnotations(String name){
        FunctionInfo info = functionMap.get(name);
        if(info == null){
            throw new Error("Cannot find function: "+name);
        }
        return info.annotations;
    }
    private static class FunctionInfo{
        AstProductType type;
        Set<FunctionAnnotation> annotations;
        private FunctionInfo(AstProductType _type, Set<FunctionAnnotation> _annotations){
            type = _type;
            annotations = _annotations;
        }
    }
}
