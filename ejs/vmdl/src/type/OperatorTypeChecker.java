package type;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
/*
public class OperatorTypeChecker{
  private AstType[]   unaryOperatorTypeTable;
  private AstType[][] binaryOperatorTypeTable;
  protected static Map<AstType, Integer> numberMap = new HashMap<>();
  protected static final AstType T_CINT         = AstType.get("int");
  protected static final AstType T_CDOUBLE      = AstType.get("double");
  protected static final AstType T_SUBSCRIPT    = AstType.get("Subscript");
  protected static final AstType T_CDISPLACEMENT = AstType.get("ConstantDisplacement");
  protected static final AstType T_IDISPLACEMENT = AstType.get("InstructionDisplacement");
  private static final int CINT         = 0;
  private static final int CDOUBLE      = 1;
  private static final int SUBSCRIPT    = 2;
  private static final int CDISPLACEMENT = 3;
  private static final int IDISPLACEMENT = 3;
  static{
    numberMap.put(T_CINT, CINT);
    numberMap.put(T_CDOUBLE, CDOUBLE);
    numberMap.put(T_SUBSCRIPT, SUBSCRIPT);
    numberMap.put(T_CDISPLACEMENT, CDISPLACEMENT);
    numberMap.put(T_IDISPLACEMENT, IDISPLACEMENT);
  }
  private static final int typeSize =  numberMap.keySet().size();
  public static final OperatorTypeChecker PLUS = new OperatorTypeChecker().unaryOperator();
  public static final OperatorTypeChecker MINUS = PLUS;
  public static final OperatorTypeChecker COMPL = new OperatorTypeChecker().unaryOperator();
  public static final OperatorTypeChecker NOT = COMPL;
  public static final OperatorTypeChecker ADD = new OperatorTypeChecker().binaryOperator();
  public static final OperatorTypeChecker SUB = new OperatorTypeChecker().binaryOperator();
  public static final OperatorTypeChecker MUL = new OperatorTypeChecker().binaryOperator();
  public static final OperatorTypeChecker DIV = MUL;
  public static final OperatorTypeChecker MOD = new OperatorTypeChecker().binaryOperator();
  public static final OperatorTypeChecker OR = new OperatorTypeChecker().binaryOperator();
  public static final OperatorTypeChecker AND = OR;
  public static final OperatorTypeChecker BITWISE_OR = new OperatorTypeChecker().binaryOperator();
  public static final OperatorTypeChecker BITWISE_XOR = BITWISE_OR;
  public static final OperatorTypeChecker BITWISE_AND = BITWISE_OR;
  public static final OperatorTypeChecker EQUALS = new EqualsOperatorTypeChecker();
  public static final OperatorTypeChecker NOT_EQUALS = EQUALS;
  public static final OperatorTypeChecker LESSTHAN_EQUALS = new OperatorTypeChecker().binaryOperator();
  public static final OperatorTypeChecker GRATORTHAN_EQUALS = LESSTHAN_EQUALS;
  public static final OperatorTypeChecker LESSTHAN = LESSTHAN_EQUALS;
  public static final OperatorTypeChecker GRATORTHAN = LESSTHAN_EQUALS;
  public static final OperatorTypeChecker LEFT_SHIFT = new OperatorTypeChecker().binaryOperator();
  public static final OperatorTypeChecker RIGHT_SHIFT = LEFT_SHIFT;
  private OperatorTypeChecker unaryOperator(){
    unaryOperatorTypeTable = new AstType[typeSize];
    for(int i=0; i<typeSize; i++){
      unaryOperatorTypeTable[i] = null;
    }
    return this;
  }
  private OperatorTypeChecker binaryOperator(){
    binaryOperatorTypeTable = new AstType[typeSize][typeSize];
    for(int i=0; i<typeSize; i++){
      for(int j=0; j<typeSize; j++){
        binaryOperatorTypeTable[i][j] = null;
      }
    }
    return this;
  }
  private void add(int operand, AstType result){
    unaryOperatorTypeTable[operand] = result;
  }
  private void add(int loperand, int roperand, AstType result){
    binaryOperatorTypeTable[loperand][roperand] = result;
  }
  static{
    //********************
    // Unary operators
    //********************
    // PLUS, MINUS
    PLUS.add(CINT, T_CINT);
    PLUS.add(CDOUBLE, T_CDOUBLE);
    // COMPL, NOT
    COMPL.add(CINT, T_CINT);

    //********************
    // Binary operators
    //********************
    // ADD
    ADD.add(CINT, CINT, T_CINT);
    ADD.add(CINT, CDOUBLE, T_CDOUBLE);
    ADD.add(CDOUBLE, CINT, T_CDOUBLE);
    ADD.add(CDOUBLE, CDOUBLE, T_CDOUBLE);
    ADD.add(CINT, SUBSCRIPT, T_SUBSCRIPT);
    ADD.add(SUBSCRIPT, CINT, T_SUBSCRIPT);
    ADD.add(CINT, CDISPLACEMENT, T_CDISPLACEMENT);
    ADD.add(CDISPLACEMENT, CINT, T_CDISPLACEMENT);
    ADD.add(CINT, IDISPLACEMENT, T_IDISPLACEMENT);
    ADD.add(IDISPLACEMENT, CINT, T_IDISPLACEMENT);
    // SUB
    SUB.add(CINT, CINT, T_CINT);
    SUB.add(CINT, CDOUBLE, T_CDOUBLE);
    SUB.add(CDOUBLE, CINT, T_CDOUBLE);
    SUB.add(CDOUBLE, CDOUBLE, T_CDOUBLE);
    SUB.add(CINT, SUBSCRIPT, T_SUBSCRIPT);
    SUB.add(SUBSCRIPT, CINT, T_SUBSCRIPT);
    SUB.add(CINT, CDISPLACEMENT, T_CDISPLACEMENT);
    SUB.add(CDISPLACEMENT, CINT, T_CDISPLACEMENT);
    SUB.add(CINT, IDISPLACEMENT, T_IDISPLACEMENT);
    SUB.add(IDISPLACEMENT, CINT, T_IDISPLACEMENT);
    SUB.add(SUBSCRIPT, SUBSCRIPT, T_SUBSCRIPT);
    //MUL, DIV
    MUL.add(CINT, CINT, T_CINT);
    MUL.add(CINT, CDOUBLE, T_CDOUBLE);
    MUL.add(CDOUBLE, CINT, T_CDOUBLE);
    MUL.add(CDOUBLE, CDOUBLE, T_CDOUBLE);
    // MOD
    MOD.add(CINT, CINT, T_CINT);
    // OR, AND
    OR.add(CINT, CINT, T_CINT);
    // BITWISE_OR, BITWISE_XOR, BITWISE_AND
    BITWISE_OR.add(CINT, CINT, T_CINT);
    // LESSTHAN_EQUALS, GRATORTHAN_EQUALS, LESSTHAN, GRATORTHAN
    LESSTHAN_EQUALS.add(CINT, CINT, T_CINT);
    LESSTHAN_EQUALS.add(CDOUBLE, CDOUBLE, T_CINT);
    LESSTHAN_EQUALS.add(SUBSCRIPT, SUBSCRIPT, T_CINT);
    LESSTHAN_EQUALS.add(CDISPLACEMENT, CDISPLACEMENT, T_CINT);
    LESSTHAN_EQUALS.add(IDISPLACEMENT, IDISPLACEMENT, T_CINT);
    // LEFT_SHIFT, RIGHT_SHIFT
    LEFT_SHIFT.add(CINT, CINT, T_CINT);
    // NOTE: EQUALS and NOT_EQUALS defined in EqualsOperatorTypeChecker
  }
  public AstType typeOf(AstType type){
    Integer index = numberMap.get(type);
    if(index == null){
      //System.err.println("InternalWarning: Index out of range: "+type.toString());
      return null;
    }
    return unaryOperatorTypeTable[index];
  }
  public AstType typeOf(AstType ltype, AstType rtype){
    if(ltype instanceof AstAliasType)
      ltype = ((AstAliasType)ltype).getRealType();
    if(rtype instanceof AstAliasType)
      rtype = ((AstAliasType)rtype).getRealType();
    Integer lindex = numberMap.get(ltype);
    Integer rindex = numberMap.get(rtype);
    if(lindex == null || rindex == null){
      //System.err.println("InternalWarning: Index out of range: ("+ltype.toString()+", "+rtype.toString()+")");
      return null;
    }
    return binaryOperatorTypeTable[lindex][rindex];
  }
}

class EqualsOperatorTypeChecker extends OperatorTypeChecker{
  @Override
  public AstType typeOf(AstType ltype, AstType rtype){
    
    AstType result;
    if(ltype.isSuperOrEqual(rtype) || rtype.isSuperOrEqual(ltype)){
      result = AstType.get("int");
    }else{
      result = null;
    }
    return result;
    
    return AstType.get("int");
  }
}
*/

import type.AstType.JSValueType;

public class OperatorTypeChecker{
  public static final OperatorChecker ADD               = new AddOperator();
  public static final OperatorChecker SUB               = ADD;
  public static final OperatorChecker MUL               = new MulOperator();
  public static final OperatorChecker DIV               = MUL;
  public static final OperatorChecker MOD               = new ModOperator();
  public static final OperatorChecker PLUS              = new PlusOperator();
  public static final OperatorChecker MINUS             = PLUS;
  public static final OperatorChecker NOT               = new NotOperator();
  public static final OperatorChecker COMPL             = NOT;
  public static final OperatorChecker OR                = new OrOperator();
  public static final OperatorChecker AND               = OR;
  public static final OperatorChecker BITWISE_OR        = new BitwiseOperator();
  public static final OperatorChecker BITWISE_AND       = BITWISE_OR;
  public static final OperatorChecker BITWISE_XOR       = BITWISE_OR;
  public static final OperatorChecker LESSTHAN_EQUALS   = new CompareOperator();
  public static final OperatorChecker GRATORTHAN_EQUALS = LESSTHAN_EQUALS;
  public static final OperatorChecker LESSTHAN          = LESSTHAN_EQUALS;
  public static final OperatorChecker GRATORTHAN        = LESSTHAN_EQUALS;
  public static final OperatorChecker EQUALS            = new EqualsOperator();
  public static final OperatorChecker NOT_EQUALS        = EQUALS;
  public static final OperatorChecker LEFT_SHIFT        = new ModOperator();
  public static final OperatorChecker RIGHT_SHIFT       = LEFT_SHIFT; 

/*
 * Type sets definitions in OperatorChecker
 * 
 * uNumbers  ::= cNumbers | vmNumbers
 * cNumbers  ::= 'double' | cIntegers
 * cIntegers ::= 'int32_t' | 'uint32_t' | 'int' | 'uint'
 * vmNumbers ::= 'InstructionDisplacement' | 'ConstantDisplacement' | 'StackDisplacement' | 'Subscript'
 */

  public static class OperatorChecker{
    private static final Map<AstType, Integer> cNumberLevel = new HashMap<>(5);
    private static final Set<AstType> cIntegers = new HashSet<>(5);
    private static final Set<AstType> vmNumbers = new HashSet<>(4); 
    static{
      cNumberLevel.put(AstType.getPrimitiveType("int32_t"),   0);
      cNumberLevel.put(AstType.getPrimitiveType("uint32_t"),  1);
      cNumberLevel.put(AstType.getPrimitiveType("intjsv_t"),  2);
      cNumberLevel.put(AstType.getPrimitiveType("int"),       3);
      cNumberLevel.put(AstType.getPrimitiveType("uintjsv_t"), 4);
      cNumberLevel.put(AstType.getPrimitiveType("uint"),      5);
      cNumberLevel.put(AstType.getPrimitiveType("double"),    6);
      cIntegers.add(AstType.getPrimitiveType("int32_t"));
      cIntegers.add(AstType.getPrimitiveType("uint32_t"));
      cIntegers.add(AstType.getPrimitiveType("int"));
      cIntegers.add(AstType.getPrimitiveType("uint"));
      cIntegers.add(AstType.getPrimitiveType("intjsv_t"));
      cIntegers.add(AstType.getPrimitiveType("uintjsv_t"));
      vmNumbers.add(AstType.getPrimitiveType("InstructionDisplacement"));
      vmNumbers.add(AstType.getPrimitiveType("ConstantDisplacement"));
      vmNumbers.add(AstType.getPrimitiveType("StackDisplacement"));
      vmNumbers.add(AstType.getPrimitiveType("Subscript"));
    }
    public static int cNumberCompare(AstType t1, AstType t2){
      return cNumberLevel.get(t1) - cNumberLevel.get(t2); 
    }
    public static AstType cNumberCalcTypeOf(AstType operand1, AstType operand2){
      if(!OperatorChecker.cNumberLevel.containsKey(operand1) || !OperatorChecker.cNumberLevel.containsKey(operand2))
        return null;
      if(cNumberCompare(operand1, operand2) >= 0)
        return operand1;
      else
        return operand2;
    }
    public static AstType vmNumberCalcTypeOf(AstType operand1, AstType operand2){
      if(vmNumbers.contains(operand1)){
        if(operand2.equals(operand1) || cIntegers.contains(operand2))
          return operand1;
        else
          return null;
      }else if(vmNumbers.contains(operand2)){
        if(operand1.equals(operand2) || cIntegers.contains(operand1))
          return operand2;
        else
          return null;
      }
      return null;
    }
    public static boolean isCInteger(AstType t){
      return cIntegers.contains(t);
    }
    public static boolean isCNumber(AstType t){
      return cNumberLevel.containsKey(t);
    }
    public static boolean isVMNumber(AstType t){
      return vmNumbers.contains(t);
    }
    public static boolean isUNumber(AstType t){
      return cNumberLevel.containsKey(t) || vmNumbers.contains(t);
    }
    public AstType typeOf(AstType operand1){
      return null;
    }
    public AstType typeOf(AstType operand1, AstType operand2){
      return null;
    }
    public boolean containBOT(AstType operand1, AstType operand2){
      return operand1 == AstType.BOT || operand2 == AstType.BOT;
    }
  }
  static class AddOperator extends OperatorChecker{
    @Override
    public AstType typeOf(AstType operand1, AstType operand2){
      AstType ret = cNumberCalcTypeOf(operand1, operand2);
      if(ret != null)
        return ret;
      return vmNumberCalcTypeOf(operand1, operand2);
    }
  }
  static class MulOperator extends OperatorChecker{
    @Override
    public AstType typeOf(AstType operand1, AstType operand2){
      return cNumberCalcTypeOf(operand1, operand2);
    }
  }
  static class ModOperator extends OperatorChecker{
    @Override
    public AstType typeOf(AstType operand1, AstType operand2){
      if(!isCInteger(operand1) || !isCInteger(operand2))
        return null;
      return operand1;
    }
  }
  static class PlusOperator extends OperatorChecker{
    @Override
    public AstType typeOf(AstType operand1){
      if(!isCNumber(operand1))
        return null;
      return operand1;
    }
  }
  static class NotOperator extends OperatorChecker{
    @Override
    public AstType typeOf(AstType operand1){
      if(!isCInteger(operand1))
        return null;
      return operand1;
    }
  }
  static class OrOperator extends OperatorChecker{
    @Override
    public AstType typeOf(AstType operand1, AstType operand2){
      if(!isCInteger(operand1) || !isCInteger(operand2))
        return null;
      return AstType.getPrimitiveType("int");
    }
  }
  static class BitwiseOperator extends OperatorChecker{
    @Override
    public AstType typeOf(AstType operand1, AstType operand2){
      if(!isCInteger(operand1) || !isCInteger(operand2))
        return null;
      return cNumberCalcTypeOf(operand1, operand2);
    }
  }
  static class CompareOperator extends OperatorChecker{
    @Override
    public AstType typeOf(AstType operand1, AstType operand2){
      if(!containBOT(operand1, operand2) && (!isUNumber(operand1) || !isUNumber(operand2) || (isVMNumber(operand1) && isVMNumber(operand2) && !operand1.equals(operand2))))
        return null;
      return AstType.getPrimitiveType("int");
    }
  }
  static class EqualsOperator extends OperatorChecker{
    @Override
    public AstType typeOf(AstType operand1, AstType operand2){
      if(containBOT(operand1, operand2) || operand1.equals(operand2) || ((operand1 instanceof JSValueType) && (operand2 instanceof JSValueType)))
        return AstType.getPrimitiveType("int");
      return null;
    }
  }
}