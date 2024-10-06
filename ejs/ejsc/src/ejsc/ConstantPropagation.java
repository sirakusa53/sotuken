/*
 * eJS Project
 * Kochi University of Technology
 * The University of Electro-communications
 *
 * The eJS Project is the successor of the SSJS Project at The University of
 * Electro-communications.
 */
package ejsc;
import java.lang.reflect.Constructor;
import java.util.ArrayList;
import java.util.List;

import ejsc.BCodeEvaluator.FixnumValue;
import ejsc.BCodeEvaluator.NumberValue;
import ejsc.BCodeEvaluator.SpecialValue;
import ejsc.BCodeEvaluator.StringValue;
import ejsc.BCodeEvaluator.Value;
import specfile.SpecFile;
import specfile.SuperinstructionSpec;
import specfile.SuperinstructionSpec.Superinstruction;

public class ConstantPropagation {
    static final boolean DEBUG = false;

    static class ConstantEvaluator extends BCodeEvaluator {
        class Environment extends BCodeEvaluator.Environment {
            BCode bc;

            Environment(BCode bc) {
                this.bc = bc;
            }

            @Override
            public BCodeEvaluator.Value lookup(Register r) {
                return findAndEvalDefinition(bc, r);
            }

            private BCode findDefinition(BCode bc, Register src) {
                BCode result = null;
                for (BCode def: rdefa.getReachingDefinitions(bc)) {
                    if (def.getDestRegister() == src) {
                        if (result == null)
                            result = def;
                        else
                            return null;
                    }
                }
                return result;
            }

            private Value findAndEvalDefinition(BCode bc, Register src) {
                BCode def = findDefinition(bc, src);
                if (def == null)
                    return null;
                return eval(new Environment(def), def);
            }
        }

        ReachingDefinition rdefa;

        ConstantEvaluator(VMImplementation vmImpl, ReachingDefinition rdefa) {
            super(vmImpl);
            this.rdefa = rdefa;
        }

        public SrcOperand evalSrcOperand(Environment env, SrcOperand src) {
            if (src instanceof RegisterOperand) {
                Value v = operandValue(env, src);
                if (v == null)
                    return src;
                if (v instanceof FixnumValue) {
                    long n = ((FixnumValue) v).getIntValue();
                    if (vmImpl.getInsnRep().inFixnumOperandRange(n))
                        return new FixnumOperand(n);
                    else
                        return src;
                } else if (v instanceof NumberValue) {
                    double d = ((NumberValue) v).getDoubleValue();
                    if (!vmImpl.getJSVRep().inFixnumRange(d))
                        return new FlonumOperand(d);
                    else
                        return src;
                } else if (v instanceof StringValue)
                    return new StringOperand(((StringValue) v).getStringValue());
                else if (v instanceof SpecialValue) {
                    SpecialValue s = (SpecialValue) v;
                    switch (s.getSpecialValue()) {
                    case TRUE:
                        return new SpecialOperand(CodeBuffer.SpecialValue.TRUE);
                    case FALSE:
                        return new SpecialOperand(CodeBuffer.SpecialValue.FALSE);
                    case NULL:
                        return new SpecialOperand(CodeBuffer.SpecialValue.NULL);
                    case UNDEFINED:
                        return new SpecialOperand(CodeBuffer.SpecialValue.UNDEFINED);
                    default:
                        throw new Error("Unknown special value");
                    }
                } else
                    throw new Error("Unknown value type");
            } else
                return src;
        }
    }

    VMImplementation vmImpl;
    List<BCode> bcodes;
    ReachingDefinition rdefa;
    ConstantEvaluator evaluator;

    ConstantPropagation(VMImplementation vmImpl, List<BCode> bcodes) {
        this.vmImpl = vmImpl;
        this.bcodes = bcodes;
        rdefa = new ReachingDefinition(bcodes);
        evaluator = new ConstantEvaluator(vmImpl, rdefa);
    }

    private BCode createConstantInstruction(Register r, Value v) {
        if (v instanceof FixnumValue) {
            FixnumValue f = (FixnumValue) v;
            long n = ((FixnumValue) v).getIntValue();
            if (vmImpl.getInsnRep().inSmallPrimitiveRange(n))
                return new IFixnum(r, (int) n);
            else
                return new INumber(r, f.getDoubleValue());
        } else if (v instanceof NumberValue)
            return new INumber(r, ((NumberValue) v).getDoubleValue());
        else if (v instanceof StringValue)
            return new IString(r, ((StringValue) v).getStringValue());
        else if (v instanceof SpecialValue) {
            SpecialValue s = (SpecialValue) v;
            switch (s.getSpecialValue()) {
            case TRUE:
                return new IBooleanconst(r, true);
            case FALSE:
                return new IBooleanconst(r, false);
            case NULL:
                return new INullconst(r);
            case UNDEFINED:
                return new IUndefinedconst(r);
            default:
                throw new Error("Unknown special value");
            }
        }
        return null;
    }


    boolean isTypeInstance(String type, SrcOperand v) {
        switch(type) {
        case "fixnum":
            return v instanceof FixnumOperand;
        case "string":
            return v instanceof StringOperand;
        case "flonum":
            return v instanceof FlonumOperand;
        case "special":
            return v instanceof SpecialOperand;
        default:
            return false;
        }
    }

    SrcOperand[] findMostSpecificOperands(ConstantEvaluator.Environment env, String insnName, SrcOperand[] ops) {
        SrcOperand[] vs = new SrcOperand[ops.length];
        for (int i = 0; i < ops.length; i++) {
            if (ops[i] != null)
                vs[i] = evaluator.evalSrcOperand(env, ops[i]);
        }
        if (DEBUG) {
            System.out.print("vs =");
            for (SrcOperand v: vs) {
                System.out.print(" ");
                System.out.print(v);
            }
            System.out.println();
        }

        SrcOperand[] result = new SrcOperand[ops.length];
        System.arraycopy(ops, 0, result, 0, ops.length);
        SuperinstructionSpec sis = vmImpl.getSpec().getSuperinstructionSpec();
        NEXT_SI: for (Superinstruction si: sis.getList()) {
            if (!si.getBaseName().equals(insnName))
                continue;
            SrcOperand[] candidate = new SrcOperand[ops.length];
            for (int i = 0; i < ops.length; i++) {
                if (si.getOpType(i).getName().equals("-")) {
                    assert(ops[i] == null);
                    continue;
                }
                if (isTypeInstance(si.getOpType(i).getName(), vs[i]))
                    candidate[i] = vs[i];
                else if (si.getOpType(i).getName().equals("_") && result[i] instanceof RegisterOperand)
                    candidate[i] = result[i];
                else
                    continue NEXT_SI;
            }
            if (DEBUG) {
                System.out.print("match");
                for (SrcOperand v: candidate) {
                    System.out.print(" ");
                    System.out.print(v);
                }
                System.out.println();
            }

            result = candidate;
            /* continue iteration to find more specific result */
        }
        return result;
    }

    BCode makeSuperinsn(ConstantEvaluator.Environment env, BCode bcx) {
        if (bcx instanceof INot) {
            INot bc = (INot) bcx;
            SrcOperand[] ops = findMostSpecificOperands(env, bcx.name, new SrcOperand[] {null, bc.src});
            return new INot(bc.dst, ops[1], bc.exceptionDest);
        } else if (bcx instanceof IGetglobal) {
            IGetglobal bc = (IGetglobal) bcx;
            SrcOperand[] ops = findMostSpecificOperands(env, bcx.name, new SrcOperand[] {null, bc.varName});
            return new IGetglobal(bc.dst, ops[1], bc.exceptionDest);
        } else if (bcx instanceof ISetglobal) {
            ISetglobal bc = (ISetglobal) bcx;
            SrcOperand[] ops = findMostSpecificOperands(env, bcx.name, new SrcOperand[] {bc.varName, bc.src});
            return new ISetglobal(ops[0], ops[1], bc.exceptionDest);
        } else if (bcx instanceof ISetlocal) {
            ISetlocal bc = (ISetlocal) bcx;
            SrcOperand[] ops = findMostSpecificOperands(env, bcx.name, new SrcOperand[] {null, null, bc.src});
            return new ISetlocal(bc.link, bc.index, ops[2]);
        } else if (bcx instanceof ISetarg) {
            ISetarg bc = (ISetarg) bcx;
            SrcOperand[] ops = findMostSpecificOperands(env, bcx.name, new SrcOperand[] {null, null, bc.src});
            return new ISetarg(bc.link, bc.index, ops[2]);
        } else if (bcx instanceof IGetprop) {
            IGetprop bc = (IGetprop) bcx;
            SrcOperand[] ops = findMostSpecificOperands(env, bcx.name, new SrcOperand[] {null, bc.obj, bc.prop});
            return new IGetprop(bc.dst, ops[1], ops[2]);
        } else if (bcx instanceof ISetprop) {
            ISetprop bc = (ISetprop) bcx;
            SrcOperand[] ops = findMostSpecificOperands(env, bcx.name, new SrcOperand[] {bc.obj, bc.prop, bc.src});
            return new ISetprop(ops[0], ops[1], ops[2]);
        } else if (bcx instanceof ISeta) {
            ISeta bc = (ISeta) bcx;
            SrcOperand[] ops = findMostSpecificOperands(env, bcx.name, new SrcOperand[] {bc.src});
            return new ISeta(ops[0]);
        } else {
            /* TODO: do not use reflection */
            Class<? extends BCode>[] rxx = new Class[] {
                    IAdd.class, ISub.class, IMul.class, IDiv.class, IMod.class,
                    IBitor.class, IBitand.class, ILeftshift.class, IRightshift.class,
                    IUnsignedrightshift.class, IEqual.class, IEq.class,
                    ILessthan.class, ILessthanequal.class
            };
            for (Class<? extends BCode> cls: rxx) {
                if (cls.isInstance(bcx)) {
                    try {
                        Register dst = (Register) BCode.class.getDeclaredField("dst").get(bcx);
                        SrcOperand[] srcOperands = new SrcOperand[] {
                                null,
                                (SrcOperand) cls.getDeclaredField("src1").get(bcx),
                                (SrcOperand) cls.getDeclaredField("src2").get(bcx)
                        };
                        SrcOperand[] ops = findMostSpecificOperands(env, bcx.name, srcOperands);
                        if (bcx instanceof CauseExceptionBCode) {
                            Constructor<? extends BCode> ctor = cls.getDeclaredConstructor(Register.class, SrcOperand.class, SrcOperand.class, Label.class);
                            return (BCode) ctor.newInstance(dst, ops[1], ops[2], ((CauseExceptionBCode) bcx).exceptionDest);
                        } else {
                            Constructor<? extends BCode> ctor = cls.getDeclaredConstructor(Register.class, SrcOperand.class, SrcOperand.class);
                            return (BCode) ctor.newInstance(dst, ops[1], ops[2]);
                        }
                    } catch (Exception e) {
                        throw new Error(e);
                    }
                }
            }
        }
        return null;
    }

    public List<BCode> exec() {
        List<BCode> newBCodes = new ArrayList<BCode>(bcodes.size());

        for (BCode bc: bcodes) {
            ConstantEvaluator.Environment env = evaluator.new Environment(bc);
            Value v = evaluator.eval(env, bc);
            if (v != null) {
                BCode newBC = createConstantInstruction(bc.getDestRegister(), v);
                newBC.addLabels(bc.getLabels());
                newBCodes.add(newBC);
            } else {
                BCode newBC = makeSuperinsn(env, bc);
                if (newBC != null) {
                    newBC.addLabels(bc.getLabels());
                    newBCodes.add(newBC);
                } else
                    newBCodes.add(bc);
            }
        }

        return newBCodes;
    }
}
